/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:10:46 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/01 21:40:02 by crendeha         ###   ########.fr       */
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
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename Allocator::pointer pointer;
  typedef typename Allocator::const_pointer const_pointer;
  // typedef ft::RandomAccessIterator iterator;
  // typedef ft::RandomAccessIterator const_iterator;
  // typedef ft::ReverseIterator reverse_iterator;
  // typedef ft::ReverseIterator const_reverse_iterator;

 public:
  Vector() : _arr(nullptr), _size(0), _capacity(0){};
  explicit Vector(const allocator_type& alloc)
      : _arr(nullptr), _size(0), _capacity(0), _alloc(alloc){};
  explicit Vector(size_type count, const value_type& value = value_type(),
                  const allocator_type& alloc = allocator_type())
      : _arr(nullptr), _size(0), _capacity(0), _alloc(alloc) {
    reserve(count);
    _size = count;
    _capacity = count;
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_arr + i, value);
    }
  };

  template <class InputIt>
  Vector(InputIt first, InputIt last,
         const allocator_type& alloc = allocator_type(),
         typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                InputIt>::type* = nullptr)
      : _arr(nullptr), _size(0), _capacity(0), _alloc(alloc) {
    difference_type size = last - first;
    reserve(size);
    _size = size;
    _capacity = size;
    value_type* ptr = _arr;
    for (size_type i = 0; i < _size; i++) {
      _alloc.construct(_arr + i, *(first++));
    }
  }
  // Vector(const Vector& other);
  ~Vector() {
    clear();
    _alloc.deallocate(_arr, _capacity);
  }

  // Vector& operator=(const Vector& other);

  // void assign(size_type count, const T& value);
  // template <class InputIt>
  // void assign(InputIt first, InputIt last);

  // allocator_type get_allocator() const { return allocator_type; };

  // // Element access
  // reference at(size_type pos);
  // const_reference at(size_type pos) const;

  reference operator[](size_type pos) { return _arr[pos]; }
  const_reference operator[](size_type pos) const { return _arr[pos]; };

  // reference front();
  // const_reference front() const;

  // reference back();
  // const_reference back() const;

  // T* data();
  // const T* data() const;

  // // Iterators
  // iterator begin();
  // const_iterator begin() const;

  // iterator end();
  // const_iterator end() const;

  // reverse_iterator rbegin();
  // const_reverse_iterator rbegin() const;

  // reverse_iterator rend();
  // const_reverse_iterator rend() const;

  // Capacity
  bool empty() const { return _size == 0; };
  size_type size() const { return _size; };
  size_type max_size() const { return allocator_type().max_size(); };

  void reserve(size_type new_cap) {
    if (new_cap <= _capacity) return;
    if (new_cap > max_size()) {
      throw std::length_error("Error: capacity exceeds maximum capacity");
    }
    value_type* newArr = _alloc.allocate(new_cap);
    size_t i = 0;
    try {
      std::uninitialized_copy(_arr, _arr + _size, newArr);
    } catch (const std::exception& e) {
      _alloc.deallocate(newArr, _size);
      throw;
    }
    for (size_type i = 0; i < _size; i++) {
      _alloc.destroy(_arr + i);
    }
    _alloc.deallocate(_arr, _size);
    _arr = newArr;
  }

  size_type capacity() const { return _capacity; }

  // // Modifiers
  void clear() {
    for (size_type i = 0; i < _size; i++) {
      _alloc.destroy(_arr + i);
    }
    _size = 0;
  }

  // iterator insert(iterator pos, const T& value);
  // void insert(iterator pos, size_type count, const T& value);
  // template <class InputIt>
  // void insert(iterator pos, InputIt first, InputIt last);

  // iterator erase(iterator pos);
  // iterator erase(iterator first, iterator last);

  void push_back(const T& value) {
    if (_size == _capacity) {
      int new_cap = max(1, _size * 2);
      reserve(new_cap);
    }
    _alloc.construct(_arr + _size++, value);
  }
  // void pop_back();
  // void resize(size_type count, T value = T());
  // void swap(Vector& other);

  // // Non-member functions
  template <class T, class Alloc>
  friend bool operator==(const Vector<T, Alloc>& lhs,
                         const Vector<T, Alloc>& rhs) {
    size_t i = 0, j = 0;
    while (i < lhs.size() && j < rhs.size()) {
      if (lhs._arr[i++] != rhs._arr[j++]) {
        return false;
      }
    }
    return i == lhs.size() && j == rhs.size();
  }
  template <class T, class Alloc>
  friend bool operator!=(const Vector<T, Alloc>& lhs,
                         const Vector<T, Alloc>& rhs) {
    return !operator==(lhs, rhs);
  }

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
    for (size_type i = 0; i < _capacity; i++) {
      std::cout << _arr[i] << " ";
    }
  }

 private:
  pointer _arr;
  size_type _size;
  size_type _capacity;
  allocator_type _alloc;
};

}  // namespace ft

#endif