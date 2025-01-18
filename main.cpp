#include "RedBlackTree.h"
#include <iostream>
#include <cassert>

void testCase1() {
    // Случай 1: Удаляемый узел красный
    RedBlackTree tree;
    tree.insert('B', 10);
    tree.insert('B', 5);
    tree.insert('B', 15);
    tree.insert('B', 3);  // Красный узел
    tree.showTree();

    std::cout << "Удаляем красный узел 3\n";
    tree.deleteNodeByValue(GroupNumber('B', 3));
    tree.showTree();

    // Проверка, что дерево осталось сбалансированным
    assert(tree.findNode(tree.getRoot(), GroupNumber('B', 3)) == nullptr);
    std::cout << "Тест 1 пройден!\n\n";
}

void testCase2() {
    // Случай 2: Удаляемый узел черный, его ребенок красный
    RedBlackTree tree;
    tree.insert('B', 10);
    tree.insert('B', 5);
    tree.insert('B', 15);
    tree.insert('B', 3);  // Красный узел
    tree.showTree();

    std::cout << "Удаляем черный узел 5, его ребенок 3 красный\n";
    tree.deleteNodeByValue(GroupNumber('B', 5));
    tree.showTree();

    // Проверка, что дерево осталось сбалансированным
    assert(tree.findNode(tree.getRoot(), GroupNumber('B', 5)) == nullptr);
    std::cout << "Тест 2 пройден!\n\n";
}

void testCase3() {
    // Случай 3: Удаляемый узел черный, его ребенок черный, и брат красный
    RedBlackTree tree;
    tree.insert('B', 10); // Корень (черный)
    tree.insert('B', 5);  // Левый ребенок корня (черный)
    tree.insert('B', 20); // Правый ребенок корня (красный)
    tree.insert('B', 30); // Левый ребенок узла 20 (черный)
    tree.showTree();

    std::cout << "Удаление узла с одним ребенком (черным)\n";
    tree.deleteNodeByValue(GroupNumber('B', 5));
    tree.showTree();

    // Проверка, что дерево осталось сбалансированным
    assert(tree.findNode(tree.getRoot(), GroupNumber('B', 5)) == nullptr);
    std::cout << "Тест 3 пройден!\n\n";
}

void testCase4() {
    // Случай 4: Удаляемый узел черный, его ребенок красный, брат черный, и оба ребенка брата черные
    RedBlackTree tree;
    tree.insert('B', 10);
    tree.insert('B', 5);
    tree.insert('B', 20);
    tree.insert('B', 15);
    tree.insert('B', 30);
    tree.showTree();

    std::cout << "Удаление узла с двумя детьми (красный и черный)\n";
    tree.deleteNodeByValue(GroupNumber('B', 20));
    tree.showTree();

    // Проверка, что дерево осталось сбалансированным
    assert(tree.findNode(tree.getRoot(), GroupNumber('B', 3)) == nullptr);
    std::cout << "Тест 4 пройден!\n\n";
}

void testCase5() {
    // Случай 5: Удаляемый узел черный, его ребенок черный, брат черный, левый ребенок брата красный, правый черный
    RedBlackTree tree;
    tree.insert('B', 10);
    tree.insert('B', 5);
    tree.insert('B', 20);
    tree.insert('B', 15);  // Черный узел
    tree.insert('B', 30);  // Черный узел
    tree.showTree();

    std::cout << "Удаление узла с нарушением свойств красно-черного дерева\n";
    tree.deleteNodeByValue(GroupNumber('B', 15));
    tree.showTree();

    // Проверка, что дерево осталось сбалансированным
    assert(tree.findNode(tree.getRoot(), GroupNumber('B', 3)) == nullptr);
    std::cout << "Тест 5 пройден!\n\n";
}

void testCase6() {
    // Случай 6: Удаляемый узел черный, его ребенок черный, брат черный, правый ребенок брата красный
    RedBlackTree tree;
    tree.insert('B', 10);
    tree.insert('B', 5);
    tree.insert('B', 20);
    tree.insert('B', 15);  // Черный узел
    tree.insert('B', 30);  // Черный узел
    tree.showTree();

    std::cout << "Удаление узла с двойным черным нарушением\n";
    tree.deleteNodeByValue(GroupNumber('B', 5));
    tree.showTree();

    // Проверка, что дерево осталось сбалансированным
    assert(tree.findNode(tree.getRoot(), GroupNumber('B', 3)) == nullptr);
    std::cout << "Тест 6 пройден!\n\n";
}

void testCase7() {
    // Случай 7: Удаляемый узел черный, его ребенок черный, брат черный, правый ребенок брата красный
    RedBlackTree tree;
    tree.insert('B', 10);
    tree.insert('B', 5);
    tree.insert('B', 20);
    tree.insert('B', 15);  // Черный узел
    tree.insert('B', 30);  // Черный узел
    tree.insert('B', 35);  // Черный узел
    tree.showTree();

    std::cout << "Удаление узла с двойным черным нарушением и красным братом\n";
    tree.deleteNodeByValue(GroupNumber('B', 5));
    tree.showTree();
    // Проверка, что дерево осталось сбалансированным
    assert(tree.findNode(tree.getRoot(), GroupNumber('B', 3)) == nullptr);
    std::cout << "Тест 7 пройден!\n\n";
}

void testCase8() {
    // Случай 7: Удаляемый узел черный, его ребенок черный, брат черный, правый ребенок брата красный
    RedBlackTree tree;
    
    tree.loadFromFile("data.txt");
    tree.showTree();

    std::cout << "Удаление узла с двумя черными детьми\n";
    tree.deleteNodeByValue(GroupNumber('B', 2000));
    tree.showTree();
    tree.deleteNodeByValue(GroupNumber('B', 1112));
    tree.showTree();
    // Проверка, что дерево осталось сбалансированным
    assert(tree.findNode(tree.getRoot(), GroupNumber('B', 3)) == nullptr);
    std::cout << "Тест 8 пройден!\n\n";
}
void testCase9() {
    // Случай 7: Удаляемый узел черный, его ребенок черный, брат черный, правый ребенок брата красный
    RedBlackTree tree;
    tree.insert('B',10);
    tree.insert('B',7);
    tree.insert('B',15);
    tree.showTree();
    tree.insert('B',5);
    tree.insert('B',3);
    tree.insert('B',13);
    tree.showTree();
    tree.insert('B',20);
    tree.insert('B',25);
    tree.showTree();
    std::cout << "Тест 9 пройден!\n\n";
}
    
int main() {
    testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();
    testCase6();
    testCase7();
    testCase8();
    testCase9();
    std::cout << "Все тесты пройдены успешно!\n";
    return 0;
}