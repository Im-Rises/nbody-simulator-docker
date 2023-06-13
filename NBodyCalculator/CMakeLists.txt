include_directories("${CMAKE_SOURCE_DIR}/dependencies")

file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.h")

find_package(CURL REQUIRED)

find_package(nlohmann_json REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${SRCS} ${HEADERS})

target_link_libraries(${PROJECT_NAME} CURL::libcurl)

target_link_libraries(${PROJECT_NAME} m)

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

