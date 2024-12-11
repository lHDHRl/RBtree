#include "RedBlackTree.h"
#include <iostream>


int main() {

    RedBlackTree tree;
    tree.loadFromFile("data.txt");
    tree.showTree();
    tree.inOrder();
    std::cout << "Корень дерева: " << tree.getRoot()->group.programType << "-" << tree.getRoot()->group.groupID << std::endl;
    std::cout << std::endl;

    return 0;
}