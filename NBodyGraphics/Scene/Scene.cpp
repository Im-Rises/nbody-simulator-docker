#include "Scene.h"

Scene::Scene(int display_w, int display_h, int particlesCount) : camera(display_w, display_h), nbodySimulatorGraphic(particlesCount) {
}

void Scene::update(float deltaTime) {
    camera.update(deltaTime);
}

void Scene::render() {
    nbodySimulatorGraphic.render(camera.getViewMatrix(), camera.getProjectionMatrix());
    //    cube.render(camera.getViewMatrix(), camera.getProjectionMatrix());
}

void Scene::updateProjectionMatrix(int display_w, int display_h) {
    camera.updateProjectionMatrix(display_w, display_h);
}

void Scene::reset() {
    camera.reset();
}
