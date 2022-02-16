/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:19:27 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/16 18:14:27 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <iostream>

#include "utils/Pair.hpp"
#include "utils/algorithm.hpp"
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
  typedef Compare key_compare;
  typedef Key key_type;
  typedef T mapped_type;

  typedef ft::Pair<const Key, T> value_type;

  typedef typename ft::RBTree<value_type, key_compare, allocator_type>::iterator
      iterator;
  typedef typename ft::RBTree<value_type, key_compare,
                              allocator_type>::const_iterator const_iterator;
  typedef
      typename ft::RBTree<value_type, key_compare,
                          allocator_type>::reverse_iterator reverse_iterator;
  typedef typename ft::RBTree<value_type, key_compare,
                              allocator_type>::const_reverse_iterator
      const_reverse_iterator;

  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;

  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

  class value_compare {
   protected:
    key_compare comp;

   public:
    bool operator()(const value_type& lhs, const value_type& rhs) const {
      return comp(lhs.first, rhs.first);
    };
    ~value_compare();

   protected:
    value_compare(key_compare c) : comp(c){};
  };

 private:
  size_type _size;
  key_compare _compare;
  allocator_type _alloc;
  RBTree<value_type, key_compare, allocator_type> _rbtree;

 public:
  Map()
      : _size(0),
        _compare(key_compare()),
        _alloc(allocator_type()),
        _rbtree(RBTree<value_type, key_compare, allocator_type>()){};

  explicit Map(const key_compare& comp,
               const allocator_type& alloc = allocator_type())
      : _size(0),
        _compare(comp),
        _alloc(alloc),
        _rbtree(RBTree<value_type, key_compare, allocator_type>()){};

  template <class InputIt>
  Map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
      const allocator_type& alloc = allocator_type())
      : _size(0),
        _compare(comp),
        _alloc(alloc),
        _rbtree(RBTree<value_type, key_compare, allocator_type>()) {
    insert(first, last);
  };

  Map(const Map& other)
      : _size(0),
        _compare(other._compare),
        _alloc(other._alloc),
        _rbtree(RBTree<value_type, key_compare, allocator_type>()) {
    *this = other;
  };

  ~Map(){};

  Map& operator=(const Map& other) {
    if (this != &other) {
      _size = other._size;
      _compare = other._compare;
      _alloc = other._alloc;
      _rbtree = other._rbtree;
    }
    return *this;
  }

  allocator_type get_allocator() const { return _alloc; };

  /*
   **=========================================================================
   **     Element Access
   **=========================================================================
   */

  mapped_type& at(const key_type& key) {
    iterator res = _rbtree.search(key);
    if (res == end()) {
      throw std::out_of_range("Error: key not found");
    } else {
      return (*res).second;
    }
  }
  const mapped_type& at(const key_type& key) const {
    iterator res = _rbtree.search(key);
    if (res == end()) {
      throw std::out_of_range("Error: key not found");
    } else {
      return (*res).second;
    }
  }

  mapped_type& operator[](const key_type& key) {
    iterator res = _rbtree.search(key);
    if (res == end()) {
      return (*insert(ft::make_pair(key, mapped_type())).first).second;
    } else {
      return (*res).second;
    }
  }

  /*
   **=========================================================================
   **     Iterators
   **=========================================================================
   */

  iterator begin() { return _rbtree.begin(); };
  const_iterator begin() const { return _rbtree.begin(); };

  iterator end() { return _rbtree.end(); };
  const_iterator end() const { return _rbtree.end(); };

  reverse_iterator rbegin() { return _rbtree.rbegin(); }
  const_reverse_iterator rbegin() const { return _rbtree.begin(); }

  reverse_iterator rend() { return _rbtree.rend(); }
  const_reverse_iterator rend() const { return _rbtree.rend(); }

  /*
   **=========================================================================
   **     Capacity
   **=========================================================================
   */

  bool empty() const { return size() == 0; };
  size_type size() const { return _size; };
  size_type max_size() const { return allocator_type().max_size(); };

  /*
   **=========================================================================
   **     Modifiers
   **=========================================================================
   */

  void clear() {
    _rbtree.clear();
    _size = 0;
  };

  ft::Pair<iterator, bool> insert(const value_type& value) {
    iterator res = find(value.first);
    if (res == end()) {
      res = iterator(_rbtree.insertNode(value));
      _size++;
      return ft::make_pair<iterator, bool>(res, true);
    } else {
      return ft::make_pair<iterator, bool>(res, false);
    }
  }

  iterator insert(iterator, const value_type& value) {
    return (insert(value)).first;
  }

  template <class InputIt>
  void insert(InputIt first, InputIt last,
              typename ft::enable_if<!ft::is_integral<InputIt>::value,
                                     InputIt>::type* = NULL) {
    while (first != last) {
      insert(*first++);
    }
  };

  void erase(iterator pos,
             typename ft::enable_if<!ft::is_integral<iterator>::value,
                                    iterator>::type* = NULL) {
    _rbtree.deleteNode((*pos).first);
    _size--;
  };

  void erase(iterator first, iterator last,
             typename ft::enable_if<!ft::is_integral<iterator>::value,
                                    iterator>::type* = NULL) {
    while (first != last) {
      erase(first++);
    }
  }

  size_type erase(const key_type& key) {
    iterator pos = find(key);
    if (pos != end()) {
      erase(pos);
      return 1;
    } else {
      return 0;
    }
  }

  void swap(Map& other) {
    size_type tmpSize = _size;
    key_compare tmpCompare = _compare;
    allocator_type tmpAlloc = _alloc;
    RBTree<value_type, key_compare, allocator_type> tmpRbtree = _rbtree;

    _size = other._size;
    _compare = other._compare;
    _alloc = other._alloc;
    _rbtree = other._rbtree;

    other._size = tmpSize;
    other._compare = tmpCompare;
    other._alloc = tmpAlloc;
    other._rbtree = tmpRbtree;
  }

  /*
   **=========================================================================
   **     Lookup
   **=========================================================================
   */

  size_type count(const Key& key) const {
    return static_cast<size_type>(find(key) != end());
  };

  iterator find(const Key& key) { return _rbtree.search(key); };
  const_iterator find(const Key& key) const { return _rbtree.search(key); }

  ft::Pair<iterator, iterator> equal_range(const Key& key) {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }
  const ft::Pair<const_iterator, const_iterator> equal_range(
      const Key& key) const {
    return ft::make_pair(lower_bound(key), upper_bound(key));
  }

  iterator lower_bound(const Key& key) { return _rbtree.lower_bound(key); }
  const_iterator lower_bound(const Key& key) const {
    return _rbtree.lower_bound(key);
  }

  iterator upper_bound(const Key& key) { return _rbtree.upper_bound(key); }
  const_iterator upper_bound(const Key& key) const {
    return _rbtree.upper_bound(key);
  }

  /*
   **=========================================================================
   **     Observers
   **=========================================================================
   */

  key_compare key_comp() const { return _compare; };
  value_compare value_comp() const {
    return ft::Map<key_type, mapped_type>::value_compare::comp;
  }

  /*
   **=========================================================================
   **     Comparison
   **=========================================================================
   */

  friend bool operator==(const Map<Key, T, Compare, allocator_type>& lhs,
                         const Map<Key, T, Compare, allocator_type>& rhs) {
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
  }
  friend bool operator!=(const Map<Key, T, Compare, allocator_type>& lhs,
                         const Map<Key, T, Compare, allocator_type>& rhs) {
    return !operator==(lhs, rhs);
  }
  friend bool operator<(const Map<Key, T, Compare, allocator_type>& lhs,
                        const Map<Key, T, Compare, allocator_type>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                       rhs.end());
  }
  friend bool operator<=(const Map<Key, T, Compare, allocator_type>& lhs,
                         const Map<Key, T, Compare, allocator_type>& rhs) {
    return !(operator<(rhs, lhs));
  }
  friend bool operator>(const Map<Key, T, Compare, allocator_type>& lhs,
                        const Map<Key, T, Compare, allocator_type>& rhs) {
    return operator<(rhs, lhs);
  }
  friend bool operator>=(const Map<Key, T, Compare, allocator_type>& lhs,
                         const Map<Key, T, Compare, allocator_type>& rhs) {
    return !(operator<(lhs, rhs));
  }

  friend void swap(Map<Key, T, Compare, allocator_type>& lhs,
                   Map<Key, T, Compare, allocator_type>& rhs) {
    lhs.swap(rhs);
  };
};

}  // namespace ft

#endif
