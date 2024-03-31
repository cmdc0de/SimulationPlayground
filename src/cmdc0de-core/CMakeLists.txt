include(GenerateExportHeader)

set(CMDC0DE_CORE_STATIC_DEFINE 1)

add_library(cmdc0de_core error_type.cpp)



add_library(SimulationPlayground::cmdc0de_core ALIAS cmdc0de_core)

target_link_libraries(cmdc0de_core PRIVATE SimulationPlayground_options SimulationPlayground_warnings)

target_include_directories(cmdc0de_core ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(cmdc0de_core PUBLIC cxx_std_20)

set_target_properties(
  cmdc0de_core
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(cmdc0de_core EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/SimulationPlayground/cmdc0de-core-export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(cmdc0de_core PUBLIC CMDC0DE_CORE_STATIC_DEFINE)
endif()
