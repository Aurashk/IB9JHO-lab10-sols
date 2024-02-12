# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProgram)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra)

set(SRC_FILES ${CMAKE_SOURCE_DIR}/src/Asset.cpp ${CMAKE_SOURCE_DIR}/src/MarketSimulation.cpp ${CMAKE_SOURCE_DIR}/src/Trader.cpp)
add_executable(my_program ${SRC_FILES} ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(my_program m)

####################### TESTING STUFF STARTS HERE ###########################################################

enable_testing()
add_subdirectory(tests)