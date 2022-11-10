add_executable(
  test
  Test.cpp
)
target_link_libraries(
  test
  GTest::gtest_main
  server
  client
)

include(GoogleTest)
gtest_discover_tests(test)