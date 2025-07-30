cmake_minimum_required(VERSION 3.20)
project(Solar_sistem)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

include_directories(
        include
        include/glad
        ${GLM_INCLUDE_DIRS}
)

file(GLOB SRC_FILES src/*.cpp)

add_executable(
        SolarMax
        main.cpp
        ${SRC_FILES}
        include/glad/glad.c
        src/shader/Shader.h
)

target_link_libraries(
        SolarMax
        glfw3
        opengl32
        glm::glm
)