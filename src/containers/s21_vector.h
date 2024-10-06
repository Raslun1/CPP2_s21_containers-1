#ifndef CPP_S21_CONTAINERS_VECTOR_H
#define CPP_S21_CONTAINERS_VECTOR_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator_ptr = T*;
  using const_iterator_ptr = const T*;
  using size_type = size_t;

  class VectorIterator {
   public:
    friend class vector;
    VectorIterator() = default;
    VectorIterator(iterator_ptr ptr) : iterator_ptr_(ptr) {}
    VectorIterator& operator--() {
      --iterator_ptr_;
      return *this;
    }
    VectorIterator operator--(int) {
      VectorIterator temp{*this};
      --(*this);
      return temp;
    }
    VectorIterator& operator++() {
      ++iterator_ptr_;
      return *this;
    }
    VectorIterator operator++(int) {
      VectorIterator temp{*this};
      ++(*this);
      return temp;
    }
    bool operator==(const VectorIterator& other) const {
      return iterator_ptr_ == other.iterator_ptr_;
    }
    bool operator!=(const VectorIterator& other) const {
      return iterator_ptr_ != other.iterator_ptr_;
    }
    reference operator*() const { return *iterator_ptr_; }
    size_type operator-(VectorIterator other) {
      return iterator_ptr_ - other.iterator_ptr_;
    }
    VectorIterator operator+(size_type value) {
      return VectorIterator(iterator_ptr_ + value);
    }
    VectorIterator operator-(size_type value) {
      return VectorIterator(iterator_ptr_ - value);
    }

   protected:
    iterator_ptr iterator_ptr_;
  };

  class ConstVectorIterator : public VectorIterator {
   public:
    ConstVectorIterator() = default;
    ConstVectorIterator(iterator_ptr ptr) : VectorIterator(ptr) {}
    ConstVectorIterator(const VectorIterator& other) : VectorIterator(other) {}
  };

 public:
  using iterator = VectorIterator;
  using const_iterator = ConstVectorIterator;

  vector() : data_(nullptr), size_(0), capacity_(0) {}
  vector(size_type n) : data_(new value_type[n]()), size_(0), capacity_(n) {}
  vector(std::initializer_list<value_type> const& items)
      : size_(items.size()), capacity_(items.size()) {
    this->data_ = new value_type[this->size_];
    std::copy(items.begin(), items.end(), this->data_);
  }
  vector(const vector& v) : vector() {
    for (const_iterator el = v.begin(); el != v.end(); el++) {
      this->push_back(*el);
    }
  }
  vector(vector&& v) : vector(v) { v.clear(); }
  ~vector() { this->clear(); }
  vector& operator=(vector&& v) {
    if (this != &v) {
      delete[] this->data_;

      this->data_ = v.data_;
      this->size_ = v.size_;
      this->capacity_ = v.capacity_;

      v.data_ = nullptr;
      v.size_ = 0;
      v.capacity_ = 0;
    }

    return *this;
  }

  vector& operator=(const vector& v) {
    if (this != &v) {
      delete[] this->data_;
      this->size_ = 0;
      this->capacity_ = 0;

      for (iterator it = v.begin(); it != v.end(); it++) {
        this->push_back(*it);
      }
    }

    return *this;
  }

  reference at(size_type pos) {
    if (pos >= this->size_) {
      throw std::out_of_range("Pos out of range");
    }
    return this->data_[pos];
  }
  reference operator[](size_type pos) { return *(this->data_ + pos); }
  const_reference front() { return this->data_[0]; }
  const_reference back() { return this->data_[this->size_ - 1]; }
  T* data() { return this->data_; }

  iterator begin() { return iterator(this->data_); }
  iterator end() { return iterator(this->data_ + this->size_); }
  const_iterator begin() const { return const_iterator(this->data_); }
  const_iterator end() const {
    return const_iterator(this->data_ + this->size_);
  }

  bool empty() const { return this->size_ == 0; }
  size_type size() const { return this->size_; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }
  void reserve(size_type size) {
    if (size > this->max_size()) {
      throw std::out_of_range("New capacity out of range");
    }

    if (size > this->capacity()) {
      iterator_ptr new_data = new value_type[size];
      std::copy(this->data_, this->data_ + this->size_, new_data);

      delete[] this->data_;
      this->data_ = new_data;
      this->capacity_ = size;
    }
  }
  size_type capacity() const { return this->capacity_; }
  void shrink_to_fit() {
    if (this->size_ < this->capacity_) {
      iterator_ptr temp_vector = new value_type[this->size_];
      std::copy(this->data_, this->data_ + this->size_, temp_vector);

      delete[] this->data_;

      this->data_ = temp_vector;
      this->capacity_ = this->size_;
    }
  }

  void clear() {
    if (this->data_ != nullptr) {
      delete[] this->data_;
      this->data_ = nullptr;
      this->size_ = 0;
    }
  }
  iterator insert(iterator pos, const_reference value) {
    iterator_ptr temp_vector = new value_type[this->size_ + 1];

    size_type index = pos - this->begin();

    for (size_type i = 0; i < index; i++) {
      temp_vector[i] = this->data_[i];
    }

    temp_vector[index] = value;

    for (size_type i = index; i < this->size_; i++) {
      temp_vector[i + 1] = this->data_[i];
    }

    delete[] this->data_;
    this->data_ = temp_vector;
    this->size_++;

    return this->begin() + index;
  }
  void erase(iterator pos) {
    iterator_ptr temp_vector = new value_type[this->size_ - 1];

    size_type index = 0;

    for (size_type i = 0; i < this->size_; i++) {
      if (pos - this->begin() == i) {
        continue;
      }
      temp_vector[index++] = this->data_[i];
    }

    delete[] this->data_;
    this->data_ = temp_vector;
    this->size_--;
  }
  void push_back(const_reference value) {
    if (this->size_ == this->capacity_) {
      size_type new_capacity = (this->capacity_ == 0) ? 1 : this->capacity_ * 2;
      this->reserve(new_capacity);
    }
    this->data_[this->size_++] = value;
  }
  void pop_back() {
    if (this->size_ > 0) {
      this->size_--;
    }
  }
  void swap(vector& other) {
    std::swap(this->data_, other.data_);
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    // Создаю временный вектор для новых элементов
    s21::vector<value_type> arguments{args...};

    size_type new_size = this->size_ + arguments.size();
    iterator_ptr temp_vector = new value_type[new_size];

    size_type pos_index = pos - this->begin();

    // Копирую элементы до позиции вставки
    for (size_type i = 0; i < pos_index; ++i) {
      temp_vector[i] = this->data_[i];
    }

    // Вставляю новые элементы
    for (size_type i = 0; i < arguments.size(); ++i) {
      temp_vector[pos_index + i] = arguments[i];
    }

    // Копирую оставшиеся элементы после позиции вставки
    for (size_type i = pos_index; i < this->size_; ++i) {
      temp_vector[i + arguments.size()] = this->data_[i];
    }

    delete[] this->data_;
    this->data_ = temp_vector;
    this->size_ = new_size;
    this->reserve(this->size_);

    return this->begin() + pos_index;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    this->insert_many(this->end(), args...);
  }

 private:
  iterator_ptr data_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21

#endif