cmake_minimum_required(VERSION 2.8)

project(student_toolkit)
add_executable(${PROJECT_NAME} "main.cpp" "png_toolkit.cpp" "png_toolkit.h"
    "stb_image.h" "stb_image_write.h" "definitions.h" "area_rect.cpp" "area_rect.h" "filters.cpp" "filters.h"
        "filters_collection.cpp" "filters_collection.h" "Manager.cpp" "Manager.h" kernel.cpp kernel.h)
