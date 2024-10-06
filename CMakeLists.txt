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

# Ejecutable de prueba para exercise03
set(SRC1_FILES ../exercise03/solution.cpp ../exercise03/test.cpp)
add_executable(runTests3 ${SRC1_FILES})
target_link_libraries(runTests3 gtest gtest_main)

# Ejecutable de prueba para exercise04
set(SRC1_FILES ../exercise04/solution.cpp ../exercise04/test.cpp)
add_executable(runTests4 ${SRC1_FILES})
target_link_libraries(runTests4 gtest gtest_main)

# Ejecutable de prueba para exercise05
set(SRC1_FILES ../exercise05/solution.cpp ../exercise05/test.cpp)
add_executable(runTests5 ${SRC1_FILES})
target_link_libraries(runTests5 gtest gtest_main)

# Ejecutable de prueba para exercise07
set(SRC1_FILES ../exercise07/solution.cpp ../exercise07/test.cpp)
add_executable(runTests7 ${SRC1_FILES})
target_link_libraries(runTests7 gtest gtest_main)

# Ejecutable de prueba para exercise08
set(SRC1_FILES ../exercise08/solution.cpp ../exercise08/test.cpp)
add_executable(runTests8 ${SRC1_FILES})
target_link_libraries(runTests8 gtest gtest_main)

# Ejecutable de prueba para exercise10
set(SRC1_FILES ../exercise10/solution.cpp ../exercise10/test.cpp)
add_executable(runTests10 ${SRC1_FILES})
target_link_libraries(runTests10 gtest gtest_main)

# Ejecutable de prueba para exercise11
set(SRC1_FILES ../exercise11/solution.cpp ../exercise11/test.cpp)
add_executable(runTests11 ${SRC1_FILES})
target_link_libraries(runTests11 gtest gtest_main)

# Ejecutable de prueba para exercise12
set(SRC1_FILES ../exercise12/solution.cpp ../exercise12/test.cpp)
add_executable(runTests12 ${SRC1_FILES})
target_link_libraries(runTests12 gtest gtest_main)


