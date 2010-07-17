#include <gtest/gtest.h>
#include "../cohits.h"

class TestCoHITS : public ::testing::Test{
protected:
  void SetUp()
  { 
    std::cout << "TestCoHITS::SetUp" << std::endl;
    g.set_edge("1", "2", 2);
    g.set_edge("1", "3", 3);
    g.set_edge("1", "4", 4);
    g.set_prob();
  }
  void TearDown()
  { 
    std::cout << "TestCoHITS::TearDown" << std::endl;
  }
  CoHITS g;
};

TEST_F(TestCoHITS, Check_set_init_score){
  g.set_init_score();
  EXPECT_DOUBLE_EQ(1, g.get_score_u("1"));
  EXPECT_DOUBLE_EQ(1/3.0, g.get_score_v("2"));
  EXPECT_DOUBLE_EQ(1/3.0, g.get_score_v("3"));
  EXPECT_DOUBLE_EQ(1/3.0, g.get_score_v("4"));
}

TEST_F(TestCoHITS, Check_score_validation){
  g.set_init_score();
  EXPECT_DOUBLE_EQ(1.0, g.calc_validation("1"));
  EXPECT_DOUBLE_EQ(1.0, g.calc_validation("2"));
  EXPECT_DOUBLE_EQ(1.0, g.calc_validation("3"));
  EXPECT_DOUBLE_EQ(1.0, g.calc_validation("4"));
}

TEST_F(TestCoHITS, Check_score_propagation_1step){
  g.set_init_score();
  g.set_parameter(0.5, 0.5);
  g.propagate();
  double v2 = g.get_score_v("2");
  double v3 = g.get_score_v("3");
  double v4 = g.get_score_v("4");
  EXPECT_DOUBLE_EQ(1, g.get_score_u("1"));
  EXPECT_DOUBLE_EQ(5/18.0, v2);
  EXPECT_DOUBLE_EQ(1/3.0, v3);
  EXPECT_DOUBLE_EQ(7/18.0, v4);
  EXPECT_DOUBLE_EQ(1.0, v2 + v3 + v4);
}
