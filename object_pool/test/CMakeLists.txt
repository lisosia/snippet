# Add souce dir as include path
include_directories(../src)

# Add the executable for the testcase which is using googletest
add_executable(test_objpool test_object_pool.cpp)
target_link_libraries(test_objpool GTest::GTest GTest::Main)

# Add the test case use the gtest feature.
gtest_discover_tests(test_objpool)