# GLUtils: OpenGL Utility Library

This is the first project in a series that I plan to create to learn graphics programming.

GLUtils is a utility library for OpenGL that abstracts core concepts required for all other projects like: shaders, textures, meshes, and many more that I will find helpful.
> [!NOTE]
> This library will be a WIP (Work In Progress) throughout the whole series. If I find something worth adding to it, I will.

## Goals

My primary goals for GLUtils include robust implementations of the following core graphics components:
- **Shaders**: Implement reliable mechanisms for loading shader source code (from files and strings) and efficiently setting uniform variables to pass data to the GPU.
- **Textures**: Develop functionality for loading various image formats, generating texture objects, and binding them correctly for use in rendering.
- **Materials**: Provide abstractions for common material properties.
- **Meshes**: Create structures to store vertex data (positions, normals, UVs, indices), and include utilities for generating common built-in primitives (e.g., quads, cubes, spheres).
- **Models**: Establish a system to encapsulate combinations of meshes, materials, and textures, representing complete renderable objects.
- **Lights**: Implement different types of light sources – directional, spot, and point.
- **Scenes**: Design a structure to manage and organize multiple models and lights within a virtual environment, facilitating scene graph management.

## Approach

Well, the plan is straightforward, at least for now. My general strategy involves treating most elements as data containers, focusing on clear organization and efficient access.

### Core Data Structures

The core components (shaders, textures, materials, meshes, models, lights, scenes) will primarily function as data containers. They will hold handles to the underlying OpenGL resources. I intend to use smart pointers for resource management, unless a more suitable approach becomes apparent.

### Resource Loading & Initialization

- Shaders: Will support loading both from raw source code strings and external files.
- Textures: Will be loaded from pixel data arrays (e.g., for procedural textures) and from image files.
- Materials & Lights: Instances will be created with sensible default values and then configured individually to meet specific rendering requirements.

### Mesh & Model Creation

- Meshes: Will be created by providing vectors of vertex data.
- Built-in Primitives: Meshes should include utilities for generating common primitives (like a quad and a cube). For simplicity, I plan to use static variables within static functions for these, with the primitive data residing in a separate header file.

### Scene Management

- Scenes: This is arguably the most complex structure. My current approach is to manage a central list of all models and a separate list for all lights. I will then design additional data structures to define and store dependencies and relationships between these elements, using references for efficient access.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details
