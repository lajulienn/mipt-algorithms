/**
 * @author Julia Ivanova
 */

#ifndef STRING_ALGORITHMS_AHO_CORASICK_H
#define STRING_ALGORITHMS_AHO_CORASICK_H

#include <string>
#include <vector>

class PatternFinder {
    static const int ALPHABET_SIZE = 256;
    struct Vertex {
        Vertex(int parent = 0);

        std::vector<int> children;
        std::vector<int> accepted_words;
        int parent;
        char jump_char;
        int suff_link;
        int accepting_link;
        std::vector<int> children_by_link;
    };

    std::vector<Vertex> vertices;
    std::vector<std::pair<std::string, int>> strings;
    std::string pattern_;

    void AddString(const std::string &string, int id);
    int GetLink(int vertex);
    int Jump(int vertex, char character);
    std::vector<std::pair<std::string, int>> SplitPattern(const std::string &pattern);
    std::vector<int> TextAnalysis(const std::string &text);
    int GetAcceptingLink(int vertex);

public:
    PatternFinder(std::string pattern);
    std::vector<int> FindOccurrences(const std::string &text);
};

#endif //STRING_ALGORITHMS_AHO_CORASICK_H
