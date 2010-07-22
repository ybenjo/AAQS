class TestHittingBiGraph : public ::testing::Test{
protected:
  void SetUp()
  { 
    std::cout << "TestHittingBiGraph::SetUp" << std::endl;
    g.set_edge("a", "1", 1);
    g.set_edge("a", "2", 1);
    g.set_edge("a", "3", 1);
    g.set_edge("b", "2", 1);
    g.set_edge("b", "4", 1);
  }
  void TearDown()
  { 
    std::cout << "TestHittingBiGraph::TearDown" << std::endl;
  }
  BiGraph g;
};

TEST_F(TestHittingBiGraph, check_set_hitting_prob){
  g.set_prob();
  g.set_hitting_prob();
  EXPECT_DOUBLE_EQ(5/6.0, g.get_hitting_prob("a","a"));
  EXPECT_DOUBLE_EQ(1/6.0, g.get_hitting_prob("a","b"));
  EXPECT_DOUBLE_EQ(3/4.0, g.get_hitting_prob("b","b"));
  EXPECT_DOUBLE_EQ(1/4.0, g.get_hitting_prob("b","a"));
}

TEST_F(TestHittingBiGraph, check_hitting_one_random_walk){
  g.set_prob();
  g.set_hitting_prob();
  cout << "1st random walk" << endl;
  g.hitting_one_random_walk("a");
  EXPECT_DOUBLE_EQ(1, g.hitting_get_hitting_score("a"));
  EXPECT_DOUBLE_EQ(1, g.hitting_get_hitting_score("b"));
  cout << "2nd random walk" << endl;
  g.hitting_one_random_walk("a");
  EXPECT_DOUBLE_EQ(1 + 1/6.0, g.hitting_get_hitting_score("a"));
  EXPECT_DOUBLE_EQ(3/4.0 + 1, g.hitting_get_hitting_score("b"));
}
