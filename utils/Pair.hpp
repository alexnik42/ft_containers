/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:51:49 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/16 18:11:45 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

/*
 **=========================================================================
 **     Pair
 **=========================================================================
 */

template <typename T1, typename T2>
struct Pair {
  typedef T1 first_type;
  typedef T2 second_type;

  Pair() : first(), second(){};
  Pair(first_type& x, second_type& y) : first(x), second(y){};

  template <class U1, class U2>
  Pair(const Pair<U1, U2>& p) : first(p.first), second(p.second){};

  Pair(const Pair& p) : first(p.first), second(p.second){};

  ~Pair(){};

  Pair& operator=(const Pair& other) {
    first = other.first;
    second = other.second;
    return *this;
  };

  first_type first;
  second_type second;
};

template <typename T1, typename T2>
Pair<T1, T2> make_pair(T1 t, T2 u) {
  return Pair<T1, T2>(t, u);
}

template <typename T1, typename T2>
bool operator==(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename T1, typename T2>
bool operator!=(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs) {
  return !(lhs == rhs);
}

template <typename T1, typename T2>
bool operator<(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs) {
  return lhs.first < rhs.first ||
         (lhs.first <= rhs.first && lhs.second < rhs.second);
}

template <typename T1, typename T2>
bool operator<=(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs) {
  return !(rhs < lhs);
}

template <typename T1, typename T2>
bool operator>(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs) {
  return rhs < lhs;
}

template <typename T1, typename T2>
bool operator>=(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs) {
  return !(lhs < rhs);
}

}  // namespace ft

#endif
