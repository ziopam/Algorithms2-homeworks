#ifndef BACKPACK_H
#define BACKPACK_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

struct Item {
  int weight;
  int volume;
  int value;
};

struct Backpack {
  std::vector<Item> items;
  int maxWeight;
  int maxVolume;
  std::vector<std::vector<std::vector<int>>> dp;

  Backpack(int max_weight, int max_volume) : maxWeight(max_weight), maxVolume(max_volume) {
  }

  void Add(int weight, int volume, int value) {
    items.push_back({weight, volume, value});
  }

  int Solve() {
    int n = items.size();

    dp.resize(n + 1);
    for (int i = 0; i <= n; i++) {
      dp[i].resize(maxWeight + 1);
      for (int w = 0; w <= maxWeight; w++) {
        dp[i][w].resize(maxVolume + 1, 0);
      }
    }

    for (int i = 1; i <= n; i++) {
      for (int w = 0; w <= maxWeight; w++) {
        for (int v = 0; v <= maxVolume; v++) {
          dp[i][w][v] = dp[i - 1][w][v];

          if (w >= items[i - 1].weight && v >= items[i - 1].volume) {
            dp[i][w][v] =
                std::max(dp[i][w][v], dp[i - 1][w - items[i - 1].weight][v - items[i - 1].volume] + items[i - 1].value);
          }
        }
      }
    }

    return dp[n][maxWeight][maxVolume];
  }

  std::vector<int> GetSelectedItems() {
    std::vector<int> selected;
    int n = items.size();
    int w = maxWeight;
    int v = maxVolume;

    for (int i = n; i > 0; i--) {
      if (dp[i][w][v] != dp[i - 1][w][v]) {
        selected.push_back(i - 1);
        w -= items[i - 1].weight;
        v -= items[i - 1].volume;
      }
    }

    std::reverse(selected.begin(), selected.end());
    return selected;
  }
};

#endif  // BACKPACK_H
