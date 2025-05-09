# RayTracer

A simple raytracer application that simulates lighting effects through raytracing. Currently implemented in grayscale mode, allowing rapid prototyping of new features. However, the architecture easily supports future RGB extensions.

---

## Ray lifecycle overview (with initial "Max Depth"):

1. A ray is emitted from the camera position, oriented according to its rotation, field of view (FOV), and image resolution.

2. The algorithm uses Bounding Volume Hierarchies (BVH) to detect intersections between the ray and scene objects:
   - **If no intersection occurs**, the ray returns the background color.
   - **If intersections occur**, a shadow ray is emitted from each intersection point toward each scene light source:
     - **If obstacles block the shadow ray**, no lighting is calculated from that particular light source.
     - **If the shadow ray is unobstructed**, diffuse and/or specular lighting values at the intersection point are incremented accordingly.

3. At this stage:
   - **If Max Depth ≤ 1**, tracing terminates.
   - **If Max Depth > 1**, additional rays are emitted:
     - Diffuse reflection rays are emitted around the intersected surface normal (`faceNormal`). The total number of diffuse rays is `dLayerCount * dRadialCount`.
     - Specular reflection rays are emitted around the reflection direction from the original intersection point. The total number of specular rays is `sLayerCount * sRadialCount`.
     - Each subsequent ray undergoes the same process from step 2, with depth reduced by one each time.

---

## Input parameters:

- **Width, Height** – Output resolution (pixels).
- **Max Depth** – Maximum reflection depth for rays.
- **Diffuse/Specular indirect factor** – Multipliers controlling the influence of indirect diffuse/specular lighting.
- **Diffuse/Specular layer count** – Determines how many angular layers are generated for diffuse/specular secondary rays.
- **Diffuse/Specular radial count** – Determines how many radial rays are emitted per angular layer for diffuse/specular lighting.

- **Camera position** – Camera's spatial coordinates (Y-axis upwards).
- **Camera rotation** – Camera orientation (Euler angles).

- **Light position** – Spatial position of each light source.
- **Light intensity** – Brightness intensity of each light source.

- **Material Diffuse** – Influence multiplier for diffuse lighting.
- **Material Specular** – Influence multiplier for specular reflections.
- **Material Roughness** – Higher roughness results in reflections from a broader range of angles, creating blurred reflections at `Max Depth ≥ 2`.

---

## Secondary Ray Generation:

Generation processes for diffuse and specular secondary rays are similar, differing mainly in orientation:

- **Diffuse reflections** are calculated around the surface normal (`faceNormal`). For example, with `dRadialCount = 4` and `dLayerCount = 5`, 20 secondary rays are generated—five rays each at 5°, 33°, 47°, 61°, and 89° angles relative to the normal. This range (5°–89°) ensures detailed capture of small surface indentations.

- **Specular reflections** are generated around the reflected direction of the original incoming ray, rather than the surface normal. This approach presents certain challenges, such as secondary rays potentially intersecting the originating mesh prematurely, which may require future optimization. Specular ray angle dispersion is tied to material roughness to achieve realistic, blurred reflections—an effect successfully demonstrated in certain renders.

---

## Performance:

- OpenMP parallelization significantly improves performance (CUDA acceleration has not yet been tested).
- BVH structures greatly accelerate rendering, particularly for complex meshes.
- Computational load increases dramatically with higher Max Depth settings. Rendering a scene at resolution 100×100 with a Max Depth of 3 may take minutes on an Intel 13900k.
- Performance scales negatively with pixel coverage of meshes and total triangle count. Each mesh uses an independent BVH structure, meaning more meshes lead to decreased relative performance.

---

## Main classes:

- **`RayTracer`** – Primary rendering logic and raytracing calculations.
- **`BVH` / `BVHNode` / `AABB`** – BVH structures for accelerating intersection tests. Work alongside `Mesh` and `Triangle` to detect ray intersections.
- **`Mesh`** – Holds collections of `Triangle` objects, each defined by vertex positions (`glm::vec3`) and normals.
- **`Ray`** – Simple class encapsulating ray origin and direction.
- **`Camera`** – Manages the camera configuration, including `Eye` and `ScreenPlane`, which determine the initial ray emission setup.
- **`Light`, `Material`** – Store relevant lighting and material parameters.
- **`Scene` / `RenderSettings`** – Container classes for scene geometry, objects, and rendering parameters, providing easy centralized access to configurations.

---

## Window Management / GUI / Texture Rendering:

- **`MyTexture`** – Custom class for storing texture data as `[x,y]`, converted to a format compatible with OpenGL textures before rendering.
- **`ApplicationManager`** – Central application manager invoking rendering and GUI functions (initialized in `main.cpp`).
- **`GUIManager`** – Defines graphical interface, includes `onClickRender` (trigger rendering) and `updateSceneData` (apply GUI inputs to the scene).
- **`OpenGLRenderer`** – Responsible for rendering textures on-screen.
- **`Defaults`** – Stores default values and constants used throughout the program.

---

## Build Environment:

- **IDE:** Visual Studio 2022
- **Libraries used:**
  - GLEW
  - GLFW
  - GLM
  - wxWidgets (for GUI)
  - tiny_obj_loader (for OBJ mesh loading)
