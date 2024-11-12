#include <stdexcept> // Include this for std::out_of_range

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class Array {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
    int capacity;
    int grow;

public:
    Array(int initialSize = 0, int growBy = 1) : head(nullptr), tail(nullptr), size(0), capacity(initialSize), grow(growBy) {
        for (int i = 0; i < initialSize; ++i) {
            append(T());
        }
    }

    ~Array() {
        removeAll();
    }

    int getSize() const {
        return size;
    }

    void setSize(int newSize, int growBy = 1) {
        grow = growBy;
        if (newSize > capacity) {
            for (int i = capacity; i < newSize; ++i) {
                append(T());
            }
        } else if (newSize < size) {
            for (int i = size; i > newSize; --i) {
                removeAt(i - 1);
            }
        }
        capacity = newSize;
    }

    int getUpperBound() const {
        return size - 1;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void freeExtra() {
        setSize(size);
    }

    void removeAll() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }

    T getAt(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void setAt(int index, T value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->data = value;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    void add(T value) {
        if (size >= capacity) {
            setSize(capacity + grow);
        }
        append(value);
    }

    void append(const Array& other) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            add(current->data);
            current = current->next;
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            removeAll();
            Node<T>* current = other.head;
            while (current != nullptr) {
                add(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    T* getData() const {
        T* data = new T[size];
        Node<T>* current = head;
        for (int i = 0; i < size; ++i) {
            data[i] = current->data;
            current = current->next;
        }
        return data;
    }

    void insertAt(int index, T value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (index == size) {
            add(value);
            return;
        }
        Node<T>* newNode = new Node<T>(value);
        if (index == 0) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }
        size++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        delete current;
        size--;
    }

private:
    void append(T value) {
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
};

int main() {
    Array<int> arr(5);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;
    arr.add(6);
    arr.add(7);
    arr.add(8);
    arr.add(9);
    arr.add(10);
    arr.insertAt(5, 100);
    arr.removeAt(5);
    arr.setSize(10);
    arr.freeExtra();
    arr.removeAll();
    return 0;
};
