/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:40:57 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/16 20:04:45 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <iostream>

namespace ft {

/*
 **=========================================================================
 **     Enable If
 **=========================================================================
 */

template <bool condition, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  typedef T type;
};

/*
 **=========================================================================
 **     Is Integral
 **=========================================================================
 */

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
struct is_integral<unsigned char> : std::true_type {};
template <>
struct is_integral<unsigned short int> : std::true_type {};
template <>
struct is_integral<unsigned int> : std::true_type {};
template <>
struct is_integral<unsigned long int> : std::true_type {};

}  // namespace ft

#endif
