#include <iostream>

#include "SkipList.h"

int main() {
  SkipList<3> list;
  list.Insert(1);
  list.Insert(2);
  list.Insert(6);
  list.Insert(-5);
  list.Insert(3);
  list.Insert(4);
  list.Insert(5);
  list.Insert(-10);

  list.DisplayAllLevels();
  std::cout << std::endl;

  list.Remove(-5);

  std::cout << "After removing -5:" << std::endl;
  list.DisplayAllLevels();
}
