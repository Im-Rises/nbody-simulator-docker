#include <iostream>
#include "NBodySimulatorGraphicsLauncher.h"

#include <cstdio>
#include <cstdlib>

auto main(int argc, char* argv[]) -> int {
    int particlesCount;
    if (argc == 2)
    {
        particlesCount = std::atoi(argv[1]);
    }
    else
    {
        exit(2);
    }

    std::cout << NBodySimulatorGraphicsLauncher::PROJECT_NAME << " " << NBodySimulatorGraphicsLauncher::PROJECT_VERSION << std::endl
              << NBodySimulatorGraphicsLauncher::PROJECT_LINK << std::endl
              << NBodySimulatorGraphicsLauncher::PROJECT_AUTHOR << "\n"
              << std::endl;
    NBodySimulatorGraphicsLauncher nbodySimulatorLauncher;
    nbodySimulatorLauncher.start(particlesCount);
    return 0;
}
