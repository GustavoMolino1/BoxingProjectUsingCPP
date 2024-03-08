#pragma once
#include <iostream>
using namespace std;

template<class L>
struct node {
    node<L>* next;
    L data;
};
// declaring linked list class
template<class L>
class NodeLinked
{
public:
    node<L>* head;
    node<L>* last;
    NodeLinked<L>() {
        head = NULL;
        last = NULL;
    }
    void add(L data) {
        if (!head) {
            // when there is no element in the list
            head = new node<L>;
            head->data = data;
            head->next = NULL;
            last = head;
        }
        else {
            // when the list is not empty
            if (last == head) {
                // when the list has one element
                last = new node<L>;
                last->data = data;
                last->next = NULL;
                head->next = last;
            }
            else {
                // when the list has more than one element
                node<L>* insdata = new node<L>;
                insdata->data = data;
                insdata->next = NULL;
                last->next = insdata;
                last = insdata;
            }
        }
    }
    L get(int index) {

        if (index < 0 || index >= getSize()) {
            cerr << "Invalid index!" << endl;
            return nullptr;
        }
        if (index == 0) {
            // returning the head element
            return this->head->data;
        }
        else {
            // Get the index'th element
            node<L>* curr = this->head;
            for (int i = 0; i < index; ++i) {
                 curr = curr->next;
            }
              return curr->data;
          
        }
    }
    L operator[](int index) {
        return get(index);
    }
    void print() const {
        node<L>* current = head;
        while (current != nullptr) {
            cout << *current->data << "\n" << " ";
            current = current->next;
        }
        cout << endl;
    }
    void remove(const L& value) {
        if (head == nullptr) {
            return;
        }

        if (head->data == value) {
            node<L>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        node<L>* current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                node<L>* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }
    int getSize() const {
        int count = 0;
        node<L>* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
};
