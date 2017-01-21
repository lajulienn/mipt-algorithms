#include "permutation.h"

#include <vector>

#include "gtest/gtest.h"

class PermutationTest : public ::testing::Test {
 protected:
  PermutationTest()
      : solved_({{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}),
      example_({{0, 1, 6}, {4, 3, 2}, {7, 5, 8}}),
      unsolvable_({{1, 2, 3}, {4, 5, 6}, {8, 7, 0}}),
      simple_({{1, 2, 3}, {4, 5, 6}, {7, 0, 8}}),
      longest_({{6, 4, 7}, {8, 5, 0}, {3, 2, 1}}) {}

  Permutation solved_;
  Permutation example_;
  Permutation unsolvable_;
  Permutation simple_;
  Permutation longest_;
};

TEST_F(PermutationTest, IsSovlable) {
    EXPECT_EQ(true, solved_.IsSolvable());
    EXPECT_EQ(true, example_.IsSolvable());
    EXPECT_EQ(false, unsolvable_.IsSolvable());
    EXPECT_EQ(true, simple_.IsSolvable());
    EXPECT_EQ(true, longest_.IsSolvable());
}

TEST_F(PermutationTest, Heuristic) {
    EXPECT_GE(0, solved_.GetHeuristic());
    EXPECT_GE(8, example_.GetHeuristic());
    EXPECT_GE(1, simple_.GetHeuristic());
    EXPECT_GE(31, longest_.GetHeuristic());
}

TEST_F(PermutationTest, Solution) {
    EXPECT_EQ("", solved_.GetSolution());
    EXPECT_EQ("RDRULDDR", example_.GetSolution());
    EXPECT_EQ("R", simple_.GetSolution());
    EXPECT_EQ("DLUURDDLLURULDRURDLDRULDLUURRDD", longest_.GetSolution());
}
