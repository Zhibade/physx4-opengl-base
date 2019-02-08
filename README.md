## Overview
Minimalist OpenGL application for testing PhysX 4.0 API

## Dependencies
- [GLAD v0.1.28](https://github.com/Dav1dde/glad)
- [GLFW 3.2.1](https://www.glfw.org/)
- [GLM 0.9.9.3](https://glm.g-truc.net/0.9.9/index.html)
- [PhysX 4.0](https://github.com/NVIDIAGameWorks/PhysX)

Put these dependencies in a folder named `lib` in the root directory. E.g `lib/glfw`. Please refer to `CMakeLists.txt` file for the specific paths.

The following binaries are needed for PhysX:
- PhysX_64.lib
- PhysX_64.dll
- PhysXCommon_64.lib
- PhysXCommon_64.dll
- PhysXFoundation_64.lib
- PhysXFoundation_64.dll
- PhysXExtensions_static_64.lib
- PhysXPvdSDK_static_64.lib

Don't forget to compile `PhysXExtensions` according to your project's CRT (C Runtime Library) setting.

## How to run
- Build project using Visual C++ compiler.
- Copy `PhysX_64.dll`, `PhysXCommon_64.dll`, `PhysXFoundation_64.dll` to the same directory as the executable.
- Run `PhysX4.exe`