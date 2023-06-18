#include "NBodySimulatorGraphic.h"

#include <random>
#include <iostream>

const char* const NBodySimulatorGraphic::VertexShaderSource =
    R"(#version 330 core

        layout(location = 0) in vec3 a_position;
        layout(location = 1) in vec3 a_velocity;

        uniform mat4 u_mvp;

        out vec3 v_velocity;

        void main()
        {
            gl_Position = u_mvp * vec4(a_position, 1.0);
            v_velocity = a_velocity;
            gl_PointSize = 1.0f;
        }
)";

const char* const NBodySimulatorGraphic::FragmentShaderSource =
    R"(#version 330 core

        in vec3 v_velocity;

        out vec4 o_fragColor;

        void main() {
            vec3 v_color = vec3(min(v_velocity.y, 0.8f), max(v_velocity.x, 0.5f), min(v_velocity.z, 0.5f));
            o_fragColor = vec4(v_color, 1.0f);
        }
)";

NBodySimulatorGraphic::NBodySimulatorGraphic(int particleCount) : shader(VertexShaderSource, FragmentShaderSource) {
    // Resize the particles vector
    particles.resize(particleCount);

    for (auto& particle : particles)
    {
        // Set random velocity (for color)
        particle.velocity = glm::vec3(
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F,
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F,
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0F - 1.0F);
    }

    // Init the VAO
    glGenVertexArrays(1, &VAO);

    // Init the VBO
    glGenBuffers(1, &VBO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Set the VBO data
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(particles.size() * sizeof(Particle)), particles.data(), GL_STATIC_DRAW);

    // Set the VAO attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, velocity));
    glEnableVertexAttribArray(1);

    // Unbind the VAO
    glBindVertexArray(0);

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

NBodySimulatorGraphic::~NBodySimulatorGraphic() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void NBodySimulatorGraphic::render(glm::mat4 cameraViewMatrix, glm::mat4 cameraProjectionMatrix) {
    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Set the VBO data
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(particles.size() * sizeof(Particle)), particles.data(), GL_STATIC_DRAW);

    // Bind the shader
    shader.use();

    // Set the uniform variables
    shader.setMat4("u_mvp", cameraProjectionMatrix * cameraViewMatrix);

    // Draw the particles
    glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(particles.size()));

    // Unbind the VAO
    glBindVertexArray(0);

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void NBodySimulatorGraphic::SetParticles(const std::vector<glm::vec3>& particles) {
    for (int i = 0; i < particles.size(); i++)
    {
        this->particles[i].position = particles[i];
    }
}
