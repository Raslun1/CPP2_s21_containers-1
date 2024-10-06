#ifndef CPP_S21_CONTAINERS_MAP_H
#define CPP_S21_CONTAINERS_MAP_H

#include "s21_rbtree.h"
#include "s21_vector.h"
namespace s21 {
template <typename Key, typename T>
class map : public s21::rbtree<Key, T> {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename rbtree<Key, T>::TreeIterator;
  using const_iterator = typename rbtree<Key, T>::ConstTreeIterator;
  using size_type = size_t;

 public:
  map() : rbtree<Key, T>(){};
  map(std::initializer_list<value_type> const& items) {
    for (value_type el : items) {
      this->insert(el);
    }
  }
  map(const map& m) {
    for (auto i = m.begin(); i != m.end(); i++) {
      this->insert(*i);
    }
  }
  map(map&& m) : map(m) { m.clear(); }
  ~map() = default;
  map& operator=(map&& m) {
    if (this != &m) {
      this->clear();
      for (auto i = m.begin(); i != m.end(); i++) {
        this->insert(*i);
      }
      m.clear();
    }
    return *this;
  }
  map& operator=(map& m) {
    if (this != &m) {
      this->clear();
      for (auto i = m.begin(); i != m.end(); i++) {
        this->insert(*i);
      }
    }
    return *this;
  }
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    if (this->contains(key)) return {iterator(nullptr), false};
    return rbtree<Key, T>::insert({key, obj});
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    return this->insert(value.first, value.second);
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    typename rbtree<Key, T>::Node* node = this->getNode({key, obj});

    if (node != nullptr) {
      iterator it = this->find(key);
      return {it, false};
    }

    if (this->contains(key)) {
      iterator it = this->find(key);
      this->erase(it);
    }

    return this->insert(key, obj);
  }

  T& at(const Key& key) {
    iterator it = rbtree<Key, T>::find(key);
    if (it == nullptr) {
      throw std::out_of_range("Out of range");
    }
    return it.getValue();
  }

  T& operator[](const Key& key) {
    iterator it = rbtree<Key, T>::find(key);
    if (it != nullptr) {
      return it.getValue();
    }
    std::pair<iterator, bool> result = this->insert(key, T());
    return result.first.getValue();
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> results;

    for (const auto& el : {args...}) {
      results.push_back(insert(el.first, el.second));
    }

    return results;
  }
};
}  // namespace s21

#endif