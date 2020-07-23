add_library(BlackboardRuntime ./src/Application.cpp)

target_include_directories(BlackboardRuntime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)