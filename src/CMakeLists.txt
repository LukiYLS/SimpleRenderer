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

include_directories(${CBOKEH_ROOT_DIR}/src)

set(thirdparty_libs 
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    freeimage
    glfw)

add_subdirectory(math)
add_subdirectory(hardwarebuffer)
add_subdirectory(texture)
add_subdirectory(example)

