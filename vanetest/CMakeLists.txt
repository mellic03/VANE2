project(testgame)

# set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output)

add_executable(
    ${PROJECT_NAME} main.cpp
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${VANE_INCPATH}
)
target_compile_features(
    ${PROJECT_NAME} PUBLIC cxx_std_23
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC vane
)

