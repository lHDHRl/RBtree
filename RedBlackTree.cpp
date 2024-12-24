#include "RedBlackTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>



RedBlackTree::RedBlackTree() : root(NULL) {}

RedBlackTree::~RedBlackTree() {
    deleteTree(root);  
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
    if (!nodeToDelete) return;

    std::cout << "Начало удаления узла: " << nodeToDelete->group.groupID << std::endl;

    Node* replacement = nullptr;
    Node* fixNode = nullptr;
    Color originalColor = nodeToDelete->color;

    if (nodeToDelete->left == nullptr && nodeToDelete->right == nullptr) {
        // Узел без детей
        std::cout << "Удаляется узел без детей." << std::endl;
        if (nodeToDelete == root) {
            root = nullptr;
        } else {
            if (nodeToDelete == nodeToDelete->parent->left) {
                nodeToDelete->parent->left = nullptr;
                std::cout << "Удаляем левый дочерний узел." << std::endl;
            } else {
                nodeToDelete->parent->right = nullptr;
                std::cout << "Удаляем правый дочерний узел." << std::endl;
            }
        }
        fixNode = nodeToDelete->parent;
        replacement = nullptr;
    } else if (nodeToDelete->left == nullptr || nodeToDelete->right == nullptr) {
        // Узел с одним ребенком
        std::cout << "Удаляется узел с одним ребенком." << std::endl;
        replacement = (nodeToDelete->left != nullptr) ? nodeToDelete->left : nodeToDelete->right;

        if (nodeToDelete == root) {
            root = replacement;
            std::cout << "Удаляемый узел был корнем, новый корень: " << root->group.groupID << std::endl;
        } else {
            if (nodeToDelete == nodeToDelete->parent->left) {
                nodeToDelete->parent->left = replacement;
                std::cout << "Заменяем левый дочерний узел." << std::endl;
            } else {
                nodeToDelete->parent->right = replacement;
                std::cout << "Заменяем правый дочерний узел." << std::endl;
            }
        }

        if (replacement) {
            replacement->parent = nodeToDelete->parent;
            std::cout << "Устанавливаем родителя для replacement: " << replacement->group.groupID << std::endl;
        }
        fixNode = replacement ? replacement : nodeToDelete->parent;
    } else {
        // Узел с двумя детьми
        std::cout << "Удаляется узел с двумя детьми." << std::endl;
        Node* predecessor = maximumNode(nodeToDelete->left);
        std::cout << "Предшественник найден: " << predecessor->group.groupID << std::endl;



        std::cout << "Данные предшественника перенесены в узел: " << nodeToDelete->group.groupID << std::endl;
        // Вместо удаления переносим данные предшественника
        nodeToDelete->group = predecessor->group;
 

        // Теперь удаляем предшественника
        if (predecessor->parent->right == predecessor) {
            predecessor->parent->right = predecessor->left;
            if (predecessor->left) {
                predecessor->left->parent = predecessor->parent;
            }
        } else {
            predecessor->parent->left = predecessor->left;
            if (predecessor->left) {
                predecessor->left->parent = predecessor->parent;
            }
        }

        fixNode = predecessor;
        originalColor = predecessor->color;

        delete predecessor;
        std::cout << "Предшественник удален." << std::endl;
    }

    // Если удаляемый узел был черным, выполняем балансировку
    if (originalColor == BLACK) {
        std::cout << "Запускаем fixDeleting." << std::endl;
        std::cout << fixNode->group.groupID << std::endl;
        fixDeleting(fixNode);
    }

    // Убедиться, что корень черный
    if (root != nullptr) {
        root->color = BLACK;
        std::cout << "Корень установлен черным: " << root->group.groupID << std::endl;
    }
}





void RedBlackTree::fixDeleting(Node* fixNode) {
    while (fixNode != root && (!fixNode || fixNode->color == BLACK)) {
        if (fixNode == fixNode->parent->left) {
            std::cout << fixNode->group.groupID << " - Левый дочерний узел родителя." << std::endl;
            Node* brother = fixNode->parent->right;
            std::cout << "Брат найден: " << brother->group.groupID << std::endl;

            if (brother && brother->color == RED) {
                std::cout << "Случай 1: Брат красный." << std::endl;
                brother->color = BLACK;
                fixNode->parent->color = RED;
                rotateLeft(root, fixNode->parent);
                brother = fixNode->parent->right;
            }

            if ((!brother || (!brother->left || brother->left->color == BLACK)) &&
                (!brother || (!brother->right || brother->right->color == BLACK))) {
                std::cout << "Случай 2: Брат черный, оба ребенка черные." << std::endl;
                if (brother) brother->color = RED;
                fixNode = fixNode->parent;
            } else {
                if (!brother || (!brother->right || brother->right->color == BLACK)) {
                    std::cout << "Случай 3: Брат черный, левый ребенок красный, правый черный." << std::endl;
                    if (brother && brother->left) brother->left->color = BLACK;
                    if (brother) brother->color = RED;
                    rotateRight(root, brother);
                    brother = fixNode->parent->right;
                }

                std::cout << "Случай 4: Брат черный, правый ребенок красный." << std::endl;
                if (brother) brother->color = fixNode->parent->color;
                fixNode->parent->color = BLACK;
                if (brother && brother->right) brother->right->color = BLACK;
                rotateLeft(root, fixNode->parent);
                fixNode = root;
            }
        } else {
            Node* brother = fixNode->parent->left;
            std::cout << "Брат найден: " << brother->group.groupID << std::endl;

            if (brother && brother->color == RED) {
                std::cout << "Случай 1: Брат красный." << std::endl;
                brother->color = BLACK;
                fixNode->parent->color = RED;
                rotateRight(root, fixNode->parent);
                brother = fixNode->parent->left;
            }

            if ((!brother || (!brother->left || brother->left->color == BLACK)) &&
                (!brother || (!brother->right || brother->right->color == BLACK))) {
                std::cout << "Случай 2: Брат черный, оба ребенка черные." << std::endl;
                if (brother) brother->color = RED;
                fixNode = fixNode->parent;
            } else {
                if (!brother || (!brother->left || brother->left->color == BLACK)) {
                    std::cout << "Случай 3: Брат черный, правый ребенок красный, левый черный." << std::endl;
                    if (brother && brother->right) brother->right->color = BLACK;
                    if (brother) brother->color = RED;
                    rotateLeft(root, brother);
                    brother = fixNode->parent->left;
                }

                std::cout << "Случай 4: Брат черный, левый ребенок красный." << std::endl;
                if (brother) brother->color = fixNode->parent->color;
                fixNode->parent->color = BLACK;
                if (brother && brother->left) brother->left->color = BLACK;
                rotateRight(root, fixNode->parent);
                fixNode = root;
            }
        }
    }

    if (fixNode) fixNode->color = BLACK;
    std::cout << "Узел сбалансирован: " << fixNode->group.groupID << std::endl;
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



void RedBlackTree::insert(char programType, int groupID, int lineNumber) {
    GroupNumber group(programType, groupID);
    Node* currentNode = root;


    while (currentNode != NULL) {
        int cmp = programTypeToInt(group.programType) - programTypeToInt(currentNode->group.programType);

        if (cmp == 0) {
            cmp = groupID - currentNode->group.groupID;
        }

        if (cmp == 0) {
            currentNode->DuplicateList.add(lineNumber);
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

    Node* node = new Node(group);
    node->DuplicateList.add(lineNumber);
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
