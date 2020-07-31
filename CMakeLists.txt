cmake_minimum_required (VERSION 3.16)

project(BlackboardEngine)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(./Vendor/glm)
add_subdirectory(./Vendor/spdlog)
add_subdirectory(./Vendor/glad)
add_subdirectory(./Vendor/glfw)
add_subdirectory(./BlackboardRuntime)
add_subdirectory(./BlackboardEditor)
add_subdirectory(./BlackboardApplication)