/**
 * @author Julia Ivanova
 */

#include "kruskal_search.h"

#include "gtest/gtest.h"

class DisjointSetSystemTest : public ::testing::Test {
protected:
    DisjointSetSystemTest()
            : one_element_(std::vector<uint16_t>(1)),
              two_elements_(std::vector<uint16_t>(2)),
              four_elements_(std::vector<uint16_t>(4)) {
        std::vector<uint16_t> elements;

        elements.push_back(0);
        one_element_ = DisjointSetSystem(elements);

        elements.push_back(1);
        two_elements_ = DisjointSetSystem(elements);

        elements.push_back(2);
        elements.push_back(3);
        four_elements_ = DisjointSetSystem(elements);
    }

    DisjointSetSystem one_element_;
    DisjointSetSystem two_elements_;
    DisjointSetSystem four_elements_;
};

TEST_F(DisjointSetSystemTest, OneElement) {
    EXPECT_EQ(0, one_element_.GetComponent(0));
    one_element_.UniteComponents(0, 0);
    EXPECT_EQ(0, one_element_.GetComponent(0));
}

TEST_F(DisjointSetSystemTest, TwoElements) {
    EXPECT_EQ(0, two_elements_.GetComponent(0));
    EXPECT_EQ(1, two_elements_.GetComponent(1));
    two_elements_.UniteComponents(0, 1);
    EXPECT_EQ(two_elements_.GetComponent(0), two_elements_.GetComponent(1));
}

TEST_F(DisjointSetSystemTest, FourElements) {
    four_elements_.UniteComponents(0, 1);
    four_elements_.UniteComponents(2, 3);
    four_elements_.UniteComponents(0, 2);
    EXPECT_EQ(four_elements_.GetComponent(0), four_elements_.GetComponent(1));
    EXPECT_EQ(four_elements_.GetComponent(1), four_elements_.GetComponent(2));
    EXPECT_EQ(four_elements_.GetComponent(2), four_elements_.GetComponent(3));
}

TEST(TreeWeightCount, Trivial) {
    std::vector<Edge<int>> tree;
    tree.emplace_back(0, 1, 42);
    EXPECT_EQ(42, TreeWeightCount(tree));
}

TEST(TreeWeightCount, TwoEdges) {
    std::vector<Edge<int>> tree;
    tree.emplace_back(0, 1, 42);
    tree.emplace_back(1, 2, 24);
    EXPECT_EQ(66, TreeWeightCount(tree));
}

TEST(KruskalSearch, Trivial) {
    std::vector<Edge<int>> tree;
    tree.emplace_back(0, 1, 42);

    std::vector<Edge<int>> answer;
    answer.emplace_back(0, 1, 42);
    EXPECT_EQ(answer, KruskalSearch(tree, 2));
}

TEST(KruskalSearch, TwoEdges) {
    std::vector<Edge<int>> tree;
    tree.emplace_back(0, 1, 42);
    tree.emplace_back(1, 2, 24);

    std::vector<Edge<int>> answer;
    answer.emplace_back(1, 2, 24);
    answer.emplace_back(0, 1, 42);
    EXPECT_EQ(answer, KruskalSearch(tree, 3));
}

TEST(KruskalSearch, Example) {
    std::vector<Edge<int>> tree;
    tree.emplace_back(1, 2, 1);
    tree.emplace_back(2, 3, 2);
    tree.emplace_back(3, 4, 5);
    tree.emplace_back(4, 1, 4);

    EXPECT_EQ(7, TreeWeightCount(KruskalSearch(tree, 4)));
}
