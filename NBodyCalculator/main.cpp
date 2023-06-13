#include <cmath>
#include <glm/glm.hpp>

#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <csignal>
#endif

const float GravityConstant = 6.67408e-11F;
const float ParticleMass = 1.0F;
const float FixedDeltaTime = 0.02F;
const float Softening = 0.1F;
const float Friction = 0.99F;

bool exitMainLoopFlag = false;
#ifdef _WIN32
auto CtrlHandler(DWORD ctrlType) -> BOOL {
    if (ctrlType == CTRL_C_EVENT)
    {
        exitMainLoopFlag = true;
        return TRUE;
    }
    return FALSE;
}
#else
void signalHandler(int signum) {
    if (signum == SIGINT)
    {
        exitMainLoopFlag = true;
    }
}
#endif

struct Particle {
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    Particle() : position(glm::vec3(0.0F)), velocity(glm::vec3(0.0F, 0.0F, 0.0F)) {}
};

void updatePhysics(std::vector<Particle>& particles, float deltaTime) {
    for (auto& particle : particles)
    {
        glm::vec3 sumForces(0.0F, 0.0F, 0.0F);
        for (auto& otherParticle : particles)
        {
            if (&particle != &otherParticle)
            {
                auto distance = glm::distance(particle.position, otherParticle.position);
                auto direction = glm::normalize(otherParticle.position - particle.position);

                auto force = GravityConstant * ParticleMass * ParticleMass / ((distance * distance) + std::pow((Softening * Softening), 3.0F / 2));
                sumForces += direction * force;
            }

            particle.acceleration = sumForces / ParticleMass;
        }
    }

    for (auto& particle : particles)
    {
        particle.velocity += particle.acceleration * deltaTime;
        particle.velocity *= Friction;
        particle.position += (particle.velocity * deltaTime) + ((particle.acceleration * (deltaTime * deltaTime)) / 2.0F);
    }
}

auto main(int argc, char* argv[]) -> int {
#ifdef _WIN32
    // Set the signal exit handler
    if (SetConsoleCtrlHandler(static_cast<PHANDLER_ROUTINE>(CtrlHandler), TRUE) == 0)
    {
        std::cerr << "Unable to install CtrlHandler" << std::endl;
        exit(1);
    }

    // Set the timer resolution to 1 ms
    timeBeginPeriod(1);
#else
    // Set the signal exit handler
    signal(SIGINT, signalHandler);
#endif

    /* Init */
    auto particles = std::vector<Particle>(100000);
    for (auto& particle : particles)
    {
        particle.position = glm::vec3(
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F,
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F,
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F);
    }

    /* Loop*/
    auto previousTime = std::chrono::high_resolution_clock::now();
    float deltaTime = 0.0F;
    float accumulator = 0.0F;
    while (!exitMainLoopFlag)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();

        accumulator += deltaTime;
        while (accumulator >= FixedDeltaTime)
        {
            updatePhysics(particles, FixedDeltaTime);
            accumulator -= FixedDeltaTime;
        }

        previousTime = currentTime;
    }

    std::cout << "Exiting..." << std::endl;

    return 0;
}