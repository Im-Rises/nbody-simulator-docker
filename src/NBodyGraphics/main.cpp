#include <iostream>
#include "NBodySimulatorGraphicsLauncher.h"

#include <cstdlib>

auto main(int argc, char* argv[]) -> int {
    int particlesCount;
    float recordingTime;

    particlesCount = std::atoi(std::getenv("NB_PARTICULES"));
    recordingTime = std::atof(std::getenv("TIME_SIMULATION"));

    std::cout << NBodySimulatorGraphicsLauncher::PROJECT_NAME << " " << NBodySimulatorGraphicsLauncher::PROJECT_VERSION << std::endl
              << NBodySimulatorGraphicsLauncher::PROJECT_LINK << std::endl
              << NBodySimulatorGraphicsLauncher::PROJECT_AUTHOR << "\n"
              << std::endl;
    NBodySimulatorGraphicsLauncher nbodySimulatorLauncher;
    nbodySimulatorLauncher.start(particlesCount, recordingTime);
    return 0;
}
