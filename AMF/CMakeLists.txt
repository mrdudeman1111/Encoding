CMAKE_MINIMUM_REQUIRED(VERSION 3.18.1)
project("OpenGL Encoder")

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

include_directories(../include)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(glenc ${SOURCES})

target_link_libraries(glenc OpenGL glm glfw)

