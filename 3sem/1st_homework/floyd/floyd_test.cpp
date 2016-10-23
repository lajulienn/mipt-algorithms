#include "floyd.h"

#include <vector>

#include "gtest/gtest.h"

using graph_t = std::vector<std::vector<int>>;

TEST(FloydTest, Trivial) {
    EXPECT_EQ(graph_t({{0, 0}, {0, 0}}), floyd(graph_t({{0, 0}, {0, 0}})));
}

TEST(FloydTest, Complicated) {
    graph_t graph{{0, 5, 9, 100}, {100, 0, 2, 8}, {100, 100, 0, 7}, {4, 100, 100, 0}};
    graph_t answer{{0, 5, 7, 13}, {12, 0, 2, 8}, {11, 16, 0, 7}, {4, 9, 11, 0}};
    EXPECT_EQ(answer, floyd(graph));
}
