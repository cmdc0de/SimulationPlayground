#include(GenerateExportHeader)

set(CMD_GRAPHICS_STATIC_DEFINE 1)

add_library(cmd_graphics  graphics.cpp)

add_library(SimulationPlayground::cmd_graphics ALIAS cmd_graphics)

target_link_libraries(cmd_graphics PRIVATE SimulationPlayground_options SimulationPlayground_warnings)

target_include_directories(cmd_graphics ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(cmd_graphics PUBLIC cxx_std_20)

set_target_properties(
  cmd_graphics
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

#generate_export_header(cmd_graphics EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/SimulationPlayground/cmd_graphics_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(cmd_graphics PUBLIC CMD_GRAPHICS_STATIC_DEFINE)
endif()
