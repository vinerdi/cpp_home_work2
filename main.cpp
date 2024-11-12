template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Клонування списку
    Node<T>* clone() const {
        if (head == nullptr) return nullptr;
        Node<T>* newHead = new Node<T>(head->data);
        Node<T>* current = head->next;
        Node<T>* newCurrent = newHead;
        while (current != nullptr) {
            newCurrent->next = new Node<T>(current->data);
            newCurrent->next->prev = newCurrent;
            newCurrent = newCurrent->next;
            current = current->next;
        }
        return newHead;
    }

    // Перевантаження оператора +
    DoublyLinkedList operator+(const DoublyLinkedList& other) const {
        DoublyLinkedList result;
        Node<T>* current = head;
        while (current != nullptr) {
            result.append(current->data);
            current = current->next;
        }
        current = other.head;
        while (current != nullptr) {
            result.append(current->data);
            current = current->next;
        }
        return result;
    }

    // Перевантаження оператора *
    DoublyLinkedList operator*(const DoublyLinkedList& other) const {
        DoublyLinkedList result;
        Node<T>* current = head;
        while (current != nullptr) {
            if (other.contains(current->data)) {
                result.append(current->data);
            }
            current = current->next;
        }
        return result;
    }

    // Допоміжні функції
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
    }

    bool contains(T value) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

int main() {
	DoublyLinkedList<int> list1;
	list1.append(1);
	list1.append(2);
	list1.append(3);

	DoublyLinkedList<int> list2;
	list2.append(2);
	list2.append(3);
	list2.append(4);

	DoublyLinkedList<int> list3 = list1 + list2;
	DoublyLinkedList<int> list4 = list1 * list2;

	return 0;
}