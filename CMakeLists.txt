cmake_minimum_required(VERSION 3.5.1)

project(test_env)

#加-g用来gdb调试
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++11 -fPIC")
endif()

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

#freeimage
find_path(FREEIMAGE_INCLUDE_DIR FreeImage.h)
find_library(FREEIMAGE_LIBRARY NAMES freeimage)

set(thirdparty_libs 
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    glfw)
set(mystatic_libs
    math
    hardwarebuffer)
set(MATH_INCLUDS math/*.h)

add_subdirectory(math)
add_subdirectory(hardwarebuffer)
add_subdirectory(test)

