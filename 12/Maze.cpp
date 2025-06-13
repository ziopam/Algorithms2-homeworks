#include <algorithm>
#include <iostream>
#include <random>
#include <stack>
#include <vector>

struct Cell {
  int x, y;
};

Cell delta_cells[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool IsInRange(int x, int y, int n, int m) {
  return x >= 0 && x < n && y >= 0 && y < m;
}

bool CanAdd(int x, int y, const std::vector<std::vector<int>>& maze, int n, int m) {
  int cnt = 0;
  for (int d = 0; d < 4; ++d) {
    int nx = x + delta_cells[d].x;
    int ny = y + delta_cells[d].y;
    if (IsInRange(nx, ny, n, m) && maze[nx][ny] == 1) {
      cnt++;
    }
  }
  return cnt <= 1;
}

void Generate(int n, int m, Cell entry, Cell exit, std::vector<std::vector<int>>& maze) {
  maze.assign(n, std::vector<int>(m, 0));
  std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
  std::stack<Cell> stack;

  stack.push(entry);
  maze[entry.x][entry.y] = 1;
  visited[entry.x][entry.y] = true;

  std::mt19937 rng(std::random_device{}());

  while (!stack.empty()) {
    Cell current = stack.top();
    std::vector<Cell> neighbors;

    for (int d = 0; d < 4; ++d) {
      int nx = current.x + delta_cells[d].x;
      int ny = current.y + delta_cells[d].y;
      if (IsInRange(nx, ny, n, m) && !visited[nx][ny]) {
        if (CanAdd(nx, ny, maze, n, m)) {
          neighbors.push_back({nx, ny});
        }
      }
    }

    if (!neighbors.empty()) {
      std::uniform_int_distribution<int> dist(0, neighbors.size() - 1);
      Cell next = neighbors[dist(rng)];
      maze[next.x][next.y] = 1;
      visited[next.x][next.y] = true;
      stack.push(next);
    } else {
      stack.pop();
    }
  }

  if (maze[exit.x][exit.y] == 0) {
    maze[exit.x][exit.y] = 1;
  }
}

void PrintMaze(const std::vector<std::vector<int>>& maze, Cell entry, Cell exit) {
  int n = maze.size();
  int m = maze[0].size();

  std::cout << "\033[48;5;240m╔";
  for (int j = 0; j < m; ++j) {
    std::cout << "══";
  }
  std::cout << "╗\033[0m\n";

  for (int i = 0; i < n; ++i) {
    std::cout << "\033[48;5;240m║\033[0m";

    for (int j = 0; j < m; ++j) {
      if (i == entry.x && j == entry.y) {
        std::cout << "\033[43m  \033[0m";
      } else if (i == exit.x && j == exit.y) {
        std::cout << "\033[42m  \033[0m";
      } else if (maze[i][j] == 1) {
        std::cout << "  ";
      } else {
        std::cout << "██";
      }
    }

    std::cout << "\033[48;5;240m║\033[0m\n";
  }

  std::cout << "\033[48;5;240m╚";
  for (int j = 0; j < m; ++j) {
    std::cout << "══";
  }
  std::cout << "╝\033[0m\n";
}

int main() {
  int n = 10;
  int m = 10;
  Cell entry = {0, 0};
  Cell exit = {9, 9};

  std::vector<std::vector<int>> maze;
  Generate(n, m, entry, exit, maze);
  PrintMaze(maze, entry, exit);

  return 0;
}