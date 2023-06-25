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

## Videos

[//]: # (https://github.com/Im-Rises/nbody-simulator-docker/assets/59691442/59ef1c71-e2bb-4bd5-99f8-66eace4280b5)

https://github.com/Im-Rises/nbody-simulator-docker/assets/59691442/622717a8-b508-4221-a79e-f00c07475979

Longer video 🚀🚀 [here](https://www.youtube.com/watch?v=OisxyKE_ioU) 🚀🚀

## How to use

To use the project, you need to have docker installed on your computer.
You can download it here: <https://www.docker.com/>

You also need to install the following linux lib:

```bash
sudo apt-get install xvfb
```

You also need python3 installed on your computer.
You can download it here: <https://www.python.org/downloads/>

Once you have installed the requirements, you can install the python libs with the following command:

```bash
pip install -r requirements.txt
```

This will install the required libs to generate the `docker-compose.yml` using the `docker-compose-generator.py` python
script.

```bash
python3 docker-compose-generator.py <total_particles> <number_of_calculators> <simulation_recording_time>
```

exemple:

```bash
python3 docker-compose-generator.py 1000 4 10
```

This will generate a `docker-compose.yml` file with 4 calculators and 1000 particles and a simulation recording time of
10 seconds.

Once created you can run the `docker-compose.yml` with the following command:

```bash
./test.sh
```

An output video will be genereated in the `./src/NBodyGraphics/output_dir` folder.

## Dependencies

- OpenGL version: 3.3
- GLSL version: 330
- GLFW version: 3.2.1
- Glad version: 0.1.36
- GLM version: 0.9.9
- OpenCV version: 4.7.0-dev
- nlhomann/json version: 3.9.1
- libcurl version: 7.74.0

## Architecture

```mermaid
flowchart LR
    
    subgraph Host
    
    subgraph Docker-Calculators
    docker1 & docker2 & docker...
    end
    docker1 & docker2 & docker... <--> |GET/POST| api-redis
    subgraph Redis
    api-redis
    end
    api-redis --> |Send particles| NBodyGraphics
    NBodyGraphics --> |Request update| api-redis
    subgraph Video-Generator
    end
    
    subgraph Video-Generator
    NBodyGraphics
    end
    
    NBodyGraphics --> |Save video | Volume
   
end
```

## Logic Diagram

```mermaid
graph TB
    A((Start))
    B[NBodyGraphics]
    C[API-Redis]
    D[NBodycalculator1]
    E[NBodycalculator2]
    F[NBodycalculator3]
    G[NBodycalculator...]
    H[API-Redis]
    I[NBodyGraphics]
    J[Volume]
    
    A --> B
    B --> | Physic update | C
    C --> | Particle request update | D & E & F & G
    D & E & F & G --> | Send updated particles | H
    H --> | Send updated particles | I
    I --> | Do another cycle | B
    I --> | Save video | J
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

Quentin MOREL:

- @Im-Rises
- <https://github.com/Im-Rises>

Alexis ROVILLE:

- @Fromiel
- <https://github.com/Fromiel>

[![GitHub contributors](https://contrib.rocks/image?repo=Im-Rises/nbody-simulator-docker)](https://github.com/Im-Rises/nbody-simulator-docker/graphs/contributors)
