/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 02:13:10 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/16 17:21:30 by crendeha         ###   ########.fr       */
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
template <typename T, typename U>
class RBTreeReverseIterator;

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

template <typename T, typename Compare, typename Allocator>
class RBTree {
 public:
  typedef Node<T> Node;
  typedef T Pair;
  typedef typename Pair::first_type key_type;
  typedef ft::RBTreeIterator<T, Node> iterator;
  typedef ft::RBTreeIterator<const T, const Node> const_iterator;
  typedef ft::RBTreeReverseIterator<T, Node> reverse_iterator;
  typedef ft::RBTreeReverseIterator<const T, const Node> const_reverse_iterator;

  typedef Allocator allocator_type;
  typedef typename allocator_type::template rebind<Node>::other node_allocator;
  typedef Compare key_compare;

 private:
  Node *_superRoot;
  Node *_dummyRoot;
  Node *_root;
  allocator_type _alloc;
  node_allocator _nodeAlloc;
  key_compare _comp;

 public:
  RBTree()
      : _superRoot(nullptr),
        _dummyRoot(nullptr),
        _root(nullptr),
        _alloc(allocator_type()),
        _nodeAlloc(node_allocator()),
        _comp(key_compare()) {
    _superRoot = _nodeAlloc.allocate(1);
    _nodeAlloc.construct(_superRoot, Node(Pair()));
    _dummyRoot = _nodeAlloc.allocate(1);
    _nodeAlloc.construct(_dummyRoot, Node(Pair()));
  };

  RBTree(const RBTree &other)
      : _superRoot(nullptr), _dummyRoot(nullptr), _root(nullptr) {
    *this = other;
  };

  ~RBTree() {
    clear();
    cleanHelperRoots();
  }

  RBTree &operator=(const RBTree &other) {
    if (this != &other) {
      clear();
      cleanHelperRoots();

      _alloc = other._alloc;
      _nodeAlloc = other._nodeAlloc;
      _comp = other._comp;

      _superRoot = _nodeAlloc.allocate(1);
      _nodeAlloc.construct(_superRoot, Node(Pair()));
      _dummyRoot = _nodeAlloc.allocate(1);
      _nodeAlloc.construct(_dummyRoot, Node(Pair()));
      _root = clone(other._root, nullptr, other._dummyRoot);

      if (_root) {
        _root->parent = _superRoot;
        _superRoot->left = _root;
        Node *minNode = getMinimum(_root);
        _dummyRoot->parent = minNode;
        minNode->left = _dummyRoot;
      }
    }
    return *this;
  }

  /*
   **=========================================================================
   **     Clear
   **=========================================================================
   */

  void clear() { clearHelper(_root); }

  void clearHelper(Node *curr) {
    if (curr == nullptr || curr == _dummyRoot) {
      return;
    } else {
      clearHelper(curr->left);
      clearHelper(curr->right);
      _nodeAlloc.destroy(curr);
      _nodeAlloc.deallocate(curr, 1);
    }
  }

  void cleanHelperRoots() {
    if (_superRoot) {
      _nodeAlloc.destroy(_superRoot);
      _nodeAlloc.deallocate(_superRoot, 1);
    }
    if (_dummyRoot) {
      _nodeAlloc.destroy(_dummyRoot);
      _nodeAlloc.deallocate(_dummyRoot, 1);
    }
  }

  /*
   **=========================================================================
   **     Clone
   **=========================================================================
   */

  Node *clone(Node *curr, Node *parent, Node *otherDummy) {
    if (curr != nullptr && curr != otherDummy) {
      Node *node = _nodeAlloc.allocate(1);
      _nodeAlloc.construct(node, Node(curr->data));
      node->parent = parent;
      node->left = clone(curr->left, node, otherDummy);
      node->right = clone(curr->right, node, otherDummy);
      return node;
    } else {
      return nullptr;
    }
  }

  /*
   **=========================================================================
   **     Search
   **=========================================================================
   */

  iterator search(const key_type &key) {
    Node *res = searchHelp(key, _root);
    return res ? iterator(res) : end();
  }

  const_iterator search(const key_type &key) const {
    Node *res = searchHelp(key, _root);
    return res ? const_iterator(res) : end();
  }

  Node *searchHelp(const key_type &key, Node *root) {
    if (root == nullptr || root == _dummyRoot) {
      return nullptr;
    } else {
      bool cmpRes = _comp(key, root->data.first);
      if (root->data.first == key) {
        return root;
      } else if (cmpRes) {
        return searchHelp(key, root->left);
      } else {
        return searchHelp(key, root->right);
      }
    }
  };

  Node *searchHelp(const key_type &key, Node *root) const {
    if (root == nullptr || root == _dummyRoot) {
      return nullptr;
    } else {
      bool cmpRes = _comp(key, root->data.first);
      if (root->data.first == key) {
        return root;
      } else if (cmpRes) {
        return searchHelp(key, root->left);
      } else {
        return searchHelp(key, root->right);
      }
    }
  };

  /*
   **=========================================================================
   **     Insert
   **=========================================================================
   */

  iterator insertNode(const Pair &data) {
    if (_root != nullptr) {
      _root->parent = nullptr;
      _dummyRoot->parent->left = nullptr;
      _dummyRoot->parent = nullptr;
    }
    _superRoot->left = nullptr;
    Node *inserted_node = _nodeAlloc.allocate(1);
    _nodeAlloc.construct(inserted_node, Node(data));
    if (_root == nullptr) {
      _root = inserted_node;
    } else {
      Node *n = _root;
      while (1) {
        bool cmpRes = _comp(data.first, n->data.first);
        if (data.first == n->data.first) {
          n->data.second = data.second;
          return n;
        } else if (cmpRes) {
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
    Node *minNode = getMinimum(_root);
    minNode->left = _dummyRoot;
    _dummyRoot->parent = minNode;
    return search(data.first);
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

  /*
   **=========================================================================
   **     Delete
   **=========================================================================
   */

  void deleteNode(const key_type &key) {
    if (_root) {
      _root->parent = nullptr;
      _superRoot->left = nullptr;
      _dummyRoot->parent->left = nullptr;
      _dummyRoot->parent = nullptr;
    }
    Node *child;
    Node *n = searchHelp(key, _root);
    if (n == nullptr) {
      return;
    }
    if (n->left != nullptr && n->right != nullptr) {
      Node *pred = getMaximum(n->left);
      bool isLeft = false;
      if (n->parent && n->parent->left == n) {
        isLeft = true;
      }
      Node *tmpParent = n->parent;
      Node *leftChild = n->left;
      Node *rightChild = n->right;
      int tmpColor = n->color;
      _nodeAlloc.destroy(n);
      _nodeAlloc.deallocate(n, 1);
      n = _nodeAlloc.allocate(1);
      _nodeAlloc.construct(n, Node(pred->data));
      if (tmpParent) {
        n->parent = tmpParent;
        if (isLeft) {
          tmpParent->left = n;
        } else {
          tmpParent->right = n;
        }
      }
      if (leftChild) {
        leftChild->parent = n;
        n->left = leftChild;
      }
      if (rightChild) {
        rightChild->parent = n;
        n->right = rightChild;
      }
      n->color = tmpColor;
      n = pred;
    }
    child = n->right == nullptr ? n->left : n->right;
    if (n->color == 0) {
      n->color = child != nullptr ? child->color : 0;
      delete_case1(n);
    }
    replace_node(n, child);
    _nodeAlloc.destroy(n);
    _nodeAlloc.deallocate(n, 1);
    if (_root) {
      _root->parent = _superRoot;
      _superRoot->left = _root;
      Node *minNode = getMinimum(_root);
      _dummyRoot->parent = minNode;
      minNode->left = _dummyRoot;
    }
  }

  void delete_case1(Node *n) {
    if (n->parent == NULL) {
      return;
    } else {
      delete_case2(n);
    }
  }

  void delete_case2(Node *n) {
    if (sibling(n) && sibling(n)->color == 1) {
      n->parent->color = 1;
      sibling(n)->color = 0;
      if (n == n->parent->left)
        rotate_left(n->parent);
      else
        rotate_right(n->parent);
    }
    delete_case3(n);
  }

  void delete_case3(Node *n) {
    if (n->parent->color == 0 && sibling(n) && sibling(n)->color == 0 &&
        (sibling(n)->left == nullptr || sibling(n)->left->color == 0) &&
        (sibling(n)->right == nullptr || sibling(n)->right->color == 0)) {
      sibling(n)->color = RED;
      delete_case1(n->parent);
    } else {
      delete_case4(n);
    }
  }

  void delete_case4(Node *n) {
    if (n->parent->color == 1 && sibling(n) && sibling(n)->color == 0 &&
        (sibling(n)->left == nullptr || sibling(n)->left->color == 0) &&
        (sibling(n)->right == nullptr || sibling(n)->right->color == 0)) {
      sibling(n)->color = 1;
      n->parent->color = 0;
    } else {
      delete_case5(n);
    }
  }

  void delete_case5(Node *n) {
    if (n == n->parent->left && sibling(n) && sibling(n)->color == 0 &&
        sibling(n)->left && sibling(n)->left->color == 1 &&
        (sibling(n)->right == nullptr || sibling(n)->right->color == 0)) {
      sibling(n)->color = 1;
      sibling(n)->left->color = 0;
      rotate_right(sibling(n));
    } else if (n == n->parent->right && sibling(n) && sibling(n)->color == 0 &&
               (sibling(n)->right && sibling(n)->right->color == 1) &&
               (sibling(n)->left == nullptr || sibling(n)->left->color == 0)) {
      sibling(n)->color = 1;
      sibling(n)->right->color = 0;
      rotate_left(sibling(n));
    }
    delete_case6(n);
  }

  void delete_case6(Node *n) {
    if (sibling(n)) {
      sibling(n)->color = n->parent->color;
    }
    n->parent->color = 0;
    if (n == n->parent->left) {
      if (sibling(n) && sibling(n)->right->color == 1) {
        sibling(n)->right->color = 0;
      }
      rotate_left(n->parent);
    } else {
      if (sibling(n) && sibling(n)->left->color == 1) {
        sibling(n)->left->color = 0;
      }
      rotate_right(n->parent);
    }
  }

  /*
   **=========================================================================
   **     Utils
   **=========================================================================
   */

  Node *getMinimum(Node *root) {
    while (root && root->left != nullptr && root->left != _dummyRoot) {
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
    while (node && node->left != nullptr && node->left != _dummyRoot) {
      node = node->left;
    }
    return node;
  }

  Node *getMinNode() const {
    if (_root == nullptr) {
      return _superRoot;
    }
    Node *node = _root;
    while (node && node->left != nullptr && node->left != _dummyRoot) {
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

  iterator begin() { return iterator(getMinNode()); };

  const_iterator begin() const { return const_iterator(getMinNode()); };

  iterator end() { return iterator(_superRoot); };
  const_iterator end() const { return const_iterator(_superRoot); };

  reverse_iterator rbegin() {
    if (_root == nullptr) {
      return reverse_iterator(_dummyRoot);
    }
    reverse_iterator rbegin = reverse_iterator(_superRoot);
    ++rbegin;
    return rbegin;
  };

  const_reverse_iterator rbegin() const {
    if (_root == nullptr) {
      return reverse_iterator(_dummyRoot);
    }
    const_reverse_iterator rbegin = const_reverse_iterator(_superRoot);
    rbegin++;
    return rbegin;
  };

  reverse_iterator rend() { return reverse_iterator(_dummyRoot); };
  const_reverse_iterator rend() const {
    return const_reverse_iterator(_dummyRoot);
  };

  iterator lower_bound(const key_type &key) {
    Node *curr = _root;
    Node *res = _superRoot;

    while (curr && curr != _dummyRoot) {
      bool cmpRes = _comp(key, curr->data.first);
      if (cmpRes || key == curr->data.first) {
        res = curr;
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return iterator(res);
  };

  const_iterator lower_bound(const key_type &key) const {
    Node *curr = _root;
    Node *res = _superRoot;

    while (curr && curr != _dummyRoot) {
      bool cmpRes = _comp(key, curr->data.first);
      if (cmpRes || key == curr->data.first) {
        res = curr;
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return const_iterator(res);
  };

  iterator upper_bound(const key_type &key) {
    Node *curr = _root;
    Node *res = _superRoot;

    while (curr && curr != _dummyRoot) {
      bool cmpRes = _comp(key, curr->data.first);
      if (cmpRes) {
        res = curr;
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return iterator(res);
  };

  const_iterator upper_bound(const key_type &key) const {
    Node *curr = _root;
    Node *res = _superRoot;

    while (curr && curr != _dummyRoot) {
      bool cmpRes = _comp(key, curr->data.first);
      if (cmpRes) {
        res = curr;
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    return const_iterator(res);
  };

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
    if (n == nullptr) {
      return;
    }
    Node *r = n->right;
    replace_node(n, r);
    if (n && r) {
      n->right = r->left;
    }
    if (r && r->left != nullptr) {
      r->left->parent = n;
    }
    if (r) {
      r->left = n;
    }
    n->parent = r;
  }

  void rotate_right(Node *n) {
    if (n == nullptr) {
      return;
    }
    Node *l = n->left;
    replace_node(n, l);
    if (n && l) {
      n->left = l->right;
    }
    if (l && l->right != nullptr) {
      l->right->parent = n;
    }
    if (l) {
      l->right = n;
    }
    n->parent = l;
  }

  void replace_node(Node *oldn, Node *newn) {
    if (oldn->parent == nullptr) {
      _root = newn;
    } else {
      if (oldn == oldn->parent->left) {
        oldn->parent->left = newn;
      } else
        oldn->parent->right = newn;
    }
    if (newn != NULL) {
      newn->parent = oldn->parent;
    }
  }
};

}  // namespace ft

#endif