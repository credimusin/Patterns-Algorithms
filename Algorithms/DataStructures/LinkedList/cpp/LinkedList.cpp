#include <iostream>

/**
 * LinkedList Data Structure
 * 
 * Concept:
 * A Singly Linked List is a linear data structure where elements are not stored
 * at contiguous memory locations. Elements (nodes) are linked using pointers.
 * Each node contains data and a pointer to the next node.
 * 
 * Complexity:
 * - Access: O(n)
 * - Search: O(n)
 * - Insertion: O(1) at the beginning, O(n) for specific positions.
 * - Deletion: O(1) at the beginning, O(n) for specific positions.
 */

struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    /**
     * @brief Inserts a value at the beginning of the list.
     * 
     * @param value The value to be inserted.
     */
    void insertAtBeginning(int value) {
        std::cout << "\n>>> Inserting " << value << " at the beginning.\n";
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;

        printList();
        std::cout << "    [✓] New node (" << value << ") points to the previous head.\n";
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

    /**
     * @brief Deletes the first node matching the value.
     * 
     * @param value The value to be deleted.
     */
    void deleteValue(int value) {
        std::cout << "\n>>> Deleting value: " << value << "\n";
        if (!head) {
            std::cout << "    [!] List is empty. Nothing to delete.\n";
            return;
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            std::cout << "    [✓] Found " << value << " at the head. Head updated.\n";
        } else {
            Node* current = head;
            while (current->next && current->next->data != value) {
                current = current->next;
                std::cout << "    [ ] Checking node: " << current->data << "...\n";
            }

            if (current->next) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                std::cout << "    [✓] Found " << value << ". Skipping and deleting node.\n";
            } else {
                std::cout << "    [!] Value " << value << " not found in the list.\n";
            }
        }

        printList();
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

    /**
     * @brief Traverses and prints the list.
     */
    void printList() {
        std::cout << "    Current List: ";
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr\n";
    }

private:
    Node* head;
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "       LINKED LIST INTERACTIVE\n";
    std::cout << "==========================================\n";

    LinkedList list;
    
    list.insertAtBeginning(10);
    list.insertAtBeginning(20);
    list.insertAtBeginning(30);

    list.deleteValue(20);
    list.deleteValue(50); // Not in list

    std::cout << "\nStructure visualization completed. Thank you for learning!\n";
    return 0;
}
