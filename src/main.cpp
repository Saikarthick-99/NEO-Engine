#include "Window.h"
#include <iostream>

int main() {
    std::cout << "Starting NEO Engine Game Loop..." << std::endl;

    // Spin up the window framework at 720p resolution
    Window window(1280, 720, "NEO Engine | Core Foundation");

    // --- THE CORE ACTIVE RUN TIME LOOP ---
    while (!window.shouldClose()) {

        // Wipe the screen canvas clean with a dark, slate-blue color vector (RGBA)
        window.clear(0.1f, 0.14f, 0.18f, 1.0f);

        // Swap buffers and handle structural events
        window.update();
    }

    std::cout << "Engine shutting down safely..." << std::endl;
    return 0;
}