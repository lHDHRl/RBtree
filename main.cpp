#include "RedBlackTree.h"
#include <iostream>


int main() {
    RedBlackTree tree;

    tree.loadFromFile("data.txt");

    tree.showTree();
    GroupNumber group('B',2000);
    tree.deleteNodeByValue(group);
    
    tree.showTree();
    tree.deleteNodeByValue(GroupNumber('B',1112));
      tree.showTree();
    tree.deleteNodeByValue(GroupNumber('B',4000));
    tree.insert('B', 33000);
    tree.showTree();
    tree.inOrder();
    std::cout << std::endl;
    tree.inOrderToFile("output.txt");
    return 0;
}