#include <iostream>
#include "NBodySimulatorGraphicsLauncher.h"

auto main(int argc, char* argv[]) -> int {
    (void)argc;
    (void)argv;
    std::cout << NBodySimulatorGraphicsLauncher::PROJECT_NAME << " " << NBodySimulatorGraphicsLauncher::PROJECT_VERSION << std::endl
              << NBodySimulatorGraphicsLauncher::PROJECT_LINK << std::endl
              << NBodySimulatorGraphicsLauncher::PROJECT_AUTHOR << "\n"
              << std::endl;
    NBodySimulatorGraphicsLauncher nbodySimulatorLauncher;
    nbodySimulatorLauncher.start();
    return 0;
}
