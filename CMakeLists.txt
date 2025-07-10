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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

find_package(GLM REQUIRED)
find_path(GLM_INCLUDE_DIR "glm/glm.hpp")

find_package(GLFW3 REQUIRED)
find_path(GLFW3_INCLUDE_DIR "GLFW/glfw3.h")

find_package(OpenGL REQUIRED)

find_package(FREETYPE REQUIRED)

# Stop conflicting order of GLAD and GLFW
add_definitions(-DGLFW_INCLUDE_NONE)

# Add subdirectories
add_subdirectory(src)

# Copy Shader files to build directory
ADD_CUSTOM_TARGET(
    copy_liveplot_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/Shaders
            ${CMAKE_CURRENT_BINARY_DIR}/bin/Shaders

    COMMENT "Copying live plot shaders into binary directory"
)

# Copy Texture files to build directory
ADD_CUSTOM_TARGET(
    copy_liveplot_textures ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/textures
            ${CMAKE_CURRENT_BINARY_DIR}/bin/textures

    COMMENT "Copying live plot shaders into binary directory"
)

# Create sample app exectuables
add_executable(examplePlot apps/examplePlot.cpp)
add_executable(movingTimeframe apps/movingTimeframe.cpp)

target_link_libraries(examplePlot PRIVATE openGLPlotLive)
target_link_libraries(movingTimeframe PRIVATE openGLPlotLive)
