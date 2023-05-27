CMAKE_MINIMUM_REQUIRED(VERSION 3.18.1)
project("FrmConv")

find_package(Vulkan REQUIRED)

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(conv ${SOURCES})

target_link_libraries(conv vulkan)
