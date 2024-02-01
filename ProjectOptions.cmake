include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(SimulationPlayground_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(SimulationPlayground_setup_options)
  option(SimulationPlayground_ENABLE_HARDENING "Enable hardening" ON)
  option(SimulationPlayground_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    SimulationPlayground_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    SimulationPlayground_ENABLE_HARDENING
    OFF)

  SimulationPlayground_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR SimulationPlayground_PACKAGING_MAINTAINER_MODE)
    option(SimulationPlayground_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(SimulationPlayground_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(SimulationPlayground_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(SimulationPlayground_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(SimulationPlayground_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(SimulationPlayground_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(SimulationPlayground_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(SimulationPlayground_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(SimulationPlayground_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(SimulationPlayground_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(SimulationPlayground_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(SimulationPlayground_ENABLE_PCH "Enable precompiled headers" OFF)
    option(SimulationPlayground_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(SimulationPlayground_ENABLE_IPO "Enable IPO/LTO" ON)
    option(SimulationPlayground_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(SimulationPlayground_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(SimulationPlayground_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(SimulationPlayground_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(SimulationPlayground_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(SimulationPlayground_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(SimulationPlayground_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(SimulationPlayground_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(SimulationPlayground_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(SimulationPlayground_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(SimulationPlayground_ENABLE_PCH "Enable precompiled headers" OFF)
    option(SimulationPlayground_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      SimulationPlayground_ENABLE_IPO
      SimulationPlayground_WARNINGS_AS_ERRORS
      SimulationPlayground_ENABLE_USER_LINKER
      SimulationPlayground_ENABLE_SANITIZER_ADDRESS
      SimulationPlayground_ENABLE_SANITIZER_LEAK
      SimulationPlayground_ENABLE_SANITIZER_UNDEFINED
      SimulationPlayground_ENABLE_SANITIZER_THREAD
      SimulationPlayground_ENABLE_SANITIZER_MEMORY
      SimulationPlayground_ENABLE_UNITY_BUILD
      SimulationPlayground_ENABLE_CLANG_TIDY
      SimulationPlayground_ENABLE_CPPCHECK
      SimulationPlayground_ENABLE_COVERAGE
      SimulationPlayground_ENABLE_PCH
      SimulationPlayground_ENABLE_CACHE)
  endif()

  SimulationPlayground_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (SimulationPlayground_ENABLE_SANITIZER_ADDRESS OR SimulationPlayground_ENABLE_SANITIZER_THREAD OR SimulationPlayground_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(SimulationPlayground_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(SimulationPlayground_global_options)
  if(SimulationPlayground_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    SimulationPlayground_enable_ipo()
  endif()

  SimulationPlayground_supports_sanitizers()

  if(SimulationPlayground_ENABLE_HARDENING AND SimulationPlayground_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR SimulationPlayground_ENABLE_SANITIZER_UNDEFINED
       OR SimulationPlayground_ENABLE_SANITIZER_ADDRESS
       OR SimulationPlayground_ENABLE_SANITIZER_THREAD
       OR SimulationPlayground_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${SimulationPlayground_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${SimulationPlayground_ENABLE_SANITIZER_UNDEFINED}")
    SimulationPlayground_enable_hardening(SimulationPlayground_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(SimulationPlayground_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(SimulationPlayground_warnings INTERFACE)
  add_library(SimulationPlayground_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  SimulationPlayground_set_project_warnings(
    SimulationPlayground_warnings
    ${SimulationPlayground_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(SimulationPlayground_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(SimulationPlayground_options)
  endif()

  include(cmake/Sanitizers.cmake)
  SimulationPlayground_enable_sanitizers(
    SimulationPlayground_options
    ${SimulationPlayground_ENABLE_SANITIZER_ADDRESS}
    ${SimulationPlayground_ENABLE_SANITIZER_LEAK}
    ${SimulationPlayground_ENABLE_SANITIZER_UNDEFINED}
    ${SimulationPlayground_ENABLE_SANITIZER_THREAD}
    ${SimulationPlayground_ENABLE_SANITIZER_MEMORY})

  set_target_properties(SimulationPlayground_options PROPERTIES UNITY_BUILD ${SimulationPlayground_ENABLE_UNITY_BUILD})

  if(SimulationPlayground_ENABLE_PCH)
    target_precompile_headers(
      SimulationPlayground_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(SimulationPlayground_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    SimulationPlayground_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(SimulationPlayground_ENABLE_CLANG_TIDY)
    SimulationPlayground_enable_clang_tidy(SimulationPlayground_options ${SimulationPlayground_WARNINGS_AS_ERRORS})
  endif()

  if(SimulationPlayground_ENABLE_CPPCHECK)
    SimulationPlayground_enable_cppcheck(${SimulationPlayground_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(SimulationPlayground_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    SimulationPlayground_enable_coverage(SimulationPlayground_options)
  endif()

  if(SimulationPlayground_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(SimulationPlayground_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(SimulationPlayground_ENABLE_HARDENING AND NOT SimulationPlayground_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR SimulationPlayground_ENABLE_SANITIZER_UNDEFINED
       OR SimulationPlayground_ENABLE_SANITIZER_ADDRESS
       OR SimulationPlayground_ENABLE_SANITIZER_THREAD
       OR SimulationPlayground_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    SimulationPlayground_enable_hardening(SimulationPlayground_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
