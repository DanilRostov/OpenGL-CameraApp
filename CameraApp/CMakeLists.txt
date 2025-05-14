cmake_minimum_required(VERSION 3.16)
project(CameraApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable verbose output (optional)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Locate Homebrew packages
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

# GLEW
pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})

# GLFW
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

# GLM
find_path(GLM_INCLUDE_DIR glm/glm.hpp PATHS /opt/homebrew/include)
include_directories(${GLM_INCLUDE_DIR})

# ImGui include path
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)

# Source files
set(SOURCES
    main.cpp
    camera.cpp
    mesh.cpp
    utils/matrix_utils.cpp

    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp

    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils)

# Executable
add_executable(CameraApp ${SOURCES})

# Link libraries
target_link_libraries(CameraApp
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    OpenGL::GL
)
