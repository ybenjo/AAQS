#include <gtest/gtest.h>
#include "../bigraph.h"

// TEST(bigraph, Check_exit_failure){
//   BiGraph g;
//   g.set_edge("1", "1", "100");
// }

TEST(bigraph, Check_get_adj_size_exist){
  BiGraph g;
  g.set_edge("1", "2", 10);
  g.set_edge("1", "2", 20);
  g.set_edge("1", "3", 10);
  g.set_edge("1", "4", 10);
  g.set_edge("5", "6", 10);
  g.set_edge("5", "7", 10);
  g.set_edge("5", "2", -100);
  EXPECT_EQ(3, g.get_adj_size("1"));
  EXPECT_EQ(2, g.get_adj_size("2"));
  EXPECT_EQ(1, g.get_adj_size("3"));
  EXPECT_EQ(1, g.get_adj_size("4"));
  EXPECT_EQ(3, g.get_adj_size("5"));
  EXPECT_EQ(1, g.get_adj_size("6"));
  EXPECT_EQ(1, g.get_adj_size("7"));
}

TEST(bigraph, Check_get_adj_size_empty){
  BiGraph g;
  EXPECT_EQ(0, g.get_adj_size("100"));
  EXPECT_EQ(0, g.get_adj_size("-10000"));
  EXPECT_EQ(0, g.get_adj_size("0"));
}

TEST(bigraph, Check_get_raw_weight_exist){
  BiGraph g;
  g.set_edge("1", "2", 10);
  g.set_edge("1", "3", 10);
  EXPECT_EQ(10, g.get_raw_weight("1", "2"));
  EXPECT_EQ(10, g.get_raw_weight("2", "1"));
  EXPECT_EQ(10, g.get_raw_weight("1", "3"));
  EXPECT_EQ(10, g.get_raw_weight("3", "1"));
  EXPECT_EQ(0, g.get_raw_weight("2", "3"));
  EXPECT_EQ(0, g.get_raw_weight("3", "2"));
}

TEST(bigraph, Check_get_raw_weight_empty){
  BiGraph g;
  EXPECT_EQ(0, g.get_raw_weight("100", "200"));
  EXPECT_EQ(0, g.get_raw_weight("200", "100"));
}


TEST(bigraph, Check_set_prob_1){
  BiGraph g;
  g.set_edge("1", "2", 1);
  g.set_edge("1", "3", 1);
  g.set_prob();
  EXPECT_EQ(0.5, g.get_prob("1", "2"));
  EXPECT_EQ(0.5, g.get_prob("1", "3"));
  EXPECT_EQ(1, g.get_prob("2", "1"));
  EXPECT_EQ(1, g.get_prob("3", "1"));
}

class TestBiGraph : public ::testing::Test{
protected:
  void SetUp()
  { 
    std::cout << "TestBiGraph::SetUp" << std::endl;
    g.set_edge("1", "2", 2);
    g.set_edge("1", "3", 3);
    g.set_edge("1", "4", 4);
    g.set_prob();
  }
  void TearDown()
  { 
    std::cout << "TestBiGraph::TearDown" << std::endl;
  }
  BiGraph g;
};

TEST_F(TestBiGraph, Check_set_weight_2){
  EXPECT_DOUBLE_EQ(2/9.0, g.get_prob("1", "2"));
  EXPECT_DOUBLE_EQ(3/9.0, g.get_prob("1", "3"));
  EXPECT_DOUBLE_EQ(4/9.0, g.get_prob("1", "4"));
  EXPECT_DOUBLE_EQ(1, g.get_prob("2", "1"));
  EXPECT_DOUBLE_EQ(1, g.get_prob("3", "1"));
  EXPECT_DOUBLE_EQ(1, g.get_prob("4", "1"));
}

TEST_F(TestBiGraph, Check_set_init_score){
  g.set_init_score();
  EXPECT_DOUBLE_EQ(1, g.get_score_u("1"));
  EXPECT_DOUBLE_EQ(1/3.0, g.get_score_v("2"));
  EXPECT_DOUBLE_EQ(1/3.0, g.get_score_v("3"));
  EXPECT_DOUBLE_EQ(1/3.0, g.get_score_v("4"));
}

TEST_F(TestBiGraph, Check_score_validation){
  g.set_init_score();
  EXPECT_DOUBLE_EQ(1.0, g.calc_validation("1"));
  EXPECT_DOUBLE_EQ(1.0, g.calc_validation("2"));
  EXPECT_DOUBLE_EQ(1.0, g.calc_validation("3"));
  EXPECT_DOUBLE_EQ(1.0, g.calc_validation("4"));
}

TEST_F(TestBiGraph, Check_score_propagation_1step){
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

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
