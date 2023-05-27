CMAKE_MINIMUM_REQUIRED(VERSION 3.18.1)
project("vaEnc")

file(GLOB SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_executable(Enc ${SOURCE})
add_executable(Query Query.cpp)

target_link_libraries(Query va va-drm)
target_link_libraries(Enc va va-drm)

