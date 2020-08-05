file(GLOB BlackboardEditor_SRC "src/*.h" "src/*.cpp")

add_executable(BlackboardEditor ${BlackboardEditor_SRC})

set_property(TARGET BlackboardEditor PROPERTY CXX_STANDARD 17)

target_link_libraries(BlackboardEditor LINK_PUBLIC BlackboardRuntime)