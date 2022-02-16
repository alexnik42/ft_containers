/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:21:44 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/16 18:17:20 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft {

template <typename T, class Container = ft::Vector<T> >
class Stack {
 public:
  typedef Container container_type;
  typedef typename container_type::value_type value_type;
  typedef typename container_type::size_type size_type;
  typedef typename container_type::reference reference;
  typedef typename container_type::const_reference const_reference;

  Stack(){};
  explicit Stack(const container_type& cont) : c(cont){};
  Stack(const Stack& other) { c = other.c; };
  ~Stack(){};

  Stack& operator=(const Stack& other) {
    c = other.c;
    return *this;
  };

  /*
   **=========================================================================
   **     Element Access
   **=========================================================================
   */

  reference top() { return c.back(); };
  const_reference top() const { return c.back(); };

  /*
   **=========================================================================
   **     Capacity
   **=========================================================================
   */

  bool empty() const { return c.empty(); };
  size_type size() const { return c.size(); };

  /*
   **=========================================================================
   **     Modifiers
   **=========================================================================
   */

  void push(const value_type& value) { c.push_back(value); };
  void push(value_type& value) { c.push_back(value); };

  void pop() { c.pop_back(); };

  /*
   **=========================================================================
   **     Comparison
   **=========================================================================
   */

  friend bool operator==(const Stack<value_type, container_type>& lhs,
                         const Stack<value_type, container_type>& rhs) {
    return lhs.c == rhs.c;
  };

  friend bool operator!=(const Stack<value_type, container_type>& lhs,
                         const Stack<value_type, container_type>& rhs) {
    return lhs.c != rhs.c;
  };

  friend bool operator<(const Stack<value_type, container_type>& lhs,
                        const Stack<value_type, container_type>& rhs) {
    return lhs.c < rhs.c;
  };

  friend bool operator<=(const Stack<value_type, container_type>& lhs,
                         const Stack<value_type, container_type>& rhs) {
    return lhs.c <= rhs.c;
  };

  friend bool operator>(const Stack<value_type, container_type>& lhs,
                        const Stack<value_type, container_type>& rhs) {
    return lhs.c > rhs.c;
  };

  friend bool operator>=(const Stack<value_type, container_type>& lhs,
                         const Stack<value_type, container_type>& rhs) {
    return lhs.c >= rhs.c;
  };

 protected:
  container_type c;
};

}  // namespace ft

#endif
