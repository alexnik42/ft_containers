/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:29:16 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/01 20:55:01 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft {

// Iterator
template <typename T>
class RandomAccessIterator {
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;

 public:
  RandomAccessIterator() : _ptr(nullptr){};
  RandomAccessIterator(pointer ptr) : _ptr(ptr){};

  reference operator*() const { return *_ptr; }
  pointer operator->() { return _ptr; }

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