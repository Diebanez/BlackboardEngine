file(GLOB BlackboardApplication_SRC "src/*.h" "src/*.cpp")

add_executable(BlackboardApplication ${BlackboardApplication_SRC})

if(UNIX AND NOT APPLE)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

add_custom_command(TARGET BlackboardApplication POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/BlackboardApplication/assets $<TARGET_FILE_DIR:BlackboardApplication>/assets)

target_link_libraries(BlackboardApplication LINK_PUBLIC BlackboardRuntime)
