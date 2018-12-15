# define exeutables

add_executable(TEST_MATH_MATRIX4D TEST_MATH_MATRIX4D.cpp)

target_link_libraries(
    TEST_MATH_MATRIX4D
    math
)
target_include_directories(TEST_MATH_MATRIX4D
    PUBLIC
    ${MATH_INCLUDS})
install(TARGETS TEST_MATH_MATRIX4D DESTINATION bin/)