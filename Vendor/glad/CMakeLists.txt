file(GLOB Glad_SRC "./include/KHR/*.h" "./include/glad/glad.h" "./src/glad.c")

add_library(glad ${Glad_SRC})

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR/include})