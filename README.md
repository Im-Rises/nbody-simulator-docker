# nbody-simulator-cloud

<p align="center">
      <img src="https://user-images.githubusercontent.com/59691442/183268126-b3d19e66-8f2d-463a-805e-ae6ef7cc6c01.png" alt="cmakeLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="cppLogo" style="height:60px;"/>
      <img src="https://img.shields.io/badge/OpenGL-FFFFFF?style=for-the-badge&logo=opengl" alt="openglLogo" style="height:60px;"/>
      <img src="https://user-images.githubusercontent.com/59691442/190315147-ec9dc33f-0090-4f0d-98ab-514eb1463e01.png" alt="glfwLogo" style="height:60px;"/>
</p>

## Description

This is a simple nbody simulator made with OpenGL and C++ with the help of the ImGui library for the UI.

## Architecture
## v1
```mermaid
flowchart TB
    client --> site-web --> |GET HTTP| redis
    subgraph Kubernetes
        HPA --> deployments-calculator --> pod1 & pod2
    end
    pod1 & pod2 --> |PUT HTTP| redis
```

## v2

```mermaid
flowchart TB
    client --> site-web --> |GET HTTP|redis
    admin --> |push| git --> |webhook| CRD
    subgraph Kubernetes 
        CRD --> |trigger| job-pod(job pod : download & build & push) --> |push| registry
        job-pod --> |restart| deployments-calculator
        HPA --> deployments-calculator --> pod1 & pod2
    end
    pod1 & pod2 --> |PUT HTTP| redis
    job-pod --> |git clone| git
```

## v3

```mermaid
flowchart TB
    client --> site-web --> |GET HTTP| ingress-video-generator
    admin --> |push| git --> |webhook| CRD
    subgraph Kubernetes 
        subgraph build 
            job-pod & registry
        end
        subgraph calculations 
            deployments-calculator & HPA & pod1 & pod2
        end
        CRD --> |trigger| job-pod(job pod : download & build & push) --> |push| registry
        job-pod --> |restart| deployments-calculator
        HPA --> deployments-calculator --> pod1 & pod2

        subgraph public
            ingress-video-generator --> service-video-generator --> pod-video-generator 
        end
        
    end
    pod1 & pod2 --> |PUT HTTP| redis
    pod-video-generator --> |GET HTTP| redis
    job-pod --> |git clone| git
    
```

## v4

```mermaid
flowchart TB
    client --> site-web --> |UDP| FBOgenerator
    subgraph Docker
        Repartitor --> deployments-calculator --> docker1 & docker2 & docker...
    end
    docker1 & docker2 & docker... --> |UDP| FBOgenerator
```

## Tasks

Fromiel:
- Docker compose

Quentin:
- Créé image pour paritucle

Alshor:
- ffmpeg

## Images

## Videos

## Features

## Dependencies

- OpenGL version: 4.6.0
- GLSL version: 4.60
- GLFW version: 3.3.8
- Glad version: 0.1.36
- ImGui version: 1.89.4 WIP
- GLM version: 0.9.8

## CMake project compilation

```bash
cmake -B . -DCMAKE_BUILD_TYPE=Release
```

then

```bash
cmake --build . --config Release
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

Dear ImGui:  
<https://github.com/ocornut/imgui>

OpenGL:  
<https://www.opengl.org/>

OpenCL:  
<https://www.khronos.org/blog/your-opencl-developer-experience-just-got-upgraded>  
<https://github.com/KhronosGroup/OpenCL-Guide>  
<https://github.com/KhronosGroup/OpenCL-SDK>

## Documentation

learnopengl (OpenGL tutorial):  
<https://learnopengl.com/In-Practice/2D-Game/Particles>

OpenCL NBody example:  
<https://github.com/KhronosGroup/OpenCL-SDK/tree/f510201a092363b66969888df49c68721ca2c4fb/samples/extensions/khr/nbody>

The coding challenge:  
<https://editor.p5js.org/codingtrain/sketches/joXNoi9WL>

## Contributors

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

Axel COURMONT:

- @Alshkor
- <https://github.com/Alshkor>

Alexis ROVILLE:

- @Fromiel
- <https://github.com/Fromiel>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/NBodySimulator)](https://github.com/Im-Rises/NBodySimulator/graphs/contributors)
