#include <chrono>
#include <iostream>

#include "B&B.h"
#include "Backpack.h"

int main() {
  BB bb(5);
  bb.AddItem(2, 40);
  bb.AddItem(3.14, 50);
  bb.AddItem(1.98, 100);
  bb.AddItem(5, 95);
  bb.AddItem(3, 30);

  Backpack backpack(500);
  backpack.AddItem(200, 40);
  backpack.AddItem(314, 50);
  backpack.AddItem(198, 100);
  backpack.AddItem(500, 95);
  backpack.AddItem(300, 30);

  auto start = std::chrono::high_resolution_clock::now();
  double bb_result = bb.Pack();
  auto end = std::chrono::high_resolution_clock::now();
  auto bb_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << "B&B result: " << bb_result << ", duration: " << bb_duration << " nanoseconds\n";

  start = std::chrono::high_resolution_clock::now();
  int backpack_result = backpack.Pack();
  end = std::chrono::high_resolution_clock::now();
  auto backpack_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
  std::cout << "Backpack result: " << backpack_result << ", duration: " << backpack_duration << " nanoseconds\n";

  return 0;
}