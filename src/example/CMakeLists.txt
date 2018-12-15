# define exeutables

#add_executable(TEST_MATH_MATRIX4D TEST_MATH_MATRIX4D.cpp)
add_executable(TEST_TEXTURE TEST_TEXTURE.cpp)

set(mylibs 
    math
    hardwarebuffer
    texture
)
MESSAGE(${thirdparty_libs})
MESSAGE(${mylibs})
target_link_libraries(
    TEST_TEXTURE
    ${mylibs}
    ${thirdparty_libs}
)

install(TARGETS TEST_TEXTURE DESTINATION bin/)