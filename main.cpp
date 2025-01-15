#include "RedBlackTree.h"
#include <iostream>


int main() {
    RedBlackTree tree;
    tree.insert('B',10);
    tree.insert('B',5);
    tree.insert('B',15);
    tree.insert('B',3);
    tree.insert('B',7);
    tree.insert('B',12);
    tree.insert('B',20);
    tree.showTree();
    tree.deleteNodeByValue(GroupNumber('B', 10));
    tree.showTree();
    tree.deleteNodeByValue(GroupNumber('B', 7));
    tree.showTree();
    std::cout << std::endl;

    return 0;
}