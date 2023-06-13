include_directories("${CMAKE_SOURCE_DIR}/dependencies")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/glad/include")
include_directories("${CMAKE_SOURCE_DIR}/dependencies/glfw/include")
#include_directories("${CMAKE_SOURCE_DIR}/dependencies/curlpp/include")


if (WIN32)
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/dependencies/OpenCV)
endif ()

file(GLOB_RECURSE SRCS_HEADERS_GLAD "${CMAKE_SOURCE_DIR}/dependencies/glad/*.c" "${CMAKE_SOURCE_DIR}/dependencies/glad/*.h")

file(GLOB_RECURSE SRCS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/*.h")

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL 3.3 REQUIRED)

find_package(OpenCV REQUIRED)

#find_package(CURL REQUIRED)
#
#find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ${SRCS} ${HEADERS} ${SRCS_HEADERS_GLAD})

target_link_libraries(${PROJECT_NAME} OpenGL::GL)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

#target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
#
#target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

if (WIN32)
    if (MSVC)
        target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/dependencies/glfw/lib-vc2019/glfw3.lib")
    elseif (MINGW)
        target_link_libraries(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/dependencies/glfw/lib-mingw-w64/libglfw3.a")
    endif ()
elseif (UNIX)
    find_package(glfw3 3.3 REQUIRED)
    target_link_libraries(${PROJECT_NAME} glfw ${CMAKE_DL_LIBS})
else ()
    message(FATAL_ERROR "OS not configured in CMakeLists.txt")
endif ()