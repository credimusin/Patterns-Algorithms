#include <iostream>

/**
 * BinaryTree (specifically Binary Search Tree) Data Structure
 * 
 * Concept:
 * A Binary Tree is a hierarchical data structure where each node has at most two children.
 * In a Binary Search Tree (BST), for any node, its left children have values less than the node,
 * and its right children have values greater than the node.
 * 
 * Complexity (BST):
 * - Access: O(log n) average, O(n) worst case (unbalanced).
 * - Search: O(log n) average, O(n) worst case.
 * - Insertion: O(log n) average, O(n) worst case.
 * - Deletion: O(log n) average, O(n) worst case.
 */

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    /**
     * @brief Public method to insert a value into the BST.
     * 
     * @param value The value to insert.
     */
    void insert(int value) {
        std::cout << "\n>>> Inserting " << value << " into the tree.\n";
        root = insertRecursive(root, value);
        
        std::cout << "    Current Tree (In-order traversal): ";
        inorderTraversal(root);
        std::cout << "\n    (Press Enter to continue...)";
        std::cin.get();
    }

    /**
     * @brief Public method to search for a value in the BST.
     * 
     * @param value The value to search for.
     * @return true if found, false otherwise.
     */
    bool search(int value) {
        std::cout << "\n>>> Searching for " << value << "...\n";
        bool found = searchRecursive(root, value);
        if (found) {
            std::cout << "    [✓] Found " << value << " in the tree!\n";
        } else {
            std::cout << "    [!] " << value << " not found in the tree.\n";
        }
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
        return found;
    }

private:
    Node* root;

    /**
     * @brief Internal recursive function to insert a value.
     */
    Node* insertRecursive(Node* node, int value) {
        if (!node) {
            std::cout << "    [+] Found a spot! Creating a new node for " << value << ".\n";
            return new Node(value);
        }

        if (value < node->data) {
            std::cout << "    [<] " << value << " < " << node->data << ". Going left.\n";
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            std::cout << "    [>] " << value << " > " << node->data << ". Going right.\n";
            node->right = insertRecursive(node->right, value);
        }
        return node;
    }

    /**
     * @brief Internal recursive function to search for a value.
     */
    bool searchRecursive(Node* node, int value) {
        if (!node) {
            std::cout << "    [!] Hit a nullptr. Value not present.\n";
            return false;
        }

        if (node->data == value) {
            return true;
        }

        if (value < node->data) {
            std::cout << "    [<] " << value << " < " << node->data << ". Searching in the left subtree.\n";
            return searchRecursive(node->left, value);
        } else {
            std::cout << "    [>] " << value << " > " << node->data << ". Searching in the right subtree.\n";
            return searchRecursive(node->right, value);
        }
    }

    /**
     * @brief Internal function to print the tree in-order (sorted).
     */
    void inorderTraversal(Node* node) {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "    BINARY SEARCH TREE INTERACTIVE\n";
    std::cout << "==========================================\n";

    BinarySearchTree bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);

    bst.search(40);
    bst.search(60);

    std::cout << "\nStructure visualization completed. Thank you for learning!\n";
    return 0;
}
