add_executable(sim-p main.cpp 
	app.cpp
	utils.cpp)

target_link_libraries(
  sim-p
  PRIVATE SimulationPlayground::SimulationPlayground_options
          SimulationPlayground::SimulationPlayground_warnings)

target_link_system_libraries(
  sim-p
  PRIVATE
          CLI11::CLI11
          fmt::fmt
          spdlog::spdlog
          lefticus::tools
          ftxui::screen
          ftxui::dom
          ftxui::component
	  Vulkan::Headers
	  vulkan
          glm::glm
	  glfw)

target_include_directories(sim-p PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
