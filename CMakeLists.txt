cmake_minimum_required(VERSION 3.10)
project(CG-pc2-tests)

# Añadir Google Test
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Ejecutable de prueba para exercise01
set(SRC1_FILES ../exercise01/solution.cpp ../exercise01/test.cpp)
add_executable(runTests1 ${SRC1_FILES})
target_link_libraries(runTests1 gtest gtest_main)

# Ejecutable de prueba para exercise02
set(SRC1_FILES ../exercise02/solution.cpp ../exercise02/test.cpp)
add_executable(runTests2 ${SRC1_FILES})
target_link_libraries(runTests2 gtest gtest_main)

# Ejecutable de prueba para exercise02
set(SRC1_FILES ../exercise03/solution.cpp ../exercise03/test.cpp)
add_executable(runTests3 ${SRC1_FILES})
target_link_libraries(runTests3 gtest gtest_main)


