cmake_minimum_required(VERSION 3.15)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OpenGL
        image_DXT.c
        image_DXT.h
        image_helper.c
        image_helper.h
        main.cpp
        SOIL.c
        SOIL.h
        stb_image_aug.c
        stb_image_aug.h
        stbi_DDS_aug.h
        stbi_DDS_aug_c.h
        Vector3D.cpp
        Vector3D.hpp)

target_link_libraries(OpenGL glut GL GLU)
