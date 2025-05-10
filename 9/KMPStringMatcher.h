#ifndef KMPSTRINGMATCHER_H
#define KMPSTRINGMATCHER_H

#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using Table = std::vector<std::vector<int>>;

struct KMPStringMatcher {

  Table BuildKmpAutomaton(const std::string& pattern) {
    Table automation(pattern.size() + 1, std::vector<int>(alphabet_map_.size(), 0));
    std::vector<int> prefix = PrefixFunction(pattern);
    for (int state = 0; state < pattern.size(); ++state) {
      for (auto [letter, l_index] : alphabet_map_) {
        if (letter == pattern[state]) {
          automation[state][l_index] = state + 1;
        } else {
          automation[state][l_index] = state != 0 ? prefix[state - 1] : 0;
        }
      }
    }

    if (pattern.size() > 0) {
      for (auto [letter, l_index] : alphabet_map_) {
        automation[pattern.size()][l_index] = prefix[pattern.size() - 1];
      }
    }

    return automation;
  }

  int CountPatternOccurrences(const std::string& text, const std::string& pattern) {
    Table automation = BuildKmpAutomaton(pattern);
    int state = 0;
    int count = 0;

    for (char c : text) {
      if (alphabet_map_.count(c)) {
        while (state > 0 && state + 1 != automation[state][alphabet_map_[c]]) {
          state = automation[state][alphabet_map_[c]];
        }
        state = automation[state][alphabet_map_[c]];

        if (state == pattern.size()) {
          state = automation[state][alphabet_map_[c]];
          ++count;
        }
      } else {
        state = 0;
      }
    }

    return count;
  }

  void PrintAutomaton(const Table& automation) {
    std::cout << "+" << std::string(state_width, '-') << "+";
    for (size_t j = 0; j < alphabet_map_.size(); ++j) {
      std::cout << std::string(col_width, '-') << "+";
    }
    std::cout << "\n";

    std::cout << "| State |";
    for (size_t j = 0; j < alphabet_map_.size(); ++j) {
      std::cout << "  " << index_to_char[j] << "  |";
    }
    std::cout << "\n";

    std::cout << "+" << std::string(state_width, '-') << "+";
    for (size_t j = 0; j < alphabet_map_.size(); ++j) {
      std::cout << std::string(col_width, '-') << "+";
    }
    std::cout << "\n";

    for (size_t i = 0; i < automation.size(); ++i) {
      std::cout << "|" << std::setw(state_width - 1) << i << " |";
      for (size_t j = 0; j < automation[i].size(); ++j) {
        std::cout << "  " << automation[i][j] << "  |";
      }
      std::cout << "\n";

      std::cout << "+" << std::string(state_width, '-') << "+";
      for (size_t j = 0; j < alphabet_map_.size(); ++j) {
        std::cout << std::string(col_width, '-') << "+";
      }
      std::cout << "\n";
    }
  }

 private:
  std::unordered_map<char, int> alphabet_map_ = {{'H', 0}, {'S', 1}, {'E', 2}};
  std::vector<char> index_to_char = {'H', 'S', 'E'};
  int state_width = 7;
  int col_width = 5;

  std::vector<int> PrefixFunction(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> prefix(m, 0);
    for (int i = 1; i < m; ++i) {
      int p = prefix[i - 1];
      while (p > 0 && pattern[i] != pattern[p]) {
        p = prefix[p - 1];
      }

      if (pattern[i] == pattern[p]) {
        ++p;
      }

      prefix[i] = p;
    }

    return prefix;
  }
};

#endif  // KMPSTRINGMATCHER_H