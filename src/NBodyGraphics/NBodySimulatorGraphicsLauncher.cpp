#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-vararg"

#include <nlohmann/json.hpp>

#include "NBodySimulatorGraphicsLauncher.h"

#include "InputManager.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "Scene/Scene.h"
#include "Recorder/Recorder.h"
#include "FfmpegPiper/FfmpegPiper.h"
#include <iostream>
#include <chrono>
#include <thread>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

NBodySimulatorGraphicsLauncher::NBodySimulatorGraphicsLauncher() {
    glfwSetErrorCallback(glfw_error_callback);
    if (glfwInit() == 0)
        exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only

    // According to init windowSize
    displayWidth = windowWidth;
    displayHeight = windowHeight;

    // Create window with graphics context
    window = glfwCreateWindow(displayWidth, displayHeight, PROJECT_NAME.data(), nullptr, nullptr);
    if (window == nullptr)
        exit(1);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    //    glfwSwapInterval(0); // Disable vsync

    // Callbacks
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, InputManager::key_callback);

    // Initialize OpenGL loader
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0)
        exit(1);

    centerWindow();

    // hide window
    //    glfwHideWindow(window
    // Setup OpenGL state
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(pointSize);

    // Same line as above but with C++ string
    std::cout << "OpenGL vendor: " << getOpenGLVendor() << std::endl
              << "OpenGL version: " << getOpenGLVersion() << std::endl
              << "GLSL version: " << getGLSLVersion() << std::endl
              << "GLFW version: " << getGLFWVersion() << std::endl
              << "Glad version: " << getGladVersion() << std::endl
              << "GLM version: " << getGLMVersion() << std::endl
              << "OpenCV version: " << getOpenCVVersion() << std::endl
              << "nlhomann/json version: " << getNlohmannJsonVersion() << std::endl;

    // Setup callback function when we get particles positions
    auto callbackSetParticles = [this](const std::vector<glm::vec3>& particles) {
        scene->SetParticles(particles);
    };

    queryEntities.SetCallback(callbackSetParticles);
}

NBodySimulatorGraphicsLauncher::~NBodySimulatorGraphicsLauncher() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void NBodySimulatorGraphicsLauncher::start(int particlesCount) {
    scene = std::make_unique<Scene>(displayWidth, displayHeight, particlesCount);
    recorder = std::make_unique<Recorder>(displayWidth, displayHeight);
    //    ffmpegPiper = std::make_unique<FfmpegPiper>(displayWidth, displayHeight, 60);

    //
    float timeStop = 5.0F;
    float accumulatorStop = 0.0F;
    //
    float deltaTime = 0.0F;
    float accumulator = 0.0F;
    float FixedDeltaTime = 0.02F;
    auto previousTime = std::chrono::high_resolution_clock::now();
    //
    while (glfwWindowShouldClose(window) == 0)
    {
        handleInputs();

        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();

        accumulator += deltaTime;
        if (accumulator >= FixedDeltaTime)
        {
            updateGame(deltaTime);
            accumulator -= FixedDeltaTime;
        }

        previousTime = currentTime;

        updateScreen();

        accumulatorStop += deltaTime;
        if (accumulatorStop >= timeStop)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    scene.reset();
    recorder.reset();
}

void NBodySimulatorGraphicsLauncher::handleInputs() {
    glfwPollEvents();

    /* Read keyboard inputs and update states (buffers) */
    if (InputManager::isLeftKeyPressed(window))
        scene->camera.moveLeft();

    if (InputManager::isRightKeyPressed(window))
        scene->camera.moveRight();

    if (InputManager::isForwardKeyPressed(window))
        scene->camera.moveForward();

    if (InputManager::isBackwardKeyPressed(window))
        scene->camera.moveBackward();

    if (InputManager::isUpKeyPressed(window))
        scene->camera.moveUp();

    if (InputManager::isDownKeyPressed(window))
        scene->camera.moveDown();

    /* Read and update mouse controls */
    // Get mouse position or drag position
    double posX = 0, posY = 0;

    InputManager::getMousePosition(window, posX, posY);

    // Get movement delta
    double mouseDeltaX = 0, mouseDeltaY = 0;
    calculateMouseMovement(posX, posY, mouseDeltaX, mouseDeltaY);

    // Read mouse inputs and update camera
    if (InputManager::isKeyMouseMovementPressed(window))
    {
        scene->camera.processMouseMovement(static_cast<float>(mouseDeltaX), static_cast<float>(mouseDeltaY));
    }
}

void NBodySimulatorGraphicsLauncher::updateGame(float deltaTime) {
    //    scene->update(deltaTime);

    /*
     * Fetch new particles position
     */

    queryEntities.AskGetAllParticles();
}

void NBodySimulatorGraphicsLauncher::updateScreen() {
    if (!isMinimized())
        updateViewport();

    recorder->StartCapture();

    clearScreen();
    scene->render();

    recorder->StopCapture();

    //    ffmpegPiper->updateFrame();

    glfwSwapBuffers(window);
}

void NBodySimulatorGraphicsLauncher::resetScene() {
    scene->reset();
}

void NBodySimulatorGraphicsLauncher::updateViewport() {
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
    if (!isFullscreen)
    {
        windowWidth = displayWidth;
        windowHeight = displayHeight;
    }
    scene->updateProjectionMatrix(displayWidth, displayHeight);
    glViewport(0, 0, displayWidth, displayHeight);
}


void NBodySimulatorGraphicsLauncher::centerWindow() {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    windowPosX = (mode->width - displayWidth) / 2;
    windowPosY = (mode->height - displayHeight) / 2;
    glfwSetWindowPos(window, windowPosX, windowPosY);
}

void NBodySimulatorGraphicsLauncher::toggleFullscreen() {
    if (isFullscreen)
    {
        glfwSetWindowMonitor(window, nullptr, 0, 0, windowWidth, windowHeight, 0);
        displayWidth = windowWidth;
        displayHeight = windowHeight;
        glfwSetWindowPos(window, windowPosX, windowPosY);
        isFullscreen = false;
    }
    else
    {
        glfwGetWindowPos(window, &windowPosX, &windowPosY);
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        isFullscreen = true;
    }
}


void NBodySimulatorGraphicsLauncher::clearScreen() const {
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
        clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto NBodySimulatorGraphicsLauncher::isMinimized() const -> bool {
    return glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0;
}

void NBodySimulatorGraphicsLauncher::calculateMouseMovement(const double& xMouse, const double& yMouse, double& xMovement,
    double& yMovement) {
    static double lastMouseX = 0.0;
    static double lastMouseY = 0.0;

    xMovement = xMouse - lastMouseX;
    yMovement = lastMouseY - yMouse;

    lastMouseX = xMouse;
    lastMouseY = yMouse;
}

auto NBodySimulatorGraphicsLauncher::getOpenGLVendor() -> std::string_view {
    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

auto NBodySimulatorGraphicsLauncher::getOpenGLVersion() -> std::string_view {
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

auto NBodySimulatorGraphicsLauncher::getGLSLVersion() -> std::string_view {
    return reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
}

auto NBodySimulatorGraphicsLauncher::getGLFWVersion() -> std::string {
    return std::to_string(GLFW_VERSION_MAJOR) + "." + std::to_string(GLFW_VERSION_MINOR) + "." +
           std::to_string(GLFW_VERSION_REVISION);
}

auto NBodySimulatorGraphicsLauncher::getGladVersion() -> std::string_view {
    return "0.1.36";
}

auto NBodySimulatorGraphicsLauncher::getGLMVersion() -> std::string {
    return std::to_string(GLM_VERSION_MAJOR) + "." + std::to_string(GLM_VERSION_MINOR) + "." +
           std::to_string(GLM_VERSION_PATCH);
}

auto NBodySimulatorGraphicsLauncher::getOpenCVVersion() -> std::string_view {
    return CV_VERSION;
}

auto NBodySimulatorGraphicsLauncher::getNlohmannJsonVersion() -> std::string_view {
    return "3.11.2";
}

#pragma clang diagnostic pop