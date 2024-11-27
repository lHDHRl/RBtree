#include "linkedList.h"

linkedList::linkedList() : head{ NULL }, last{ NULL }, size{ 0 } {}

linkedList::~linkedList() {
    if (!head) return;
    Node* curr = head->next;
    while (curr != head) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete head;
    head = last = NULL;
}

void linkedList::add(int x) {
    Node* temp = new Node{ x, NULL };
    if (!head) {
        head = last = temp;
        temp->next = head;
    }
    else if (x >= head->value) {
        temp->next = head;
        head = temp;
        last->next = head;
    }
    else {
        Node* curr = head->next;
        Node* prev = head;
        while (curr != head && curr->value > x) {
            prev = curr;
            curr = curr->next;
        }
        temp->next = curr;
        prev->next = temp;
        if (curr == head) {
            last = temp;
        }
    }
    size++;
}

void linkedList::show() {
    if (!head) {
        std::cout << "Список пуст.\n";
        return;
    }
    Node* temp = head;
    do {
        std::cout << temp->value << " ";
        temp = temp->next;
    } while (temp != head);
    std::cout << "\n";
}

void linkedList::removeAll(int x) {
    if (!head) return;

    while (head && head->value == x) {
        if (head == last) {
            delete head;
            head = last = NULL;
            size--;
            return;
        }
        Node* temp = head;
        head = head->next;
        last->next = head;
        delete temp;
        size--;
    }

    if (!head) return;

    Node* curr = head;
    do {
        if (curr->next->value == x) {
            Node* temp = curr->next;
            curr->next = temp->next;
            if (temp == last) last = curr;
            delete temp;
            size--;
            if (curr->next == head) break;
        }
        else {
            curr = curr->next;
        }
    } while (curr != last);
}

linkedList* linkedList::inAddition() {
    linkedList* list3 = new linkedList;
    if (size % 2 == 0) {
        Node* curr = head->next;
        Node* prev = head;
        do {
            list3->add(prev->value + curr->value);
            prev = curr->next;
            curr = prev->next;
        } while (curr != head && curr != head->next);
    }
    else {
        Node* curr = head->next;
        Node* prev = head;
        do {
            list3->add(prev->value + curr->value);
            prev = curr->next;
            curr = prev->next;
        } while (prev->next != head);
        if (prev->next == head) {
            list3->add(prev->value);
        }
    }
    return list3;
}

int linkedList::search(int x) {
    if (!head) return -1;
    Node* curr = head;
    int index = 0;
    do {
        if (curr->value == x) return index;
        curr = curr->next;
        ++index;
    } while (curr != head);
    return -1;
}

void linkedList::removeAfter(int value) {
    if (!head) return;

    Node* curr = head;
    do {
        if (curr->value == value) {
            Node* temp = curr->next;

            if (temp == head) {
                head = head->next;
            }

            curr->next = temp->next;

            if (temp == last) {
                last = curr;
            }

            delete temp;
            size--;
            break;
        }
        curr = curr->next;
    } while (curr != head);
}

bool linkedList::existsinList(int value) {
    if (!head) return false;
    Node* temp = head;
    do {
        if (temp->value == value) return true;
        temp = temp->next;
    } while (temp != head);
    return false;
}

void linkedList::merge(linkedList& secondList) {
    if (!head || !secondList.head) return;

    Node* curr = secondList.head;
    do {
        add(curr->value);
        curr = curr->next;
    } while (curr != secondList.head);

    secondList.last->next = NULL;
    Node* temp = secondList.head;
    while (temp) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    secondList.head = secondList.last = NULL;
    secondList.size = 0;
}
