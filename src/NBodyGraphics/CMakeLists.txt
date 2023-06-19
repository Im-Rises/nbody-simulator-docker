cmake_minimum_required(VERSION 3.8)

option(DOCKER_BUILD "Build inside Docker" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(NBodyGraphics)

if (DOCKER_BUILD)
    include_directories("${CMAKE_SOURCE_DIR}/dependencies")
    include_directories("${CMAKE_SOURCE_DIR}/dependencies/glad/include")
    file(GLOB_RECURSE SRCS_HEADERS_GLAD "${CMAKE_SOURCE_DIR}/dependencies/glad/*.c")
else ()
    include_directories("${CMAKE_SOURCE_DIR}/../dependencies")
    include_directories("${CMAKE_SOURCE_DIR}/../dependencies/glad/include")
    file(GLOB_RECURSE SRCS_HEADERS_GLAD "${CMAKE_SOURCE_DIR}/../dependencies/glad/*.c")
endif ()

set(SRCS FfmpegPiper/FfmpegPiper.cpp
        QueryEntities/QueryCallbackParameter.cpp QueryEntities/QueryEntities.cpp
        Recorder/Recorder.cpp
        Scene/Scene.cpp Scene/Camera/Camera.cpp Scene/Entity/Entity.cpp Scene/Entity/NBodySimulator/NBodySimulatorGraphic.cpp
        Shader/Shader.cpp
        InputManager.cpp
        NBodySimulatorGraphicsLauncher.cpp)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL 3.3 REQUIRED)

find_package(OpenCV REQUIRED)

find_package(CURL REQUIRED)

find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${SRCS} ${SRCS_HEADERS_GLAD})

target_link_libraries(${PROJECT_NAME} OpenGL::GL)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} glfw ${CMAKE_DL_LIBS})

