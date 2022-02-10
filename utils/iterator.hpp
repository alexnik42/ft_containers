/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:44:11 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/10 21:21:46 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "red_black_tree.hpp"

namespace ft {

template <typename T>
class RandomAccessIterator {
 public:
  typedef typename std::random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;

  RandomAccessIterator() : _ptr(nullptr){};
  RandomAccessIterator(pointer ptr) : _ptr(ptr){};
  RandomAccessIterator(const RandomAccessIterator& other) { *this = other; };

  RandomAccessIterator& operator=(const RandomAccessIterator& other) {
    _ptr = other._ptr;
    return *this;
  };

  reference operator*() { return *_ptr; }
  pointer operator->() { return _ptr; }

  const_reference operator*() const { return *_ptr; }
  const_pointer operator->() const { return _ptr; }

  RandomAccessIterator operator++() {
    ++_ptr;
    return *this;
  }

  RandomAccessIterator operator++(int) {
    RandomAccessIterator tmp = *this;
    ++_ptr;
    return tmp;
  }

  RandomAccessIterator operator--() {
    --_ptr;
    return *this;
  }

  RandomAccessIterator operator--(int) {
    RandomAccessIterator tmp = *this;
    --_ptr;
    return tmp;
  }

  RandomAccessIterator& operator+=(difference_type n) {
    _ptr += n;
    return *this;
  }

  RandomAccessIterator operator+(difference_type n) {
    RandomAccessIterator copy = *this;
    copy += n;
    return copy;
  }

  RandomAccessIterator& operator-=(difference_type n) {
    _ptr -= n;
    return *this;
  }

  RandomAccessIterator operator-(difference_type n) {
    RandomAccessIterator copy = *this;
    copy -= n;
    return copy;
  }

  friend difference_type operator-(const RandomAccessIterator& lhs,
                                   const RandomAccessIterator& rhs) {
    return lhs._ptr - rhs._ptr;
  }

  friend bool operator==(const RandomAccessIterator& lhs,
                         const RandomAccessIterator& rhs) {
    return lhs._ptr == rhs._ptr;
  }
  friend bool operator!=(const RandomAccessIterator& lhs,
                         const RandomAccessIterator& rhs) {
    return lhs._ptr != rhs._ptr;
  }
  friend bool operator>(const RandomAccessIterator& lhs,
                        const RandomAccessIterator& rhs) {
    return lhs._ptr > rhs._ptr;
  }
  friend bool operator>=(const RandomAccessIterator& lhs,
                         const RandomAccessIterator& rhs) {
    return lhs._ptr >= rhs._ptr;
  }
  friend bool operator<(const RandomAccessIterator& lhs,
                        const RandomAccessIterator& rhs) {
    return lhs._ptr < rhs._ptr;
  }
  friend bool operator<=(const RandomAccessIterator& lhs,
                         const RandomAccessIterator& rhs) {
    return lhs._ptr <= rhs._ptr;
  }

 private:
  pointer _ptr;
};

template <typename T>
class ReverseIterator {
 public:
  typedef typename std::random_access_iterator_tag iterator_category;
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;

  ReverseIterator() : _ptr(nullptr){};
  ReverseIterator(pointer ptr) : _ptr(ptr){};
  ReverseIterator(const ReverseIterator& other) { *this = other; };

  ReverseIterator& operator=(const ReverseIterator& other) {
    _ptr = other._ptr;
    return *this;
  };

  reference operator*() { return *_ptr; }
  pointer operator->() { return _ptr; }

  const_reference operator*() const { return *_ptr; }
  const_pointer operator->() const { return _ptr; }

  ReverseIterator operator++() {
    --_ptr;
    return *this;
  }

  ReverseIterator operator++(int) {
    ReverseIterator tmp = *this;
    --_ptr;
    return tmp;
  }

  ReverseIterator operator--() {
    ++_ptr;
    return *this;
  }

  ReverseIterator operator--(int) {
    ReverseIterator tmp = *this;
    ++_ptr;
    return tmp;
  }

  ReverseIterator& operator+=(difference_type n) {
    _ptr -= n;
    return *this;
  }

  ReverseIterator operator+(difference_type n) {
    ReverseIterator copy = *this;
    copy += n;
    return copy;
  }

  ReverseIterator& operator-=(difference_type n) {
    _ptr += n;
    return *this;
  }

  ReverseIterator operator-(difference_type n) {
    ReverseIterator copy = *this;
    copy -= n;
    return copy;
  }

  friend difference_type operator-(const ReverseIterator& lhs,
                                   const ReverseIterator& rhs) {
    return rhs._ptr - lhs._ptr;
  }

  friend bool operator==(const ReverseIterator& lhs,
                         const ReverseIterator& rhs) {
    return lhs._ptr == rhs._ptr;
  }
  friend bool operator!=(const ReverseIterator& lhs,
                         const ReverseIterator& rhs) {
    return lhs._ptr != rhs._ptr;
  }
  friend bool operator>(const ReverseIterator& lhs,
                        const ReverseIterator& rhs) {
    return lhs._ptr < rhs._ptr;
  }
  friend bool operator>=(const ReverseIterator& lhs,
                         const ReverseIterator& rhs) {
    return lhs._ptr <= rhs._ptr;
  }
  friend bool operator<(const ReverseIterator& lhs,
                        const ReverseIterator& rhs) {
    return lhs._ptr > rhs._ptr;
  }
  friend bool operator<=(const ReverseIterator& lhs,
                         const ReverseIterator& rhs) {
    return lhs._ptr >= rhs._ptr;
  }

 private:
  pointer _ptr;
};

template <typename Key, typename T>
class RBTreeIterator {
 public:
  typedef typename std::bidirectional_iterator_tag iterator_category;

  typedef Node<const Key, T> node;
  typedef node* node_pointer;

  typedef std::ptrdiff_t difference_type;

  typedef Pair<const Key, T> value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;

 private:
  node_pointer _ptr;

 public:
  RBTreeIterator() : _ptr(nullptr){};
  RBTreeIterator(node_pointer ptr) : _ptr(ptr){};
  RBTreeIterator(const RBTreeIterator& other) { *this = other; };

  RBTreeIterator& operator=(const RBTreeIterator& other) {
    _ptr = other._ptr;
    return *this;
  };

  reference operator*() { return _ptr->data; }
  pointer operator->() { return &(_ptr->data); }

  const_reference operator*() const { return _ptr->data; }
  const_pointer operator->() const { return &(_ptr->data); }

  RBTreeIterator operator++() {
    _ptr = successor(_ptr);
    return *this;
  }

  RBTreeIterator operator++(int) {
    RBTreeIterator tmp = *this;
    operator++();
    return tmp;
  }

  RBTreeIterator operator--() {
    _ptr = predecessor(_ptr);
    return *this;
  }

  RBTreeIterator operator--(int) {
    RBTreeIterator tmp = *this;
    operator--();
    return tmp;
  }

  friend bool operator==(const RBTreeIterator& lhs, const RBTreeIterator& rhs) {
    return lhs._ptr == rhs._ptr;
  }
  friend bool operator!=(const RBTreeIterator& lhs, const RBTreeIterator& rhs) {
    return lhs._ptr != rhs._ptr;
  }
  friend bool operator<(const RBTreeIterator& lhs, const RBTreeIterator& rhs) {
    return lhs._ptr < rhs._ptr;
  }
  friend bool operator<=(const RBTreeIterator& lhs, const RBTreeIterator& rhs) {
    return lhs._ptr <= rhs._ptr;
  }
  friend bool operator>(const RBTreeIterator& lhs, const RBTreeIterator& rhs) {
    return lhs._ptr < rhs._ptr;
  }
  friend bool operator>=(const RBTreeIterator& lhs, const RBTreeIterator& rhs) {
    return lhs._ptr < rhs._ptr;
  }

 private:
  node_pointer getMinElementOnThePath(node_pointer node) {
    while (node && node->left) {
      node = node->left;
    }
    return node;
  }

  node_pointer getMaxElementOnThePath(node_pointer node) {
    while (node && node->right) {
      node = node->right;
    }
    return node;
  }

  node_pointer predecessor(node_pointer node) {
    if (node->left) {
      return getMaxElementOnThePath(node->left);
    } else {
      node_pointer parent = node->parent;
      while (parent && node == parent->left) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }
  }

  node_pointer successor(node_pointer node) {
    if (node->right) {
      return getMinElementOnThePath(node->right);
    } else {
      node_pointer parent = node->parent;
      while (parent && node == parent->right) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }
  }
};

template <typename Key, typename T>
class RBTreeReverseIterator {
 public:
  typedef typename std::bidirectional_iterator_tag iterator_category;

  typedef Node<Key, T> node;
  typedef node* node_pointer;

  typedef std::ptrdiff_t difference_type;

  typedef Pair<const Key, T> value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;

 private:
  node_pointer _ptr;

 public:
  RBTreeReverseIterator() : _ptr(nullptr){};
  RBTreeReverseIterator(node_pointer ptr) : _ptr(ptr){};
  RBTreeReverseIterator(const RBTreeReverseIterator& other) { *this = other; };

  RBTreeReverseIterator& operator=(const RBTreeReverseIterator& other) {
    _ptr = other._ptr;
    return *this;
  };

  reference operator*() { return _ptr->data; }
  pointer operator->() { return &(_ptr->data); }

  const_reference operator*() const { return _ptr->data; }
  const_pointer operator->() const { return &(_ptr->data); }

  RBTreeReverseIterator operator++() {
    _ptr = predecessor(_ptr);
    return *this;
  }

  RBTreeReverseIterator operator++(int) {
    RBTreeReverseIterator tmp = *this;
    operator++();
    return tmp;
  }

  RBTreeReverseIterator operator--() {
    _ptr = successor(_ptr);
    return *this;
  }

  RBTreeReverseIterator operator--(int) {
    RBTreeReverseIterator tmp = *this;
    operator--();
    return tmp;
  }

  friend bool operator==(const RBTreeReverseIterator& lhs,
                         const RBTreeReverseIterator& rhs) {
    return lhs._ptr == rhs._ptr;
  }
  friend bool operator!=(const RBTreeReverseIterator& lhs,
                         const RBTreeReverseIterator& rhs) {
    return lhs._ptr != rhs._ptr;
  }

 private:
  node_pointer getMinElementOnThePath(node_pointer node) {
    while (node->left) {
      node = node->left;
    }
    return node;
  }

  node_pointer getMaxElementOnThePath(node_pointer node) {
    while (node->right) {
      node = node->right;
    }
    return node;
  }

  node_pointer predecessor(node_pointer node) {
    if (node->left) {
      return getMaxElementOnThePath(node->left);
    } else {
      node_pointer parent = node->parent;
      while (node == parent->left) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }
  }

  node_pointer successor(node_pointer node) {
    if (node->right) {
      return getMinElementOnThePath(node->right);
    } else {
      node_pointer parent = node->parent;
      while (node == parent->right) {
        node = parent;
        parent = parent->parent;
      }
      return parent;
    }
  }
};

}  // namespace ft

#endif