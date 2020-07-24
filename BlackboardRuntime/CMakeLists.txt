file(GLOB BlackboardRuntime_SRC "src/*.h" "src/*.cpp" "src/Core/*.h" "src/Core/*.cpp" "src/Events/*.h" "src/Events/*.cpp" "src/Input/*.h" "src/Input/*.cpp")

add_library(BlackboardRuntime ${BlackboardRuntime_SRC})

target_include_directories(BlackboardRuntime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ../Vendor/spdlog/include/spdlog)
target_link_libraries(BlackboardRuntime spdlog)