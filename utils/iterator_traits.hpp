/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:31:06 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/04 00:12:02 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft {

template <class Iter>
struct iterator_traits {
 public:
  typedef typename Iter::difference_type difference_type;
  typedef typename Iter::value_type value_type;
  typedef typename Iter::pointer pointer;
  typedef typename Iter::reference reference;
  typedef typename Iter::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
 public:
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef value_type& pointer;
  typedef value_type& reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
 public:
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const value_type& const_pointer;
  typedef const value_type& const_reference;
  typedef std::random_access_iterator_tag iterator_category;
};

}  // namespace ft

#endif