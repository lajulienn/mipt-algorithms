/**
 * @author Julia Ivanova
 */

#ifndef STRING_ALGORITHMS_AHO_CORASICK_H
#define STRING_ALGORITHMS_AHO_CORASICK_H

#include <string>
#include <vector>

class PatternFinder {
    static const int ALPHABET_SIZE = 26;
    struct Vertex {
        Vertex(int parent = 0);

        std::vector<int> children;
        std::vector<int> accepted_words;
        int parent;
        char jump_char;
        int suff_link;
        std::vector<int> children_by_link;
    };

    std::vector<Vertex> vertices;
    std::vector<std::pair<std::string, int>> strings;

    void AddString(const std::string &string, int id);
    int GetLink(int vertex);
    int Jump(int vertex, char character);
    std::vector<std::pair<std::string, int>> SplitPattern(const std::string &pattern);
    void TextAnalysis(const std::string &text, std::vector<int> &entry_count);
public:
    PatternFinder();
    std::vector<int> FindPattern(const std::string &pattern, const std::string &text);
};

#endif //STRING_ALGORITHMS_AHO_CORASICK_H
/**
 * @author Julia Ivanova
 */

#include <iostream>

PatternFinder::Vertex::Vertex(int parent) :
        children(ALPHABET_SIZE, -1),
        parent(parent),
        suff_link(-1),
        children_by_link(ALPHABET_SIZE, -1) {}

PatternFinder::PatternFinder() {
    vertices.emplace_back();
}

void PatternFinder::AddString(const std::string &string, int id){
    int vertex = 0;
    for (int i = 0; i < string.length(); ++i) {
        char character = string[i] - 'a';
        if (vertices[vertex].children[character] == -1) {
            vertices[vertex].children[character] = vertices.size();
            vertices.emplace_back(vertex);
        }
        vertex = vertices[vertex].children[character];
    }
    vertices[vertex].accepted_words.push_back(id);
}

int PatternFinder::GetLink(int vertex){
    if (vertices[vertex].suff_link == -1) {
        if (vertex == 0 || vertices[vertex].parent == 0) {
            vertices[vertex].suff_link = 0;
        } else {
            vertices[vertex].suff_link = Jump(GetLink(vertices[vertex].parent),
                                              vertices[vertex].jump_char);
        }
    }
    return vertices[vertex].suff_link;
}

int PatternFinder::Jump(int vertex, char character) {
    if (vertices[vertex].children_by_link[character] == -1) {
        if (vertices[vertex].children[character] != -1) {
            vertices[vertex].children_by_link[character] = vertices[vertex].children[character];
        } else {
            if (vertex == 0){
                vertices[vertex].children_by_link[character] = 0;
            } else {
                vertices[vertex].children_by_link[character] = Jump(GetLink(vertex), character);
            }
        }
    }
    return vertices[vertex].children_by_link[character];
}

std::vector<std::pair<std::string, int>> PatternFinder::SplitPattern(const std::string &pattern) {
    std::vector<std::pair<std::string, int>> strings;
    std::string next_string;
    for (int i = 0; i < pattern.length(); ++i) {
        if (pattern[i] != '?') {
            next_string.push_back(pattern[i]);
        } else if (!next_string.empty()) {
            //strings.push_back({next_string, i - next_string.length()});
            strings.push_back({next_string, i});
            next_string.clear();
        }
    }
    if (!next_string.empty()) {
        strings.push_back({next_string, pattern.length()});
        //strings.push_back({next_string, pattern.length() - next_string.length()});
    }
    return strings;
}

std::vector<int> PatternFinder::FindPattern(const std::string &pattern, const std::string &text) {
    std::vector<std::pair<std::string, int>> strings = SplitPattern(pattern);

    for (auto string : strings) {
  //      std::cout << string.first << ':' << string.second << std::endl;
        AddString(string.first, string.second);
    }
//    std::cout << "Added " << strings.size() << " strings" << std::endl;

    std::vector<int> entry_count(text.length());
    TextAnalysis(text, entry_count);
    //std::cout << "Text analysed" << std::endl;
    for (auto x : entry_count) {
   //     std::cout << x << ' ';
    }
    //std::cout << std::endl;

    std::vector<int> entry;
    for (int i = 0; i < entry_count.size(); ++i) {
      //  std::cout << i << ':' << entry_count[i] << std::endl;
        if (entry_count[i] == strings.size()) {
        //    std::cout << i << std::endl;
            entry.push_back(i);
        }
    }
   // std::cout << "ok" << std::endl;
    return entry;
}

void PatternFinder::TextAnalysis(const std::string &text, std::vector<int> &entry_count) {
    int current = 0;
    for (int i = 0; i < text.length(); ++i) {
        char character = text[i] - 'a';
        current = Jump(current, character);
        for (auto word : vertices[current].accepted_words) {
            if (i - word + 1 >= 0)
            ++entry_count[i - word + 1];
       //     std::cout << "0 <= " << (i - word + 1) << " <= " << entry_count.size() << std::endl;
        }
    }
}/**
 * @author Julia Ivanova
 */

#include <iostream>
#include <string>

int main() {
    std::string pattern;
    std::string text;

    std::cin >> pattern >> text;

    PatternFinder finder = PatternFinder();
    std::vector<int> entry = finder.FindPattern(pattern, text);


    for (auto x : entry) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}
