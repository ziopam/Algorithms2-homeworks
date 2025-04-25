#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#ifndef DAMERAY_LEVENSTEIN_H
#define DAMERAY_LEVENSTEIN_H

struct DamerayLevenshtein {
  std::vector<std::vector<int>> d;

  void BuildTable(const std::string& s1, const std::string& s2) {
    d = std::vector<std::vector<int>>(s1.size() + 1, std::vector<int>(s2.size() + 1, 0));
    for (int i = 0; i <= s1.size(); ++i) {
      for (int j = 0; j <= s2.size(); ++j) {
        CountD(s1, s2, i, j);
      }
    }
  }

  int GetDistance() const {
    return d.back().back();
  }

 private:
  void CountD(const std::string& s1, const std::string& s2, int i, int j) {
    if (i == 0 || j == 0) {
      d[i][j] = i + j;
      return;
    }

    int add = d[i][j - 1] + 1;
    int remove = d[i - 1][j] + 1;
    int replace = d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1);

    d[i][j] = std::min({add, remove, replace});

    if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
      int swap = d[i - 2][j - 2] + 1;
      d[i][j] = std::min(d[i][j], swap);
    }
  }
};

#endif  // DAMERAY_LEVENSTEIN_H