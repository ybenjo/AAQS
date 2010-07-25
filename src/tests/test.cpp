#include <gtest/gtest.h>
#include "./base_tests.cpp"
#include "./cohits_tests.cpp"
#include "./hitting_time_tests.cpp"
#include "./rwr_tests.cpp"

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
