# NEO Engine

**NEO (Next-gen Engine Object)** is a custom, high-performance 3D game engine built from scratch in C++20 and modern OpenGL 4.6 Core Profile. Inspired by raw, high-refresh-rate rendering frameworks, NEO focuses on explicit architecture, high performance, and advanced rendering techniques like point-cloud-based global illumination.

---

## 🛠️ Tech Stack & Dependencies

NEO manages its dependencies natively within the repository to ensure platform-agnostic, repeatable compilation:

*   **Language Standard:** C++20 / C11
*   **Build System:** CMake (Version 3.22+)
*   **Windowing & Input:** [GLFW 3.4.0](https://www.glfw.org/) (Compiled from source)
*   **OpenGL Function Loader:** [GLAD 1.0](https://glad.dav1d.de/) (OpenGL 4.6 Core Profile)
*   **Linear Algebra:** [GLM](https://github.com/g-truc/glm) *(Upcoming)*

---

## 🏗️ Architecture Layout

```text
NEO-Engine/
├── cmake/             # Build system utility modules
├── dependencies/      # Third-party source dependencies
│   ├── glad/          # OpenGL 4.6 Core Function Loader
│   └── glfw/          # Multi-platform windowing framework
├── include/           # Engine subsystem headers (.h)
│   └── Window.h       # OS Window & Graphics Context Abstraction
└── src/               # Engine implementation source files (.cpp)
    ├── main.cpp       # Engine Application Entry Point
    └── Window.cpp     # Window Lifecycle & Graphics Setup
