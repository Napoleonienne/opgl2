
cmake_minimum_required(VERSION 3.0.0)
project(opengl2 VERSION 0.1.0)

cmake_policy(SET CMP0072 NEW)
find_package(glm REQUIRED)

find_package(OpenGL REQUIRED)

add_executable(opengl2
    src/main.cpp
    src/glad.c
    src/Shader.cpp
    # Pas besoin d'inclure les headers dans add_executable
)

target_include_directories(opengl2 PRIVATE dependance)

target_link_libraries(opengl2 
    glfw
    glm::glm
    )