file(GLOB BlackboardApplication_SRC "src/*.h" "src/*.cpp")

add_executable(BlackboardApplication ${BlackboardApplication_SRC})

set_target_properties(BlackboardApplication PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)

target_link_libraries(BlackboardApplication LINK_PUBLIC BlackboardRuntime)