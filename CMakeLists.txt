cmake_minimum_required(VERSION 3.20)
project(LightRail VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(LIGHTRAIL_ENABLE_LTO "Enable Link-Time Optimization (IPO) for Release builds" OFF)
option(LIGHTRAIL_BUILD_DOCS "Enable Doxygen HTML documentation target when Doxygen is installed" ON)

# Compiler flags for safety and performance (Debug vs. Release separated)
if (MSVC)
    add_compile_options(/W4 /permissive- /wd4100 $<$<CONFIG:Release>:/O2>)
else()
    add_compile_options(
        -Wall -Wextra -Wpedantic -Wno-unused-parameter
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Release>:-O3>
    )
endif()

if (LIGHTRAIL_ENABLE_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT lto_supported OUTPUT lto_error)
    if (lto_supported)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
    else()
        message(WARNING "LTO requested but not supported: ${lto_error}")
    endif()
endif()

# Core library source files
set(LIGHTRAIL_CORE_SOURCES
    src/math/constants.cpp
    src/math/vec3.cpp
    src/math/mat3.cpp
    src/math/ray.cpp
    src/math/complex.cpp
    src/math/quaternion.cpp
    src/math/algebra_functions.cpp
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

# Abstract algebra tests
add_executable(test_algebra tests/test_algebra.cpp)
target_link_libraries(test_algebra PRIVATE lightrail_core)

# Main ray tracer executable
add_executable(lightrail src/main.cpp)
target_link_libraries(lightrail PRIVATE lightrail_core)

# Optional Doxygen HTML documentation target (does not add any dependency to lightrail_core)
if (LIGHTRAIL_BUILD_DOCS)
    find_package(Doxygen QUIET OPTIONAL_COMPONENTS dot)
    if (DOXYGEN_FOUND)
        if (DOXYGEN_DOT_FOUND)
            set(LIGHTRAIL_DOXYGEN_HAVE_DOT YES)
        else()
            set(LIGHTRAIL_DOXYGEN_HAVE_DOT NO)
        endif()

        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating LightRail HTML documentation with Doxygen (HAVE_DOT=${LIGHTRAIL_DOXYGEN_HAVE_DOT})"
            VERBATIM
        )
    else()
        message(STATUS "Doxygen not found; 'docs' target will not be generated.")
    endif()
endif()
