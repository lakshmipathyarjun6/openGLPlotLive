# Set minimum cmake
cmake_minimum_required(VERSION 3.10)

# Setup project
project(openGLPlotLive-proj)

# Resolves issue with unable to debug with CLion, reverts back to g++9
add_compile_options(-gdwarf-4)

# Set OpenGL Policy
set(OpenGL_GL_PREFERENCE "GLVND")

# Add c++20 flag to compiler
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

find_package(GLM REQUIRED)
find_path(GLM_INCLUDE_DIR "glm/glm.hpp")

find_package(GLFW3 REQUIRED)
find_path(GLFW3_INCLUDE_DIR "GLFW/glfw3.h")

find_package(OpenGL REQUIRED)

find_package(FREETYPE REQUIRED)

set(OPENGLPLOTS_LIBS ${FREETYPE_LIBRARY} glfw z)

# Stop conflicting order of GLAD and GLFW
add_definitions(-DGLFW_INCLUDE_NONE)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(apps)
