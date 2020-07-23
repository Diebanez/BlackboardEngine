file(GLOB BlackboardEditor_SRC "src/*.h" "src/*.cpp")

add_executable(BlackboardEditor ${BlackboardEditor_SRC})

target_link_libraries(BlackboardEditor LINK_PUBLIC BlackboardRuntime)