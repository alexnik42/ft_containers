#include <iostream>
#include <stack>

#include "Stack.hpp"
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
  // ft::Vector<int> arr;
  // ft::Vector<int> arr2(std::allocator<int>);
  // ft::Vector<int> arr3(5, 21);
  // ft::Vector<int> arr4(arr3);
  // ft::Vector<int> arr5 = arr4;
  ft::Vector<int> arr6;
  for (int i = 0; i < 10; i++) {
    arr6.push_back(i);
  }
  ft::Vector<int> arr7;
  arr7.assign(5, -10);
  // arr6.printVector();
  // std::vector<int> arr4;
  // arr4.push_back(21);
  // arr4.push_back(42);
  // arr4.push_back(84);
  // ft::Vector<int> arr5(arr4.begin(), arr4.end());
  arr6.insert(arr6.begin(), arr7.begin(), arr7.begin() + 3);
  arr6.printVector();
  // arr6.printVector();
  // std::cout << "Size: " << arr6.size() << std::endl;
  arr6.insert(arr6.begin() + 3, 99);
  arr6.printVector();
  // std::cout << "Size: " << arr6.size() << std::endl;
  // arr6.printVector();
  arr6.insert(arr6.end() - 1, 123);
  arr6.printVector();
  // ft::Vector<int>::reverse_iterator it = arr6.rbegin();
  // while (it < arr6.rend()) {
  //   std::cout << *it++ << " ";
  // }
  // std::cout << std::endl;

  // std::vector<int> test;
  // test.assign(10, 22);
  // test.insert(test.begin(), 42);
  // test.insert(test.begin() + 3, 99);
  // test.insert(test.end(), 123);
  // std::cout << "Size (test): " << test.size() << std::endl;
  // for (size_t i = 0; i < test.size(); i++) {
  //   std::cout << test[i] << " ";
  // }
  // std::cout << std::endl;
  // std::vector<int>::reverse_iterator itTest = test.rbegin();
  // while (itTest < test.rend()) {
  //   std::cout << *itTest++ << " ";
  // }
  // std::cout << std::endl;
  // arr6.resize(15);
  // std::cout << "Size: " << arr6.size() << std::endl;
  // arr6.printVector();
  // arr6.resize(10);
  // arr6.insert(arr6.begin(), 0, -1);
  // std::cout << "Size: " << arr6.size() << std::endl;
  // arr6.printVector();
  // ft::Vector<int> arr8;
  // arr8.push_back(1);
  // arr8.push_back(2);
  // arr8.push_back(3);
  // arr8.push_back(4);
  // arr8.push_back(5);
  // ft::Vector<int> arr9;
  // arr9.push_back(7);
  // arr9.push_back(8);
  // arr9.push_back(9);

  // ft::Vector<int>::iterator it = arr8.begin();
  // std::cout << *it <<" arr8: size " << arr8.size() << " capacity " <<
  // arr8.capacity()
  //           << std::endl;
  // arr8.printVector();
  // std::cout << "arr9: size " << arr9.size() << " capacity " <<
  // arr9.capacity()
  //           << std::endl;
  // arr9.printVector();
  // arr8.swap(arr9);
  // std::cout << *it << " arr8: size " << arr8.size() << " capacity " <<
  // arr8.capacity()
  //           << std::endl;
  // arr8.printVector();
  // std::cout << "arr9: size " << arr9.size() << " capacity " <<
  // arr9.capacity()
  //           << std::endl;
  // arr9.printVector();
}
