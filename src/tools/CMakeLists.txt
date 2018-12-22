AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} TOOLS_SRCS)
MESSAGE(${TOOLS_SRCS})
add_library(tools ${TOOLS_SRCS}
                        )
target_link_libraries(tools
            math
            hardwarebuffer)

	
