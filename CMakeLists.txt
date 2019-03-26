cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()
 
# Link runTests with what we want to test and the GTest and pthread library
file(GLOB_RECURSE test_SRC "*test.cpp")
set(test_SRC
    "09arboles/test"
)

foreach(test IN LISTS test_SRC)
    message(STATUS ${test})
    add_executable(${test}.out ${test}.cpp)
    target_link_libraries(${test}.out ${GTEST_LIBRARIES} pthread)
    add_test( ${test} ${test}.out ) 
endforeach()