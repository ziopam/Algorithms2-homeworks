#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <vector>

struct Graph {
  int V;
  std::vector<int> path;
  std::vector<std::vector<int>> adj;

  explicit Graph(int v) : V(v) {
    adj.resize(V);
    visited_.resize(V, false);
  }

  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  const std::vector<int>& Adj(int v) const {
    return adj[v];
  }

  void DFS(int s) {
    visited_[s] = true;
    path.push_back(s);  // Для тестов DFS
    for (const int& v : adj[s]) {
      if (!visited_[v]) {
        DFS(v);
      }
    }
  }

  bool IsConnected() {
    std::fill(visited_.begin(), visited_.end(), false);
    DFS(0);
    return std::find(visited_.begin(), visited_.end(), false) == visited_.end();
  }

  int CountOddDegrees() {
    int count = 0;
    for (int i = 0; i < V; ++i) {
      if (adj[i].size() % 2 != 0) {
        ++count;
      }
    }
    return count;
  }

  bool IsEulerian() {
    int odd_degrees = CountOddDegrees();
    return IsConnected() && (odd_degrees == 0 || odd_degrees == 2);
  }

 private:
  std::vector<bool> visited_;
};

#endif  // GRAPH_H