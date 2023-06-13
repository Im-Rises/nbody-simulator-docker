#include <cmath>
#include <glm/glm.hpp>

#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>

#include <nlohmann/json.hpp>

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

void signalHandler(int signum) {
    if (signum == SIGINT)
    {
        exitMainLoopFlag = true;
    }
}

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

auto particlesToJson(const std::vector<Particle>& particles) -> nlohmann::json {
    nlohmann::json json;
    json["particles"] = nlohmann::json::array();
    for (auto& particle : particles)
    {
        json["particles"].push_back({ { "position", { particle.position.x, particle.position.y, particle.position.z } },
            { "velocity", { particle.velocity.x, particle.velocity.y, particle.velocity.z } } });
    }
    return json;
}

auto main(int argc, char* argv[]) -> int {
    // Init random
    srand(static_cast<unsigned int>(time(nullptr)));

    // Set exit signals
    signal(SIGINT, signalHandler);

    /* Init */
    auto particles = std::vector<Particle>(100000);
    for (auto& particle : particles)
    {
        particle.position = glm::vec3(
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F,
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F,
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F);
    }

    auto json = particlesToJson(particles);
    //    std::cout << json.dump() << std::endl;
    // print json of first particle
    //    std::cout << json["particles"][0] << std::endl;
    //    std::cout << json["particles"][1] << std::endl;
    //    std::cout << json["particles"][2]["position"] << std::endl;

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
            auto json = particlesToJson(particles);
        }

        previousTime = currentTime;
    }

    std::cout << "Exiting..." << std::endl;

    return 0;
}