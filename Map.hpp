/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 02:19:27 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/09 18:01:58 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>

#include "utils/Pair.hpp"
#include "utils/iterator.hpp"
#include "utils/iterator_traits.hpp"
#include "utils/red_black_tree.hpp"

namespace ft {

template <typename Key, typename T, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::Pair<const Key, T> > >
class Map {
 public:
  typedef Allocator allocator_type;
  typedef ft::RBTreeIterator<T> iterator;
  typedef ft::RBTreeIterator<const T> const_iterator;
  //   typedef ft::ReverseIterator<T> reverse_iterator;
  //   typedef ft::ReverseIterator<const T> const_reverse_iterator;

  typedef Key key_type;
  typedef T mapped_type;
  typedef
      typename ft::iterator_traits<iterator>::difference_type difference_type;
  typedef ft::Pair<const Key, T> value_type;
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
        _root(nullptr){};
  explicit Map(const Compare& comp,
               const allocator_type& alloc = allocator_type()){};
  template <class InputIt>
  Map(InputIt first, InputIt last, const Compare& comp = Compare(),
      const allocator_type& alloc = allocator_type());
  Map(const Map& other);

  ~Map() { delete _root; };

  Map& operator=(const Map& other);

  allocator_type get_allocator() const;

  // Element access
  T& at(const Key& key);
  const T& at(const Key& key) const;
  T& operator[](const Key& key) {
    Node<Key, T>* res = _root->search(key, _root->getRoot());
    if (res == nullptr) {
      insert(ft::make_pair(key,
                           mapped_type()));  // once iterator is added - fix it
      res = _root->search(key, _root->getRoot());
    }
    return res->data.second;
  }

  // Iterators
  iterator begin() { return iterator(_root->getMinNode()); };
  const_iterator begin() const { return const_iterator(_root->getMinNode()); };

//   iterator end() {
//     iterator it = iterator(_root->getMinNode());
//     it++;
//     return it;
//   };
//   const_iterator end() const {
//     iterator it = iterator(_root->getMinNode());
//     it++;
//     return const_cast<> it;
//   };

  reverse_iterator rbegin();
  const_reverse_iterator rbegin() const;

  reverse_iterator rend();
  const_reverse_iterator rend() const;

  // Capacity
  bool empty() const;
  size_type size() const { return _size; };
  size_type max_size() const;

  // Modifiers
  void clear();

  void insert(const value_type& value) {
    if (size() == 0) {
      _root = new RBTree<key_type, mapped_type>();
    }
    _root->insert(value);
    _size++;
  }
  // ft::Pair<iterator, bool> insert(const value_type& value) {
  //   if (size() == 0) {
  //     _root = new RBTree<key_type, mapped_type>();
  //   }
  //   *_root->insert(value.first);
  //   _size++;
  // }
  iterator insert(iterator hint, const value_type& value);

  template <class InputIt>
  void insert(InputIt first, InputIt last);

  // void erase(iterator pos);
  // void erase(iterator first, iterator last);
  size_type erase(const Key& key) {
    _root->deleteKey(key);
    return 1;
  }

  void swap(Map& other);

  // Lookup
  size_type count(const Key& key) const;
  iterator find(const Key& key);
  const_iterator find(const Key& key) const;
  ft::Pair<iterator, iterator> equal_range(const Key& key);
  ft::Pair<const_iterator, const_iterator> equal_range(const Key& key) const;
  iterator lower_bound(const Key& key);
  const_iterator lower_bound(const Key& key) const;
  iterator upper_bound(const Key& key);
  const_iterator upper_bound(const Key& key) const;

  // Observers
  key_compare key_comp() const;
  //   value_compare value_comp() const;

  // Comparators
  friend bool operator==(const Map<Key, T, Compare, allocator_type>& lhs,
                         const Map<Key, T, Compare, allocator_type>& rhs);
  friend bool operator!=(const Map<Key, T, Compare, allocator_type>& lhs,
                         const Map<Key, T, Compare, allocator_type>& rhs);
  friend bool operator<(const Map<Key, T, Compare, allocator_type>& lhs,
                        const Map<Key, T, Compare, allocator_type>& rhs);
  friend bool operator<=(const Map<Key, T, Compare, allocator_type>& lhs,
                         const Map<Key, T, Compare, allocator_type>& rhs);
  friend bool operator>(const Map<Key, T, Compare, allocator_type>& lhs,
                        const Map<Key, T, Compare, allocator_type>& rhs);
  friend bool operator>=(const Map<Key, T, Compare, allocator_type>& lhs,
                         const Map<Key, T, Compare, allocator_type>& rhs);

  void swap(Map<Key, T, Compare, allocator_type>& lhs,
            Map<Key, T, Compare, allocator_type>& rhs);

 private:
  size_type _size;
  key_compare _compare;
  allocator_type _alloc;
  RBTree<key_type, mapped_type>* _root;
};

}  // namespace ft

#endif