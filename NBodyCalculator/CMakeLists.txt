include_directories("${CMAKE_SOURCE_DIR}/dependencies")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/glm")

file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.h")

find_package(CURL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${SRCS} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} m)
