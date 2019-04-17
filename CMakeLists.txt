cmake_minimum_required (VERSION 3.8)
project (CoalApple)

#Include directories
include_directories(${PROJECT_SOURCE_DIR})
include_directories($ENV{ASSIMP_INCLUDE})
include_directories($ENV{GLEW_INCLUDE})
include_directories($ENV{SDL_INCLUDE})

#libary directories
link_directories($ENV{ASSIMP_LIB_x64})
link_directories($ENV{GLEW_LIB_x64})
link_directories($ENV{SDL_LIB_x64})

find_package(OpenGL REQUIRED)

# Add files
add_executable (CoalApple Sources/main.cpp Sources/Context.cpp Sources/Application.cpp Sources/Shaders/Shaders.cpp Sources/Shaders/Shaders.h Sources/VertexBuffer.h Sources/VertexBuffer.cpp Sources/FpsCamera.cpp Sources/Camera.cpp Sources/IndexBuffer.cpp Sources/Renderer.cpp)

target_link_libraries(CoalApple ${OPENGL_gl_LIBRARY} SDL2 Assimp glew32  )
