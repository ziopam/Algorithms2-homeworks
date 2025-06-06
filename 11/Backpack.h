#ifndef BACKPACK_H
#define BACKPACK_H

#include <algorithm>
#include <vector>

struct Backpack {
 private:
  struct Item {
    int weight;
    int cost;

    Item(int w, int c) : weight(w), cost(c) {
    }
  };

 public:
  int maxWeight = 0;
  std::vector<Item> items;
  explicit Backpack(int mw) : maxWeight(mw) {
  }

  void AddItem(int weight, int cost) {
    items.emplace_back(weight, cost);
  }

  int Pack() const {
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(maxWeight + 1, 0));

    for (int i = 1; i <= n; ++i) {
      for (int w = 0; w <= maxWeight; ++w) {
        if (items[i - 1].weight <= w) {
          dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].cost);
        } else {
          dp[i][w] = dp[i - 1][w];
        }
      }
    }

    return dp[n][maxWeight];
  }
};

#endif  // BACKPACK_H