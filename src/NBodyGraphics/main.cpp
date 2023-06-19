#include <iostream>
#include "NBodySimulatorGraphicsLauncher.h"

#include <cstdlib>

auto main(int argc, char* argv[]) -> int {
    int particlesCount;
    float recordingTime;
    if (argc == 3)
    {
        particlesCount = std::atoi(argv[1]);
        recordingTime = std::atof(argv[2]);
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " <particlesCount> <recordingTime>" << std::endl;
        exit(2);
    }

    std::cout << "Argv 1" << argv[1] << std::endl;
    std::cout << "Argv 2" << argv[2] << std::endl;

    std::cout << NBodySimulatorGraphicsLauncher::PROJECT_NAME << " " << NBodySimulatorGraphicsLauncher::PROJECT_VERSION << std::endl
              << NBodySimulatorGraphicsLauncher::PROJECT_LINK << std::endl
              << NBodySimulatorGraphicsLauncher::PROJECT_AUTHOR << "\n"
              << std::endl;
    NBodySimulatorGraphicsLauncher nbodySimulatorLauncher;
    nbodySimulatorLauncher.start(particlesCount, recordingTime);
    return 0;
}
