/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair_test.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:06:59 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/04 20:39:26 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/Pair.hpp"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
  int n = 1;
  int a[5] = {1, 2, 3, 4, 5};

  // build a pair from two ints
  auto p1 = ft::make_pair(n, a[1]);
  std::cout << "The value of p1 is "
            << "(" << p1.first << ", " << p1.second << ")\n";

  // build a pair from a reference to int and an array (decayed to pointer)
  auto p2 = ft::make_pair(std::ref(n), a);
  n = 7;
  std::cout << "The value of p2 is "
            << "(" << p2.first << ", " << *(p2.second + 2) << ")\n";

  std::vector<ft::Pair<int, std::string>> v = {
      {2, "baz"}, {2, "bar"}, {1, "foo"}};
  std::sort(v.begin(), v.end());

  for (auto p : v) {
    std::cout << "{" << p.first << ", " << std::quoted(p.second) << "}\n";
  }
}