#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

// Node class for linked list
class Node {
public:
    int data;
    Node* next;
    Node(int val); // Constructor
};

// Sorted Linked List Class
class SortedLinkedList {
private:
    Node* head; // Pointer to the head of the list

public:
    SortedLinkedList();  // Constructor

    void insert(int value);  // Insert a value while keeping the list sorted
    void remove(int index);// Delete node at given index

    // Overloaded operators
    friend ostream& operator<<(ostream& os, const SortedLinkedList& list);
    int operator[](int index);

    ~SortedLinkedList(); // Destructor to free memory
};

// --------- IMPLEMENTATION
Node :: Node(int val) {
    data = val;
    next = nullptr;
}
SortedLinkedList::SortedLinkedList() {
    head = nullptr;
}
void SortedLinkedList::insert(int val) {
    Node* newNode = new Node(val);
    newNode->data = val;
    if (!head  || (head->data >= val)) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* previous = head;
    while (previous->next != nullptr) {
        if (previous->next->data >= val) {
            break;
        }
        previous = previous->next;
    }
    newNode->next = previous->next;
    previous->next = newNode;
}

void SortedLinkedList::remove(int index) {
    if (!head || index< 0 ) return;
    Node* delptr = head;
    Node* previous = nullptr;
    if (index == 0) {
        head = head->next;
        delete delptr;
        return;
    }
    for (int i = 0; i < index && delptr != nullptr; i++) {
        previous = delptr;
        delptr = delptr->next;
    }
    if (delptr == nullptr) return;
    previous->next = delptr->next;
    delete delptr;
}
ostream& operator<<(ostream& os, const SortedLinkedList& list) {
    os << "[";
    Node* temp = list.head;
    while (temp != nullptr) {
        os << temp->data ;
        if (temp->next) os<<", ";
        temp = temp->next;
    }
    os<<"]";
    return os;
}

int SortedLinkedList::operator[](int index) {
    try {
        Node* current = head;
        int counter = 0;

        if (current == nullptr) {
            throw out_of_range("Error: The list is empty.");
        } else {
            while (current != nullptr) {
                if (counter == index) {
                    break;
                }
                counter++;
                current = current->next;
            }

            if (counter == index) {
                return current->data;
            } else {
                throw out_of_range("Out of range");
            }
        }
    } catch (const std::exception& e) {
        cout << e.what()<<" ";
        return -1;
    }
}




SortedLinkedList::~SortedLinkedList() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
}


int main() {
    SortedLinkedList L;
    L.insert(5); // L = [5]
    L.insert(8); // L = [5, 8]


    L.insert(7); // L = [5, 7, 8]
    L.insert(6); // L = [5, 6, 7, 8]
    L.insert(6); // L = [5, 6, 6, 7, 8]
    cout << L<<endl; // Output: [5, 6, 6, 7, 8]


    cout << L[2]<<endl; // Output: 6
    cout << L[10]<<endl; // Throws out_of_range exception


    //L = [5, 6, 6, 7, 8];


    L.remove(0); // L = [6, 6, 7, 8]
    cout << L<<endl; // Output: [6, 6, 7, 8]
    L.remove(100); // No change (out of bounds)
    cout << L <<endl; // Output: [6, 6, 7, 8]
    L.remove(2); // L = [6, 6, 8]
    cout << L<<endl; // Output: [6, 6, 8]
    L.remove(2); // L = [6, 6]
    cout << L<<endl; // Output: [6, 6]

    return 0;
}
