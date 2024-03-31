
#if 1

#include <CLI/CLI.hpp>
#include "app.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <spdlog/spdlog.h>
#include <internal_use_only/config.hpp>

int main([[maybe_unused]] int argc, [[maybe_unused]]  char *argv[]) {
   App MyApp;
   try {
      CLI::App app{ fmt::format("{} version {}", SimulationPlayground::cmake::project_name, SimulationPlayground::cmake::project_version) };
      bool show_version = false;
      app.add_flag("--version", show_version, "Show version information");
      CLI11_PARSE(app, argc, argv);

      if (show_version) {
         fmt::print("{}\n", SimulationPlayground::cmake::project_version);
         return EXIT_SUCCESS;
      }
        MyApp.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
	return 0;	
}

#endif
