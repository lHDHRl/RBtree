#include "RedBlackTree.h"
#include <iostream>


int main() {
    RedBlackTree tree;

    tree.loadFromFile("data.txt");

    tree.showTree();



    GroupNumber group('M', 1999);
    tree.deleteNodeByValue(group);

    


    tree.showTree();
    tree.inOrder();
    std::cout << std::endl;
    return 0;
}