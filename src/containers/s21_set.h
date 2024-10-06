#ifndef CPP_S21_CONTAINERS_SET_H
#define CPP_S21_CONTAINERS_SET_H

#include <set>

#include "s21_rbtree.h"
namespace s21 {
template <typename Key>
class set : public s21::rbtree<Key> {
 public:
  class SetIterator : public s21::rbtree<Key>::TreeIterator {
   public:
    SetIterator(typename s21::rbtree<Key>::Node *ptr = nullptr)
        : s21::rbtree<Key>::TreeIterator(ptr) {}
    Key operator*() { return this->node_ptr->key; }
  };
  class ConstSetIterator : public SetIterator {
   public:
    ConstSetIterator(typename s21::rbtree<Key>::Node *node)
        : SetIterator(node) {}
  };
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = SetIterator;
  using const_iterator = ConstSetIterator;
  set() : rbtree<Key>() {}

  set(std::initializer_list<value_type> const &items) {
    for (value_type item : items) {
      this->insert(item);
    }
  }
  set(const set &s) {
    for (const_iterator i = s.begin(); i != s.end(); i++) {
      this->insert(*i);
    }
  }
  set(set &&s) : set(s) { s.clear(); }
  ~set() = default;
  set &operator=(set &&s) {
    if (this != &s) {
      for (iterator i = s.begin(); i != s.end(); i++) {
        this->insert(*i);
      }
      s.clear();
    }
    return *this;
  }
  set &operator=(set &s) {
    if (this != &s) {
      for (iterator i = s.begin(); i != s.end(); i++) {
        this->insert(*i);
      }
    }
    return *this;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    if (this->contains(value)) return {iterator(nullptr), false};
    auto treeIter = rbtree<Key, Key>::insert({value, value});
    return {iterator(rbtree<Key>::getNode(
                {(*treeIter.first).first, (*treeIter.first).second})),
            treeIter.second};
  }

  void erase(iterator pos) {
    if (pos != nullptr)
      rbtree<Key, Key>::erase(typename rbtree<Key, Key>::TreeIterator(
          rbtree<Key, Key>::getNode({*pos, *pos})));
  }

  void swap(set &other) { rbtree<Key>::swap(other); }

  void merge(set &other) { rbtree<Key>::merge(other); }

  iterator begin() {
    if (rbtree<Key>::size() == 0) return end();
    return iterator(rbtree<Key>::findMin());
  }

  iterator end() { return iterator(nullptr); }
  const_iterator begin() const {
    if (rbtree<Key>::size() == 0) return end();
    return const_iterator(rbtree<Key>::findMin());
  }

  const_iterator end() const { return const_iterator(nullptr); }
  void clear() { rbtree<Key>::clear(); }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(set<Key>) / 2;
  }
  iterator find(const Key &key) {
    for (iterator it = begin(); it != end(); it++) {
      if (*it == key) return it;
    }
    return iterator(nullptr);
  }
};

}  // namespace s21

#endif