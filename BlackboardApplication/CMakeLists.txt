file(GLOB BlackboardApplication_SRC "src/*.h" "src/*.cpp")

add_executable(BlackboardApplication ${BlackboardApplication_SRC})

if(UNIX AND NOT APPLE)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

target_link_libraries(BlackboardApplication LINK_PUBLIC BlackboardRuntime)
