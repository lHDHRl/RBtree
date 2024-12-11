#include "linkedList.h"

linkedList::linkedList() : head{ NULL }, last{ NULL }, size{ 0 } {}

linkedList::~linkedList() {
    if (!head) return;
    lNode* curr = head->next;
    while (curr != head) {
        lNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete head;
    head = last = NULL;
}


bool linkedList::isEmpty() const {
    return head == NULL;
}

void linkedList::add(int x) {
    lNode* temp = new lNode{ x, NULL };
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
        lNode* curr = head->next;
        lNode* prev = head;
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

std::string linkedList::show() {
    if (!head) {
        return "Список пуст.";
    }

    std::string result = "[";
    lNode* temp = head;
    do {
        result += std::to_string(temp->value);
        temp = temp->next;
        if (temp != head) {
            result += ", "; // Добавляем запятую с пробелом между элементами
        }
    } while (temp != head);
    result += "]";

    return result;
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
        lNode* temp = head;
        head = head->next;
        last->next = head;
        delete temp;
        size--;
    }

    if (!head) return;

    lNode* curr = head;
    do {
        if (curr->next->value == x) {
            lNode* temp = curr->next;
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
        lNode* curr = head->next;
        lNode* prev = head;
        do {
            list3->add(prev->value + curr->value);
            prev = curr->next;
            curr = prev->next;
        } while (curr != head && curr != head->next);
    }
    else {
        lNode* curr = head->next;
        lNode* prev = head;
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
    lNode* curr = head;
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

    lNode* curr = head;
    do {
        if (curr->value == value) {
            lNode* temp = curr->next;

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
    lNode* temp = head;
    do {
        if (temp->value == value) return true;
        temp = temp->next;
    } while (temp != head);
    return false;
}

void linkedList::merge(linkedList& secondList) {
    if (!head || !secondList.head) return;

    lNode* curr = secondList.head;
    do {
        add(curr->value);
        curr = curr->next;
    } while (curr != secondList.head);

    secondList.last->next = NULL;
    lNode* temp = secondList.head;
    while (temp) {
        lNode* next = temp->next;
        delete temp;
        temp = next;
    }
    secondList.head = secondList.last = NULL;
    secondList.size = 0;
}
