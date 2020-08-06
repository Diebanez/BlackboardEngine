file(GLOB BlackboardRuntime_SRC
        "src/*.h" "src/*.cpp"
        "src/Core/*.h" "src/Core/*.cpp"
        "src/Events/*.h" "src/Events/*.cpp"
        "src/Input/*.h" "src/Input/*.cpp"
        "src/Rendering/*.h" "src/Rendering/*.cpp"
        "src/Rendering/Buffers/*.h" "src/Rendering/Buffers/*.cpp"
        "src/Resources/*.h" "src/Resources/*.cpp"
        "src/Platform/OpenGL/*.h" "src/Platform/OpenGL/*.cpp"
        "src/Platform/Windows/*.h" "src/Platform/Windows/*.cpp"
        "src/Platform/Linux/*.h" "src/Platform/Linux/*.cpp"
        "src/Rendering/Camera/*.h" "src/Rendering/Camera/*.cpp")

add_library(BlackboardRuntime ${BlackboardRuntime_SRC})

if(UNIX AND NOT APPLE)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif()

if(WIN32)
	add_definitions(-DBB_WINDOWS_PLATFORM)
elseif(UNIX AND NOT APPLE)
	add_definitions(-DBB_LINUX_PLATFORM)
else()
	message(FATAL_ERROR "Platform not supported")
endif()

find_package(OpenGL REQUIRED)


target_include_directories(BlackboardRuntime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ../Vendor/spdlog/include/spdlog ../Vendor/glad/include ../Vendor/glfw/include ../Vendor/glm)

if(WIN32)
	target_link_libraries(BlackboardRuntime OpenGL::GL spdlog glad glfw)
elseif(UNIX AND NOT APPLE)
	target_link_libraries(BlackboardRuntime GL GLU spdlog glad glfw)
else()
	message(FATAL_ERROR "Platform not supported")
endif()


