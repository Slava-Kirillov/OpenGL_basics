cmake_minimum_required(VERSION 3.15)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OpenGL
        includes/image_DXT.c
        includes/image_DXT.h
        includes/image_helper.c
        includes/image_helper.h
        src/main.cpp
        includes/SOIL.c
        includes/SOIL.h
        includes/stb_image_aug.c
        includes/stb_image_aug.h
        includes/stbi_DDS_aug.h
        includes/stbi_DDS_aug_c.h)

target_link_libraries(OpenGL glut GL GLU)

include_directories(${CMAKE_SOURCE_DIR}/includes)