#include <gtest/gtest.h>
#include "../bigraph.h"

TEST(bigraph, Check_set_edge){
  BiGraph g;
  g.set_edge(1, 2, 10);
}

TEST(bigraph, Check_get_adj_size_exist){
  BiGraph g;
  g.set_edge(1, 2, 10);
  g.set_edge(1, 2, 20);
  g.set_edge(1, 3, 10);
  g.set_edge(1, 4, 10);
  g.set_edge(5, 6, 10);
  g.set_edge(5, 7, 10);
  g.set_edge(5, 2, -100);
  EXPECT_EQ(3, g.get_adj_size(1));
  EXPECT_EQ(2, g.get_adj_size(2));
  EXPECT_EQ(1, g.get_adj_size(3));
  EXPECT_EQ(1, g.get_adj_size(4));
  EXPECT_EQ(3, g.get_adj_size(5));
  EXPECT_EQ(1, g.get_adj_size(6));
  EXPECT_EQ(1, g.get_adj_size(7));
}

TEST(bigraph, Check_get_adj_size_empty){
  BiGraph g;
  EXPECT_EQ(0, g.get_adj_size(100));
  EXPECT_EQ(0, g.get_adj_size(-10000));
  EXPECT_EQ(0, g.get_adj_size(0));
}


int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
