/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 02:13:10 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/09 17:58:11 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>

#include "Pair.hpp"

namespace ft {

template <typename T1, typename T2>
struct Node {
  Node(Pair<T1, T2> data)
      : data(data), parent(nullptr), left(nullptr), right(nullptr), color(1){};
  Pair<T1, T2> data;
  Node<T1, T2> *parent;
  Node<T1, T2> *left;
  Node<T1, T2> *right;
  int color;  // 1 -> Red, 0 -> Black
};

template <typename T1, typename T2>
class RBTree {
 public:
  RBTree() : _root(nullptr), ll(false), rr(false), rl(false), lr(false){};

  Node<T1, T2> *search(const T1 &key, Node<T1, T2> *root) {
    if (root == nullptr || root->data.first == key) {
      return root;
    } else {
      if (key < root->data.first) {
        return search(key, root->left);
      } else {
        return search(key, root->right);
      }
    }
  };

  // Rotation
  Node<T1, T2> *rotateLeft(Node<T1, T2> *node) {
    Node<T1, T2> *x = node->right;
    Node<T1, T2> *y = x->left;
    x->left = node;
    node->right = y;
    node->parent = x;
    if (y != nullptr) {
      y->parent = node;
    }
    return x;
  }

  Node<T1, T2> *rotateRight(Node<T1, T2> *node) {
    Node<T1, T2> *x = node->left;
    Node<T1, T2> *y = x->right;
    x->right = node;
    node->left = y;
    node->parent = x;
    if (y != nullptr) {
      y->parent = node;
    }
    return x;
  }

  Node<T1, T2> *insertHelp(Node<T1, T2> *root, Pair<T1, T2> data) {
    bool f = false;  // Red Red Conflict
    if (root == nullptr) {
      return (new Node<T1, T2>(data));
    } else if (data.first < root->data.first) {
      root->left = insertHelp(root->left, data);
      root->left->parent = root;
      if (root != _root) {
        if (root->color && root->left->color) {
          f = true;
        }
      }
    } else {
      root->right = insertHelp(root->right, data);
      root->right->parent = root;
      if (root != _root) {
        if (root->color && root->right->color) {
          f = true;
        }
      }
    }

    if (ll) {
      root = rotateLeft(root);
      root->color = 0;
      root->left->color = 1;
      ll = false;
    } else if (rr) {
      root = rotateRight(root);
      root->color = 0;
      root->right->color = 1;
      rr = false;
    } else if (rl) {
      root->right = rotateRight(root->right);
      root->right->parent = root;
      root = rotateLeft(root);
      root->color = 0;
      root->left->color = 1;
      rl = false;
    } else if (lr) {
      root->left = rotateLeft(root->left);
      root->left->parent = root;
      root = rotateRight(root);
      root->color = 0;
      root->right->color = 1;
      lr = false;
    }

    if (f) {
      if (root->parent->right == root) {
        if (root->parent->left == nullptr || root->parent->left->color == 0) {
          if (root->left != nullptr && root->left->color == 1) {
            rl = true;
          } else if (root->right != nullptr && root->right->color == 1) {
            ll = true;
          }
        } else {
          root->parent->left->color = 0;
          root->color = 0;
          if (root->parent != _root) {
            root->parent->color = 1;
          }
        }
      } else {
        if (root->parent->right == nullptr || root->parent->right->color == 0) {
          if (root->left != nullptr && root->left->color == 1) {
            rr = true;
          } else if (root->right != nullptr && root->right->color == 1) {
            lr = true;
          }
        } else {
          root->parent->right->color = 0;
          root->color = 0;
          if (root->parent != _root) {
            root->parent->color = 1;
          }
        }
      }
      f = false;
    }
    return root;
  }

  Node<T1, T2> *insert(Pair<T1, T2> data) {
    if (_root == nullptr) {
      _root = new Node<T1, T2>(data);
      _root->color = 0;
      return _root;
    } else {
      _root = insertHelp(_root, data);
    }
    return search(data.first, _root);
  };

  void fixDeletion(Node<T1, T2> *x) {
    Node<T1, T2> *s;
    while (x != _root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rotateLeft(x->parent);  // double check | different implementations
          s = x->parent->right;
        }
        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rotateRight(s);
            s = x->parent->right;
          }
          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          rotateLeft(x->parent);
          x = _root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rotateRight(x->parent);
          s = x->parent->left;
        }
        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            rotateLeft(s);
            s = x->parent->left;
          }
          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rotateRight(x->parent);
          x = _root;
        }
      }
    }
    x->color = 0;
  }

  void swapNodesForDeletion(Node<T1, T2> *u, Node<T1, T2> *v) {
    if (u->parent == nullptr) {
      _root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteHelp(Node<T1, T2> *root, const T1 &key) {
    Node<T1, T2> *z = nullptr;
    Node<T1, T2> *x, *y;
    while (root != nullptr) {
      if (root->data.first == key) {
        z = root;
        break;
      } else if (root->data.first < key) {
        root = root->right;
      } else {
        root = root->left;
      }
    }
    if (z == nullptr) {
      return;
    }
    y = z;
    int yColor = y->color;
    if (z->left == nullptr) {
      x = z->right;
      swapNodesForDeletion(z, z->right);
    } else if (z->right == nullptr) {
      x = z->left;
      swapNodesForDeletion(z, z->left);
    } else {
      y = getMinimum(z->right);
      yColor = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        swapNodesForDeletion(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      swapNodesForDeletion(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    if (yColor == 0) {
      fixDeletion(x);
    }
  }

  void deleteKey(const T1 &key) { deleteHelp(_root, key); }

  Node<T1, T2> *getMinimum(Node<T1, T2> *root) {
    while (root->left != nullptr) {
      root = root->left;
    }
    return root;
  }

  Node<T1, T2> *getMaximum(Node<T1, T2> *root) {
    while (root->right != nullptr) {
      root = root->right;
    }
    return root;
  }

  Node<T1, T2> *getRoot() { return _root; };
  Node<T1, T2> *getMinNode() {
    Node<T1, T2> *node = _root;
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }
  Node<T1, T2> *getMaxNode() {
    Node<T1, T2> *node = _root;
    while (node->right != nullptr) {
      node = node->right;
    }
    return node;
  }

 private:
  Node<T1, T2> *_root;
  bool ll;
  bool rr;
  bool rl;
  bool lr;
};

}  // namespace ft

#endif