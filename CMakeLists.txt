# Assuming this your tests/CMakeLists.txt (and your libs are setup in a root config)
# Just make sure to include(CTest) in your *root* cmake config.

# 3.9 adds support for "GoogleTest" which enumerates the tests inside
# of the code and adds them to ctest.
cmake_minimum_required(VERSION 3.9)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# Configure google-test as a downloadable library.
include(External_GTest.cmake)

add_library(lineales INTERFACE)
add_library(arbin INTERFACE)
add_library(dict INTERFACE)

# 08lineales/cola 08lineales/dcola 08lineales/pila
target_include_directories(lineales INTERFACE 08lineales/lista/nodos_doblemente_enlazados 08lineales/pila/nodos_enlazados 08lineales/cola/nodos_enlazados)
target_include_directories(arbin INTERFACE 09arboles/arbol_binario)
target_include_directories(dict INTERFACE 10diccionarios/arbol_busqueda 10diccionarios/hash_table 10diccionarios/hash 08lineales/pila/nodos_enlazados)

add_executable(testLineales 08lineales/test.cpp)
add_executable(testArboles 09arboles/test.cpp)
add_executable(testDiccionarios 10diccionarios/test.cpp)
add_executable(testAplicaciones 11aplicaciones/test.cpp)

add_executable(c06 09arboles/c06/c06.cpp)
add_executable(c07 09arboles/c07/c07.cpp)
add_executable(c08 10diccionarios/c08/c08.cpp)

# This will automatically handle all of the lib linkage and include dirs
target_link_libraries(testLineales ${GTEST_LIBRARY} lineales)
target_link_libraries(testArboles ${GTEST_LIBRARY} arbin)
target_link_libraries(testDiccionarios ${GTEST_LIBRARY} dict lineales)
target_link_libraries(testAplicaciones ${GTEST_LIBRARY} arbin dict lineales)
# target_link_libraries(testExamenes ${GTEST_LIBRARY})

target_link_libraries(c06 arbin)
target_link_libraries(c07 arbin)
target_link_libraries(c08 lineales dict)

# Tell ctest about my tests
enable_testing()
include(GoogleTest)
gtest_add_tests(
    TARGET      testLineales
    TEST_LIST   myTests_targets
)

gtest_add_tests(
    TARGET  testArboles
    TEST_LIST   myTests_targets
)

gtest_add_tests(
    TARGET  testDiccionarios
    TEST_LIST myTests_targets
)

gtest_add_tests(
    TARGET testAplicaciones
    TEST_LIST myTests_targets
)

file(GLOB_RECURSE files "12examenes/*/test.cpp")
foreach (file ${files})
    string(REPLACE "/test.cpp" "" folder ${file})
    string(REPLACE "${CMAKE_SOURCE_DIR}/12examenes/" "" testname ${folder})
    string(REPLACE "/" "_" testname E${testname})
    message("F: ${file}, T: ${testname}")
    set(testTarget test${testname})

    file(GLOB everything ${folder}/*.h ${folder}/*.cpp)
    list(REMOVE_ITEM everything ${folder}/main.cpp)
    add_executable(${testTarget} ${everything})
    target_link_libraries(${testTarget} ${GTEST_LIBRARY})
    gtest_add_tests(
        TARGET ${testTarget}
        TEST_LIST tests_examen
        TEST_PREFIX ${testname}.
    )
endforeach(file ${files})

file(GLOB_RECURSE files "12examenes/*/main.cpp")
foreach (file ${files})
    string(REPLACE "/main.cpp" "" folder ${file})
    string(REPLACE "${CMAKE_SOURCE_DIR}/12examenes/" "" targetName ${folder})
    string(REPLACE "/" "_" targetName E${targetName})

    file(GLOB everything ${folder}/*.h ${folder}/*.cpp)
    list(REMOVE_ITEM everything ${folder}/test.cpp)
    add_executable(${targetName} ${everything})
endforeach(file ${files})

# set each target to timeout if not finished within 10 sec
set_tests_properties(${myTests_targets} PROPERTIES TIMEOUT 5)
set_tests_properties(${test_examen} PROPERTIES TIMEOUT 5)