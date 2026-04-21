cmake_minimum_required(VERSION 3.20)

project(TextPulse LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG QUIET)
if(NOT glfw3_FOUND)
  set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
  )
  FetchContent_MakeAvailable(glfw)
endif()

find_package(OpenAL CONFIG QUIET)
if(NOT OpenAL_FOUND)
  FetchContent_Declare(
    openal_soft
    GIT_REPOSITORY https://github.com/kcat/openal-soft.git
    GIT_TAG 1.24.3
  )
  set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
  set(ALSOFT_TESTS OFF CACHE BOOL "" FORCE)
  set(ALSOFT_NO_CONFIG_UTIL ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(openal_soft)
endif()

add_library(textpulse_core src/core/platform.cpp)
target_include_directories(textpulse_core PUBLIC src)
target_link_libraries(textpulse_core PUBLIC OpenGL::GL glfw OpenAL)

add_executable(textpulse_runtime src/runtime/main.cpp)
target_link_libraries(textpulse_runtime PRIVATE textpulse_core)

add_executable(textpulse_editor src/editor/main.cpp)
target_link_libraries(textpulse_editor PRIVATE textpulse_core)
