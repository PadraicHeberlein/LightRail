# LightRail API & Mathematical Reference {#mainpage}

**LightRail** is a lightweight, zero-dependency, modern C++20 ray tracing engine built from first mathematical principles.

Its public headers serve both as an executable API contract and as a self-contained educational reference covering 3D linear algebra, abstract algebraic structures (Groups, Rings, Fields, Normed & Lie Algebras), geometric ray-primitive intersections, physical optics, and Whitted-style recursive rendering.

---

## Rendering Pipeline Overview

@image html render_pipeline.svg "LightRail Rendering Pipeline: Camera -> Multithreaded Renderer -> Scene / Hittable -> Material & Lighting -> Image Export"

---

## Subsystems

- **Math (`include/lightrail/math/`)**: `Vec3`, `Mat3`, `Quaternion`, `Complex`, `Ray`, C++20 algebraic `concept`s (`Group`, `Ring`, `Field`, `VectorSpace`, `Algebra`, `NormedAlgebra`, `LieAlgebra`), CRTP interfaces, and Lie group exponential/logarithmic bridges between \f$ \mathfrak{so}(3) \f$, \f$ SO(3) \f$, and unit quaternions.
- **Image (`include/lightrail/image/`)**: Linear floating-point `Color` with gamma correction and handwritten binary/ASCII Netpbm `.ppm` and 24-bit Windows `.bmp` writers.
- **Scene (`include/lightrail/scene/`)**: `Hittable` interface, `HitRecord`, analytical `Plane` and `Sphere`, Möller–Trumbore `Triangle`, Wavefront `.obj` `Mesh`, and aggregate `Scene`.
- **Material & Lighting (`include/lightrail/material/`, `include/lightrail/lighting/`)**: Blinn–Phong shading, mirror reflection, dielectric refraction (Snell's Law + Schlick's Fresnel approximation), and point/directional/area lights with stochastic soft shadows.
- **Camera & Renderer (`include/lightrail/camera/`, `include/lightrail/render/`)**: Perspective camera with sub-pixel SSAA jitter, thin-lens depth of field, and a multithreaded Whitted ray tracer.

---

## Building This Documentation

```bash
cmake -B build -S .
cmake --build build --target docs
```

Then open `build/docs/html/index.html` in any modern web browser.
If **Graphviz** (`dot`) is installed, Doxygen also generates interactive SVG class inheritance, collaboration, and include dependency graphs automatically.
