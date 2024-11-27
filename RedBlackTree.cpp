#include "RedBlackTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>



RedBlackTree::RedBlackTree() : root(NULL) {}

RedBlackTree::~RedBlackTree() {
    deleteTree(root);  
    std::cout<< "Капитан, дерево уничтожено!";
}

Node::Node(GroupNumber group) : group(group), color(RED), left(NULL), right(NULL), parent(NULL) {}

void RedBlackTree::rotateLeft(Node*& root, Node*& node) {
    Node* nodeRight = node->right;
    node->right = nodeRight->left;

    if (node->right != NULL)
        node->right->parent = node;

    nodeRight->parent = node->parent;

    if (node->parent == NULL)
        root = nodeRight;
    else if (node == node->parent->left)
        node->parent->left = nodeRight;
    else
        node->parent->right = nodeRight;

    nodeRight->left = node;
    node->parent = nodeRight;
}

void RedBlackTree::rotateRight(Node*& root, Node*& node) {
    Node* nodeLeft = node->left;
    node->left = nodeLeft->right;

    if (node->left != NULL)
        node->left->parent = node;

    nodeLeft->parent = node->parent;

    if (node->parent == NULL)
        root = nodeLeft;
    else if (node == node->parent->left)
        node->parent->left = nodeLeft;
    else
        node->parent->right = nodeLeft;

    nodeLeft->right = node;
    node->parent = nodeLeft;
}

void RedBlackTree::fixInsert(Node*& root, Node*& node) {
    Node* parent = NULL;
    Node* grandparent = NULL;

    while (node != root && node->color == RED && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else {
                if (node == parent->right) {
                    rotateLeft(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(root, grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
        else {
            Node* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else {
                if (node == parent->left) {
                    rotateRight(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(root, grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }

    root->color = BLACK;
}

// Функция для получения числового значения типа программы
int programTypeToInt(char programType) {
    if (programType == 'B')
        return 1;
    else if (programType == 'M')
        return 2;
    else if (programType == 'S')
        return 3;
    else
        return 0;  
}

Node* RedBlackTree::BSTInsert(Node* root, Node* node) {
    if (root == NULL)
        return node;
    // WIP, Пока не правильная логика
    // Сравнение по числовому значению типа программы
    int nodeTypeValue = programTypeToInt(node->group.programType);
    int rootTypeValue = programTypeToInt(root->group.programType);

    if (nodeTypeValue < rootTypeValue) {
        root->left = BSTInsert(root->left, node);
        root->left->parent = root;
    }
    else if (nodeTypeValue > rootTypeValue) {
        root->right = BSTInsert(root->right, node);
        root->right->parent = root;
    }
    else {
        // Если тип программы одинаковый, сравниваем по groupID
        if (node->group.groupID < root->group.groupID) {
            root->left = BSTInsert(root->left, node);
            root->left->parent = root;
        }
        else if (node->group.groupID > root->group.groupID) {
            root->right = BSTInsert(root->right, node);
            root->right->parent = root;
        }
    }

    return root;
}


void RedBlackTree::insert(char programType, int groupID) {
    GroupNumber group(programType, groupID);
    Node* node = new Node(group);
    root = BSTInsert(root, node);
    fixInsert(root, node);
}

void RedBlackTree::inOrderHelper(Node* root) {
    if (root == NULL)
        return;

    inOrderHelper(root->left);

    // Выводим тип программы
    std::cout << root->group.programType << "-";

    // Преобразуем groupID в строку и добавляем ведущие нули до 4 символов
    std::string groupIDStr = std::to_string(root->group.groupID);
    while (groupIDStr.length() < 4) {
        groupIDStr = "0" + groupIDStr;
    }

    std::cout << groupIDStr << " ";

    inOrderHelper(root->right);
}

void RedBlackTree::inOrder() {
    inOrderHelper(root);
}

bool isValidProgramType(char programType) {
    return (programType == 'B' || programType == 'M' || programType == 'S');
}

void RedBlackTree::loadFromFile(const std::string& filename) {

    std::ifstream inputFile(filename);  // Используем ifstream для чтения обычных символов
    if (!inputFile) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {  // Считываем файл построчно
        std::istringstream iss(line);
        char programType;
        int groupID;

        std::cout << "Считали строку: " << line << std::endl;  // Выводим считанную строку

        if (iss >> programType >> groupID) {
            if (!isValidProgramType(programType)) {
                std::cerr << "Ошибка: Недопустимый тип программы в строке: " << line << std::endl;
                continue;
            }

            if (groupID < 1000 || groupID > 9999) {
                std::cerr << "Ошибка: Номер группы должен быть четырёхзначным числом в строке: " << line << std::endl;
                continue;
            }

            insert(programType, groupID);
        } else {
            std::cerr << "Ошибка чтения строки: " << line << std::endl;
        }
    }

    inputFile.close();
}



void RedBlackTree::deleteTree(Node* node) {
    if (node == NULL)
        return;

    // Рекурсивно удаляем левого и правого потомков
    deleteTree(node->left);
    deleteTree(node->right);

    delete node;  // Удаляем текущий узел
}
