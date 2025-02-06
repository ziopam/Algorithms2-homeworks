#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

struct Node {
  int value;
  std::vector<Node*>
      next;  // next[i] is the next node at level i. There is nodes that are on the same level as this node and beyond.

  explicit Node(int value, int level) : value(value), next(level, nullptr) {};
};

template <unsigned int MaxLevel>
struct SkipList {
  Node* head;

  SkipList() {
    if (MaxLevel < 1) {
      throw std::invalid_argument("MaxLevel must be at least 1");
    }
    head = new Node(0, MaxLevel);
  }

  void Insert(int value) {
    // Generate a random level for the new node
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    int level = 0;
    while (level < MaxLevel - 1 && dist(rng) <= 0.5) {
      ++level;
    }

    std::vector<Node*> update(level + 1, nullptr);  // update[i] is the last node at level i before the insertion point

    Node* current = head;
    for (int i = level; i >= 0; --i) {
      while (current->next[i] != nullptr && current->next[i]->value < value) {
        current = current->next[i];
      }
      update[i] = current;
    }

    current = current->next[0];

    // If the value is not already in the list, insert it
    if (current == nullptr || current->value != value) {

      Node* new_node = new Node(value, level + 1);
      for (int i = 0; i <= level; i++) {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node;
      }
    }
  }

  Node* Search(int value) {
    Node* current = head;
    for (int i = MaxLevel - 1; i >= 0; --i) {
      while (current->next[i] != nullptr && current->next[i]->value < value) {
        current = current->next[i];
      }
    }
    current = current->next[0];
    if (current == nullptr) {
      return nullptr;
    }
    return current->value == value ? current : nullptr;
  }

  void Remove(int value) {
    std::vector<Node*> update(MaxLevel, nullptr);
    Node* current = head;
    for (int i = MaxLevel - 1; i >= 0; --i) {
      while (current->next[i] != nullptr && current->next[i]->value < value) {
        current = current->next[i];
      }
      update[i] = current;
    }

    current = current->next[0];
    if (current != nullptr && current->value == value) {
      for (int i = 0; i < MaxLevel; ++i) {
        if (update[i]->next[i] != current) {
          break;
        }
        update[i]->next[i] = current->next[i];
      }
      delete current;
    }
  }

  void DisplayAllLevels() {
    for (int i = MaxLevel - 1; i >= 0; --i) {
      Node* current = head->next[i];
      std::cout << "Level " << i << ": ";
      while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next[i];
      }
      std::cout << std::endl;
    }
  }
};

#endif  // "SKIP_LIST_H"