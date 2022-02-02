/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:21:44 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/02 16:24:09 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

namespace ft {

  template <typename T, class Container = std::vector<T> >
  class Stack {
    typedef Container container_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::size_type size_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;

  public:
    Stack() {};
    explicit Stack(const container_type& cont) : c(cont) {};
    Stack(const Stack& other) { c = other.c; };
    ~Stack() {};

    Stack& operator=(const Stack& other) {
      c = other.c;
      return *this;
    };

    reference top() { return c.back(); };
    const_reference top() const { return c.back(); };

    bool empty() const { return c.empty(); };
    size_type size() const { return c.size(); };

    void push(const value_type& value) { c.push_back(value); };
    void push(value_type& value) { c.push_back(value); };

    void pop() { c.pop_back(); };

    template <typename T1, class C1>
    friend bool operator==(const Stack<T1, C1>& lhs, const Stack<T1, C1>& rhs);

    template <typename T1, class C1>
    friend bool operator!=(const Stack<T1, C1>& lhs, const Stack<T1, C1>& rhs);

    template <typename T1, class C1>
    friend bool operator<(const Stack<T1, C1>& lhs, const Stack<T1, C1>& rhs);

    template <typename T1, class C1>
    friend bool operator<=(const Stack<T1, C1>& lhs, const Stack<T1, C1>& rhs);

    template <typename T1, class C1>
    friend bool operator>(const Stack<T1, C1>& lhs, const Stack<T1, C1>& rhs);

    template <typename T1, class C1>
    friend bool operator>=(const Stack<T1, C1>& lhs, const Stack<T1, C1>& rhs);

  protected:
    container_type c;
  };

  template <typename T, class Container>
  bool operator==(const Stack<T, Container>& lhs,
    const Stack<T, Container>& rhs) {
    return lhs.c == rhs.c;
  };

  template <typename T, typename Container>
  bool operator!=(const Stack<T, Container>& lhs,
    const Stack<T, Container>& rhs) {
    return lhs.c != rhs.c;
  };

  template <typename T, typename Container>
  bool operator<(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs) {
    return lhs.c < rhs.c;
  };

  template <typename T, typename Container>
  bool operator<=(const Stack<T, Container>& lhs,
    const Stack<T, Container>& rhs) {
    return lhs.c <= rhs.c;
  };

  template <typename T, typename Container>
  bool operator>(const Stack<T, Container>& lhs, const Stack<T, Container>& rhs) {
    return lhs.c > rhs.c;
  };

  template <typename T, typename Container>
  bool operator>=(const Stack<T, Container>& lhs,
    const Stack<T, Container>& rhs) {
    return lhs.c >= rhs.c;
  };

}  // namespace ft

#endif