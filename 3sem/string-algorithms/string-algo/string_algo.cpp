/**
 * @author Julia Ivanova
 */

#include <set>
#include "include/string_algo.h"

#include <iostream>

std::vector<int> StringToPrefix(const std::string &string) {
    std::vector<int> prefix = std::vector<int>(string.length());
    prefix[0] = 0;
    for (int i = 1; i < string.length(); ++i) {
        int possible_prefix = prefix[i - 1];
        while (possible_prefix > 0 && string[i] != string[possible_prefix]) {
            possible_prefix = prefix[possible_prefix - 1];
        }
        if (string[i] == string[possible_prefix]) {
            prefix[i] = possible_prefix + 1;
        } else {
            prefix[i] = 0;
        }
    }
    return prefix;
}

std::vector<int> StringToZ(const std::string &string) {
    std::vector<int> z_func = std::vector<int>(string.length());
    z_func[0] = string.length();
    int left = 0;
    int right = 0;
    for (int i = 1; i < string.length(); ++i) {
        if (i > right) {
            int offset = 0;
            while (offset < string.length() - i
                   && string[i + offset] == string[offset++]) {}
            z_func[i] = offset;
            left = i;
            right = i + offset - 1;
        } else {
            int prefix = z_func[i - left] + i;
            if (right < prefix) {
                int offset = right + 1;
                while (offset < string.length() - right
                       && string[offset - i] == string[offset++]) {}
                z_func[i] = offset - i;
            } else {
                z_func[i] = z_func[i - left];
            }
        }
    }
}

std::string PrefixToString(const std::vector<int> &prefix) {
    std::string string = std::string(prefix.size(), 'a');
    for (int i = 1; i < string.length(); ++i) {
        if (prefix[i] != 0) {
            string[i] = string[prefix[i] - 1];
        } else {
            std::set<char> forbidden_symbols = {'a'};
            int prefix_end = prefix[i - 1];

            do {
                forbidden_symbols.insert(string[prefix_end]);
                prefix_end = prefix[prefix_end - 1];
            } while (prefix_end > 0);

            char character = 'a';
            while (forbidden_symbols.find(character) != forbidden_symbols.end()) {
                ++character;
            }
            string[i] = character;
        }
    }
    return string;
}

std::string ZToString(std::vector<int> z_func) {
    z_func[0] = 0;
    std::string string = std::string(z_func.size(), 'a');

    int left_to_write = 0;
    int index_to_write = 0;

    for (int i = 1; i < string.length(); ++i) {
        if (z_func[i] == 0 && left_to_write == 0) {
            std::set<char> forbidden_symbols = {'a'};
            for (int j = 1; j <= i; ++j) {
                if (z_func[j] + j >= i) {
                    forbidden_symbols.insert(string[i - j]);
                }
            }

            char character = 'a';
            while (forbidden_symbols.find(character) != forbidden_symbols.end()) {
                ++character;
            }
            string[i] = character;
        } else {
            if (z_func[i] > left_to_write) {
                left_to_write = z_func[i];
                index_to_write = 0;
            }
            if (left_to_write > 0) {
                string[i] = string[index_to_write++];
                --left_to_write;
            }
        }
    }
    return string;
}

std::vector<int> PrefixToZ(const std::vector<int> &prefix) {
    std::vector<int> z_func = std::vector<int>(prefix.size(), 0);

    z_func[0] = prefix.size();
    for (int i = 1; i < z_func.size(); ++i) {
        if (prefix[i] > 0) {
            z_func[i - prefix[i] + 1] = prefix[i];
        }
    }

    for (int i = 1; i < z_func.size(); ) {
        int shift = 1;
        for (int prefix_index = 0; prefix_index < z_func[i]; ++prefix_index) {
            shift = prefix_index;
            if (z_func[prefix_index] < z_func[i + prefix_index]) {
                break;
            } else {
                z_func[i + prefix_index] = std::min(z_func[prefix_index],
                                                    z_func[i] - prefix_index);
            }
        }
        i += shift;
    }
    return z_func;
}

std::vector<int> ZToPrefix(const std::vector<int> &z_func) {
    std::vector<int> prefix = std::vector<int>(z_func.size(), 0);

    for (int i = 1; i < prefix.size(); ++i) {
        for (int prefix_index = z_func[i] - 1; prefix_index >= 0; --prefix_index) {
            if (prefix[i + prefix_index] > 0) {
                break;
            } else {
                prefix[i + prefix_index] = prefix_index + 1;
            }
        }
    }
    return prefix;
}

std::vector<int> FindSubstring(std::string &pattern, const std::string &string) {
    std::vector<int> substring_indices;

    pattern.append("#");
    std::vector<int> prefix = StringToPrefix(pattern);

    int previous_p_func = 0;

    for (int i = 0; i < string.length(); ++i) {
        int possible_prefix = previous_p_func;
        while (possible_prefix > 0 && string[i] != pattern[possible_prefix]) {
            possible_prefix = prefix[possible_prefix - 1];
        }
        if (string[i] == pattern[possible_prefix]) {
            if (possible_prefix + 1 == pattern.length() - 1) {
                substring_indices.push_back(i - (pattern.length() - 1) + 1);
            }
            previous_p_func = possible_prefix + 1;
        } else {
            previous_p_func = 0;
        }
    }
    return substring_indices;
}

int DifferentSubstringsCount(std::string &string) {
    string.append("!");
    std::vector<int> suf_array = BuildSufArray(string);
    std::vector<int> lcp = BuildLcp(string, suf_array);
    auto old = std::move(suf_array);
    for (int i = 1; i< old.size(); ++i)
        suf_array.push_back(old[i]);
    old = std::move(lcp);
    for (int i = 1; i< old.size(); ++i)
        lcp.push_back(old[i]);
    string.pop_back();
    int substrings_count = 0;
    for (auto x : suf_array) {
        substrings_count += string.length() - x;
    }
    return substrings_count + lcp[string.length() - 1];
}

std::vector<int> BuildSufArray(const std::string &string) {
    const int alphabet_size = 256;

    std::vector<int> suf_array = std::vector<int>(string.length());
    std::vector<int> char_count = std::vector<int>(alphabet_size, 0);

    for (int i = 0; i < string.length(); ++i) {
        ++char_count[string[i]];
    }
    for (int i = 1; i < alphabet_size; ++i) {
        char_count[i] += char_count[i - 1];
    }
    for (int i = string.length() - 1; i >= 0; --i) {
        suf_array[--char_count[string[i]]] = i;
    }

    std::vector<int> equality_class = std::vector<int>(string.length());
    int current_class_count = 0;
    equality_class[suf_array[0]] = current_class_count;
    for (int i = 1; i < string.length(); ++i) {
        if (string[suf_array[i]] != string[suf_array[i - 1]]) {
            ++current_class_count;
        }
        equality_class[suf_array[i]] = current_class_count;
    }

    std::vector<int> sorted_by_second_part = std::vector<int>(string.length());
    std::vector<int> new_equality_class = std::vector<int>(string.length());

    for (int shift = 1; shift < string.length(); shift *= 2) {
        for (int i = 0; i < sorted_by_second_part.size(); ++i) {
            sorted_by_second_part[i] = (suf_array[i] - shift + string.length()) % string.length();
        }

        std::vector<int> classes_count = std::vector<int>(current_class_count + 1, 0);
        for (int i = 0; i < string.length(); ++i) {
            ++classes_count[equality_class[sorted_by_second_part[i]]];
        }
        for (int i = 1; i < classes_count.size(); ++i) {
            classes_count[i] += classes_count[i - 1];
        }

        for (int i = suf_array.size() - 1; i >= 0; --i) {
            int suffix = sorted_by_second_part[i];
            suf_array[--classes_count[equality_class[suffix]]] = suffix;
        }

        current_class_count = 0;
        new_equality_class[suf_array[0]] = current_class_count;
        for (int i = 1; i < new_equality_class.size(); ++i) {
            int left_part_first = suf_array[i];
            int left_part_second = suf_array[i - 1];
            int right_part_first = (left_part_first + shift) % string.length();
            int right_part_second = (left_part_second + shift) % string.length();

            if (equality_class[left_part_first] != equality_class[left_part_second]
                || equality_class[right_part_first] != equality_class[right_part_second]) {
                ++current_class_count;
            }
            new_equality_class[suf_array[i]] = current_class_count;
        }
        equality_class = new_equality_class;
    }

    return suf_array;
}

std::vector<int> BuildLcp(const std::string &string, const std::vector<int> &suf_array) {
    std::vector<int> lcp = std::vector<int>(string.length());
    std::vector<int> position_in_suf_array = std::vector<int>(string.length());

    for (int i = 0; i < string.length(); ++i) {
        position_in_suf_array[suf_array[i]] = i;
    }
    int common_prefix = 0;
    for (int i = 0; i < string.length(); ++i) {
        if (common_prefix > 0) {
            --common_prefix;
        }
        if (position_in_suf_array[i] == string.length() - 1) {
            lcp[string.length() - 1] = -1;
            common_prefix = 0;
        } else {
            int next_suffix = suf_array[position_in_suf_array[i] + 1];
            while (std::max(i + common_prefix, common_prefix + next_suffix) < string.length()
                   && string[i + common_prefix] == string[common_prefix + next_suffix]) {
                ++common_prefix;
            }
            lcp[position_in_suf_array[i]] = common_prefix;
        }
    }
    return lcp;
}