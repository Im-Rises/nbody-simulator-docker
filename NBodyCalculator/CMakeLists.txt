include_directories("${CMAKE_SOURCE_DIR}/dependencies")

file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.h")

add_executable(${PROJECT_NAME} main.cpp ${SRCS} ${HEADERS})

if (UNIX)
    target_link_libraries(${PROJECT_NAME} m)
endif (UNIX)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm.lib)
endif ()