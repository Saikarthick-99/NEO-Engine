# NEO Engine

NEO (Next-gen Engine Object) is a custom, high-performance 3D game engine developed from scratch utilizing the C++20 standard and a modern OpenGL 4.6 Core Profile hardware rendering pipeline. Built with an explicit structural architecture, NEO isolates game runtime execution from underlying core engine systems. The engine is engineered to support fast, low-overhead frame delivery, structured compilation boundaries, and advanced real-time rendering systems.

---

## Technical Specifications & Dependencies

NEO manages core dependencies natively within the repository structure to guarantee platform-agnostic, repeatable compilation across environments:

* **Language Standard:** C++20 / C11
* **Build Architecture:** CMake (Version 3.22+)
* **Windowing & Input Vector:** [GLFW 3.4.0](https://www.glfw.org/) (Compiled directly from source)
* **Graphics Function Loader:** [GLAD 1.0](https://glad.dav1d.de/) (Targeting OpenGL 4.6 Core Profile API maps)
* **Mathematics Library:** [GLM](https://github.com/g-truc/glm) (Header-only vector/matrix calculations)
* **Asset Processing:** [stb_image](https://github.com/nothings/stb) (Single-header image decoding implementation)

---

## Project Architecture

The engine uses a strict separation between the engine subsystem libraries (`src/` and `include/`), external vendor assets (`dependencies/`), static project data (`assets/`, `shaders/`), and the client game entry executable (`main.cpp`).

```text
NEO-Engine/
├── assets/                 # Non-code static runtime assets
│   └── icons/              # Window branding graphics (.png / .ico)
├── cmake/                  # Build system utility modules
├── dependencies/           # Managed third-party source frameworks
│   ├── glad/               # OpenGL 4.6 function pointer loader
│   ├── glfw/               # Cross-platform window and input context
│   ├── glm/                # Graphics-focused linear algebra headers
│   └── stb_image.h         # Multi-format image parsing library
├── include/                # Subsystem engine header interfaces (.h)
│   ├── Shader.h            # GPU Program compilation & pipeline interface
│   └── Window.h            # OS Window context abstraction
├── shaders/                # Programmable GLSL pipeline source code
│   ├── shader.frag         # Fragment color rasterization operations
│   └── shader.vert         # Vertex transformation operations
├── src/                    # Core engine implementation routines (.cpp)
│   ├── resource.rc         # Windows application build resource script
│   ├── Shader.cpp          # Shader compilation and tracking logic
│   ├── stb_image.cpp       # Image loader compilation unit
│   └── Window.cpp          # Window life-cycle & OpenGL driver context
├── CMakeLists.txt          # Root build configuration script
└── main.cpp                # Client game entry point and execution loop
