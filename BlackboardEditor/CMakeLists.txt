file(GLOB BlackboardEditor_SRC "src/*.h" "src/*.cpp")

add_executable(BlackboardEditor ${BlackboardEditor_SRC})

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

target_link_libraries(BlackboardEditor LINK_PUBLIC BlackboardRuntime)
