# define exeutables
#add_executable(TEST_MATH_MATRIX4D TEST_MATH_MATRIX4D.cpp)
#add_executable(TEST_TEXTURE TEST_TEXTURE.cpp)
add_executable(RENDERER_TEST RENDERER_TEST.cpp)

set(mylibs 
    math
    hardwarebuffer
    texture
    light
    graphic
    object
    tools
    utils
)
MESSAGE(${thirdparty_libs})
MESSAGE(${mylibs})

target_link_libraries(
    RENDERER_TEST
    ${mylibs}
    ${thirdparty_libs}
)

install(TARGETS RENDERER_TEST DESTINATION bin/)