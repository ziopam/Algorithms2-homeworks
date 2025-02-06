#ifndef HASHLPTABLE_H
#define HASHLPTABLE_H

#include <stdexcept>
#include <vector>

struct HashTableElement {
  int key;
  int value;
  bool deleted;

  HashTableElement() {
    key = 0;
    value = 0;
    deleted = true;
  }

  HashTableElement(int key, int value) {
    this->key = key;
    this->value = value;
    deleted = false;
  }
};

struct HashLPTable {
  int table_size_;
  std::vector<HashTableElement> table_;

  explicit HashLPTable(int table_size) {
    if (table_size <= 0) {
      throw std::invalid_argument("Table size must be positive");
    }

    table_size_ = table_size;
    table_.resize(table_size);
  }

  void Insert(int key, int value) {
    int index = Hash(key);
    int index_in_table = index;
    for (int i = 0; i < table_size_; i++) {
      index_in_table = (index + i) % table_size_;

      // Если есть место для вставки или ключ уже есть в таблице
      if (table_[index_in_table].deleted || table_[index_in_table].key == key) {
        table_[index_in_table] = HashTableElement(key, value);
        return;
      }
    }
  }

  void Remove(int key) {
    int index = Hash(key);
    int index_in_table = index;
    for (int i = 0; i < table_size_; i++) {
      index_in_table = (index + i) % table_size_;

      // Если ключ найден
      if (table_[index_in_table].key == key) {
        table_[index_in_table].deleted = true;
        return;
      }
    }
  }

  int Search(int key) {
    int index = Hash(key);
    int index_in_table = index;
    for (int i = 0; i < table_size_; i++) {
      index_in_table = (index + i) % table_size_;

      // Если ключ найден
      if (!table_[index_in_table].deleted && table_[index_in_table].key == key) {
        return table_[index_in_table].value;
      }
    }

    // Будем предполагать, что значение не может быть отрицательным
    return -1;
  }

  int Hash(int key) {
    return key % table_size_;
  }
};

#endif  // HASHLPTABLE_H