project(vanetest)

add_executable(
    ${PROJECT_NAME} main.cpp
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${VANE_INCLUDE_DIR}
)
target_compile_features(
    ${PROJECT_NAME} PUBLIC cxx_std_23
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC vane
)

