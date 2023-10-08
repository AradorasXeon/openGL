#This video was really useful: https://www.youtube.com/watch?v=LxEFn-cGdE0
cmake_minimum_required(VERSION 3.0.0)
project(my_opengl_begginer_project VERSION 0.1.1)
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)

# Specify the source directory
set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")

# Use a wildcard to gather all source files in the directory
file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.c")

# Recursively gather header files from subdirectories under 'include'
file(GLOB_RECURSE INCLUDE_FILES "${INCLUDE_DIR}/*.h")

# Create the executable and link it with the source files
add_executable(my_opengl_begginer_project ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(my_opengl_begginer_project glfw OpenGL::GL)