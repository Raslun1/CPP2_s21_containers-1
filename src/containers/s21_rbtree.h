#ifndef CPP_S21_CONTAINERS_RBTREE_H
#define CPP_S21_CONTAINERS_RBTREE_H

#include <iostream>
#include <limits>
#include <utility>

#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T = Key>
class rbtree {
 protected:
  enum colors { RED, BLACK };
  struct Node {
    Node *left, *right, *parent;
    colors color;
    Key key;
    T value;
  };

 private:
  Node* root;

 protected:
  Node* getNode(const std::pair<Key, T>& value) {
    return getNodeRecursive(root, value);
  }
  Node* getNodeRecursive(Node* node, const std::pair<Key, T>& value) {
    if (node == nullptr) {
      return nullptr;
    }
    if (node->key == value.first && node->value == value.second) {
      return node;
    }

    if (value.first < node->key) {
      return getNodeRecursive(node->left, value);
    }
    return getNodeRecursive(node->right, value);
  }

 public:
  class TreeIterator {
    friend class rbtree;

   public:
    TreeIterator(Node* ptr = nullptr) : node_ptr(ptr) {}
    std::pair<Key, T> operator*() {
      if (node_ptr) {
        return {node_ptr->key, node_ptr->value};
      }
      return {0, 0};
    }

    T& getValue() { return node_ptr->value; }

    TreeIterator& operator--() {
      this->node_ptr = decrement_operator(this->node_ptr);
      return *this;
    }
    TreeIterator operator--(int) {
      TreeIterator copy{*this};
      --(*this);
      return copy;
    }
    TreeIterator& operator++() {
      this->node_ptr = increment_operator(this->node_ptr);
      return *this;
    }
    TreeIterator operator++(int) {
      TreeIterator copy{*this};
      ++(*this);
      return copy;
    }
    bool operator!=(const TreeIterator& right_iter) const {
      return node_ptr != right_iter.node_ptr;
    }
    bool operator==(const TreeIterator& right_iter) const {
      return node_ptr == right_iter.node_ptr;
    }

   protected:
    Node* decrement_operator(Node* node_ptr) {
      if (node_ptr->left == nullptr) {
        if (node_ptr->parent && node_ptr->key >= node_ptr->parent->key)
          node_ptr = node_ptr->parent;
        else {
          while (node_ptr->parent && node_ptr->key <= node_ptr->parent->key) {
            node_ptr = node_ptr->parent;
          }
          node_ptr = node_ptr->parent;
        }
      } else if (node_ptr->left) {
        node_ptr = node_ptr->left;
        while (node_ptr->right) node_ptr = node_ptr->right;
      }
      return node_ptr;
    }
    Node* increment_operator(Node* node_ptr) {
      if (node_ptr->right == nullptr) {
        if (node_ptr->parent && node_ptr->key <= node_ptr->parent->key)
          node_ptr = node_ptr->parent;
        else {
          while (node_ptr->parent && node_ptr->key >= node_ptr->parent->key) {
            node_ptr = node_ptr->parent;
          }  // дошел до старшего
          node_ptr = node_ptr->parent;
        }
      } else if (node_ptr->right) {
        node_ptr = node_ptr->right;
        while (node_ptr->left) node_ptr = node_ptr->left;
      }
      return node_ptr;
    }
    Node* node_ptr;
  };

  class ConstTreeIterator : public TreeIterator {
   public:
    ConstTreeIterator(Node* node) : TreeIterator(node) {}
  };
  using iterator = TreeIterator;
  using const_iterator = ConstTreeIterator;
  using size_type = size_t;

  rbtree() : root(nullptr) {}
  ~rbtree() { clear(); }

  Node* findMin() {
    Node* min_node = root;
    while (min_node->left) min_node = min_node->left;
    return min_node;
  }

  Node* findMax() {
    Node* max_node = root;
    while (max_node->right) max_node = max_node->right;
    return max_node;
  }

  Node* findMin() const {
    Node* min_node = root;
    while (min_node && min_node->left) {
      min_node = min_node->left;
    }
    return min_node;
  }

  Node* findMax() const {
    Node* max_node = root;
    while (max_node && max_node->right) {
      max_node = max_node->right;
    }
    return max_node;
  }

  std::pair<iterator, bool> create_tree(const std::pair<Key, T>& value) {
    root = new Node;
    root->color = BLACK;
    root->key = value.first;
    root->value = value.second;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    return {iterator(root), true};
  }

  Node* create_node(const std::pair<Key, T>& value) {
    Node* newNode = new Node;
    newNode->color = RED;
    newNode->key = value.first;
    newNode->value = value.second;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;
    return newNode;
  }
  iterator begin() {
    if (size() == 0) return end();
    Node* ptr = findMin();
    return iterator(ptr);
  }

  iterator end() { return iterator(nullptr); }

  const_iterator begin() const {
    if (size() == 0) return end();
    Node* ptr = findMin();
    return const_iterator(ptr);
  }

  const_iterator end() const { return const_iterator(nullptr); }

  void InsertFix(Node* node) {
    if (node == root) return;
    while (
        node->parent && node->parent->parent &&
        node->parent->color ==
            RED) {  // новая нода - всегда красная, поэтому проверка ноды выше
      Node* parent = node->parent;
      Node* ded = parent->parent;
      if (ded->left == parent) {  // отец - левый сын
        if (ded->right &&
            ded->right->color ==
                RED) {  // если есть красный дядя, то просто меняем цвета
          parent->color = BLACK;
          ded->right->color = BLACK;
          ded->color = RED;
          node = ded;  // проверяем все тоже самое на деде, тк родитель деда
                       // может быть красным
        } else {  // тогда нам не важен вообще дядя
          if (parent->right ==
              node) {  // если сын правый, то нужно поворот по родителю влево
            node = parent;
            rotateLeft(node);  // при повороте родитель и сын становятся сыном и
                               // родителем
            node->color = BLACK;  // node теперь родитель
          } else
            parent->color = BLACK;
          ded->color = RED;
          rotateRight(ded);
        }
      } else {  // отец - правый сын . тут все тоже самое, только разворот в
                // другую сторону, тк на другой ветке.
        if (ded->left && ded->left->color == RED) {
          parent->color = BLACK;
          ded->left->color = BLACK;
          ded->color = RED;
          node = ded;
        } else {
          if (parent->left == node) {
            node = parent;
            rotateRight(node);
            node->color = BLACK;
          } else
            parent->color = BLACK;
          ded->color = RED;
          rotateLeft(ded);
        }
      }
    }
    root->color = BLACK;
  }

  std::pair<iterator, bool> insert(const std::pair<Key, T>& value) {
    if (root == nullptr) return create_tree(value);
    Node *current_node = root, *current_parent = nullptr,
         *newNode = create_node(value);
    bool duplicate = false;
    while (current_node != nullptr) {
      current_parent = current_node;
      if (value.first < current_node->key) {
        current_node = current_node->left;
      } else if (value.first > current_node->key) {
        current_node = current_node->right;
      } else {
        duplicate = true;
        newNode->parent = current_node;

        if (current_node->left) {
          newNode->left = current_node->left;
          current_node->left->parent = newNode;
        }
        current_node->left = newNode;
        break;
      }
    }
    if (!duplicate) {
      newNode->parent = current_parent;
      if (newNode->key <= current_parent->key)
        current_parent->left = newNode;
      else
        current_parent->right = newNode;
    }
    InsertFix(newNode);
    return {iterator(newNode), true};
  }

  void rotateLeft(Node* node) {
    Node* new_parent = node->right;
    node->right = new_parent->left;
    if (node->right) {
      node->right->parent = node;
    }
    new_parent->parent = node->parent;
    if (node->parent == nullptr)
      root = new_parent;
    else if (node == node->parent->left)
      node->parent->left = new_parent;
    else
      node->parent->right = new_parent;
    node->parent = new_parent;
    new_parent->left = node;
  }
  void rotateRight(Node* node) {
    Node* new_parent = node->left;
    node->left = new_parent->right;
    if (node->left) {
      node->left->parent = node;
    }
    new_parent->parent = node->parent;
    if (node->parent == nullptr)
      root = new_parent;
    else if (node == node->parent->left)
      node->parent->left = new_parent;
    else
      node->parent->right = new_parent;
    node->parent = new_parent;
    new_parent->right = node;
  }

  void fixDelete(Node* parent) {
    int direction = parent->left ? 0 : 1;  // 0 - left 1 - right
    Node* node =
        parent->left ? parent->left : parent->right;  // node - брат удаленного
    if (node->color == BLACK) {                       // ЧЕРНЫЙ БРАТ

      if (node->right && node->right->color == RED) {
        node->color = parent->color;
        parent->color = BLACK;
        node->right->color = BLACK;
        rotateLeft(parent);
      } else if (node->left && node->right && node->left->color == RED &&
                 node->right->color == BLACK) {
        std::swap(node->left->color, node->color);
        rotateRight(node);
        fixDelete(parent);  // переход к случаю выше
      } else {
        node->color = RED;
        bool flag_fix = parent->color == BLACK;
        // std::cout << flag_fix;
        parent->color = BLACK;
        if (node->left) node->left->color = BLACK;
        if (flag_fix && parent != root) {
          fixDelete(parent);
        }
      }
    } else {
      parent->color = RED;
      node->color = BLACK;
      if (node->left) {
        node->left->color = BLACK;
      }
      if (node->right) {
        node->right->color = BLACK;
      }
      if (direction == 0) {
        rotateRight(parent);
      } else {
        rotateLeft(parent);
      }
      fixDelete(parent);
    }
    //}
  }

  void deleteNode(Node* node) {
    if (!node->left && !node->right) {  // 0
      if (node->color == RED) {
        if (node->parent->left == node)
          node->parent->left = nullptr;
        else
          node->parent->right = nullptr;
        delete node;
      } else {
        if (node == root) {
          delete node;
          root = nullptr;
        } else {
          Node* parent = node->parent;
          if (node->parent->left == node)
            node->parent->left = nullptr;
          else
            node->parent->right = nullptr;
          delete node;
          fixDelete(parent);
        }
      }
    } else if ((!node->left && node->right) ||
               (node->left && !node->right)) {  // 1
      if (node->color == RED) {
        throw std::out_of_range(
            "ERROR такой случай в правильном дереве невозможен");
      } else {
        Node* sswap = node->right ? node->right : node->left;
        std::swap(node->key, sswap->key);
        std::swap(node->value, sswap->value);
        deleteNode(sswap);
      }
    } else {  // 2
      Node* update = node->left;
      while (update->right) {
        update = update->right;
      }
      std::swap(update->key, node->key);
      std::swap(update->value, node->value);
      deleteNode(update);
    }
  }
  void erase(iterator pos) {
    if (pos != nullptr) {
      Node* node = getNode({(*pos).first, (*pos).second});
      deleteNode(node);
    }
  }

  void clear() {
    helper_clear(this->root);
    this->root = nullptr;
  }
  void helper_clear(Node* node) {
    if (node != nullptr) {
      helper_clear(node->left);
      helper_clear(node->right);
      delete node;
    }
  }
  size_type size() { return helper_in_order(this->root); }

  size_type size() const { return helper_in_order(this->root); }

  size_type helper_in_order(Node* node) const {
    if (node == nullptr) return 0;
    return 1 + helper_in_order(node->left) + helper_in_order(node->right);
  }

  void swap(rbtree& other) { std::swap(root, other.root); }

  void merge(rbtree& other) {
    for (iterator it = other.begin(); it != other.end(); it++) {
      this->insert({(*it).first, (*it).second});
    }
    other.clear();
  }

  iterator find(const Key& key) {
    for (iterator it = begin(); it != end(); it++) {
      if ((*it).first == key) return it;
    }
    return iterator(nullptr);
  }

  bool contains(const Key& key) {
    for (iterator it = begin(); it != end(); it++) {
      if ((*it).first == key) {
        return true;
      }
    }
    return false;
  }
  bool empty() { return this->root == nullptr; }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(rbtree<Key, T>) / 2;
  }

  void inorder(Node* node) const {
    if (node != nullptr) {
      inorder(node->left);
      if (node == root) std::cout << "root->";
      std::cout << node->key << " (" << (node->color == RED ? "RED" : "BLACK")
                << ")\n";
      inorder(node->right);
    }
  }

  void print() const { inorder(root); }
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> results;

    for (const auto& el : {args...}) {
      results.push_back(insert({el, el}));
    }

    return results;
  }
};
};  // namespace s21

#endif