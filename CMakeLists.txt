cmake_minimum_required(VERSION 3.20)
project(LightRail VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags for safety and performance
if (MSVC)
    add_compile_options(/W4 /permissive- /O2 /wd4100)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter -O3)
endif()

# Core library source files
set(LIGHTRAIL_CORE_SOURCES
    src/math/constants.cpp
    src/math/vec3.cpp
    src/math/mat3.cpp
    src/math/ray.cpp
    src/image/color.cpp
    src/image/image.cpp
    src/scene/hit_record.cpp
    src/scene/plane.cpp
    src/scene/sphere.cpp
    src/scene/triangle.cpp
    src/scene/mesh.cpp
    src/scene/scene.cpp
    src/material/material.cpp
    src/lighting/light.cpp
    src/camera/camera.cpp
    src/render/renderer.cpp
)

add_library(lightrail_core STATIC ${LIGHTRAIL_CORE_SOURCES})
target_include_directories(lightrail_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Math verification tests
add_executable(test_math tests/test_math.cpp)
target_link_libraries(test_math PRIVATE lightrail_core)

# Main ray tracer executable
add_executable(lightrail src/main.cpp)
target_link_libraries(lightrail PRIVATE lightrail_core)
