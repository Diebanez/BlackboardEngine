file(GLOB BlackboardApplication_SRC "src/*.h" "src/*.cpp")

add_executable(BlackboardApplication ${BlackboardApplication_SRC})

set_property(TARGET BlackboardApplication PROPERTY CXX_STANDARD 17)

target_link_libraries(BlackboardApplication LINK_PUBLIC BlackboardRuntime)