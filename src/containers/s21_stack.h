#ifndef CPP_S21_CONTAINERS_STACK_H
#define CPP_S21_CONTAINERS_STACK_H

#include <iostream>

namespace s21 {

template <typename T>

class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() noexcept : top_(nullptr), size_(0) {}
  stack(std::initializer_list<value_type> const &items) noexcept
      : top_(nullptr), size_(0) {
    for (value_type el : items) {
      push(el);
    }
  }
  stack(const stack &s) : top_(nullptr), size_(0) {
    Node_ *head = s.top_;
    stack<T> temp;
    while (head) {
      temp.push(head->value_);
      head = head->next_;
    }
    for (size_type i = 0; i < s.size_; i++) {
      push(temp.top());
      temp.pop();
    }
  }
  stack(stack &&s) : top_(s.top_), size_(s.size_) {
    s.top_ = nullptr;
    s.size_ = 0;
  }
  ~stack() {
    while (top_ != nullptr) {
      Node_ *tmp = top_;
      top_ = top_->next_;
      delete tmp;
    }
    size_ = 0;
  }
  stack<T> &operator=(stack &&s) {
    if (this != &s) {
      while (top_ != nullptr) {
        pop();
      }

      top_ = s.top_;
      size_ = s.size_;

      s.top_ = nullptr;
      s.size_ = 0;
    }

    return *this;
  }
  bool operator==(const stack<T> &st) const {
    if (size_ != st.size_) {
      return false;
    }

    stack<T> temp1 = *this;
    stack<T> temp2 = st;

    for (size_t i = 0; i < size_; i++) {
      if (temp1.top() != temp2.top()) {
        return false;
      }
      temp1.pop();
      temp2.pop();
    }

    return true;
  }

  const_reference top() const {
    if (top_ == nullptr) throw std::out_of_range("stack is empty");
    return top_->value_;
  }

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }

  void push(const_reference value) {
    Node_ *node = new Node_(value);

    if (top_ == nullptr) {
      top_ = node;
    } else {
      node->next_ = top_;
      top_ = node;
    }
    size_++;
  }
  void pop() {
    if (top_ == nullptr) throw std::out_of_range("stack is empty");
    Node_ *tmp_top = top_;
    top_ = tmp_top->next_;
    delete tmp_top;
    size_--;
  }
  void swap(stack &other) {
    std::swap(top_, other.top_);
    std::swap(size_, other.size_);
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    std::initializer_list<value_type> arguments{args...};
    for (value_type elem : arguments) {
      push(elem);
    }
  }

 private:
  typedef struct Node_ {
    value_type value_;
    Node_ *next_;
    Node_(value_type value) : value_(value), next_(nullptr) {}
  } Node_;

  Node_ *top_;
  size_type size_;
};

}  // namespace s21
#endif
