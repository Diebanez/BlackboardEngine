file(GLOB BlackboardEditor_SRC "src/*.h" "src/*.cpp")

add_executable(BlackboardEditor ${BlackboardEditor_SRC})

set_target_properties(BlackboardEditor PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF)

target_link_libraries(BlackboardEditor LINK_PUBLIC BlackboardRuntime)