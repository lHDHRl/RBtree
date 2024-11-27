#include "RedBlackTree.h"
#include <iostream>
int main() {


    RedBlackTree tree;

    tree.loadFromFile("data.txt");

    std::cout << "Traversal of Created Tree:\n";
    tree.inOrder();
    std::cout << std::endl;

    return 0;
}