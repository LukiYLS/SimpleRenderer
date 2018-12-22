AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} UTILS_SRCS)
MESSAGE(${UTILS_SRCS})
add_library(utils ${UTILS_SRCS}
                        )
target_link_libraries(utils
            math
            hardwarebuffer)

	
