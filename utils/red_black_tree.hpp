/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 02:13:10 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/13 04:13:52 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>

#include "Pair.hpp"
#include "iterator.hpp"

#define RED 1
#define BLACK 0

namespace ft {

template <typename T, typename U>
class RBTreeIterator;

template <typename T>
struct Node {
  Node(T data)
      : data(data), parent(nullptr), left(nullptr), right(nullptr), color(1){};
  T data;
  Node<T> *parent;
  Node<T> *left;
  Node<T> *right;
  int color;  // 1 -> Red, 0 -> Black
};

template <typename T>
class RBTree {
 public:
  typedef Node<T> Node;
  typedef T Pair;
  typedef ft::RBTreeIterator<T, Node> iterator;
  typedef ft::RBTreeIterator<const T, const Node> const_iterator;

 private:
  Node *_superRoot;
  Node *_root;

 public:
  RBTree() : _superRoot(nullptr), _root(nullptr) {
    _superRoot = new Node(Pair());
  };

  // Search RBTree
  iterator search(const Pair &data) {
    Node *res = searchHelp(data, _root);
    return res ? iterator(res) : end();
  }

  const_iterator search(const Pair &data) const {
    Node *res = searchHelp(data, _root);
    return res ? const_iterator(res) : end();
  }

  Node *searchHelp(const Pair &data, Node *root) {
    if (root == nullptr || root->data.first == data.first) {
      return root;
    } else {
      if (data.first < root->data.first) {
        return searchHelp(data, root->left);
      } else {
        return searchHelp(data, root->right);
      }
    }
  };

  // Insert
  iterator insertNode(const Pair &data) {
    if (_root != nullptr) {
      _root->parent = nullptr;
    }
    Node *inserted_node = new Node(data);
    if (_root == nullptr) {
      _root = inserted_node;
    } else {
      Node *n = _root;
      while (1) {
        if (data.first == n->data.first) {
          n->data.second = data.second;
          return n;
        } else if (data.first < n->data.first) {
          if (n->left == nullptr) {
            n->left = inserted_node;
            break;
          } else {
            n = n->left;
          }
        } else {
          if (n->right == nullptr) {
            n->right = inserted_node;
            break;
          } else {
            n = n->right;
          }
        }
      }
      inserted_node->parent = n;
    }
    insert_case1(inserted_node);

    _root->parent = _superRoot;
    _superRoot->left = _root;
    return search(data);
  }

  void insert_case1(Node *n) {
    if (n->parent == nullptr) {
      n->color = 0;
    } else {
      insert_case2(n);
    }
  }

  void insert_case2(Node *n) {
    if (n->parent->color == 0) {
      return;
    } else {
      insert_case3(n);
    }
  }

  void insert_case3(Node *n) {
    if (uncle(n) && uncle(n)->color == 1) {
      n->parent->color = 0;
      uncle(n)->color = 0;
      grandparent(n)->color = 1;
      insert_case1(grandparent(n));
    } else {
      insert_case4(n);
    }
  }

  void insert_case4(Node *n) {
    if (n == n->parent->right &&
        (grandparent(n) && n->parent == grandparent(n)->left)) {
      rotate_left(n->parent);
      n = n->left;
    } else if (n == n->parent->left &&
               (grandparent(n) && n->parent == grandparent(n)->right)) {
      rotate_right(n->parent);
      n = n->right;
    }
    insert_case5(n);
  }

  void insert_case5(Node *n) {
    n->parent->color = 0;
    grandparent(n)->color = 1;
    if (n == n->parent->left &&
        (grandparent(n) && n->parent == grandparent(n)->left)) {
      rotate_right(grandparent(n));
    } else {
      rotate_left(grandparent(n));
    }
  }

  // Delete
  void deleteNode(const Pair &data) { return; }

  // Utils
  Node *getMinimum(Node *root) {
    while (root && root->left != nullptr) {
      root = root->left;
    }
    return root;
  }

  Node *getMaximum(Node *root) {
    while (root && root->right != nullptr) {
      root = root->right;
    }
    return root;
  }

  Node *getRoot() { return _root; };
  Node *getMinNode() {
    if (_root == nullptr) {
      return _superRoot;
    }
    Node *node = _root;
    while (node && node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  Node *getMaxNode() {
    if (_root == nullptr) {
      return _superRoot;
    }
    Node *node = _root;
    while (node && node->right != nullptr) {
      node = node->right;
    }
    return node;
  }

  iterator begin() {
    if (_root == nullptr) {
      return _superRoot;
    }
    Node *node = _root;
    while (node && node->left != nullptr) {
      node = node->left;
    }
    return iterator(node);
  };

  const_iterator begin() const {
    if (_root == nullptr) {
      return _superRoot;
    }
    Node *node = _root;
    while (node && node->left != nullptr) {
      node = node->left;
    }
    return const_iterator(node);
  };

  iterator end() { return iterator(_superRoot); };
  const_iterator end() const { return const_iterator(_superRoot); };

  Node *getEnd() { return _superRoot; };

 private:
  Node *grandparent(Node *n) {
    if (n && n->parent && n->parent->parent) {
      return n->parent->parent;
    } else {
      return nullptr;
    }
  }
  Node *sibling(Node *n) {
    if (n == nullptr || n->parent == nullptr) {
      return nullptr;
    } else {
      if (n == n->parent->left) {
        return n->parent->right;
      } else {
        return n->parent->left;
      }
    }
  };
  Node *uncle(Node *n) {
    if (n != nullptr && n->parent != nullptr && n->parent->parent != nullptr) {
      return sibling(n->parent);
    } else {
      return nullptr;
    }
  };

  void rotate_left(Node *n) {
    Node *r = n->right;
    replace_node(n, r);
    n->right = r->left;
    if (r->left != nullptr) {
      r->left->parent = n;
    }
    r->left = n;
    n->parent = r;
  }

  void rotate_right(Node *n) {
    Node *l = n->left;
    replace_node(n, l);
    n->left = l->right;
    if (l->right != nullptr) {
      l->right->parent = n;
    }
    l->right = n;
    n->parent = l;
  }

  void replace_node(Node *oldn, Node *newn) {
    if (oldn->parent == nullptr) {
      _root = newn;
    } else {
      if (oldn == oldn->parent->left)
        oldn->parent->left = newn;
      else
        oldn->parent->right = newn;
    }
    if (newn != NULL) {
      newn->parent = oldn->parent;
    }
  }
};

}  // namespace ft

#endif