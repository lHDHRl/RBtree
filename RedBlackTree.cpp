#include "RedBlackTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <optional>

int lastLineNumber = 0;

RedBlackTree::RedBlackTree() : root(NULL) {}

RedBlackTree::~RedBlackTree() {
    deleteTree(root);
    lastLineNumber = 0;
    std::cout<< "Дерево уничтожено!";
}

Node::Node(GroupNumber group) : group(group), color(RED), left(NULL), right(NULL), parent(NULL), DuplicateList() {}


Node* RedBlackTree::getRoot() {
    return root;
}

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

void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

void RedBlackTree::fixInsert(Node*& root, Node*& node) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;

    while (node != root && node->color == RED && node->parent != nullptr && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent ? grandparent->right : nullptr;

            // Случай 1: Дядя красный
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                // Случай 2 и 3: Дядя черный
                if (node == parent->right) {
                    rotateLeft(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(root, grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            Node* uncle = grandparent ? grandparent->left : nullptr;

            // Случай 1: Дядя красный
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                // Случай 2 и 3: Дядя черный
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

    root->color = BLACK;  // Убедиться, что корень всегда черный
}



bool isValidProgramType(char programType) {
    return (programType == 'B' || programType == 'M' || programType == 'S');
}


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

Node* RedBlackTree::findNode(Node* root, const GroupNumber& group) {
    if (root == NULL) {
        return NULL;
    }

    if (root->group.programType == group.programType && root->group.groupID == group.groupID) {
        std::cout << "Найден узел: " << root->group.programType << "-" << root->group.groupID << std::endl;
        return root;
    }

    int cmp = programTypeToInt(group.programType) - programTypeToInt(root->group.programType);
    if (cmp == 0) {
        cmp = group.groupID - root->group.groupID;
    }

    if (cmp < 0) {
        return findNode(root->left, group);
    } else {
        return findNode(root->right, group);
    }   
}

void RedBlackTree::deleteNode(Node* nodeToDelete) {
    Node* child = nullptr;
    Node* parent = nullptr;
    Color originalColor = nodeToDelete->color;

    if (nodeToDelete->left == nullptr) {
        // Случай 1: Нет левого ребенка
        child = nodeToDelete->right;
        if (child == nullptr) {
            // Создаем пустышку, если оба ребенка nullptr
            child = new Node(GroupNumber(' ', 0));
            child->color = BLACK;
            child->parent = nodeToDelete;
            nodeToDelete->right = child;
        }
        transplant(nodeToDelete, child);
        parent = nodeToDelete->parent;
    } else if (nodeToDelete->right == nullptr) {
        // Случай 2: Нет правого ребенка
        child = nodeToDelete->left;
        if (child == nullptr) {
            // Создаем пустышку, если оба ребенка nullptr
            child = new Node(GroupNumber(' ', 0));
            child->color = BLACK;
            child->parent = nodeToDelete;
            nodeToDelete->left = child;
        }
        transplant(nodeToDelete, child);
        parent = nodeToDelete->parent;
    } else {
        // Случай 3: Есть оба ребенка
        // Находим максимальный элемент в левом поддереве
        Node* predecessor = maximumNode(nodeToDelete->left);
        originalColor = predecessor->color;
        child = predecessor->left;
        if (child == nullptr) {
            // Создаем пустышку, если левый ребенок nullptr
            child = new Node(GroupNumber(' ', 0));
            child->color = BLACK;
            child->parent = predecessor;
            predecessor->left = child;
        }
        if (predecessor->parent == nodeToDelete) {
            parent = predecessor;
        } else {
            transplant(predecessor, child);
            predecessor->left = nodeToDelete->left;
            predecessor->left->parent = predecessor;
            parent = predecessor->parent;
        }
        transplant(nodeToDelete, predecessor);
        predecessor->right = nodeToDelete->right;
        predecessor->right->parent = predecessor;
        predecessor->color = nodeToDelete->color;
    }

    delete nodeToDelete;

    if (originalColor == BLACK) {
        fixDeleting(child);
    }

    // Удаляем пустышку, если она была создана
    if (child != nullptr && child->group.programType == ' ' && child->group.groupID == 0) {
        if (child->parent != nullptr) {
            if (child->parent->left == child) {
                child->parent->left = nullptr;
            } else {
                child->parent->right = nullptr;
            }
        }
        delete child;
    }
}





void RedBlackTree::fixDeleting(Node* fixNode) {
    while (fixNode != root && fixNode->color == BLACK) {
        if (fixNode == fixNode->parent->left) {
            Node* sibling = fixNode->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                fixNode->parent->color = RED;
                rotateLeft(root, fixNode->parent);
                sibling = fixNode->parent->right;
            }
            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK)) {
                sibling->color = RED;
                fixNode = fixNode->parent;
            } else {
                if (sibling->right == nullptr || sibling->right->color == BLACK) {
                    if (sibling->left != nullptr) {
                        sibling->left->color = BLACK;
                    }
                    sibling->color = RED;
                    rotateRight(root, sibling);
                    sibling = fixNode->parent->right;
                }
                sibling->color = fixNode->parent->color;
                fixNode->parent->color = BLACK;
                if (sibling->right != nullptr) {
                    sibling->right->color = BLACK;
                }
                rotateLeft(root, fixNode->parent);
                fixNode = root;
            }
        } else {
            Node* sibling = fixNode->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                fixNode->parent->color = RED;
                rotateRight(root, fixNode->parent);
                sibling = fixNode->parent->left;
            }
            if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
                (sibling->left == nullptr || sibling->left->color == BLACK)) {
                sibling->color = RED;
                fixNode = fixNode->parent;
            } else {
                if (sibling->left == nullptr || sibling->left->color == BLACK) {
                    if (sibling->right != nullptr) {
                        sibling->right->color = BLACK;
                    }
                    sibling->color = RED;
                    rotateLeft(root, sibling);
                    sibling = fixNode->parent->left;
                }
                sibling->color = fixNode->parent->color;
                fixNode->parent->color = BLACK;
                if (sibling->left != nullptr) {
                    sibling->left->color = BLACK;
                }
                rotateRight(root, fixNode->parent);
                fixNode = root;
            }
        }
    }
    fixNode->color = BLACK;
}



Node* RedBlackTree::maximumNode(Node* node) {
    while (node && node->right != nullptr) {
        node = node->right;
    }
    return node;
}






void RedBlackTree::deleteNodeByValue(const GroupNumber& group) {
    Node* nodeToDelete = findNode(root, group);
    if (nodeToDelete == NULL) {
        std::cout << "Узел с заданным значением не найден!" << std::endl;
        return;
    }

    deleteNode(nodeToDelete);  
}


Node* RedBlackTree::BSTInsert(Node* parent, Node* node) {
    if (parent == NULL)
        return node; 

   
    int nodeTypeValue = programTypeToInt(node->group.programType);
    int parentTypeValue = programTypeToInt(parent->group.programType);

    if (nodeTypeValue < parentTypeValue || 
       (nodeTypeValue == parentTypeValue && node->group.groupID < parent->group.groupID)) {

        parent->left = BSTInsert(parent->left, node);
        parent->left->parent = parent;
    } else {

        parent->right = BSTInsert(parent->right, node);
        parent->right->parent = parent;
    }

    return parent;
}


void RedBlackTree::insert(char programType, int groupID, std::optional<int> lineNumber) {
    GroupNumber group(programType, groupID);
    Node* currentNode = root;

    // If lineNumber is not provided, assign the default value based on lastLineNumber
    int resolvedLineNumber = lineNumber.value_or(lastLineNumber + 1);

    while (currentNode != NULL) {
        int cmp = programTypeToInt(group.programType) - programTypeToInt(currentNode->group.programType);

        if (cmp == 0) {
            cmp = groupID - currentNode->group.groupID;
        }

        if (cmp == 0) {
            // Add to duplicate list if the node already exists
            currentNode->DuplicateList.add(resolvedLineNumber);
            return;
        }

        if (cmp < 0) {
            if (currentNode->left == NULL) break;
            currentNode = currentNode->left;
        } else {
            if (currentNode->right == NULL) break;
            currentNode = currentNode->right;
        }
    }

    // Insert a new node if not found
    Node* node = new Node(group);
    lastLineNumber = resolvedLineNumber;
    node->DuplicateList.add(resolvedLineNumber);
    root = BSTInsert(root, node);
    fixInsert(root, node);
}


void RedBlackTree::loadFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(inputFile, line)) {
        lineNumber++;
        std::istringstream iss(line);
        char programType;
        int groupID;

        if (iss >> programType >> groupID) {
            if (!isValidProgramType(programType)) {
                std::cerr << "Ошибка: Недопустимый тип программы в строке: " << lineNumber << std::endl;
                continue;
            }

            if (groupID < 1000 || groupID > 9999) {
                std::cerr << "Ошибка: Номер группы должен быть четырёхзначным числом в строке: " << lineNumber << std::endl;
                continue;
            }

            insert(programType, groupID, lineNumber);
        } else {
            std::cerr << "Ошибка чтения строки: " << lineNumber << std::endl;
        }
    }

    inputFile.close();
}


void RedBlackTree::showTreeHelper(Node* root, int level) {
    if (root == NULL)
        return;


    showTreeHelper(root->right, level + 1);


    for (int i = 0; i < level; ++i) {
        std::cout << "    ";
    }


    std::string color = (root->color == RED) ? "RED" : "BLACK";
    std::cout << root->group.programType << "-";


    std::string groupIDStr = std::to_string(root->group.groupID);
    while (groupIDStr.length() < 4) {
        groupIDStr = "0" + groupIDStr;
    }

    std::cout << groupIDStr << " (" << color << ") ";


    if (!root->DuplicateList.isEmpty()) {
        std::cout << root->DuplicateList.show() << " ";
    }

    std::cout << std::endl;


    showTreeHelper(root->left, level + 1);
}

void RedBlackTree::showTree() {
    std::cout << "Дерево слева-направо по уровням: " << '\n';
    showTreeHelper(root, 0);  
}


void RedBlackTree::inOrderHelper(Node* root) {
    if (root == NULL)
        return;

    inOrderHelper(root->left);

    std::cout << root->group.programType << "-";


    std::string groupIDStr = std::to_string(root->group.groupID);
    while (groupIDStr.length() < 4) {
        groupIDStr = "0" + groupIDStr;
    }

    std::cout << groupIDStr << " ";

 
    if (!root->DuplicateList.isEmpty()) {
        std::cout << root->DuplicateList.show() << "\n";
    }

    inOrderHelper(root->right);
}


void RedBlackTree::inOrder() {
     std::cout << "Обход слева-направо КЧ дерева: " << '\n';
    inOrderHelper(root);
}


void RedBlackTree::deleteTree(Node* node) {
    if (node == NULL)
        return;


    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void RedBlackTree::inOrderToFileHelper(Node* root, std::ofstream& outputFile) {
    if (root == NULL)
        return;

    inOrderToFileHelper(root->left, outputFile);

    outputFile << root->group.programType << "-";

    std::string groupIDStr = std::to_string(root->group.groupID);
    while (groupIDStr.length() < 4) {
        groupIDStr = "0" + groupIDStr;
    }

    outputFile << groupIDStr;

    if (!root->DuplicateList.isEmpty()) {
        outputFile << " " << root->DuplicateList.show();
    }
    outputFile << "\n";

    inOrderToFileHelper(root->right, outputFile);
}

void RedBlackTree::inOrderToFile(const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile) {
        std::cerr << "Ошибка открытия файла для записи!" << std::endl;
        return;
    }

    inOrderToFileHelper(root, outputFile);
    outputFile.close();
    std::cout << "Обход дерева записан в файл: " << filename << std::endl;
}
