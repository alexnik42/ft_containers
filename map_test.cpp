/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:53:25 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/09 14:34:08 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

#include <iostream>

int main() {
  ft::Map<std::string, int> newMap;

  newMap.insert(ft::make_pair("Hello", 1));
  newMap.insert(ft::make_pair("World", 21));
  newMap.insert(ft::make_pair("!", 42));
  std::cout << "Hello: " << newMap["Hello"] << std::endl;
  std::cout << "World: " << newMap["World"] << std::endl;
  std::cout << "!: " << newMap["!"] << std::endl;
  std::cout << newMap["kek"] << std::endl;

  newMap.erase("World");
  std::cout << "World is deleted" << std::endl;
  std::cout << "World: " << newMap["World"] << std::endl;
};