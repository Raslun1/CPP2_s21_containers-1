#ifndef CPP_S21_CONTAINERS_ARRAY_H
#define CPP_S21_CONTAINERS_ARRAY_H

#include <iostream>
#include <utility>

namespace s21 {
template <typename T, size_t template_size>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  array() : size_(template_size) {
    for (size_type i = 0; i < size_; i++) {
      this->array_[i] = 0;
    }
  }
  array(std::initializer_list<value_type> const& items) : size_(template_size) {
    size_t i = 0;
    for (const_reference el : items) {
      this->array_[i++] = el;
    }
  }
  array(const array& a) {
    for (size_type i = 0; i < a.size_; i++) {
      this->array_[i] = a.array_[i];
    }
  }
  array(array&& a) : array(a) {}
  ~array() {}
  array& operator=(const array& a) {
    if (this != &a) {
      for (size_type i = 0; i < a.size_; i++) {
        this->array_[i] = a.array_[i];
      }
    }
    return *this;
  }
  array& operator=(array&& a) {
    if (this != &a) {
      for (size_type i = 0; i < a.size_; i++) {
        this->array_[i] = std::move(a.array_[i]);
      }
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos > this->size_) {
      throw std::out_of_range("Out of range");
    }
    return *(this->array_ + pos);
  }
  reference operator[](size_type pos) { return *(this->array_ + pos); }
  const_reference front() { return *(this->array_); }
  const_reference back() { return *(this->array_ + this->size_ - 1); }
  iterator data() { return this->array_; }

  iterator begin() { return this->array_; }
  iterator end() { return this->array_ + this->size_; }

  bool empty() { return this->size_ == 0; }
  size_type size() { return this->size_; }
  size_type max_size() { return this->size(); }

  void swap(array& other) {
    std::swap(this->array_, other.array_);
    std::swap(this->size_, other.size_);
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < this->size_; i++) {
      this->array_[i] = value;
    }
  }

 private:
  size_type size_ = template_size;
  value_type array_[template_size];
};
};  // namespace s21

#endif