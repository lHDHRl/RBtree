#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

struct Node {
    int value;
    Node* next;
};

class linkedList {
    Node* head;
    Node* last;
    int size;

public:
    linkedList();
    ~linkedList();
    
    void add(int value);
    void show();
    void removeAll(int value);
    int search(int x);
    void removeAfter(int value);
    void merge(linkedList& secondList);
    bool existsinList(int value);
    linkedList* inAddition();
};

#endif // LINKEDLIST_H
