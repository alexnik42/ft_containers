/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:29:16 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/02 20:37:31 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {

// Iterators
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
    copy -= n;
    return copy;
  }

  ReverseIterator& operator-=(difference_type n) {
    _ptr += n;
    return *this;
  }

  ReverseIterator operator-(difference_type n) {
    ReverseIterator copy = *this;
    copy += n;
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
    return lhs._ptr > rhs._ptr;
  }
  friend bool operator>=(const ReverseIterator& lhs,
                         const ReverseIterator& rhs) {
    return lhs._ptr >= rhs._ptr;
  }
  friend bool operator<(const ReverseIterator& lhs,
                        const ReverseIterator& rhs) {
    return lhs._ptr < rhs._ptr;
  }
  friend bool operator<=(const ReverseIterator& lhs,
                         const ReverseIterator& rhs) {
    return lhs._ptr <= rhs._ptr;
  }

 private:
  pointer _ptr;
};

// Meta functions
template <bool condition, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

template <typename>
struct is_integral : std::false_type {};

template <>
struct is_integral<bool> : std::true_type {};
template <>
struct is_integral<char> : std::true_type {};
template <>
struct is_integral<char16_t> : std::true_type {};
template <>
struct is_integral<char32_t> : std::true_type {};
template <>
struct is_integral<signed char> : std::true_type {};
template <>
struct is_integral<short int> : std::true_type {};
template <>
struct is_integral<int> : std::true_type {};
template <>
struct is_integral<long int> : std::true_type {};
template <>
struct is_integral<long long int> : std::true_type {};
template <>
struct is_integral<unsigned char> : std::true_type {};
template <>
struct is_integral<unsigned short int> : std::true_type {};
template <>
struct is_integral<unsigned int> : std::true_type {};
template <>
struct is_integral<unsigned long int> : std::true_type {};
template <>
struct is_integral<unsigned long long int> : std::true_type {};

}  // namespace ft

#endif