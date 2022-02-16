/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_containers.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:54:26 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/17 00:26:51 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

#include <iostream>
#include "Stack.hpp"

void stack_test() {
  clock_t g_start = clock();
  ft::Stack<int> st;
  for (int i = 0; i < 100000; i++) {
    st.push(i * 3);
  }
  std::cout << "Top element (st): " << st.top() << std::endl;
  std::cout << "Stack size (st): " << (st.empty() ? "true" : "false")
            << std::endl;

  ft::Stack<int> st2(st);
  std::cout << "Top element (st2): " << st2.top() << std::endl;
  std::cout << "Stack size (st2): " << (st2.empty() ? "true" : "false")
            << std::endl;
  std::cout << "Stack empty (st2): " << (st2.empty() ? "true" : "false")
            << std::endl;

  st2.push(99);
  st2.push(42);
  std::cout << "Top element (st2): " << st2.top() << std::endl;
  std::cout << "Stack size (st2): " << (st2.empty() ? "true" : "false")
            << std::endl;

  ft::Stack<int> st3 = st2;
  std::cout << "st2 == st3: " << (st2 == st3 ? "true" : "false") << std::endl;

  st3.pop();
  st3.pop();
  st3.pop();
  st3.pop();
  st3.pop();
  std::cout << "Top element (st3): " << st2.top() << std::endl;
  std::cout << "st2 == st3: " << (st2 == st3 ? "true" : "false") << std::endl;
  std::cout << "st2 != st3: " << (st2 != st3 ? "true" : "false") << std::endl;
  std::cout << "st2 < st3: " << (st2 < st3 ? "true" : "false") << std::endl;
  std::cout << "st2 >= st3: " << (st2 >= st3 ? "true" : "false") << std::endl;

  int count = 0;
  while (!st3.empty()) {
    count++;
    st3.pop();
  }
  std::cout << "Count of pop operations (st3): " << count << std::endl;
  std::cout << "Stack empty (st3): " << (st3.empty() ? "true" : "false")
            << std::endl;
  clock_t g_end = clock();
  printf("Execution time (ms): %.2fms\n",
         (double)(g_end - g_start) / CLOCKS_PER_SEC * 1000);
}

int main() {
  std::cout << "\n***** STACK TEST *****\n" << std::endl;
  stack_test();
  std::cout << std::endl;

  return 0;
}
