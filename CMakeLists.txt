cmake_minimum_required(VERSION 3.12)
project(PhysX4)

set(CMAKE_CXX_STANDARD 14)

if(MINGW)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
endif(MINGW)

# Include directories
set(GLFW_INCLUDE_DIR lib/glfw/include)
set(GLFW_DIR lib/glfw)

set(GLAD_INCLUDE_DIR lib/glad/include)
set(GLM_INCLUDE_DIR lib/glm)

set(PHYSX_INCLUDE_DIR lib/physx/include)
set(PHYSX_SHARED_INCLUDE_DIR lib/physx/pxshared/include)
set(PHYSX_LIB_DIR lib/physx/bin)

# GLFW build settings (turn off building docs, examples, and tests)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

add_subdirectory(${GLFW_DIR})

include_directories(${GLFW_INCLUDE_DIR})
include_directories(${GLAD_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories((${PHYSX_INCLUDE_DIR}))
include_directories((${PHYSX_SHARED_INCLUDE_DIR}))

link_directories(${PHYSX_LIB_DIR})

add_executable(PhysX4 main.cpp callbacks.h callbacks.cpp constants.h drawing/scene.cpp drawing/scene.h drawing/cube.cpp drawing/cube.h utils/fileLoader.cpp utils/fileLoader.h utils/shaderLoader.cpp utils/shaderLoader.h lib/glad/src/glad.c physics/PhysicsErrorCallback.cpp physics/PhysicsErrorCallback.h drawing/drawable3D.cpp drawing/drawable3D.h)

target_link_libraries(PhysX4 ${OPENGL_gl_LIBRARY})
target_link_libraries(PhysX4 glfw)

# These are not needed if using DLLs?
target_link_libraries(PhysX4 PhysX_64)
target_link_libraries(PhysX4 PhysXCommon_64)
target_link_libraries(PhysX4 PhysXFoundation_64)