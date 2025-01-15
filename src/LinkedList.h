#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

struct lNode {
    int value;
    lNode* next;
};

class linkedList {
    lNode* head;
    lNode* last;
    int size;

public:
    linkedList();
    ~linkedList();
    int removeFirst();
    bool isEmpty() const;
    void add(int value);
    std::string show();
    void removeAll(int value);
    int search(int x);
    void removeAfter(int value);
    void merge(linkedList& secondList);
    bool existsinList(int value);
    linkedList* inAddition();
};

#endif // LINKEDLIST_H
