cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 23)
set(GOOGLE_TEST_SOURCE "GoogleTest/googletest-1.14.0")
set(TARGET "ADTEHashing")

project(${TARGET})

add_subdirectory(${GOOGLE_TEST_SOURCE})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(${TARGET} main.cpp HopScochHasher/HopScotchHasher.hpp HopScochHasher/HopScotchHasherCore.inl HopScochHasher/HopScotchHasherInter.inl ExtendibleHasher/ExtendibleHasher.hpp)
target_link_libraries(${TARGET} gtest gtest_main)

