file(GLOB BlackboardRuntime_SRC "src/*.h" "src/*.cpp")

add_library(BlackboardRuntime ${BlackboardRuntime_SRC})

target_include_directories(BlackboardRuntime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ../Vendor/spdlog/include/spdlog)
target_link_libraries(BlackboardRuntime spdlog)