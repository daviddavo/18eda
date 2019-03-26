cmake_minimum_required(VERSION 2.6)

# Locate GTest
# find_package(GTest REQUIRED)
# find_package(Threads REQUIRED)

include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)


# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")

# include_directories(${GTEST_INCLUDE_DIRS})
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