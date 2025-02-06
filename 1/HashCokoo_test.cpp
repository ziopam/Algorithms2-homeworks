#include "HashCokooTable.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("COKOO") {
  HashCokooTable table(11);

  table.Insert(20, 1);
  REQUIRE(table.table1_[9].key == 20);
  REQUIRE(table.Find(20) == 1);

  table.Insert(50, 2);
  REQUIRE(table.table1_[6].key == 50);
  REQUIRE(table.Find(50) == 2);

  table.Insert(53, 3);
  REQUIRE(table.table1_[9].key == 53);
  REQUIRE(table.table2_[1].key == 20);
  REQUIRE(table.table1_[6].key == 50);  // Проверим, что не испортился
  REQUIRE(table.Find(53) == 3);
  REQUIRE(table.Find(20) == 1);

  table.Insert(75, 4);
  REQUIRE(table.table1_[9].key == 75);
  REQUIRE(table.table2_[4].key == 53);

  table.Insert(100, 5);
  REQUIRE(table.table1_[1].key == 100);

  table.Insert(67, 6);
  REQUIRE(table.table1_[1].key == 67);
  REQUIRE(table.table2_[9].key == 100);

  table.Insert(105, 7);
  REQUIRE(table.table1_[6].key == 105);
  REQUIRE(table.table2_[4].key == 50);
  REQUIRE(table.table1_[9].key == 53);
  REQUIRE(table.table2_[6].key == 75);

  table.Insert(3, 8);
  REQUIRE(table.table1_[3].key == 3);

  table.Insert(36, 9);
  REQUIRE(table.table1_[3].key == 36);
  REQUIRE(table.table2_[0].key == 3);

  // Проверим, что все элементы на месте
  REQUIRE(table.Find(20) == 1);
  REQUIRE(table.Find(50) == 2);
  REQUIRE(table.Find(53) == 3);
  REQUIRE(table.Find(75) == 4);
  REQUIRE(table.Find(100) == 5);
  REQUIRE(table.Find(67) == 6);
  REQUIRE(table.Find(105) == 7);
  REQUIRE(table.Find(3) == 8);
  REQUIRE(table.Find(36) == 9);

  // Не рабочая вставка
  REQUIRE(table.Insert(39, 10) == false);

  // Проверим find
  REQUIRE(table.Find(99) == -1);
}