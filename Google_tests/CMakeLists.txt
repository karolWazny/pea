project(Google_tests)
#add_subdirectory(lib)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run
        InitialTest.cpp
        TSPInputMatrixTest.cpp
        FileReaderTest.cpp
        BruteForceTest.cpp DynamicProgrammingTest.cpp BnBTest.cpp mathTest.cpp treeTest.cpp listTest.cpp ffarrayTest.cpp AtspCompareTests.cpp SimulatedAnnealingTest.cpp tabuSearchTest.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main tspalgorithms program)