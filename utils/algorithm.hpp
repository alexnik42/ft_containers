/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 22:08:46 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/16 18:08:38 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {

/*
 **=========================================================================
 **     Equal
 **=========================================================================
 */

template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  for (; first1 != last1; ++first1, ++first2) {
    if (!(*first1 == *first2)) {
      return false;
    }
  }
  return true;
}

/*
 **=========================================================================
 **     Lexicographical Compare
 **=========================================================================
 */

template <class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (*first1 < *first2) return true;
    if (*first2 < *first1) return false;
  }
  return (first1 == last1) && (first2 != last2);
}

}  // namespace ft

#endif
