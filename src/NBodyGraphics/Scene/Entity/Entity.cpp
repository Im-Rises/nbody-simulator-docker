#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>

void Entity::updateModelMatrix() {
    modelMatrix = glm::mat4(1.0F);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0F, 0.0F, 0.0F));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0F, 1.0F, 0.0F));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0F, 0.0F, 1.0F));
    modelMatrix = glm::scale(modelMatrix, scale);
}
