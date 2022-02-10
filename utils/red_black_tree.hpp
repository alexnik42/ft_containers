/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crendeha <crendeha@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 02:13:10 by crendeha          #+#    #+#             */
/*   Updated: 2022/02/11 02:01:39 by crendeha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include <iostream>

#include "Pair.hpp"

namespace ft {

template <typename Key, typename T>
struct Node {
  Node(Pair<const Key, T> data)
      : data(data), parent(nullptr), left(nullptr), right(nullptr), color(1){};
  Pair<const Key, T> data;
  Node<const Key, T> *parent;
  Node<const Key, T> *left;
  Node<const Key, T> *right;
  int color;  // 1 -> Red, 0 -> Black
};

template <typename Key, typename T>
class RBTree {
 public:
  typedef Node<const Key, T> Node;

  RBTree()
      : _superRoot(nullptr),
        _root(nullptr),
        ll(false),
        rr(false),
        rl(false),
        lr(false) {
    _superRoot = new Node(Pair<const Key, T>());
  };

  Node *search(const T &key) { return searchHelp(key, _root); }

  Node *searchHelp(const T &key, Node *root) {
    if (root == nullptr || root->data.first == key) {
      return root;
    } else {
      if (key < root->data.first) {
        return searchHelp(key, root->left);
      } else {
        return searchHelp(key, root->right);
      }
    }
  };

  // Rotation
  // Node *rotateLeft(Node *node) {
  //   Node *x = node->right;
  //   Node *y = x->left;
  //   x->left = node;
  //   node->right = y;
  //   node->parent = x;
  //   if (y != nullptr) {
  //     y->parent = node;
  //   }
  //   return x;
  // }

  // Node *rotateRight(Node *node) {
  //   Node *x = node->left;
  //   Node *y = x->right;
  //   x->right = node;
  //   node->left = y;
  //   node->parent = x;
  //   if (y != nullptr) {
  //     y->parent = node;
  //   }
  //   return x;
  // }

  // Node *insertHelp(Node *root, Pair<const Key, T> data) {
  //   bool f = false;  // Red Red Conflict
  //   if (root == nullptr) {
  //     return (new Node(data));
  //   } else if (data.first < root->data.first) {
  //     root->left = insertHelp(root->left, data);
  //     root->left->parent = root;
  //     if (root != _root) {
  //       if (root->color == 1 && root->left->color == 1) {
  //         f = true;
  //       }
  //     }
  //   } else {
  //     root->right = insertHelp(root->right, data);
  //     root->right->parent = root;
  //     if (root != _root) {
  //       if (root->color == 1 && root->right->color == 1) {
  //         f = true;
  //       }
  //     }
  //   }

  //   if (ll) {
  //     root = rotateLeft(root);
  //     root->color = 0;
  //     root->left->color = 1;
  //     ll = false;
  //   } else if (rr) {
  //     root = rotateRight(root);
  //     root->color = 0;
  //     root->right->color = 1;
  //     rr = false;
  //   } else if (rl) {
  //     root->right = rotateRight(root->right);
  //     root->right->parent = root;
  //     root = rotateLeft(root);
  //     root->color = 0;
  //     root->left->color = 1;
  //     rl = false;
  //   } else if (lr) {
  //     root->left = rotateLeft(root->left);
  //     root->left->parent = root;
  //     root = rotateRight(root);
  //     root->color = 0;
  //     root->right->color = 1;
  //     lr = false;
  //   }

  //   if (f) {
  //     if (root->parent->right == root) {
  //       if (root->parent->left == nullptr || root->parent->left->color ==
  //       0)
  //       {
  //         if (root->left != nullptr && root->left->color == 1) {
  //           rl = true;
  //         } else if (root->right != nullptr && root->right->color == 1) {
  //           ll = true;
  //         }
  //       } else {
  //         root->parent->left->color = 0;
  //         root->color = 0;
  //         if (root->parent != _root) {
  //           root->parent->color = 1;
  //         }
  //       }
  //     } else {
  //       if (root->parent->right == nullptr || root->parent->right->color
  //       == 0) {
  //         if (root->left != nullptr && root->left->color == 1) {
  //           rr = true;
  //         } else if (root->right != nullptr && root->right->color == 1) {
  //           lr = true;
  //         }
  //       } else {
  //         root->parent->right->color = 0;
  //         root->color = 0;
  //         if (root->parent != _root) {
  //           root->parent->color = 1;
  //         }
  //       }
  //     }
  //     f = false;
  //   }
  //   return root;
  // }

  Node *insertInTheTree(Node *root, Node *pt) {
    if (root == nullptr) {
      return pt;
    }

    if (pt->data.first < root->data.first) {
      root->left = insertInTheTree(root->left, pt);
      root->left->parent = root;
    } else if (pt->data.first > root->data.first) {
      root->right = insertInTheTree(root->right, pt);
      root->right->parent = root;
    }
    return root;
  };

  void rotateLeftInsertion(Node *&root, Node *&pt) {
    Node *pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != nullptr) pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
      root = pt_right;

    else if (pt == pt->parent->left)
      pt->parent->left = pt_right;

    else
      pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
  }

  void rotateRightInsertion(Node *&root, Node *&pt) {
    Node *pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != nullptr) pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
      root = pt_left;

    else if (pt == pt->parent->left)
      pt->parent->left = pt_left;

    else
      pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
  }

  void fixInsertion(Node *&root, Node *&pt) {
    Node *parent_pt = nullptr;
    Node *grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != 0) && (pt->parent->color == 1)) {
      parent_pt = pt->parent;
      grand_parent_pt = pt->parent->parent;

      if (parent_pt == grand_parent_pt->left) {
        Node *uncle_pt = grand_parent_pt->right;

        if (uncle_pt != nullptr && uncle_pt->color == 1) {
          grand_parent_pt->color = 1;
          parent_pt->color = 0;
          uncle_pt->color = 0;
          pt = grand_parent_pt;
        }

        else {
          if (pt == parent_pt->right) {
            rotateLeftInsertion(root, parent_pt);
            pt = parent_pt;
            parent_pt = pt->parent;
          }
          rotateRightInsertion(root, grand_parent_pt);
          std::swap(parent_pt->color, grand_parent_pt->color);
          pt = parent_pt;
        }
      }

      else {
        Node *uncle_pt = grand_parent_pt->left;

        if ((uncle_pt != nullptr) && (uncle_pt->color == 1)) {
          grand_parent_pt->color = 1;
          parent_pt->color = 0;
          uncle_pt->color = 0;
          pt = grand_parent_pt;
        } else {
          if (pt == parent_pt->left) {
            rotateRightInsertion(root, parent_pt);
            pt = parent_pt;
            parent_pt = pt->parent;
          }

          rotateLeftInsertion(root, grand_parent_pt);
          std::swap(parent_pt->color, grand_parent_pt->color);
          pt = parent_pt;
        }
      }
    }

    root->color = 0;
  };

  Node *insert(Pair<const Key, T> data) {
    if (_root != nullptr) {
      _root->parent = nullptr;
      _superRoot->left = nullptr;
    }
    delete _superRoot;
    Node *pt = new Node(data);
    _root = insertInTheTree(_root, pt);
    fixInsertion(_root, pt);

    // _root = insertHelp(_root, data);

    _superRoot = new Node(Pair<const Key, T>());
    _root->parent = _superRoot;
    _superRoot->left = _root;
    return search(data.first);
  };

  void leftRotateDeletion(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      _root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotateDeletion(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      _root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  void fixDeletion(Node *x) {
    Node *s;
    while (x != _root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotateDeletion(x->parent);
          s = x->parent->right;
        }
        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotateDeletion(s);
            s = x->parent->right;
          }
          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotateDeletion(x->parent);
          x = _root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotateDeletion(x->parent);
          s = x->parent->left;
        }
        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotateDeletion(s);
            s = x->parent->left;
          }
          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotateDeletion(x->parent);
          x = _root;
        }
      }
    }
    x->color = 0;
  }

  void swapNodesForDeletion(Node *u, Node *v) {
    if (u->parent == nullptr) {
      _root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteHelp(Node *root, const T &key) {
    Node *z = nullptr;
    Node *x, *y;
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

  void deleteKey(const T &key) { deleteHelp(_root, key); }

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

  Node *getBegin() { return getMinNode(); }
  Node *getEnd() { return _superRoot; }

 private:
  Node *_superRoot;
  Node *_root;
  bool ll;
  bool rr;
  bool rl;
  bool lr;
};

}  // namespace ft

#endif