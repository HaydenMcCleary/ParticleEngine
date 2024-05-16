cmake_minimum_required(VERSION 3.13.0)
project(opengl_project VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

# Add the stb_image library to your project
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/path_to_stb_image_directory)


add_executable(opengl_project 
                src/main.cpp
                src/glad.h
                src/glad.c
                src/stb_image_write.h)

target_link_libraries(opengl_project 
    PRIVATE glfw
    PRIVATE OpenGL::GL
    PRIVATE dl
    PRIVATE stb_image
)
        