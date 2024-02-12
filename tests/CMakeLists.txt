add_executable(test_trader ${SRC_FILES} test_trader.cpp)
target_include_directories(test_trader PUBLIC ${CMAKE_SOURCE_DIR}/extern/catch2 ${CMAKE_SOURCE_DIR}/src)
add_test(NAME test_trader COMMAND test_trader)
