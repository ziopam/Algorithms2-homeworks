#ifndef BB_H
#define BB_H

#include <algorithm>
#include <queue>
#include <vector>

struct Node {
  int level;
  double profit;
  double weight;
  double bound;

  explicit Node(int l = 0, double p = 0.0, double w = 0.0, double b = 0.0) : level(l), profit(p), weight(w), bound(b) {
  }
  bool operator<(const Node& other) const {
    return bound < other.bound;
  }
};

struct BB {
 private:
  struct Item {
    double weight;
    double profit;
    double ratio;

    Item(double w, double v) : weight(w), profit(v), ratio(v / w) {
    }

    bool operator<(const Item& other) const {
      return ratio > other.ratio;
    }
  };

 public:
  std::vector<Item> items;
  double capacity;

  explicit BB(double cap) : capacity(cap) {
  }

  void AddItem(double weight, double value) {
    items.emplace_back(weight, value);
  }

  double CalculateBound(Node& node) {
    if (node.weight >= capacity) {
      return 0.0;
    }

    double bound = node.profit;
    double weight = node.weight;
    int j = node.level + 1;

    while (j < items.size() && weight + items[j].weight <= capacity) {
      weight += items[j].weight;
      bound += items[j].profit;
      j++;
    }

    if (j < items.size()) {
      bound += (capacity - weight) * items[j].ratio;
    }

    return bound;
  }
  double Pack() {
    std::sort(items.begin(), items.end());

    std::priority_queue<Node> pq;

    Node current;
    current.bound = CalculateBound(current);
    pq.push(current);

    double max_profit = 0.0;
    while (!pq.empty()) {
      current = pq.top();
      pq.pop();

      if (current.bound <= max_profit || current.level >= static_cast<int>(items.size() - 1)) {
        continue;
      }

      Node next;
      next.level = current.level + 1;

      // Взять следующий элемент
      next.weight = current.weight + items[current.level].weight;
      next.profit = current.profit + items[current.level].profit;

      if (next.weight <= capacity && next.profit > max_profit) {
        max_profit = next.profit;
      }
      next.bound = CalculateBound(next);

      if (next.bound > max_profit) {
        pq.push(next);
      }

      // Не брать следующий элемент
      next.weight = current.weight;
      next.profit = current.profit;
      next.bound = CalculateBound(next);
      if (next.bound > max_profit) {
        pq.push(next);
      }
    }
    return max_profit;
  }
};

#endif  // BB_H