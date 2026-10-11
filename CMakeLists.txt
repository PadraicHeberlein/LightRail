cmake_minimum_required(VERSION 3.20)
project(LightRail VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags for safety and performance
if (MSVC)
    add_compile_options(/W4 /permissive- /O2)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

# Header-only library interface for LightRail engine
add_library(lightrail_core INTERFACE)
target_include_directories(lightrail_core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Math tests
add_executable(test_math tests/test_math.cpp)
target_link_libraries(test_math PRIVATE lightrail_core)

# Main ray tracer executable
add_executable(lightrail src/main.cpp)
target_link_libraries(lightrail PRIVATE lightrail_core)
