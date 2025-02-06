#ifndef HASHCOKOOTABLE_H
#define HASHCOKOOTABLE_H

#include <stdexcept>
#include <vector>

struct HashTableElement {
  int key;
  int value;
  bool empty;

  HashTableElement() : key(0), value(0), empty(true) {
  }

  HashTableElement(int k, int v) : key(k), value(v), empty(false) {
  }

  bool operator==(const HashTableElement& other) const {
    return key == other.key && value == other.value && empty == other.empty;
  }
};

struct HashCokooTable {
  std::vector<HashTableElement> table1_;
  std::vector<HashTableElement> table2_;
  int table_size_;

 public:
  explicit HashCokooTable(int table_size) {
    if (table_size <= 0) {
      throw std::invalid_argument("Table size must be positive");
    }

    table_size_ = table_size;
    table1_.resize(table_size, HashTableElement());
    table2_.resize(table_size, HashTableElement());
  }

  bool Insert(int key, int value) {
    int pos1 = hash1(key);
    int currKey = key;
    int currValue = value;

    int started_with_pos = pos1;
    for (bool just_started = true;;) {
      // Проверим на цикл
      if (!just_started && pos1 == started_with_pos) {
        return false;
      }
      just_started = false;

      // Пытаемся вставить в первую таблицу
      if (table1_[pos1].empty) {
        table1_[pos1] = HashTableElement(currKey, currValue);
        return true;
      }

      // Вставляем элемент в первую таблицу
      int oldKey = table1_[pos1].key;
      int oldValue = table1_[pos1].value;
      table1_[pos1] = HashTableElement(currKey, currValue);

      // Вычисляем позицию для второй таблицы
      int pos2 = hash2(oldKey);
      if (table2_[pos2].empty) {
        // Просто вставляем
        table2_[pos2] = HashTableElement(oldKey, oldValue);
        return true;
      }

      // Пытаемся вставить в первую таблицу и записываем во вторуб
      currKey = table2_[pos2].key;
      currValue = table2_[pos2].value;
      table2_[pos2] = HashTableElement(oldKey, oldValue);
      pos1 = hash1(currKey);
    }
  }

  int Find(int key) {
    int pos1 = hash1(key);
    if (!table1_[pos1].empty && table1_[pos1].key == key) {
      return table1_[pos1].value;
    }

    int pos2 = hash2(key);
    if (!table2_[pos2].empty && table2_[pos2].key == key) {
      return table2_[pos2].value;
    }

    return -1;  // Элемент не найден
  }

  int hash1(int key) const {
    return key % table_size_;
  }

  int hash2(int key) const {
    return (key / table_size_) % table_size_;
  }
};

#endif  // HASHCOKOOTABLE_H