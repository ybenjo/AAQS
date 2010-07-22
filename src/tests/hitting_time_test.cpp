// class TestSubBiGraph : public ::testing::Test{
// protected:
//   void SetUp()
//   { 
//     std::cout << "TestSubBiGraph::SetUp" << std::endl;
//     g.set_edge("a", "1", 1);
//     g.set_edge("a", "2", 1);
//     g.set_edge("a", "3", 1);
//     g.set_edge("b", "2", 1);
//     g.set_edge("b", "4", 1);
//   }
//   void TearDown()
//   { 
//     std::cout << "TestSubBiGraph::TearDown" << std::endl;
//   }
//   BiGraph g;
// };

TEST_F(TestSubBiGraph, check_hitting_one_random_walk){
  g.set_prob();
}
