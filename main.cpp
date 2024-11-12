#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    ~Queue() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void enqueue(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail != nullptr) {
            tail->next = newNode;
            newNode->prev = tail;
        }
        tail = newNode;
        if (head == nullptr) {
            head = newNode;
        }
        size++;
    }

    T dequeue() {
        if (head == nullptr) {
            throw std::out_of_range("Queue is empty");
        }
        Node<T>* temp = head;
        T value = head->data;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
        return value;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }
};

int main() {

    return 0;
}