# 🚂 LightRail

**LightRail** is a lightweight, zero-dependency, modern C++20 ray tracing engine built from first mathematical principles. 

Originally ported from an undergraduate 3D linear algebra library written in C#, LightRail is structured as a clean, modular, hands-on educational scaffold: class interfaces, mathematical contracts, and unit tests are defined up-front so that core algorithms, geometric intersection tests, illumination models, and rendering loops can be implemented completely by hand.

---

## 🌟 Key Features

* **Zero External Dependencies**: Implemented entirely with the standard C++20 library. No OpenGL, DirectX, Vulkan, GLM, or third-party image decoding/encoding libraries.
* **Handwritten Raw Image Writers**: Generates displayable images directly from memory buffers to:
  * Windows 24-bit uncompressed Bitmap (`.bmp`) with binary header packing and row padding.
  * Netpbm PPM binary (`P6`) and ASCII (`P3`) formats (`.ppm`).
* **Linear Algebra Foundation**:
  * 3D vectors (`Vec3`, `Point3`) with vector arithmetic, dot products, cross products, reflections, refractions, and stochastic spatial distributions.
  * 3x3 matrices (`Mat3`) with Euler angle rotation generators, matrix inversion via adjugate/determinant, and vector transformations.
  * Parametric 3D rays ($P(t) = O + tD$).
* **Geometric Primitives & Acceleration**:
  * **Plane**: Analytical ray-plane intersections with procedural 2D checkerboard texturing.
  * **Sphere**: Analytical quadratic ray-sphere intersections.
  * **Triangle**: Fast ray-triangle intersection via the **Möller–Trumbore** algorithm.
  * **Mesh**: Handwritten zero-dependency Wavefront `.obj` file parser with automatic n-gon polygon fan-triangulation.
* **Optics & Material Shading**:
  * **Blinn-Phong Illumination**: Ambient, diffuse, and specular highlights.
  * **Mirror Reflections**: Recursive Whitted-style specular bounce tracking.
  * **Dielectric Glass & Water**: Refractive transmission obeying Snell's Law and Fresnel reflection via **Schlick's approximation**.
  * **Illumination Sources**: Point lights, directional lights, and area lights with stochastic shadow sampling for soft penumbrae.
* **Camera System**:
  * Perspective projection with arbitrary `look_from`, `look_at`, and vertical field-of-view (`vfov`).
  * Sub-pixel jittering for super-sampled anti-aliasing (SSAA).
  * Thin-lens defocus blur (depth of field) using simulated aperture and focal planes.
* **Multithreaded CPU Renderer**: Scanline dispatch across available CPU cores via standard `std::thread`.

---

## 📁 Project Structure

```text
LightRail/
├── CMakeLists.txt                # Builds static library liblightrail_core.a & binaries
├── README.md                     # Project documentation
├── include/
│   └── lightrail/
│       ├── camera/camera.hpp     # Perspective camera & defocus blur declarations
│       ├── image/
│       │   ├── color.hpp         # Floating-point RGB & gamma correction declarations
│       │   └── image.hpp         # Pixel buffer & PPM/BMP file writer declarations
│       ├── lighting/light.hpp    # Point, directional, and area light declarations
│       ├── material/material.hpp # Blinn-Phong & dielectric glass declarations
│       ├── math/
│       │   ├── constants.hpp     # Math constants & random number generator headers
│       │   ├── mat3.hpp          # 3x3 Matrix, determinant, & inverse declarations
│       │   ├── ray.hpp           # Parametric ray declaration
│       │   └── vec3.hpp          # Vec3/Point3 arithmetic & vector operations
│       ├── render/renderer.hpp   # Multithreaded Whitted ray tracer declaration
│       └── scene/
│           ├── hit_record.hpp    # Ray-surface intersection record
│           ├── hittable.hpp      # Abstract Hittable geometry interface
│           ├── mesh.hpp          # Triangle mesh & .obj parser declarations
│           ├── plane.hpp         # Analytical plane geometry declarations
│           ├── scene.hpp         # Aggregate scene container declarations
│           ├── sphere.hpp        # Quadratic sphere geometry declarations
│           └── triangle.hpp      # Möller–Trumbore triangle declarations
├── src/
│   ├── camera/camera.cpp         # Camera & ray generation implementations
│   ├── image/
│   │   ├── color.cpp             # Color clamping & gamma-to-byte implementations
│   │   └── image.cpp             # Binary PPM and BMP file serialization
│   ├── lighting/light.cpp        # Light sampling implementations
│   ├── material/material.cpp     # Scattering & Fresnel reflectance implementations
│   ├── math/
│   │   ├── constants.cpp         # Random number generator implementations
│   │   ├── mat3.cpp              # Matrix algebra & rotation implementations
│   │   ├── ray.cpp               # Parametric ray evaluation
│   │   └── vec3.cpp              # Vector algebra, dot, cross, & reflection
│   ├── render/renderer.cpp       # Recursive ray tracing & scanline scheduler
│   ├── scene/
│   │   ├── hit_record.cpp        # Surface normal alignment
│   │   ├── mesh.cpp              # Wavefront .obj loader & triangle aggregation
│   │   ├── plane.cpp             # Plane intersection calculations
│   │   ├── scene.cpp             # Scene-wide closest-hit testing loop
│   │   ├── sphere.cpp            # Sphere quadratic calculations
│   │   └── triangle.cpp          # Möller–Trumbore intersection algorithm
│   └── main.cpp                  # Showcase demo scene application
└── tests/
    └── test_math.cpp             # Math verification unit tests
```

---

## 🛠️ Building the Project

### Prerequisites
* A C++20 compliant compiler:
  * GCC 11+
  * Clang 13+
  * MSVC 2019+ (v19.29+)
* CMake 3.20 or newer

### Build Instructions
```bash
# 1. Configure the project
cmake -B build -S .

# 2. Compile all targets
cmake --build build
```

This produces two binaries inside `build/`:
* `build/test_math`: The math foundation test suite.
* `build/lightrail`: The ray tracer engine executable.

---

## 🧪 Test-Driven Development (TDD) Workflow

The engine on `main` is configured for **by-hand implementation**. Unimplemented functions throw `std::logic_error` with descriptive messages and implementation formulas in their comments.

### Step 1: Pass the Math Tests
Run the test runner:
```bash
./build/test_math
```

The output will guide you step-by-step:
```text
======================================
  LightRail Math Foundation Tests     
======================================
[Test] Vec3 operations...

[Next Step to Implement]: Not implemented: operator+(Vec3, Vec3)
```

Implement each function in [`src/math/vec3.cpp`](file:///home/padraiceah/Projects/LightRail/src/math/vec3.cpp), [`src/math/ray.cpp`](file:///home/padraiceah/Projects/LightRail/src/math/ray.cpp), and [`src/math/mat3.cpp`](file:///home/padraiceah/Projects/LightRail/src/math/mat3.cpp) until all unit tests pass:
```text
[Test] Vec3 operations...
  -> Vec3 PASSED
[Test] Ray parametric evaluation...
  -> Ray PASSED
[Test] Mat3 operations, determinant, and inverse...
  -> Mat3 PASSED
======================================
All math tests passed successfully!
```

### Step 2: Implement Image Export
Flesh out [`src/image/color.cpp`](file:///home/padraiceah/Projects/LightRail/src/image/color.cpp) and [`src/image/image.cpp`](file:///home/padraiceah/Projects/LightRail/src/image/image.cpp) to export gradient images directly to `.ppm` and `.bmp`.

### Step 3: Implement Geometry & Shading
Implement intersection tests for spheres, planes, and triangles, wire up the camera model, and complete the Whitted recursive shading loop in [`src/render/renderer.cpp`](file:///home/padraiceah/Projects/LightRail/src/render/renderer.cpp).

### Step 4: Run the Showcase Render
```bash
./build/lightrail
```
This renders a full demonstration scene featuring mirror spheres, refractive glass, checkered planes, and soft shadows, outputting `output_render.bmp` and `output_render.ppm`.

---

## 📖 Reference Implementation

If you would like to inspect a fully-working reference implementation for comparison, performance benchmarking, or algorithm verification, a complete implementation is preserved in git:

* **Branch**: [`reference/full-implementation`](https://github.com/PadraicHeberlein/LightRail/tree/reference/full-implementation)
* **Tag**: `v0.1.0-complete-reference`

To view or checkout the reference solution:
```bash
# Inspect files on the reference branch without altering your working tree:
git show reference/full-implementation:src/math/vec3.cpp
git show reference/full-implementation:src/render/renderer.cpp

# Or checkout the reference branch to a separate worktree:
git worktree add ../LightRail-Reference reference/full-implementation
```

---

## 📜 License

MIT License. Feel free to use, modify, and build upon this engine.
