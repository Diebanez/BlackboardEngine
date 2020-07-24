file(GLOB BlackboardRuntime_SRC
        "src/*.h" "src/*.cpp"
        "src/Core/*.h" "src/Core/*.cpp"
        "src/Events/*.h" "src/Events/*.cpp"
        "src/Input/*.h" "src/Input/*.cpp"
        "src/Rendering/*.h" "src/Rendering/*.cpp"
        "src/Rendering/Buffers/*.h" "src/Rendering/Buffers/*.cpp"
        "src/Resources/*.h" "src/Resources/*.cpp"
        "src/Platform/OpengGL/*.h" "src/Platform/OpengGL/*.cpp"
        "src/Platform/Windows/*.h" "src/Platform/Windows/*.cpp")

add_library(BlackboardRuntime ${BlackboardRuntime_SRC})

target_include_directories(BlackboardRuntime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ../Vendor/spdlog/include/spdlog../Vendor/glad/include)
target_link_libraries(BlackboardRuntime spdlog glad)