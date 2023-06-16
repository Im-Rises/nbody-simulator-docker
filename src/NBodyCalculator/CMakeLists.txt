cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(NBodyCalculator)

include_directories("${CMAKE_SOURCE_DIR}/dependencies")

#file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/*.cpp")
#file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/*.h")

find_package(CURL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} m)
