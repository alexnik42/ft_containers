#include <iostream>
#include <stack>

#include "Stack.hpp"
#include "Utility.hpp"
#include "Vector.hpp"

int main() {
  // ft::Stack<int> stack;
  // std::stack<int> x;
  // x.push(10);
  // stack.push(10);
  // std::cout << x.top() << std::endl;
  // std::cout << stack.top() << std::endl;

  // std::vector<int> newInt;
  // newInt.push_back(42);
  // ft::Stack<int> stack2(newInt);
  // std::cout << stack2.top() << std::endl;
  // std::cout << (stack == stack2) << std::endl;
  // std::cout << (stack == stack) << std::endl;
  ft::Vector<int> arr;
  ft::Vector<int> arr2(std::allocator<int>);
  ft::Vector<int> arr3(5, 21);
  std::vector<int> arr4;
  arr4.push_back(21);
  arr4.push_back(42);
  arr4.push_back(84);
  ft::Vector<int> arr5(arr4.begin(), arr4.end());
  arr5.printVector();
}
