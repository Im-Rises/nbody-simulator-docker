# nbody-simulator-cloud

<p align="center">
      <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="cppLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/OpenGL-FFFFFF?style=for-the-badge&logo=opengl" alt="openglLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/190315147-ec9dc33f-0090-4f0d-98ab-514eb1463e01.png" alt="glfwLogo" style="height:60px;"/>
</p>

## Description

This is a simple nbody simulator made with OpenGL and C++ with the help of the ImGui library for the UI.

## Images

## Videos

## Features

## Dependencies

- OpenGL version: 3.3
- GLSL version: 330
- GLFW version: 3.3.8
- Glad version: 0.1.36
- GLM version: 0.9.9
- OpenCV version: 4.7.0-dev
- nlhomann/json version: 3.9.1

## Architecture

```bash
ffmpeg -f x11grab -i title="Nbody Simulator raphics" -vcodec libx264 -pix_fmt yuv420p -tune zerolatency -preset ultrafast -f mpegts http://127.0.0.1:8080
ffmpeg -f x11grab -y -r 30 -s 1920x1080 -i $DISPLAY -vcodec huffyuv out.avi
ffmpeg -f x11grab -video_size 1920x1080 -framerate 30 -i $DISPLAY -vcodec libx264 -preset ultrafast -tune zerolatency -f mpegts udp://localhost:1234
```

```mermaid
flowchart LR
    subgraph Architecture
        subgraph Docker-Calculator
        docker1 & docker2 & docker...
        end
        docker1 & docker2 & docker... <--> |GET/POST| api-redis
        subgraph Redis
        api-redis
        end
        api-redis --> |GET| api-video-generator
        subgraph Video-Generator
        docker-volume
        api-video-generator --> |Save| docker-volume
        ffmpeg --> |Read| docker-volume
        end
        ffmpeg --> |UDP| site-web
    end
```

## Json data transfer

```json
{
  "particles": [
    {
      "index": 0,
      "position": [
        0,
        0,
        0
      ],
      "velocity": [
        0,
        0,
        0
      ]
    },
    {
      "index": 1,
      "position": [
        0,
        0,
        0
      ],
      "velocity": [
        0,
        0,
        0
      ]
    }
  ]
}
```

## Github-Actions

[![CodeQL](https://github.com/Im-Rises/NBodySimulator/actions/workflows/codeql.yml/badge.svg?branch=main)](https://github.com/Im-Rises/NBodySimulator/actions/workflows/codeql.yml)
[![CMake](https://github.com/Im-Rises/NBodySimulator/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Im-Rises/NBodySimulator/actions/workflows/cmake.yml)
[![flawfinder](https://github.com/Im-Rises/NBodySimulator/actions/workflows/flawfinder.yml/badge.svg?branch=main)](https://github.com/Im-Rises/NBodySimulator/actions/workflows/flawfinder.yml)
[![cpp-linter](https://github.com/Im-Rises/NBodySimulator/actions/workflows/cpp-linter.yml/badge.svg?branch=main)](https://github.com/Im-Rises/NBodySimulator/actions/workflows/cpp-linter.yml)

The project is set with a set of different scripts:

- CodeQL: This script is used to check the code for security issues.
- CMake: This script is used to build the project.
- Flawfinder: This script is used to check the code for security issues.
- Cpp Linter: This script is used to check the code for security issues.

## Libraries

glfw:  
<https://www.glfw.org/docs/latest/>

glm:  
<https://glm.g-truc.net/0.9.9/index.html>

glad:  
<https://glad.dav1d.de/>

OpenGL:  
<https://www.opengl.org/>

Json:  
<https://github.com/nlohmann/json>

libcurl:  
<https://curl.se/libcurl/>

## Contributors

Axel COURMONT:

- @Alshkor
- <https://github.com/Alshkor>

Alexis ROVILLE:

- @Fromiel
- <https://github.com/Fromiel>

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/NBodySimulator)](https://github.com/Im-Rises/NBodySimulator/graphs/contributors)
