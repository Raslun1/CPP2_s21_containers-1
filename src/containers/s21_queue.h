#ifndef CPP_S21_CONTAINERS_QUEUE_H
#define CPP_S21_CONTAINERS_QUEUE_H

#include <iostream>

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  queue() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}
  queue(std::initializer_list<value_type> const& items) noexcept
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (auto el : items) {
      this->push(el);
    }
  }
  queue(const queue& q) : head_(nullptr), tail_(nullptr), size_(0) {
    *this = q;
  }
  queue(queue&& q) : head_(q.head_), tail_(q.tail_), size_(q.size_) {
    q.head_ = nullptr;
    q.tail_ = nullptr;
    q.size_ = 0;
  }

  ~queue() {
    while (this->head_ != nullptr) {
      Node_* temp_queue = this->head_;
      this->head_ = this->head_->next_;
      delete temp_queue;
    }
    this->size_ = 0;
  }

  queue<T>& operator=(queue&& q) {
    if (this != &q) {
      while (this->head_ != nullptr) {
        this->pop();
      }

      this->head_ = q.head_;
      this->tail_ = q.tail_;
      this->size_ = q.size_;

      q.head_ = nullptr;
      q.tail_ = nullptr;
      q.size_ = 0;
    }

    return *this;
  }

  queue<T>& operator=(const queue& q) {
    if (this != &q) {
      // Очищаем текущую очередь
      while (this->head_ != nullptr) {
        this->pop();
      }

      // Копируем элементы из очереди q
      Node_* current = q.head_;
      while (current != nullptr) {
        this->push(current->value_);
        current = current->next_;
      }
    }

    return *this;
  }

  const_reference front() { return this->head_->value_; }
  const_reference back() { return this->tail_->value_; }

  bool empty() { return this->size_ == 0; }
  size_type size() { return this->size_; }

  void push(const_reference value) {
    Node_* new_node = new Node_(value);

    if (this->head_ == nullptr) {  // если это первый элемент, устанавливаю
                                   // указатели head tail на начало.
      this->head_ = new_node;
      this->tail_ = new_node;
    } else {  // если уже head не пустой, инициализирую next для связки с
              // прошлым элементом и вставляю новый элемент.
      this->tail_->next_ =
          new_node;  // раньше был this->tail = this->tail->next что
                     // неправильно, тк я не связывал очередь друг с
                     // другом(прошлый с нынешним)
      // и в конечном счете у меня оставалось только 2 элемета в очереди,
      // остальные просто терялись (обнаружил на pop())
      this->tail_ = new_node;
    }
    this->size_++;
  }

  void pop() {
    Node_* temp_queue = this->head_;
    this->head_ = this->head_->next_;
    delete temp_queue;
    this->size_--;

    if (this->head_ == nullptr) {
      this->tail_ = nullptr;
    }
  }

  void swap(queue& other) {
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
    std::swap(this->size_, other.size_);
  }
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    std::initializer_list<value_type> arguments{args...};
    for (value_type elem : arguments) {
      this->push(elem);
    }
  }

 private:
  typedef struct Node_ {
    value_type value_;
    Node_* next_;
    Node_(value_type value) : value_(value), next_(nullptr) {}
  } Node_;

  Node_* head_;
  Node_* tail_;
  size_type size_;
};

}  // namespace s21

#endif