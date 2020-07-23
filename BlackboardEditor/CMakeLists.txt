add_executable(BlackboardEditor ./src/main.cpp)

target_link_libraries(BlackboardEditor LINK_PUBLIC BlackboardRuntime)