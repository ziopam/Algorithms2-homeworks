#ifndef GRAPH_H
#define GRAPH_H

#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

struct Edge {
  int to;
  int weight;
};

using Pair = std::pair<int, int>;

class Graph {
 public:
  std::unordered_map<int, std::vector<Edge>> adj;
  std::vector<std::vector<int>> heuristic;

  explicit Graph(int n = 0) : adj(n) {
    heuristic.resize(n, std::vector<int>(n, 0));
  }

  void AddEdge(int u, int v, int weight) {
    adj[u].push_back({v, weight});
    adj[v].push_back({u, weight});
  }

  std::vector<int> Dijkstra(int start, int goal, int &checked_nodes) {
    std::vector<int> dist(adj.size(), INT_MAX);
    std::vector<bool> visited(adj.size(), false);
    std::vector<int> prev(adj.size(), -1);
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;

    checked_nodes = 0;

    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
      auto [_, u] = pq.top();
      pq.pop();

      if (visited[u]) {
        continue;
      }

      visited[u] = true;
      ++checked_nodes;

      if (u == goal) {
        break;
      }

      for (const auto &edge : adj[u]) {
        int new_dist = dist[u] + edge.weight;
        if (new_dist < dist[edge.to]) {
          dist[edge.to] = new_dist;
          pq.emplace(dist[edge.to], edge.to);
          prev[edge.to] = u;
        }
      }
    }

    return ReconstructPath(prev, start, goal);
  }

  std::vector<int> AStar(int start, int goal, int &checked_nodes) {
    std::vector<int> dist(adj.size(), INT_MAX);
    std::vector<bool> visited(adj.size(), false);
    std::vector<int> prev(adj.size(), -1);
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    std::vector<int> f_score(adj.size(), INT_MAX);

    checked_nodes = 0;

    f_score[start] = heuristic[start][goal];
    pq.emplace(0, start);

    while (!pq.empty()) {
      auto [_, u] = pq.top();
      pq.pop();

      if (visited[u]) {
        continue;
      }

      visited[u] = true;
      ++checked_nodes;

      if (u == goal) {
        break;
      }

      for (const auto &edge : adj[u]) {
        int new_dist = dist[u] + edge.weight;
        if (new_dist < dist[edge.to]) {
          dist[edge.to] = new_dist;
          f_score[edge.to] = dist[edge.to] + heuristic[edge.to][goal];
          pq.emplace(f_score[edge.to], edge.to);
          prev[edge.to] = u;
        }
      }
    }

    return ReconstructPath(prev, start, goal);
  }

 private:
  std::vector<int> ReconstructPath(std::vector<int> &prev, int start, int goal) {
    std::vector<int> path;
    int cur = goal;
    while (cur != start) {
      path.push_back(cur);
      cur = prev[cur];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
  };
};
#endif  // GRAPH_H