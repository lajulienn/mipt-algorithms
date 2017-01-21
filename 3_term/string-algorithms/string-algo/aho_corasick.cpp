/**
 * @author Julia Ivanova
 */

#include <iostream>
#include "aho_corasick.h"

PatternFinder::Vertex::Vertex(int parent) :
        children(ALPHABET_SIZE, -1),
        parent(parent),
        suff_link(-1),
        children_by_link(ALPHABET_SIZE, -1),
        accepting_link(-1) {}

PatternFinder::PatternFinder(std::string pattern) : pattern_(pattern) {
    vertices.emplace_back();
    vertices.back().accepting_link = 0;
    strings = SplitPattern(pattern);

    for (auto string : strings) {
        AddString(string.first, string.second);
    }
}

/* TODO: Fix
 * a?aa?aaa?aaaaa?a aaaaaaaaaaaaaaaaaaa
 * ?a?aa aaaaa
 * a:1 , aa:4 , aaa:8 , aaaaa:14 , a:16 ,
 */
void PatternFinder::AddString(const std::string &string, int id){
    int vertex = 0;
    for (int i = 0; i < string.length(); ++i) {
        char character = string[i];
        if (vertices[vertex].children[character] == -1) {
            vertices[vertex].children[character] = vertices.size();
            vertices.emplace_back(vertex);
            vertices.back().jump_char = character;
        }
        vertex = vertices[vertex].children[character];
    }
    vertices[vertex].accepted_words.push_back(id);
}

int PatternFinder::GetLink(int vertex){
    if (vertices[vertex].suff_link == -1) {
        if (vertices[vertex].parent == 0) {
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
    std::string next_string = "";
    for (int i = 0; i < pattern.length(); ++i) {
        if (pattern[i] != '?') {
            next_string.push_back(pattern[i]);
        } else if (!next_string.empty()) {
            strings.push_back({next_string, i});
            next_string.clear();
        }
    }
    if (!next_string.empty()) {
        strings.push_back({next_string, pattern.length()});
    }
    return strings;
}

std::vector<int> PatternFinder::FindOccurrences(const std::string &text) {
    std::vector<int> entry_count = TextAnalysis(text);

    std::vector<int> entry;
    for (int i = 0; i < entry_count.size() && i + pattern_.length() <= text.length(); ++i) {
        if (entry_count[i] == strings.size()) {
            entry.push_back(i);
        }
    }

    return entry;
}

std::vector<int> PatternFinder::TextAnalysis(const std::string &text) {
    std::vector<int> entry_count(text.length());
    int current = 0;
    for (int i = 0; i < text.length(); ++i) {
        //char character = text[i] - 'a''
        char character = text[i];
        current = Jump(current, character);

        int accepting_state = current;
        while (accepting_state) {
            for (auto word : vertices[accepting_state].accepted_words) {
                if (i - word + 1 >= 0) {
                    ++entry_count[i - word + 1];
                }
            }
            accepting_state = GetAcceptingLink(accepting_state);
        }
    }
    return entry_count;
}

int PatternFinder::GetAcceptingLink(int id) {
    auto &vertex = vertices[id];
    if (vertex.accepting_link < 0) {
        int link = GetLink(id);
        if (vertices[link].accepted_words.empty()) {
            vertex.accepting_link = GetAcceptingLink(link);
        } else {
            vertex.accepting_link = link;
        }
    }

    return vertex.accepting_link;
}