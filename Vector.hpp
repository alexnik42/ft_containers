/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:10:46 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/02 21:35:36 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>

#include "Utility.hpp"

namespace ft {

template <typename T, class Allocator = std::allocator<T> >
class Vector {
 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  typedef ft::RandomAccessIterator<T> iterator;
  typedef ft::RandomAccessIterator<const T> const_iterator;
  typedef ft::ReverseIterator<T> reverse_iterator;
  typedef ft::ReverseIterator<const T> const_reverse_iterator;

  Vector() : _arr(nullptr), _size(0), _capacity(0){};

  explicit Vector(const allocator_type& alloc)
      : _arr(nullptr), _size(0), _capacity(0), _alloc(alloc){};

  explicit Vector(size_type count, const value_type& value = value_type(),
                  const allocator_type& alloc = allocator_type())
      : _arr(nullptr), _size(0), _capacity(0), _alloc(alloc) {
    reserve(count);
    _size = count;
    _capacity = count;
    for (size_type i = 0; i < size(); i++) {
      _alloc.construct(_arr + i, value);
    }
  };

  template <class InputIt>
  Vector(InputIt first, InputIt last,
         const allocator_type& alloc = allocator_type(),
         typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                InputIt>::type* = nullptr)
      : _arr(nullptr), _size(0), _capacity(0), _alloc(alloc) {
    difference_type range = last - first;
    reserve(range);
    _size = range;
    value_type* ptr = _arr;
    for (size_type i = 0; i < size(); i++) {
      _alloc.construct(_arr + i, *(first++));
    }
  };

  Vector(const Vector& other) : _arr(nullptr), _size(0), _capacity(0) {
    *this = other;
  };

  ~Vector() {
    clear();
    _alloc.deallocate(_arr, capacity());
  };

  Vector& operator=(const Vector& other) {
    clear();
    reserve(other.capacity());
    _size = other.size();
    _alloc = other._alloc;
    for (size_type i = 0; i < size(); i++) {
      _alloc.construct(_arr + i, other._arr[i]);
    }
    return *this;
  };

  void assign(size_type count, const value_type& value) {
    if (count > capacity()) {
      reserve(count);
    }

    if (count >= size()) {
      clear();
    } else {
      for (size_type i = 0; i < count; i++) {
        _alloc.destroy(_arr + i);
      }
    }
    for (size_type i = 0; i < count; i++) {
      _alloc.construct(_arr + i, value);
    }
    _size = count;
  };

  template <class InputIt>
  void assign(InputIt first, InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = nullptr) {
    size_type count = static_cast<size_type>(last - first);
    if (count > capacity()) {
      reserve(count);
    }

    if (count >= size()) {
      clear();
    } else {
      for (size_type i = 0; i < count; i++) {
        _alloc.destroy(_arr + i);
      }
    }
    for (size_type i = 0; i < count; i++) {
      _alloc.construct(_arr + i, *(first++));
    }
    _size = count;
  }

  allocator_type get_allocator() const { return _alloc; };

  // Element access
  reference at(size_type pos) { return _arr[pos]; };
  const_reference at(size_type pos) const { return _arr[pos]; };

  reference operator[](size_type pos) { return _arr[pos]; };
  const_reference operator[](size_type pos) const { return _arr[pos]; };

  reference front() { return *_arr; };
  const_reference front() const { return *_arr; };

  reference back() { return *(_arr + _size - 1); };
  const_reference back() const { return *(_arr + _size - 1); };

  T* data() {
    if (_size == 0) {
      return nullptr;
    }
    return _arr;
  }
  const T* data() const {
    if (_size == 0) {
      return nullptr;
    }
    return _arr;
  };

  // Iterators
  iterator begin() { return iterator(_arr); };
  const_iterator begin() const { return const_iterator(_arr); };

  iterator end() { return iterator(_arr + _size); };
  const_iterator end() const { return const_iterator(_arr + _size); };

  reverse_iterator rbegin() { return reverse_iterator(_arr + _size); };
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(_arr + _size);
  };

  reverse_iterator rend() { return reverse_iterator(_arr); };
  const_reverse_iterator rend() const { return const_reverse_iterator(_arr); };

  // Capacity
  bool empty() const { return size() == 0; };
  size_type size() const { return _size; };
  size_type max_size() const { return allocator_type().max_size(); };

  void reserve(size_type new_cap) {
    if (new_cap <= capacity()) return;
    if (new_cap > max_size()) {
      throw std::length_error("Error: parameter exceeds maximum capacity");
    }
    value_type* newArr = _alloc.allocate(new_cap);
    size_type i = 0;
    try {
      std::uninitialized_copy(_arr, _arr + _size, newArr);
    } catch (const std::exception&) {
      _alloc.deallocate(newArr, size());
      throw;
    }
    for (size_type i = 0; i < size(); i++) {
      _alloc.destroy(_arr + i);
    }
    _alloc.deallocate(_arr, size());
    _capacity = new_cap;
    _arr = newArr;
  };

  size_type capacity() const { return _capacity; }

  // Modifiers
  void clear() {
    for (size_type i = 0; i < size(); i++) {
      _alloc.destroy(_arr + i);
    }
    _size = 0;
  };

  iterator insert(iterator pos, const value_type& value) {
    size_type insertIdx = static_cast<size_type>(pos - begin());
    if (size() == capacity()) {
      int new_cap = size() * 2 > 1 ? size() * 2 : 1;
      reserve(new_cap);
    }
    if (insertIdx < size()) {
      for (size_type i = size(); i > insertIdx; --i) {
        if (i != size()) {
          _alloc.destroy(_arr + i);
        }
        _alloc.construct(_arr + i, _arr[i - 1]);
      }
      _alloc.destroy(_arr + insertIdx);
      _alloc.construct(_arr + insertIdx, value);
      _size++;
    } else {
      push_back(value);
    }
    return pos;
  };
  // void insert(iterator pos, size_type count, const T& value);
  // template <class InputIt>
  // void insert(iterator pos, InputIt first, InputIt last);

  // iterator erase(iterator pos);
  // iterator erase(iterator first, iterator last);

  void push_back(const value_type& value) {
    if (size() == capacity()) {
      int new_cap = size() * 2 > 1 ? size() * 2 : 1;
      reserve(new_cap);
    }
    _alloc.construct(_arr + _size++, value);
  };

  void pop_back() {
    _alloc.destroy(_arr + size() - 1);
    _size--;
  };

  void resize(size_type count, value_type value = value_type()) {
    if (count <= size()) {
      for (size_type i = count; i < size(); ++i) {
        _alloc.destroy(_arr + i);
      }
    } else {
      for (size_type i = size(); i < count; ++i) {
        try {
          push_back(value);
        } catch (const std::exception&) {
          for (size_type j = size(); j < i; ++j) {
            _alloc.destroy(_arr + j);
          }
          throw;
        }
      }
    }
    _size = count;
  }
  // void swap(Vector& other);

  // // Non-member functions
  friend bool operator==(const Vector<value_type, allocator_type>& lhs,
                         const Vector<value_type, allocator_type>& rhs) {
    size_t i = 0, j = 0;
    while (i < lhs.size() && j < rhs.size()) {
      if (lhs._arr[i++] != rhs._arr[j++]) {
        return false;
      }
    }
    return i == lhs.size() && j == rhs.size();
  };

  friend bool operator!=(const Vector<value_type, allocator_type>& lhs,
                         const Vector<value_type, allocator_type>& rhs) {
    return !operator==(lhs, rhs);
  };

  // template <class T, class Alloc>
  // friend bool operator<(const Vector<T, Alloc>& lhs,
  //                       const Vector<T, Alloc>& rhs);

  // template <class T, class Alloc>
  // friend bool operator<=(const Vector<T, Alloc>& lhs,
  //                        const Vector<T, Alloc>& rhs);

  // template <class T, class Alloc>
  // friend bool operator>(const Vector<T, Alloc>& lhs,
  //                       const Vector<T, Alloc>& rhs);

  // template <class T, class Alloc>
  // friend bool operator>=(const Vector<T, Alloc>& lhs,
  //                        const Vector<T, Alloc>& rhs);

  // template <class T, class Alloc>
  // friend void swap(Vector<T, Alloc>& lhs, Vector<T, Alloc>& rhs);

  void printVector() const {
    for (size_type i = 0; i < _size; i++) {
      std::cout << _arr[i] << " ";
    }
  };

 private:
  pointer _arr;
  size_type _size;
  size_type _capacity;
  allocator_type _alloc;
};

}  // namespace ft

#endif