#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>

enum Color { RED, BLACK };

struct Node {
  int value;
  Color color;
  Node *left, *right, *parent;

  Node{int data{}};
};

class RedBlackTree {
 private:
  Node *root;

  void rotateLeft(Node *root)
}
}
