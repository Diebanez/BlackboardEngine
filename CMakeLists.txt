cmake_minimum_required (VERSION 3.16)

project(BlackboardEngine)

add_subdirectory(./Vendor/spdlog)
add_subdirectory(./Vendor/glad)
add_subdirectory(./BlackboardRuntime)
add_subdirectory(./BlackboardEditor)
add_subdirectory(./BlackboardApplication)