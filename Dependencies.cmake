include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(SimulationPlayground_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  if(NOT TARGET fmtlib::fmtlib)
    cpmaddpackage("gh:fmtlib/fmt#9.1.0")
  endif()

  if(NOT TARGET spdlog::spdlog)
    cpmaddpackage(
      NAME
      spdlog
      VERSION
      1.11.0
      GITHUB_REPOSITORY
      "gabime/spdlog"
      OPTIONS
      "SPDLOG_FMT_EXTERNAL ON")
  endif()

  if(NOT TARGET Catch2::Catch2WithMain)
    cpmaddpackage("gh:catchorg/Catch2@3.3.2")
  endif()

  if(NOT TARGET CLI11::CLI11)
    cpmaddpackage("gh:CLIUtils/CLI11@2.3.2")
  endif()

  if(NOT TARGET ftxui::screen)
    cpmaddpackage("gh:ArthurSonzogni/FTXUI#e23dbc7473654024852ede60e2121276c5aab660")
  endif()

  if(NOT TARGET tools::tools)
    cpmaddpackage("gh:lefticus/tools#update_build_system")
  endif()

  #  if(NOT TARGET vulkan::hpp-headers)
  #  cpmaddpackage("gh:KhronosGroup/Vulkan-Hpp@1.3.268")
  #endif()

  if(NOT TARGET Vulkan::Headers)
     cpmaddpackage("gh:KhronosGroup/Vulkan-Headers@1.3.268")
  endif()

  if(NOT TARGET vulkan)
     cpmaddpackage(
	NAME vulkan
	GIT_REPOSITORY "https://github.com/KhronosGroup/Vulkan-Loader"
	GIT_TAG "v1.3.268"
	OPTIONS
	"UPDATE_DEPS ON BUILD_STATIC_LOADER")
  endif()

  if(NOT TARGET glm::glm)
    cpmaddpackage("gh:g-truc/glm#bf71a83")
  endif()

  if(NOT TARGET glfw)
    cpmaddpackage("gh:glfw/glfw#7482de6")
  endif()

  if(NOT TARGET stb)
    cpmaddpackage("gh:nothings/stb#03f50e343d796e492e6579a11143a085429d7f5d")
  endif()

  if(NOT TARGET tinyobj)
	  cpmaddpackage("gh:tinyobjloader/tinyobjloader@2.0.0rc10")
  endif()

  #if (NOT TARGET spirv)
  #  cpmaddpackage(
  #	    NAME spirv
  #	    GIT_REPOSITORY "https://github.com/KhronosGroup/SPIRV-Cross"
  #	    GIT_TAG "sdk-1.3.261.1"
  #	    )
  #endif()

endfunction()
