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

FIND_PACKAGE(GLM REQUIRED)
FIND_PATH(GLM_INCLUDE_DIR "glm/glm.hpp")

FIND_PACKAGE(GLFW3 REQUIRED)
FIND_PATH(GLFW3_INCLUDE_DIR "GLFW/glfw3.h")

FIND_PACKAGE(OpenGL REQUIRED)

FIND_PACKAGE(FREETYPE REQUIRED)

set(LIBS ${FREETYPE_LIBRARY} glfw)

# Stop conflicting order of GLAD and GLFW
add_definitions(-DGLFW_INCLUDE_NONE)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(apps)
