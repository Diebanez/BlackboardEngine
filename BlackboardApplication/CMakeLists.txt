file(GLOB BlackboardApplication_SRC "src/*.h" "src/*.cpp")

add_executable(BlackboardApplication ${BlackboardApplication_SRC})

target_link_libraries(BlackboardApplication LINK_PUBLIC BlackboardRuntime)