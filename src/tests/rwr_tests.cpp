class TestRWR : public ::testing::Test{
protected:
  void SetUp()
  { 
    std::cout << "TestRWR::SetUp" << std::endl;
    g.set_edge("a", "2", 2);
    g.set_edge("a", "3", 3);
    g.set_edge("a", "4", 4);
    g.set_edge("b", "4", 5);
    g.set_edge("b", "5", 6);
    g.set_prob();
  }
  void TearDown()
  { 
    std::cout << "TestRWR::TearDown" << std::endl;
  }
  BiGraph g;
};

TEST_F(TestRWR, Check_rwr_one_random_walk){
  id_type query  = "a";
  double damping  = 0.5;
  g.rwr_set_init(query, damping);
  g.rwr_one_random_walk(query);
  cout << "1st random walk." << endl;
  EXPECT_DOUBLE_EQ(0.5, g.rwr_get_score("a"));
  EXPECT_DOUBLE_EQ(0.0, g.rwr_get_score("b"));
  EXPECT_DOUBLE_EQ(0.5, g.rwr_get_score("2"));
  EXPECT_DOUBLE_EQ(0.5, g.rwr_get_score("3"));
  EXPECT_DOUBLE_EQ(2/9.0, g.rwr_get_score("4"));
  EXPECT_DOUBLE_EQ(0.0, g.rwr_get_score("5"));
}
