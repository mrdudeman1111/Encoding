CMAKE_MINIMUM_REQUIRED(VERSION 3.18.1)
project("vaEnc")

file(GLOB SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(Enc ${SOURCE})

target_link_libraries(Enc va)

