/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:22:54 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/16 20:04:24 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

#define RED 1
#define BLACK 0

namespace ft {

/*
 **=========================================================================
 **     Node
 **=========================================================================
 */

template <typename T>
struct Node {
  Node(T data)
      : data(data), parent(NULL), left(NULL), right(NULL), color(RED){};
  T data;
  Node<T> *parent;
  Node<T> *left;
  Node<T> *right;
  int color;
};

}  // namespace ft

#endif
