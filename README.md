# nbody-simulator-docker

<p align="center">
        <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
        <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="cppLogo" style="height:60px;"/>
        <img src="https://img.shields.io/badge/OpenGL-FFFFFF?style=for-the-badge&logo=opengl" alt="openglLogo" style="height:60px;"/>
        <img src="https://github.com/Im-Rises/nbody-simulator-docker/assets/59691442/b527fd70-f38f-4384-878d-3de6929e1e30" alt="imGuiLogo" style="height:60px;"/>
        <img src="https://user-images.githubusercontent.com/59691442/190315147-ec9dc33f-0090-4f0d-98ab-514eb1463e01.png" alt="glfwLogo" style="height:60px;"/>
</p>

[//]: # (         <img src="https://img.shields.io/badge/ImGui-FFFFFF?style=for-the-badge&logo=imGui" alt="imGuiLogo" style="height:60px;"/>)

## Description

This is a simple n-body simulator made with OpenGL for the graphics part and C++ for the logic part.
The project is running on a complete docker environment.

> **Note**  
> The project is a test of paralleling the calculation of the particles on different docker containers and store them in
> a redis database.
> A docker is also used to generate the video from the redis database.

## Images

## Videos

## Dependencies

- OpenGL version: 3.3
- GLSL version: 330
- GLFW version: 3.3.8
- Glad version: 0.1.36
- GLM version: 0.9.9
- OpenCV version: 4.7.0-dev
- nlhomann/json version: 3.9.1
- libcurl version: 7.74.0

## Architecture

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

## Libraries

docker:  
<https://www.docker.com/>

cmake:  
<https://cmake.org/>

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
