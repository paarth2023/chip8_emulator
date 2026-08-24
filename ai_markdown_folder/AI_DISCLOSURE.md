# AI Code Disclosure

This markdown file tracks AI-assisted code in this project. It exists as a form of AI disclosure and to keep myself accountable about where AI contributed to the codebase. The goal is to document intent, ownership, and the boundaries of generated assistance rather than hide that assistance in the implementation.

## Project Modules

| Module                                | Location                  | Responsibility                                                                                                                                                                                            |
| ------------------------------------- | ------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| CHIP-8 application and emulator state | `src/main.cpp`            | Owns the application entry point, the CHIP-8 state structure, and the current display test data. This is where future instruction execution and timing can be connected to the renderer.                  |
| OpenGL renderer interface             | `src/opengl_renderer.h`   | Defines the reusable `OpenGLRenderer` API. The emulator only needs to initialize it, check whether the window should close, submit its 64x32 display buffer, and poll events.                             |
| OpenGL renderer implementation        | `src/opengl_renderer.cpp` | Owns GLFW window/context setup, GLAD loading, shader compilation and linking, the fullscreen textured quad, the CHIP-8 display texture, resize handling, frame presentation, and OpenGL resource cleanup. |
| Build configuration                   | `CMakeLists.txt`          | Builds the application and connects the renderer with GLFW, GLAD, and the system OpenGL library.                                                                                                          |
| Third-party OpenGL loading            | `external/glad/`          | Supplies generated GLAD loader source and headers so OpenGL functions can be accessed after context creation.                                                                                             |
| Windowing library                     | `external/glfw-3.5.1/`    | Supplies GLFW for window creation, the OpenGL context, input/event polling, and buffer swapping.                                                                                                          |

## OpenGL Module Intent

`OpenGLRenderer` is deliberately independent from the CHIP-8 state type. It accepts a pointer to a byte display buffer and treats each byte as one grayscale pixel, so the emulation core does not need to include OpenGL or GLFW headers. The display dimensions are provided to the constructor, which keeps the renderer reusable for the CHIP-8's 64x32 screen and for later experiments.

The implementation keeps the OpenGL details in one ownership boundary:

- `initialize()` creates the GLFW window and context, loads GLAD, builds the shaders, creates the quad geometry, and allocates the display texture.
- `render(display)` uploads the current display buffer and draws it with nearest-neighbor filtering, preserving the crisp pixel-art look.
- `framebufferSizeCallback()` updates the viewport when the window is resized.
- The destructor releases GPU resources, destroys the window, and terminates GLFW.

The current fragment shader maps active CHIP-8 pixels to dark green. This is a presentation choice, not part of emulation, so it can be changed later without modifying CPU, memory, input, or timing code.

## AI-Assisted Change Record

- Extracted the OpenGL and GLFW lifecycle from `src/main.cpp` into `OpenGLRenderer`.
- Added shader compile and link error reporting.
- Added RAII cleanup and window resize handling to make renderer reuse less error-prone.
- Updated CMake to compile the new renderer implementation.
- Wrote this disclosure document to make the AI-assisted scope explicit.
