#ifndef CPP_S21_CONTAINERS_LIST_H
#define CPP_S21_CONTAINERS_LIST_H

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  struct Node_ {
    value_type data_;
    Node_* next_;
    Node_* prev_;
    Node_(value_type value) : data_(value), next_(nullptr), prev_(nullptr) {}
  };
  Node_* head_;
  Node_* tail_;
  size_type size_;

  class ListIterator {
   public:
    friend class list;
    ListIterator(Node_* ptr = nullptr) : node_ptr_(ptr) {}
    ListIterator& operator--() {  // префиксный
      if (node_ptr_ != nullptr) {
        node_ptr_ = node_ptr_->prev_;
      }
      return *this;
    }
    ListIterator operator--(int) {  // постфиксный
      ListIterator temp{*this};
      --(*this);
      return temp;
    }
    ListIterator& operator++() {
      if (node_ptr_ != nullptr) {
        node_ptr_ = node_ptr_->next_;
      }
      return *this;
      // node_ptr_ = node_ptr_->next_;
      // return *this;
    }
    ListIterator operator++(int) {
      ListIterator temp{*this};
      ++(*this);
      return temp;
    }
    ListIterator operator+=(value_type value) {
      while (value--) {
        node_ptr_ = node_ptr_->next_;
      }
      return ListIterator(*this);
    }
    bool operator==(const ListIterator& other) const {
      return node_ptr_ == other.node_ptr_;
    }
    bool operator!=(const ListIterator& other) const {
      return node_ptr_ != other.node_ptr_;
    }
    reference operator*() const { return node_ptr_->data_; }

   protected:
    Node_* node_ptr_;
  };

  class ConstListIterator : public ListIterator {
   public:
    ConstListIterator(Node_* node) : ListIterator(node) {}
  };

 public:
  using iterator = ListIterator;
  using const_iterator = ConstListIterator;

  list() : head_(nullptr), tail_(nullptr), size_(0) {}
  list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
    for (size_type i = 0; i < n; i++) {
      this->push_back(T());
    }
  }
  list(std::initializer_list<value_type> const& items)
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (value_type el : items) {
      push_back(el);
    }
  }
  list(const list& l) : head_(nullptr), tail_(nullptr), size_(0) {
    for (const_iterator el = l.begin(); el != l.end(); el++) {
      this->push_back(*el);
    }
  }
  list(list&& l) : list(l) { l.clear(); }

  ~list() { this->clear(); }
  list& operator=(list&& l) {
    if (this != &l) {
      this->clear();
      for (iterator i = l.begin(); i != l.end(); i++) {
        this->push_back(*i);
      }
      l.clear();
    }
    return *this;
  }

  list& operator=(list& l) {
    if (this != &l) {
      this->clear();
      for (iterator i = l.begin(); i != l.end(); i++) {
        this->push_back(*i);
      }
    }
    return *this;
  }

  const_reference front() { return this->head_->data_; }
  const_reference back() { return this->tail_->data_; }

  iterator begin() { return iterator(this->head_); }
  iterator end() { return iterator(nullptr); }
  const_iterator begin() const { return const_iterator(this->head_); }
  const_iterator end() const { return const_iterator(nullptr); }
  const_iterator cbegin() const { return const_iterator(this->head_); }
  const_iterator cend() const { return const_iterator(nullptr); }
  bool empty() { return this->size_ == 0; }
  size_type size() { return this->size_; }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Node_) / 2;
  }

  void clear() {
    Node_* current_node = this->head_;
    while (current_node != nullptr) {
      Node_* next_node = current_node->next_;
      delete current_node;
      current_node = next_node;
    }
    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = 0;
  }
  iterator insert(iterator pos, const_reference value) {
    if (this->head_ == nullptr) {
      this->push_back(value);
      return this->begin();
    }

    Node_* current = this->head_;
    for (iterator it = this->begin(); it != pos; it++) {
      current = current->next_;
    }
    Node_* new_node = new Node_(value);
    if (current == nullptr) {
      current = head_;
      while (current->next_) current = current->next_;
      current->next_ = new_node;
      new_node->prev_ = current;
      tail_ = new_node;
    } else {
      if (current->prev_) {
        current->prev_->next_ = new_node;  // указывает на element data_ 3.5
        new_node->prev_ =
            current->prev_;  //  ставим новой ноде значение предыдущей ноды(3)
      } else
        head_ = new_node;
      current->prev_ = new_node;  // устаналвиаем новое значнеие
      new_node->next_ = current;  // связываем со следущим элементом.
    }
    this->size_++;

    return iterator(current->prev_);
  }
  void erase(iterator pos) {
    if (pos == end()) {
      throw std::out_of_range("OUT OF RANGE");
    }
    if (pos == nullptr || this->head_ == nullptr) {
      return;
    }

    Node_* current = this->head_;

    for (iterator it = this->begin(); it != pos; it++) {
      current = current->next_;
    }

    if (current == this->head_) {
      this->pop_front();
    } else if (current == this->tail_) {
      this->pop_back();
    } else {
      current->prev_->next_ = current->next_;
      current->next_->prev_ = current->prev_;
      delete current;
      this->size_--;
    }
  }
  void pop_back() {
    if (this->tail_ != nullptr) {
      Node_* deleted_tail = this->tail_;

      if (this->head_ == this->tail_) {
        this->head_ = nullptr;
        this->tail_ = nullptr;
      } else {
        this->tail_ = this->tail_->prev_;
        this->tail_->next_ = nullptr;
      }
      delete deleted_tail;
      this->size_--;
    }
  }
  void pop_front() {
    if (this->head_ != nullptr) {
      Node_* deleted_head = this->head_;
      this->head_ = this->head_->next_;
      if (this->head_ != nullptr) {
        this->head_->prev_ = nullptr;
      } else {
        this->tail_ = nullptr;
      }
      delete deleted_head;
      this->size_--;
    }
  }
  void push_front(const_reference value) {
    if (this->head_ == nullptr) {
      this->push_back(value);
    } else {
      Node_* new_node = new Node_(value);
      new_node->next_ = this->head_;
      this->head_->prev_ = new_node;
      this->head_ = new_node;
    }
    this->size_++;
  }
  void push_back(const_reference value) {
    Node_* new_node = new Node_(value);

    if (this->head_ == nullptr) {
      this->head_ = new_node;
      this->tail_ = new_node;
    } else {
      new_node->prev_ =
          this->tail_;  // связываю новый узел с текущим хвостом ( то есть
                        // указатель на предыдущий элемент)
      this->tail_->next_ = new_node;  // связываю текущий хвост с новым узлом
      this->tail_ = new_node;  // устанавливаю значение на новый хвост.
    }
    this->size_++;
  }
  void swap(list& other) {
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
    std::swap(this->size_, other.size_);
  }

  void reverse() {
    if (head_ != nullptr && head_->next_ != nullptr) {
      Node_* current = head_;
      Node_* temp = nullptr;

      while (current != nullptr) {
        temp = current->prev_;
        current->prev_ = current->next_;
        current->next_ = temp;
        current = current->prev_;
      }

      if (temp != nullptr) {
        tail_ = head_;
        head_ = temp->prev_;
      }
    }
  }
  void unique() {
    if (head_ != nullptr && head_->next_ != nullptr) {
      Node_* current = head_;
      while (current != nullptr && current->next_ != nullptr) {
        if (current->data_ == current->next_->data_) {
          Node_* duplicate = current->next_;
          current->next_ = duplicate->next_;
          if (duplicate->next_ != nullptr)
            duplicate->next_->prev_ = current;
          else
            tail_ = current;
          delete duplicate;
        } else
          current = current->next_;
      }
    }
  }

  void splice(const_iterator pos, list& other) {
    if (other.size() != 0) {
      for (auto item : other) {
        insert(pos, item);
      }
    }
  }
  void merge(list& other) {
    if (other.size() != 0) {
      iterator pos1 = begin();
      iterator pos2 = other.begin();
      while (pos2 != other.end()) {
        if (pos1 == end() || *pos1 >= *pos2) {
          insert(pos1, *pos2);
          ++pos2;
        } else
          ++pos1;
      }
      other.clear();
    }
  }

  Node_* split(Node_* head_) {
    Node_* slow = head_;
    Node_* fast = head_;

    while (fast->next_ != nullptr && fast->next_->next_ != nullptr) {
      slow = slow->next_;
      fast = fast->next_->next_;
    }

    Node_* second_half = slow->next_;
    slow->next_ = nullptr;
    if (second_half != nullptr) second_half->prev_ = nullptr;

    return second_half;
  }

  Node_* merge(Node_* first, Node_* second) {
    if (!first) return second;
    if (!second) return first;

    if (first->data_ < second->data_) {
      first->next_ = merge(first->next_, second);
      if (first->next_) first->next_->prev_ = first;

      first->prev_ = nullptr;
      return first;
    } else {
      second->next_ = merge(first, second->next_);
      if (second->next_) second->next_->prev_ = second;

      second->prev_ = nullptr;
      return second;
    }
  }

  Node_* mergeSort(Node_* head_) {
    if (!head_ || !head_->next_) return head_;
    Node_* second = split(head_);
    head_ = mergeSort(head_);
    second = mergeSort(second);
    return merge(head_, second);
  }

  void sort() {
    if (head_ != nullptr && head_->next_ != nullptr) {
      head_ = mergeSort(head_);
      tail_ = head_;
      while (tail_->next_ != nullptr) {
        tail_ = tail_->next_;
      }
    }
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    std::initializer_list<value_type> arguments{args...};
    iterator current_pos = nullptr;
    for (auto elem : arguments) {
      current_pos = insert(pos, elem);
    }
    return current_pos;
  }
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    std::initializer_list<value_type> arguments{args...};
    for (auto elem : arguments) {
      push_back(elem);
    }
  }
  template <typename... Args>
  void insert_many_front(Args&&... args) {
    std::initializer_list<value_type> arguments{args...};
    for (auto elem : arguments) {
      push_front(elem);
    }
  }
};
}  // namespace s21

#endif