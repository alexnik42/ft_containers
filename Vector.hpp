/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:10:46 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/16 18:16:00 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils/iterator.hpp"
#include "utils/iterator_traits.hpp"
#include "utils/type_traits.hpp"

namespace ft {

template <typename T, class Allocator = std::allocator<T> >
class Vector {
 public:
  typedef Allocator allocator_type;
  typedef ft::RandomAccessIterator<T> iterator;
  typedef ft::RandomAccessIterator<const T> const_iterator;
  typedef ft::ReverseIterator<T> reverse_iterator;
  typedef ft::ReverseIterator<const T> const_reverse_iterator;

  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;
  typedef typename ft::iterator_traits<iterator>::value_type value_type;
  typedef typename allocator_type::size_type size_type;

  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

  Vector() : _arr(NULL), _size(0), _capacity(0){};

  explicit Vector(const allocator_type& alloc)
      : _arr(NULL), _size(0), _capacity(0), _alloc(alloc){};

  explicit Vector(size_type count, const value_type& value = value_type(),
                  const allocator_type& alloc = allocator_type())
      : _arr(NULL), _size(0), _capacity(0), _alloc(alloc) {
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
                                InputIt>::type* = NULL)
      : _arr(NULL), _size(0), _capacity(0), _alloc(alloc) {
    difference_type range = last - first;
    reserve(range);
    _size = range;
    value_type* ptr = _arr;
    for (size_type i = 0; i < size(); i++) {
      _alloc.construct(_arr + i, *(first++));
    }
  };

  Vector(const Vector& other) : _arr(NULL), _size(0), _capacity(0) {
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
    for (size_type i = 0; i < count; ++i) {
      _alloc.construct(_arr + i, value);
    }
    _size = count;
  };

  template <class InputIt>
  void assign(InputIt first, InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = NULL) {
    size_type count = static_cast<size_type>(std::distance(first, last));
    if (count > capacity()) {
      reserve(count);
    }
    for (size_type i = 0; i < count; ++i) {
      _alloc.construct(_arr + i, *(first++));
    }
    _size = count;
  }

  allocator_type get_allocator() const { return _alloc; };

  /*
   **=========================================================================
   **     Element Access
   **=========================================================================
   */

  reference at(size_type pos) {
    if (!(pos < size())) {
      throw std::out_of_range("Error: pos is out of range");
    }
    return _arr[pos];
  };

  const_reference at(size_type pos) const {
    if (!(pos < size())) {
      throw std::out_of_range("Error: pos is out of range");
    }
    return _arr[pos];
  };

  reference operator[](size_type pos) { return _arr[pos]; };
  const_reference operator[](size_type pos) const { return _arr[pos]; };

  reference front() { return *_arr; };
  const_reference front() const { return *_arr; };

  reference back() { return *(_arr + _size - 1); };
  const_reference back() const { return *(_arr + _size - 1); };

  value_type* data() { return _arr; }
  const value_type* data() const { return _arr; };

  /*
   **=========================================================================
   **     Iterators
   **=========================================================================
   */

  iterator begin() { return iterator(_arr); };
  const_iterator begin() const { return const_iterator(_arr); };

  iterator end() { return iterator(_arr + _size); };
  const_iterator end() const { return const_iterator(_arr + _size); };

  reverse_iterator rbegin() { return reverse_iterator(_arr + _size - 1); };
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(_arr + _size - 1);
  };

  reverse_iterator rend() { return reverse_iterator(_arr - 1); };
  const_reverse_iterator rend() const {
    return const_reverse_iterator(_arr - 1);
  };

  /*
   **=========================================================================
   **     Capacity
   **=========================================================================
   */

  bool empty() const { return size() == 0; };
  size_type size() const { return _size; };
  size_type max_size() const { return allocator_type().max_size(); };

  void reserve(size_type newCapacity) {
    if (newCapacity <= capacity()) return;
    if (newCapacity > max_size()) {
      throw std::length_error("Error: parameter exceeds maximum capacity");
    }
    value_type* newArr = _alloc.allocate(newCapacity);
    try {
      std::uninitialized_copy(_arr, _arr + _size, newArr);
    } catch (const std::exception&) {
      _alloc.deallocate(newArr, _size);
      throw;
    }
    for (size_type i = 0; i < size(); i++) {
      _alloc.destroy(_arr + i);
    }
    _alloc.deallocate(_arr, size());
    _capacity = newCapacity;
    _arr = newArr;
  };

  size_type capacity() const { return _capacity; };

  /*
  **=========================================================================
  **     Modifiers
  **=========================================================================
  */

  void clear() {
    for (size_type i = 0; i < size(); i++) {
      _alloc.destroy(_arr + i);
    }
    _size = 0;
  };

  iterator insert(iterator pos, const value_type& value) {
    size_type insertIdx = static_cast<size_type>(std::distance(begin(), pos));
    insert(pos, 1, value);
    return iterator(_arr + insertIdx);
  };

  void insert(iterator pos, size_type count, const value_type& value) {
    try {
      value_type x = value;
    } catch (...) {
      throw;
    }
    if (count == 0) return;
    size_type insertIdx = static_cast<size_type>(std::distance(begin(), pos));
    if (size() + count > capacity()) {
      int newCapacity =
          capacity() * 2 >= size() + count ? capacity() * 2 : size() + count;
      reserve(newCapacity);
    }
    if (empty()) {
      assign(count, value);
    } else {
      for (size_type i = size() - 1; i >= insertIdx; --i) {
        _alloc.construct(_arr + i + count, _arr[i]);
        if (i == 0) break;
      }
      for (size_type i = 0; i < count; ++i) {
        _alloc.construct(_arr + insertIdx++, value);
        _size++;
      }
    }
  };

  template <class InputIt>
  void insert(iterator pos, InputIt first, InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = NULL) {
    try {
      InputIt s = first;
      while (s < last) {
        value_type x = *s++;
      }
    } catch (...) {
      throw;
    }
    size_type count = static_cast<size_type>(std::distance(first, last));
    if (count == 0) return;
    size_type insertIdx = static_cast<size_type>(std::distance(begin(), pos));
    if (size() + count > capacity()) {
      int newCapacity =
          capacity() * 2 >= size() + count ? capacity() * 2 : size() + count;
      reserve(newCapacity);
    }
    if (empty()) {
      assign(first, last);
    } else {
      for (size_type i = size() - 1; i >= insertIdx; --i) {
        _alloc.construct(_arr + i + count, _arr[i]);
        if (i == 0) break;
      }
      for (size_type i = 0; i < count; ++i) {
        _alloc.construct(_arr + insertIdx++, *first++);
        _size++;
      }
    }
  };

  iterator erase(iterator pos) {
    size_type deletedIndex =
        static_cast<size_type>(std::distance(begin(), pos));
    for (size_type i = deletedIndex; i < size() - 1; ++i) {
      _alloc.construct(_arr + i, _arr[i + 1]);
    }
    _alloc.destroy(_arr + size() - 1);
    _size--;
    return iterator(_arr + deletedIndex);
  };

  iterator erase(iterator first, iterator last) {
    if (first == last) {
      return last;
    }
    size_type deletionStartIndex =
        static_cast<size_type>(std::distance(begin(), first));
    size_type valueToMoveIndex =
        static_cast<size_type>(std::distance(begin(), last));
    size_type count = valueToMoveIndex - deletionStartIndex;

    for (size_type i = deletionStartIndex; valueToMoveIndex < size(); i++) {
      _alloc.construct(_arr + i, _arr[valueToMoveIndex++]);
    }
    for (size_type i = size() - count; i < size(); i++) {
      _alloc.destroy(_arr + i);
    }
    _size -= count;
    return iterator(_arr + deletionStartIndex);
  }

  void push_back(const value_type& value) {
    if (size() == capacity()) {
      int newCapacity = capacity() * 2 > 1 ? capacity() * 2 : 1;
      reserve(newCapacity);
    }
    _alloc.construct(_arr + _size, value);
    _size++;
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
  };

  void swap(Vector& other) {
    pointer tmpArr = _arr;
    size_type tmpSize = _size;
    size_type tmpCapacity = _capacity;
    allocator_type tmpAlloc = _alloc;

    _arr = other._arr;
    _size = other._size;
    _capacity = other._capacity;
    _alloc = other._alloc;

    other._arr = tmpArr;
    other._size = tmpSize;
    other._capacity = tmpCapacity;
    other._alloc = tmpAlloc;
  };

  /*
   **=========================================================================
   **    Comparison
   **=========================================================================
   */

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

  friend bool operator<(const Vector<value_type, allocator_type>& lhs,
                        const Vector<value_type, allocator_type>& rhs) {
    size_type i = 0;
    while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i]) {
      i++;
    }
    return (i != rhs.size() && (i == lhs.size() || lhs._arr[i] < rhs._arr[i]));
  }

  friend bool operator<=(const Vector<value_type, allocator_type>& lhs,
                         const Vector<value_type, allocator_type>& rhs) {
    size_type i = 0;
    while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i]) {
      i++;
    }
    return (i == lhs.size() && i == rhs.size()) ||
           (i != rhs.size() && (i == lhs.size() || lhs._arr[i] < rhs._arr[i]));
  }

  friend bool operator>(const Vector<value_type, allocator_type>& lhs,
                        const Vector<value_type, allocator_type>& rhs) {
    size_type i = 0;
    while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i]) {
      i++;
    }
    return (i != lhs.size() && (i == rhs.size() || rhs._arr[i] < lhs._arr[i]));
  }

  friend bool operator>=(const Vector<value_type, allocator_type>& lhs,
                         const Vector<value_type, allocator_type>& rhs) {
    size_type i = 0;
    while (i < lhs.size() && i < rhs.size() && lhs._arr[i] == rhs._arr[i]) {
      i++;
    }
    return (i == rhs.size() && i == lhs.size()) ||
           (i != lhs.size() && (i == rhs.size() || rhs._arr[i] < lhs._arr[i]));
  }

  friend void swap(const Vector<value_type, allocator_type>& lhs,
                   const Vector<value_type, allocator_type>& rhs) {
    lhs.swap(rhs);
  }

 private:
  pointer _arr;
  size_type _size;
  size_type _capacity;
  allocator_type _alloc;
};

}  // namespace ft

#endif
