#ifndef SCENE_H
#define SCENE_H

#include "Camera/Camera.h"
#include "Entity/NBodySimulator/NBodySimulatorGraphic.h"
#include "Entity/Cube/Cube.h"

class Scene {
public:
    Camera camera;

    //    Cube cube;

    NBodySimulatorGraphic nbodySimulatorGraphic;

public:
    Scene(int display_w, int display_h, int particlesCount);

    void update(float deltaTime);

    void render();

public:
    void updateProjectionMatrix(int display_w, int display_h);

    void reset();
};

#endif // SCENE_H
