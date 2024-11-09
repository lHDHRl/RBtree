#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>

enum Color { RED, BLACK };

struct GroupNumber {
    char programType;
    int groupID;

    GroupNumber(char type, int id) : programType(type), groupID(id) {}
};

struct Node {
  GroupNumber group;
  Color color;
  Node *left, *right, *parent;

  Node(GroupNumber group);
};

class RedBlackTree {
 private:
  Node *root;

  void rotateLeft(Node*& root, Node*& node);
  void rotateRight(Node*& root, Node*& node);
  void fixInsert(Node*& root, Node*& node);
  Node* BSTInsert(Node* root, Node* node);
  void inOrderHelper(Node* root);
public:
    RedBlackTree();
    void insert(char programType, int groupID);
    void inOrder();
};

#endif