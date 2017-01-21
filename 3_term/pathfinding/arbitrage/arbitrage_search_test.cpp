#include "arbitrage_search.h"

#include <vector>

#include "gtest/gtest.h"

TEST(FindCycleTest, Trivial) {
    auto rates1 = std::vector<ExchangeRate>{};
    EXPECT_EQ(false, FindCycle(0, 1, rates1));
    auto rates2 = std::vector<ExchangeRate>{{0, 0, 2.0F}};
    EXPECT_EQ(true, FindCycle(0, 1, rates2));
}

TEST(FindCycleTest, Existing) {
    auto rates1 = std::vector<ExchangeRate>{{0, 1, 1.0F}, {1, 0, 2.0F}};
    EXPECT_EQ(true, FindCycle(0, 2, rates1));
    auto rates2 = std::vector<ExchangeRate>{{0, 1, 2.0F}, {1, 0, 0.75F}};
    EXPECT_EQ(true, FindCycle(0, 2, rates2));
}

TEST(FindCycleTest, Neutral) {
    auto rates = std::vector<ExchangeRate>{{0, 1, 0.5F}, {1, 0, 2.0F}};
    EXPECT_EQ(false, FindCycle(0, 1, rates));
}
