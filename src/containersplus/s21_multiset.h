#ifndef CPP_S21_CONTAINERS_MULTISET_H
#define CPP_S21_CONTAINERS_MULTISET_H

#include <iostream>

#include "../containers/s21_set.h"

namespace s21 {
template <typename Key>
class multiset : public s21::set<Key> {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename set<Key>::SetIterator;
  using const_iterator = typename set<Key>::ConstSetIterator;
  using size_type = size_t;

 public:
  multiset() : set<Key>() {}
  multiset(std::initializer_list<value_type> const& items) {
    for (value_type item : items) {
      this->insert(item);
    }
  }
  multiset(const multiset& ms) : set<Key>() {
    for (const_iterator i = ms.begin(); i != ms.end(); i++) {
      this->insert(*i);
    }
  }
  multiset(multiset&& ms) : multiset(ms) { ms.clear(); }
  ~multiset() = default;

  multiset& operator=(multiset&& ms) {
    if (this != &ms) {
      this->clear();
      for (iterator it = ms.begin(); it != ms.end(); it++) {
        this->insert(*it);
      }
      ms.clear();
    }
    return *this;
  }

  multiset& operator=(multiset& ms) {
    if (this != &ms) {
      this->clear();
      for (iterator it = ms.begin(); it != ms.end(); it++) {
        this->insert(*it);
      }
    }
    return *this;
  }

  iterator insert(const value_type& value) {
    auto treeIter = rbtree<Key, Key>::insert({value, value});
    return iterator(rbtree<Key>::getNode(
        {(*treeIter.first).first, (*treeIter.first).second}));
  }

  void swap(multiset& other) { rbtree<Key>::swap(other); }
  void merge(multiset& other) { rbtree<Key>::merge(other); }

  size_type count(const Key& key) {
    size_type counter = 0;
    for (iterator it = this->begin(); it != this->end(); it++) {
      if (*it == key) {
        counter++;
      }
    }
    return counter;
  }

  iterator find(const Key& key) {
    for (iterator it = this->begin(); it != this->end(); it++) {
      if (*it == key) {
        return it;
      }
    }
    return iterator(nullptr);
  }

  std::pair<iterator, iterator> equal_range(
      const Key& key) {  // возвращает диапазон элементов, соответствующих
                         // определенному ключу
    return {lower_bound(key), upper_bound(key)};
  }

  iterator lower_bound(const Key& key) {  // возвращает итератор на первый
                                          // элемент не меньше указанного ключа
    iterator it = this->begin();

    while (it != this->end()) {
      // если текущий элемент не меньше ключа, возвращаем этот итератор
      if (key <= *it) {
        return it;
      }
      ++it;
    }
    return this->end();
  }

  iterator upper_bound(const Key& key) {  // возвращает итератор на первый
                                          // элемент, больший указанного ключа
    iterator it = this->begin();

    // проходим по элементам контейнера
    while (it != this->end()) {
      // если текущий элемент строго больше ключа, возвращаем этот итератор
      if (key < *it) {
        return it;
      }
      ++it;
    }
    // если не найден элемент, строго больший ключа, возвращаем end()
    return this->end();
  }

  void erase(iterator pos) {
    if (pos != nullptr)
      rbtree<Key, Key>::erase(typename rbtree<Key, Key>::TreeIterator(
          rbtree<Key, Key>::getNode({*pos, *pos})));
  }
};
}  // namespace s21

#endif