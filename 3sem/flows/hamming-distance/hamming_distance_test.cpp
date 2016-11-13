/**
 * @author Julia Ivanova
 */

#include "hamming_distance.h"

#include "gtest/gtest.h"

TEST(FindDistance, Trivial) {
    std::string string("0");
    std::string pattern("0");
    EXPECT_EQ(0, FindDistance(string, pattern));
    pattern = "1";
    EXPECT_EQ(1, FindDistance(string, pattern));
    string = "1";
    EXPECT_EQ(0, FindDistance(string, pattern));
}

TEST(FindDistance, OneSpace) {
    std::string string("0");
    std::string pattern("?");
    EXPECT_EQ(0, FindDistance(string, pattern));
    std::string answer("0");
    EXPECT_EQ(answer, pattern);
}

TEST(FindDistance, BothSpaces) {
    std::string string("?");
    std::string pattern("?");
    EXPECT_EQ(0, FindDistance(string, pattern));
    std::string answer("1");
    EXPECT_EQ(answer, string);
    EXPECT_EQ(answer, pattern);
}

TEST(FindDistance, ManySpaces) {
    std::string string("?????????");
    std::string pattern("????");
    EXPECT_EQ(0, FindDistance(string, pattern));
    std::string string_answer("111111111");
    std::string pattern_answer("1111");
    EXPECT_EQ(string_answer, string);
    EXPECT_EQ(pattern_answer, pattern);
}

TEST(FindDistance, Example) {
    std::string string("00?");
    std::string pattern("1?");
    EXPECT_EQ(2, FindDistance(string, pattern));
    std::string string_answer("000");
    std::string pattern_answer("10");
    EXPECT_EQ(string_answer, string);
    EXPECT_EQ(pattern_answer, pattern);
}