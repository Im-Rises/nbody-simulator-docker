#ifndef NBODY_SIMULATOR_H
#define NBODY_SIMULATOR_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../Entity.h"

class NBodySimulatorGraphic : public Entity {
private:
    static const char* const VertexShaderSource;
    static const char* const FragmentShaderSource;

    Shader shader;

    GLuint VAO, VBO;

    struct Particle {
        glm::vec3 position;
        glm::vec3 velocity;

        Particle() : position(glm::vec3(0.0F)), velocity(glm::vec3(1.0F, 1.0F, 1.0F)) {}
    };

    std::vector<Particle> particles;

public:
    explicit NBodySimulatorGraphic(int particleCount);

    NBodySimulatorGraphic(const NBodySimulatorGraphic&) = delete;
    auto operator=(const NBodySimulatorGraphic&) -> NBodySimulatorGraphic& = delete;
    NBodySimulatorGraphic(NBodySimulatorGraphic&&) = delete;
    auto operator=(NBodySimulatorGraphic&&) -> NBodySimulatorGraphic& = delete;

    ~NBodySimulatorGraphic() override;

public:
    void render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) override;

    void SetParticles(const std::vector<glm::vec3>& particles);
};

#endif // NBODY_SIMULATOR_H
