/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 01:49:44 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/04 01:56:41 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iterator>
#include <vector>

#include "Vector.hpp"

void print(int id, const ft::Vector<int>& container) {
  std::cout << id << ". ";
  for (const int x : container) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}

int main() {
  ft::Vector<int> c1(3, 100);
  print(1, c1);

  auto it = c1.begin();
  it = c1.insert(it, 200);
  print(2, c1);

  c1.insert(it, 2, 300);
  print(3, c1);

  // `it` no longer valid, get a new one:
  it = c1.begin();

  ft::Vector<int> c2(2, 400);
  c1.insert(std::next(it, 2), c2.begin(), c2.end());
  print(4, c1);

  int arr[] = {501, 502, 503};
  c1.insert(c1.begin(), arr, arr + 3);
  print(5, c1);

  int arr2[] = {601, 602, 603};
  c1.insert(c1.end(), arr2, arr2 + 3);
  print(6, c1);

  ft::Vector<int> c;
  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  std::cout << "The vector holds: ";
  for (const auto& el : c) std::cout << el << ' ';
  std::cout << '\n';
  c.resize(5);
  std::cout << "After resize up to 5: ";
  for (const auto& el : c) std::cout << el << ' ';
  std::cout << '\n';
  c.resize(2);
  std::cout << "After resize down to 2: ";
  for (const auto& el : c) std::cout << el << ' ';
  std::cout << '\n';
  c.resize(6, 4);
  std::cout << "After resize up to 6 (initializer = 4): ";
  for (const auto& el : c) std::cout << el << ' ';
  std::cout << '\n';
}