#ifndef DINIC_GRAPH_H
#define DINIC_GRAPH_H

#include <algorithm>
#include <climits>
#include <queue>
#include <vector>

struct Edge {
  int to;
  int flow;
  int weight;
  int reverse_edge;
};

using ADJ = std::vector<std ::vector<Edge>>;

struct DinicGraph {
  int n;
  std::vector<int> level;
  ADJ adj;

  explicit DinicGraph(int n) : n(n), level(n), adj(n) {
  }

  void AddEdge(int from, int to, int weight) {
    int to_size = adj[to].size();
    int from_size = adj[from].size();

    adj[from].push_back({to, 0, weight, to_size});
    adj[to].push_back({from, 0, 0, from_size});
  }

  bool BFS(int s, int t) {
    std::fill(level.begin(), level.end(), -1);
    level[s] = 0;

    std::queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (const auto& edge : adj[u]) {
        if (level[edge.to] == -1 && edge.flow < edge.weight) {
          level[edge.to] = level[u] + 1;
          q.push(edge.to);
        }
      }
    }

    return level[t] != -1;
  }

  int DFS(int u, int flow, int t, std::vector<int>& start) {
    if (u == t) {
      return flow;
    }

    for (; start[u] < adj[u].size(); ++start[u]) {
      Edge& edge = adj[u][start[u]];

      if (level[edge.to] == level[u] + 1 && edge.flow < edge.weight) {
        int cur_flow = std::min(flow, edge.weight - edge.flow);
        int temp_flow = DFS(edge.to, cur_flow, t, start);

        if (temp_flow > 0) {
          edge.flow += temp_flow;
          adj[edge.to][edge.reverse_edge].flow -= temp_flow;
          return temp_flow;
        }
      }
    }

    return 0;
  }

  int DinicMaxFlow(int s, int t) {
    if (s == t) {
      return -1;
    }

    int max_flow = 0;
    while (BFS(s, t)) {
      std::vector<int> start(n, 0);
      while (int flow = DFS(s, INT_MAX, t, start)) {
        max_flow += flow;
      }
    }

    return max_flow;
  }
};

#endif  // DINIC_GRAPH_H