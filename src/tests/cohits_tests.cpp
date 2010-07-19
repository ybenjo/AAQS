class TestCoHITS : public ::testing::Test{
protected:
  void SetUp()
  { 
    std::cout << "TestCoHITS::SetUp" << std::endl;
    g.set_edge("a", "2", 2);
    g.set_edge("a", "3", 3);
    g.set_edge("a", "4", 4);
    g.set_edge("b", "4", 5);
    g.set_edge("b", "5", 6);
    g.set_prob();
    g.cohits_set_init_score();
  }
  void TearDown()
  { 
    std::cout << "TestCoHITS::TearDown" << std::endl;
  }
  BiGraph g;
};

TEST_F(TestCoHITS, Check_set_weight_2){
  EXPECT_DOUBLE_EQ(2/9.0, g.get_prob("a", "2"));
  EXPECT_DOUBLE_EQ(3/9.0, g.get_prob("a", "3"));
  EXPECT_DOUBLE_EQ(4/9.0, g.get_prob("a", "4"));
  EXPECT_DOUBLE_EQ(5/11.0, g.get_prob("b", "4"));
  EXPECT_DOUBLE_EQ(6/11.0, g.get_prob("b", "5"));
  EXPECT_DOUBLE_EQ(1, g.get_prob("2", "a"));
  EXPECT_DOUBLE_EQ(1, g.get_prob("3", "a"));
  EXPECT_DOUBLE_EQ(4/9.0, g.get_prob("4", "a"));
  EXPECT_DOUBLE_EQ(5/9.0, g.get_prob("4", "b"));
  EXPECT_DOUBLE_EQ(1, g.get_prob("5", "b"));
}


TEST_F(TestCoHITS, Check_set_init_score){
  EXPECT_DOUBLE_EQ(0.5, g.get_score_u("a"));
  EXPECT_DOUBLE_EQ(0.5, g.get_score_u("b"));
  EXPECT_DOUBLE_EQ(1/4.0, g.get_score_v("2"));
  EXPECT_DOUBLE_EQ(1/4.0, g.get_score_v("3"));
  EXPECT_DOUBLE_EQ(1/4.0, g.get_score_v("4"));
  EXPECT_DOUBLE_EQ(1/4.0, g.get_score_v("5"));
}

TEST_F(TestCoHITS, Check_score_validation){
  EXPECT_DOUBLE_EQ(1.0, g.cohits_calc_validation("a"));
  EXPECT_DOUBLE_EQ(1.0, g.cohits_calc_validation("b"));
  EXPECT_DOUBLE_EQ(1.0, g.cohits_calc_validation("2"));
  EXPECT_DOUBLE_EQ(1.0, g.cohits_calc_validation("3"));
  EXPECT_DOUBLE_EQ(1.0, g.cohits_calc_validation("4"));
  EXPECT_DOUBLE_EQ(1.0, g.cohits_calc_validation("5"));
}

TEST_F(TestCoHITS, Check_score_propagation_1step){
 g.cohits_set_parameter(0.9, 0.1);
 g.cohits_one_propagate();

 double ua = g.get_score_u("a");
 double ub = g.get_score_u("b");
 
 double v2 = g.get_score_v("2");
 double v3 = g.get_score_v("3");
 double v4 = g.get_score_v("4");
 double v5 = g.get_score_v("5");
 EXPECT_DOUBLE_EQ((3/5.0), ua);
 EXPECT_DOUBLE_EQ((2/5.0), ub);
 EXPECT_DOUBLE_EQ(1, ua + ub);
 EXPECT_DOUBLE_EQ((143/600.0), v2);
 EXPECT_DOUBLE_EQ((49/200.0), v3);
 EXPECT_DOUBLE_EQ((1781/6600.0), v4);
 EXPECT_DOUBLE_EQ((543/2200.0), v5);
 EXPECT_DOUBLE_EQ(1, v2 + v3 + v4 + v5);
}
