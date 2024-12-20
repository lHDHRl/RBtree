#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <string>
#include "src/LinkedList.h"


enum Color { RED, BLACK };

struct GroupNumber {
    char programType;
    int groupID;

    GroupNumber(char type, int id) : programType(type), groupID(id) {}
};

struct Node {
    GroupNumber group;
    Color color;
    Node* left, * right, * parent;
    linkedList DuplicateList;

    Node(GroupNumber group);
};

class RedBlackTree {
private:
    void transplant(Node* u, Node* v);
    Node* root;
    void rotateLeft(Node*& root, Node*& node);
    void rotateRight(Node*& root, Node*& node);
    void fixInsert(Node*& root, Node*& node);
    Node* BSTInsert(Node* root, Node* node);
    void inOrderHelper(Node* root);
    void showTreeHelper(Node* root, int level);
    Node* maximumNode(Node* node);
    void deleteNode(Node* nodeToDelete);
    void fixDeleting(Node* p);
public:
    ~RedBlackTree(); 
    void deleteNodeByValue(const GroupNumber& group);
    Node* findNode(Node* root, const GroupNumber& group);
    Node* getRoot();
    void showTree();
    void deleteTree(Node* node);  
    RedBlackTree();
    void insert(char programType, int groupID,int lineNumber);
    void inOrder();
    void loadFromFile(const std::string& filename);
};

#endif
