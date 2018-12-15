AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} TEXTURE_SRCS)
MESSAGE(${TEXTURE_SRCS})
add_library(texture ${TEXTURE_SRCS}
                        )
target_link_libraries(texture
            math
            hardwarebuffer)

	
