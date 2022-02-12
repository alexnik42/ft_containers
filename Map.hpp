/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:19:27 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/12 23:06:13 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <iostream>

#include "utils/Pair.hpp"
#include "utils/iterator.hpp"
#include "utils/iterator_traits.hpp"
#include "utils/red_black_tree.hpp"
#include "utils/type_traits.hpp"

namespace ft {

template <typename Key, typename T, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::Pair<const Key, T> > >
class Map {
 public:
  typedef Allocator allocator_type;
  typedef Key key_type;
  typedef T mapped_type;

  typedef ft::Pair<const Key, T> value_type;
  typedef ft::RBTreeIterator<value_type> iterator;
  typedef ft::RBTreeIterator<const value_type> const_iterator;
  // typedef ft::RBTreeReverseIterator<value_type> reverse_iterator;
  // typedef ft::RBTreeReverseIterator<const value_type> const_reverse_iterator;

  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;
  typedef Compare key_compare;

  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

  Map()
      : _size(0),
        _compare(key_compare()),
        _alloc(allocator_type()),
        _rbtree(nullptr){};

  explicit Map(const key_compare& comp,
               const allocator_type& alloc = allocator_type())
      : _size(0), _compare(comp), _alloc(alloc), _rbtree(nullptr){};

  template <class InputIt>
  Map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : _size(0), _compare(comp), _alloc(alloc), _rbtree(nullptr) {
    insert(first, last);
  };

  Map(const Map& other)
      : _size(0),
        _compare(other._compare),
        _alloc(other._alloc),
        _rbtree(nullptr) {
    *this = other;
  };

  ~Map() { delete _rbtree; };  // check erase

  Map& operator=(const Map& other) {
    const_iterator first = other.begin();
    // const_iterator last = other.end();
    // while (first != last) {
    //   insert(make_pair((*first).first, (*first).second));
    //   first++;
    // }
    return *this;
  }

  allocator_type get_allocator() const { return _alloc; };

  // Element access
  mapped_type& at(const key_type& key) {
    iterator res = _rbtree->search(ft::make_pair(key, mapped_type()));
    if (res == end()) {
      throw std::out_of_range("Error: key not found");
    } else {
      return (*res).second;
    }
  }
  const mapped_type& at(const key_type& key) const {
    iterator res = _rbtree->search(ft::make_pair(key, mapped_type()));
    if (res == end()) {
      throw std::out_of_range("Error: key not found");
    } else {
      return (*res).second;
    }
  }

  mapped_type& operator[](const key_type& key) {
    iterator res = _rbtree->search(ft::make_pair(key, mapped_type()));
    if (res == end()) {
      return (*insert(ft::make_pair(key, mapped_type())).first).second;
    } else {
      return (*res).second;
    }
  }

  // Iterators
  iterator begin() { return _rbtree->begin(); };
  const_iterator begin() const { return _rbtree->begin(); };

  iterator end() { return _rbtree->end(); };
  const_iterator end() const { return _rbtree->end(); };

  // reverse_iterator rbegin();
  // const_reverse_iterator rbegin() const;

  // reverse_iterator rend();
  // const_reverse_iterator rend() const;

  // Capacity
  bool empty() const { return size() == 0; };
  size_type size() const { return _size; };
  size_type max_size() const { return allocator_type().max_size(); };

  // Modifiers
  void clear() { erase(begin(), end()); };

  ft::Pair<iterator, bool> insert(const value_type& value) {
    if (empty()) {
      _rbtree = new RBTree<value_type>();
    }
    iterator res = find(value.first);
    if (res == end()) {
      res = iterator(_rbtree->insertNode(value));
      _size++;
      return ft::make_pair<iterator, bool>(res, true);
    } else {
      return ft::make_pair<iterator, bool>(res, false);
    }
  }

  // iterator insert(iterator hint, const value_type& value) {}

  template <class InputIt>
  void insert(InputIt first, InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = nullptr) {
    while (first != last) {
      insert(*first++);
    }
  };

  void erase(iterator pos,
             typename ft::enable_if<!ft::is_integral<iterator>::value,
                                    iterator>::type* = nullptr) {
    _rbtree->deleteNode(*pos);
    _size--;
  };

  void erase(iterator first, iterator last,
             typename ft::enable_if<!ft::is_integral<iterator>::value,
                                    iterator>::type* = nullptr) {
    while (first != last) {
      erase(first++);
    }
  }

  size_type erase(const key_type& key) {
    // std::cout << "Erase1\n";
    iterator pos = find(key);
    // std::cout << "Erase2\n";
    if (pos != end()) {
      // std::cout << "Erase3\n";
      erase(pos);
      // std::cout << "Erase4\n";
      return 1;
    } else {
      return 0;
    }
  }

  // void swap(Map& other);

  // Lookup
  size_type count(const Key& key) const { return find(key) != end(); };

  iterator find(const Key& key) {
    return _rbtree->search(ft::make_pair(key, mapped_type()));
  };

  const_iterator find(const Key& key) const {
    return _rbtree->search(ft::make_pair(key, mapped_type()));
  }

  // ft::Pair<iterator, iterator> equal_range(const Key& key);
  // ft::Pair<const_iterator, const_iterator> equal_range(const Key& key) const;
  // iterator lower_bound(const Key& key);
  // const_iterator lower_bound(const Key& key) const;
  // iterator upper_bound(const Key& key);
  // const_iterator upper_bound(const Key& key) const;

  // Observers
  // key_compare key_comp() const;
  //   value_compare value_comp() const;

  // Comparators
  // friend bool operator==(const Map<Key, T, Compare, allocator_type>& lhs,
  //                        const Map<Key, T, Compare, allocator_type>& rhs);
  // friend bool operator!=(const Map<Key, T, Compare, allocator_type>& lhs,
  //                        const Map<Key, T, Compare, allocator_type>& rhs);
  // friend bool operator<(const Map<Key, T, Compare, allocator_type>& lhs,
  //                       const Map<Key, T, Compare, allocator_type>& rhs);
  // friend bool operator<=(const Map<Key, T, Compare, allocator_type>& lhs,
  //                        const Map<Key, T, Compare, allocator_type>& rhs);
  // friend bool operator>(const Map<Key, T, Compare, allocator_type>& lhs,
  //                       const Map<Key, T, Compare, allocator_type>& rhs);
  // friend bool operator>=(const Map<Key, T, Compare, allocator_type>& lhs,
  //                        const Map<Key, T, Compare, allocator_type>& rhs);

  // void swap(Map<Key, T, Compare, allocator_type>& lhs,
  //           Map<Key, T, Compare, allocator_type>& rhs);

 private:
  size_type _size;
  key_compare _compare;
  allocator_type _alloc;
  RBTree<value_type>* _rbtree;
};

}  // namespace ft

#endif