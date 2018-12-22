AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} LIGHT_SRCS)
MESSAGE(${LIGHT_SRCS})
add_library(light ${LIGHT_SRCS}
                        )
target_link_libraries(light
            math
            hardwarebuffer)

	
