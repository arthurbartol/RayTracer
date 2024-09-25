cmake_minimum_required(VERSION 3.20)

project(raytracer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compile options
option(BUILD_TESTS "Build th tests" OFF)

include_directories(${PROJECT_SOURCE_DIR}/src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Find necessary packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Define paths for each component
set(CORE_SOURCES
    src/core/window.cpp
)

set(RENDERER_SOURCES
    src/renderer/renderer.cpp
)

add_library(core STATIC ${CORE_SOURCES})
add_library(renderer STATIC ${RENDERER_SOURCES})

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    core
    renderer
    OpenGL::GL
    GLEW::GLEW
    glfw
    glm::glm
)

# Compiler specific configurations
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()
