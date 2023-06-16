#ifndef NBODY_SIMULATOR_LAUNCHER_H
#define NBODY_SIMULATOR_LAUNCHER_H

#include <memory>
#include <string_view>
#include <glm/glm.hpp>
#include "QueryEntities/QueryEntities.h"

class Scene;
class Recorder;
class FfmpegPiper;

struct GLFWwindow;

class NBodySimulatorGraphicsLauncher {
public:
    static constexpr std::string_view PROJECT_NAME = "Nbody Simulator Graphics";
    static constexpr std::string_view PROJECT_VERSION = "1.0.0";
    static constexpr std::string_view PROJECT_LINK = "https://github.com/Im-Rises/nbody-simulator-cloud";
    static constexpr std::string_view PROJECT_AUTHOR = "Alshkor (Axel Courmont), Im-Rises (Quentin Morel), Fromiel (Alexis Roville)";

private:
    GLFWwindow* window;
    QueryEntities queryEntities;

    int windowWidth = 1280;
    int windowHeight = 720;

    const int fixedDeltaTime = 0.02F;

    int displayWidth, displayHeight;
    int windowPosX, windowPosY;

    std::unique_ptr<Scene> scene;
    std::unique_ptr<Recorder> recorder;
    //    std::unique_ptr<FfmpegPiper> ffmpegPiper;

    struct {
        float x = 0.0F;
        float y = 0.0F;
        float z = 0.0F;
        float w = 1.0F;
    } clear_color;

    float pointSize = 1.0F;

    bool isFullscreen = false;

public:
    NBodySimulatorGraphicsLauncher();

    NBodySimulatorGraphicsLauncher(const NBodySimulatorGraphicsLauncher&) = delete;

    auto operator=(const NBodySimulatorGraphicsLauncher&) -> NBodySimulatorGraphicsLauncher& = delete;

    NBodySimulatorGraphicsLauncher(NBodySimulatorGraphicsLauncher&&) = delete;

    auto operator=(NBodySimulatorGraphicsLauncher&&) -> NBodySimulatorGraphicsLauncher& = delete;

    ~NBodySimulatorGraphicsLauncher();

public:
    void start(int particlesCount);

private:
    void handleInputs();

    void updateGame(float deltaTime);

    void updateScreen();

public:
    void resetScene();

    void updateViewport();

    void centerWindow();

    void toggleFullscreen();

    void clearScreen() const;

    [[nodiscard]] auto isMinimized() const -> bool;

private:
    static void calculateMouseMovement(const double& xMouse, const double& yMouse, double& xMovement, double& yMovement);

private:
    static auto getOpenGLVendor() -> std::string_view;

    static auto getOpenGLVersion() -> std::string_view;

    static auto getGLSLVersion() -> std::string_view;

    static auto getGLFWVersion() -> std::string;

    static auto getGladVersion() -> std::string_view;

    static auto getGLMVersion() -> std::string;

    static auto getOpenCVVersion() -> std::string_view;

    static auto getNlohmannJsonVersion() -> std::string_view;
};

#endif // NBODY_SIMULATOR_LAUNCHER_H
