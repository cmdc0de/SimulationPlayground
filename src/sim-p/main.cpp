
#if 1
#include "app.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main([[maybe_unused]] int arc, [[maybe_unused]]  char *agrv[]) {
	App MyApp;
	try {
        MyApp.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
	return 0;	
}

#endif
