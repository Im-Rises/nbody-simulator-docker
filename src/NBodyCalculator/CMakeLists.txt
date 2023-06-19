cmake_minimum_required(VERSION 3.8)

option(DOCKER_BUILD "Build inside Docker" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(NBodyCalculator)

if (DOCKER_BUILD)
    include_directories("${CMAKE_SOURCE_DIR}/dependencies")
else ()
    include_directories("${CMAKE_SOURCE_DIR}/../dependencies")
endif ()

find_package(CURL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} m)
