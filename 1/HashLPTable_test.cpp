#include "HashLPTable.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("INSERT", "[INSERT]") {

  // Проверка на вставку одного элемента
  SECTION("Insert one element") {
    HashLPTable table(10);
    table.Insert(15, 23);

    REQUIRE(table.table_[5].key == 15);
    REQUIRE(table.table_[5].value == 23);
    REQUIRE(table.table_[5].deleted == false);
  }

  // Проверка на вставку с разными хешами
  SECTION("Insert few elements with different cashes") {
    HashLPTable table(10);

    table.Insert(15, 23);
    table.Insert(4, 33);

    REQUIRE(table.table_[5].key == 15);
    REQUIRE(table.table_[5].value == 23);
    REQUIRE(table.table_[5].deleted == false);

    REQUIRE(table.table_[4].key == 4);
    REQUIRE(table.table_[4].value == 33);
    REQUIRE(table.table_[4].deleted == false);
  }

  // Проверка на вставку с одинаковыми хешами
  SECTION("Insert few elements with same cashes") {
    HashLPTable table(10);

    table.Insert(18, 23);
    table.Insert(8, 33);
    table.Insert(38, 43);

    REQUIRE(table.table_[8].key == 18);
    REQUIRE(table.table_[8].value == 23);
    REQUIRE(table.table_[8].deleted == false);

    REQUIRE(table.table_[9].key == 8);
    REQUIRE(table.table_[9].value == 33);
    REQUIRE(table.table_[9].deleted == false);

    REQUIRE(table.table_[0].key == 38);
    REQUIRE(table.table_[0].value == 43);
    REQUIRE(table.table_[0].deleted == false);
  }

  // Проверка на вставку элемента с тем же ключом (КРАЙНИЙ СЛУЧАЙ)
  SECTION("Insert element with same key") {
    HashLPTable table(10);

    table.Insert(18, 11);
    table.Insert(8, 55);
    table.Insert(18, 22);

    // Проверим, что этот элемент не вставился как новый
    REQUIRE(table.table_[0].deleted == true);

    // Проверим, что не испортил другой элемент
    REQUIRE(table.table_[9].key == 8);
    REQUIRE(table.table_[9].value == 55);
    REQUIRE(table.table_[9].deleted == false);

    // Проверим, что значение обновилось
    REQUIRE(table.table_[8].key == 18);
    REQUIRE(table.table_[8].value == 22);
    REQUIRE(table.table_[8].deleted == false);

    table.Insert(8, 44);
    // Проверим, что значение обновилось
    REQUIRE(table.table_[9].key == 8);
    REQUIRE(table.table_[9].value == 44);
    REQUIRE(table.table_[9].deleted == false);
  }

  // Проверка на вставку элемента в таблицу, которая заполнена (КРАЙНИЙ СЛУЧАЙ)
  SECTION("Insert element in full table") {
    HashLPTable table(2);

    table.Insert(18, 11);
    table.Insert(1, 3);

    // Попробуем вставить элемент
    table.Insert(8, 55);

    // Проверим, что таблица не изменилась
    REQUIRE(table.table_[0].key == 18);
    REQUIRE(table.table_[0].value == 11);
    REQUIRE(table.table_[0].deleted == false);

    REQUIRE(table.table_[1].key == 1);
    REQUIRE(table.table_[1].value == 3);
    REQUIRE(table.table_[1].deleted == false);
  }
}

TEST_CASE("SEARCH", "[SEARCH]") {

  // Проверка на поиск элемента
  SECTION("Search element") {
    HashLPTable table(10);

    table.Insert(15, 23);
    table.Insert(4, 33);

    REQUIRE(table.Search(15) == 23);
    REQUIRE(table.Search(4) == 33);
  }

  // Проверка на поиск элемента, которого нет
  SECTION("Search element that doesn't exist") {
    HashLPTable table(10);

    table.Insert(15, 23);
    table.Insert(4, 33);

    REQUIRE(table.Search(5) == -1);
    REQUIRE(table.Search(6) == -1);
  }

  // Проверка на поиск элемента, который был сдвинут при вставке
  SECTION("Search element that was moved") {
    HashLPTable table(10);

    table.Insert(18, 11);
    table.Insert(8, 55);
    table.Insert(38, 22);

    REQUIRE(table.Search(18) == 11);
    REQUIRE(table.Search(8) == 55);
    REQUIRE(table.Search(38) == 22);
  }
}

TEST_CASE("REMOVE", "[REMOVE]") {

  // Проверка на удаление элемента
  SECTION("Remove element") {
    HashLPTable table(10);

    table.Insert(15, 23);
    table.Insert(4, 33);

    table.Remove(15);
    REQUIRE(table.Search(15) == -1);
    REQUIRE(table.table_[5].deleted == true);
    REQUIRE(table.table_[4].deleted == false);  // Проверим, что другой элемент не пострадал

    table.Remove(4);
    REQUIRE(table.Search(4) == -1);
    REQUIRE(table.table_[4].deleted == true);
  }

  // Проверка на удаление элемента, которого нет
  SECTION("Remove element that doesn't exist") {
    HashLPTable table(10);

    table.Insert(15, 23);
    table.Insert(4, 33);
    table.Remove(5);

    // Проверим, что таблица не изменилась
    REQUIRE(table.table_[5].key == 15);
    REQUIRE(table.table_[5].value == 23);
    REQUIRE(table.table_[5].deleted == false);

    REQUIRE(table.table_[4].key == 4);
    REQUIRE(table.table_[4].value == 33);
    REQUIRE(table.table_[4].deleted == false);
  }

  // Проверка на удаление элемента, который был сдвинут при вставке
  SECTION("Remove element that was moved") {
    HashLPTable table(10);

    table.Insert(18, 11);
    table.Insert(8, 55);
    table.Insert(38, 22);

    table.Remove(18);
    REQUIRE(table.table_[8].deleted == true);
    REQUIRE(table.table_[9].deleted == false);
    REQUIRE(table.table_[0].deleted == false);

    table.Remove(8);
    REQUIRE(table.table_[9].deleted == true);
    REQUIRE(table.table_[0].deleted == false);

    table.Remove(38);
    REQUIRE(table.table_[0].deleted == true);
  }

  // Проверка на вставку элемента после удаления
  SECTION("Insert element after remove") {
    HashLPTable table(10);

    table.Insert(18, 11);
    table.Insert(8, 55);
    table.Insert(38, 22);

    table.Remove(8);
    table.Insert(49, 33);

    REQUIRE(table.table_[9].key == 49);
    REQUIRE(table.table_[9].value == 33);
    REQUIRE(table.table_[9].deleted == false);

    // Проверим, что search не сломался
    REQUIRE(table.Search(8) == -1);
    REQUIRE(table.Search(49) == 33);
    REQUIRE(table.Search(18) == 11);
    REQUIRE(table.Search(38) == 22);
  }
}