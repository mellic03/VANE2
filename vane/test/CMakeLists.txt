cmake_minimum_required(VERSION 3.28)

project(vanetest CXX)
add_executable(
    ${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC "$ENV{VANE_INCLUDE_DIR}"
)
target_compile_features(
    ${PROJECT_NAME} PUBLIC cxx_std_23
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC vane
)

