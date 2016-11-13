/**
 * @author Julia Ivanova
 */

#include "include/flow_network.h"

#include "gtest/gtest.h"

class FlowNetworkTest : public ::testing::Test {
protected:
    FlowNetworkTest()
            : trivial_(0, 1, 2),
              not_so_trivial_(0, 2, 3),
              example_(0, 3, 4) {}

    FlowNetwork trivial_;
    FlowNetwork not_so_trivial_;
    FlowNetwork example_;
};

TEST_F(FlowNetworkTest, TrivialMaxFlowSearch) {
    trivial_.AddEdge(0, 1, 42);
    trivial_.AddEdge(1, 0, 42);
    EXPECT_EQ(42, trivial_.MaxFlowSearch());
}

TEST_F(FlowNetworkTest, TrivialMinCut) {
    std::vector<int> answer;
    answer.push_back(0);

    trivial_.AddEdge(0, 1, 42);
    trivial_.AddEdge(1, 0, 42);
    trivial_.MaxFlowSearch();
    EXPECT_EQ(answer, trivial_.MinimalCut());
}

TEST_F(FlowNetworkTest, NotSoTrivialMaxFlowSearch) {
    not_so_trivial_.AddEdge(0, 1, 42);
    not_so_trivial_.AddEdge(1, 0, 42);
    not_so_trivial_.AddEdge(1, 2, 24);
    not_so_trivial_.AddEdge(2, 1, 24);
    EXPECT_EQ(24, not_so_trivial_.MaxFlowSearch());
}

TEST_F(FlowNetworkTest, NotSoTrivialMinCut) {
    std::vector<int> answer;
    answer.push_back(0);
    answer.push_back(1);

    not_so_trivial_.AddEdge(0, 1, 42);
    not_so_trivial_.AddEdge(1, 0, 42);
    not_so_trivial_.AddEdge(1, 2, 24);
    not_so_trivial_.AddEdge(2, 1, 24);
    not_so_trivial_.MaxFlowSearch();
    EXPECT_EQ(answer, not_so_trivial_.MinimalCut());
}

TEST_F(FlowNetworkTest, ExampleMaxFlowSearch) {
    example_.AddEdge(0, 1, 20);
    example_.AddEdge(1, 0, 20);

    example_.AddEdge(0, 2, 10);
    example_.AddEdge(2, 0, 10);

    example_.AddEdge(1, 2, 5);
    example_.AddEdge(2, 1, 5);

    example_.AddEdge(1, 3, 10);
    example_.AddEdge(3, 1, 10);

    example_.AddEdge(2, 3, 20);
    example_.AddEdge(3, 2, 20);
    EXPECT_EQ(25, example_.MaxFlowSearch());
}

TEST_F(FlowNetworkTest, ExampleMinCut) {
    std::vector<int> answer;
    answer.push_back(0);
    answer.push_back(1);

    example_.AddEdge(0, 1, 20);
    example_.AddEdge(1, 0, 20);

    example_.AddEdge(0, 2, 10);
    example_.AddEdge(2, 0, 10);

    example_.AddEdge(1, 2, 5);
    example_.AddEdge(2, 1, 5);

    example_.AddEdge(1, 3, 10);
    example_.AddEdge(3, 1, 10);

    example_.AddEdge(2, 3, 20);
    example_.AddEdge(3, 2, 20);
    example_.MaxFlowSearch();
    EXPECT_EQ(answer, example_.MinimalCut());
}