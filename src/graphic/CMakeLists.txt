AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} GRAPHIC_SRCS)
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/render RENDER_SRCS)

MESSAGE(${GRAPHIC_SRCS})
MESSAGE(${RENDER_SRCS})

add_library(graphic 
            ${GRAPHIC_SRCS}
            ${RENDER_SRCS})

target_link_libraries(graphic
                math
                hardwarebuffer
                object
                
)       

            