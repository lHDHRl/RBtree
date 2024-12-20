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

void RedBlackTree::fixDeleting(Node* p) {
    while (p != root && (p == NULL || p->color == BLACK)) {
        if (p == p->parent->left) {
            Node* brother = p->parent->right;

            if (brother != NULL && brother->color == RED) {
                brother->color = BLACK;
                p->parent->color = RED;
                rotateLeft(root, p->parent);
                brother = p->parent->right;
            }

            if ((brother->left == NULL || brother->left->color == BLACK) &&
                (brother->right == NULL || brother->right->color == BLACK)) {
                if (brother != NULL) brother->color = RED;
                p = p->parent;
            } else {
                if (brother->right == NULL || brother->right->color == BLACK) {
                    if (brother->left != NULL) brother->left->color = BLACK;
                    brother->color = RED;
                    rotateRight(root, brother);
                    brother = p->parent->right;
                }
                brother->color = p->parent->color;
                p->parent->color = BLACK;
                if (brother->right != NULL) brother->right->color = BLACK;
                rotateLeft(root, p->parent);
                p = root;
            }
        } else {
            Node* brother = p->parent->left;

            if (brother != NULL && brother->color == RED) {
                brother->color = BLACK;
                p->parent->color = RED;
                rotateRight(root, p->parent);
                brother = p->parent->left;
            }

            if ((brother->left == NULL || brother->left->color == BLACK) &&
                (brother->right == NULL || brother->right->color == BLACK)) {
                if (brother != NULL) brother->color = RED;
                p = p->parent;
            } else {
                if (brother->left == NULL || brother->left->color == BLACK) {
                    if (brother->right != NULL) brother->right->color = BLACK;
                    brother->color = RED;
                    rotateLeft(root, brother);
                    brother = p->parent->left;
                }
                brother->color = p->parent->color;
                p->parent->color = BLACK;
                if (brother->left != NULL) brother->left->color = BLACK;
                rotateRight(root, p->parent);
                p = root;
            }
        }
    }
    if (p != NULL) p->color = BLACK;
}

Node* RedBlackTree::maximumNode(Node* node) {
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

void RedBlackTree::deleteNode(Node* nodeToDelete) {
    Node* target = nodeToDelete;    
    Node* replacement = NULL;       
    Node* fixNode = NULL;           
    bool originalColor = target->color;

    if (nodeToDelete->left == NULL && nodeToDelete->right == NULL) {
        // Случай: узел — лист
        if (nodeToDelete == root) {
            root = NULL; 
        } else {
            if (nodeToDelete == nodeToDelete->parent->left) {
                nodeToDelete->parent->left = NULL;
            } else {
                nodeToDelete->parent->right = NULL;
            }
        }
        fixNode = nodeToDelete->parent; 
    } else if (nodeToDelete->left == NULL || nodeToDelete->right == NULL) {
        // Случай: один потомок
        replacement = (nodeToDelete->left != NULL) ? nodeToDelete->left : nodeToDelete->right;

        
        if (nodeToDelete == root) {
            root = replacement;
        } else if (nodeToDelete == nodeToDelete->parent->left) {
            nodeToDelete->parent->left = replacement;
        } else {
            nodeToDelete->parent->right = replacement;
        }

        if (replacement != NULL) {
            replacement->parent = nodeToDelete->parent;
        }
        fixNode = replacement;
    } else {
        // Случай: два потомка
        Node* maxLeft = maximumNode(nodeToDelete->left); 
        originalColor = maxLeft->color;                 
        replacement = maxLeft->left;                   

        if (maxLeft->parent == nodeToDelete) {
            if (replacement != NULL) {
                replacement->parent = maxLeft;
            }
        } else {
            if (replacement != NULL) {
                replacement->parent = maxLeft->parent;
            }
            maxLeft->parent->right = replacement;
            maxLeft->left = nodeToDelete->left;
            maxLeft->left->parent = maxLeft;
        }

        if (nodeToDelete == root) {
            root = maxLeft;
        } else if (nodeToDelete == nodeToDelete->parent->left) {
            nodeToDelete->parent->left = maxLeft;
        } else {
            nodeToDelete->parent->right = maxLeft;
        }

        maxLeft->parent = nodeToDelete->parent;
        maxLeft->right = nodeToDelete->right;
        maxLeft->right->parent = maxLeft;
        maxLeft->color = nodeToDelete->color;

        fixNode = replacement;
    }

    delete nodeToDelete;

    // Если удаляемый или замещающий узел был черным, восстанавливаем баланс
    if (originalColor == BLACK && fixNode != NULL) {
        fixDeleting(fixNode);
    }
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
