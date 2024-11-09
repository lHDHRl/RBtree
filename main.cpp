#include "RedBlackTree.h"

int main() {
    RedBlackTree tree;

    tree.insert('B', 1001);  // Бакалавриат
    tree.insert('M', 2001);  // Магистратура
    tree.insert('S', 3001);  // Специалитет
    tree.insert('B', 1002);
    tree.insert('M', 2002);
    tree.insert('S', 3002);

    std::cout << "Traversal of Created Tree:\n";
    tree.inOrder();
    std::cout << std::endl;

    return 0;
}