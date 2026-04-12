#include <iostream>
#include <stack>
#include <vector>

/**
 * Stack Data Structure
 * 
 * Concept:
 * A Stack is a linear data structure that follows the Last-In-First-Out (LIFO) principle.
 * Elements are added (push) and removed (pop) from the top only.
 * 
 * Complexity:
 * - Access: O(n)
 * - Search: O(n)
 * - Insertion: O(1) - (Push to the top)
 * - Deletion: O(1) - (Pop from the top)
 */

class InteractiveStack {
public:
    /**
     * @brief Pushes a value onto the stack.
     * 
     * @param value The value to push.
     */
    void push(int value) {
        std::cout << "\n>>> Push: Adding " << value << " to the top.\n";
        s.push(value);
        vec_s.push_back(value); // Mirror to a vector for visualization

        printStack();
        std::cout << "    [✓] " << value << " is now the top-most element.\n";
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

    /**
     * @brief Pops the top-most element from the stack.
     */
    void pop() {
        if (s.empty()) {
            std::cout << "\n[!] Stack is empty. Nothing to pop.\n";
            return;
        }

        int topValue = s.top();
        std::cout << "\n>>> Pop: Removing " << topValue << " from the top.\n";
        s.pop();
        vec_s.pop_back(); // Remove from the mirrored vector

        printStack();
        std::cout << "    [✓] " << topValue << " has been popped. The previous element is now at the top.\n";
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

private:
    std::stack<int> s;
    std::vector<int> vec_s; // Mirrored for easy printing

    /**
     * @brief Prints the current state of the stack.
     */
    void printStack() {
        std::cout << "    Stack (Top to Bottom):\n";
        if (vec_s.empty()) {
            std::cout << "    [ Empty ]\n";
            return;
        }

        for (int i = vec_s.size() - 1; i >= 0; i--) {
            std::cout << "    | " << vec_s[i] << " |" << (i == vec_s.size() - 1 ? " <-- TOP" : "") << "\n";
        }
        std::cout << "    +---+\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "          STACK INTERACTIVE\n";
    std::cout << "==========================================\n";

    InteractiveStack myStack;

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    myStack.pop();
    myStack.pop();

    myStack.push(40);
    myStack.pop();

    std::cout << "\nStructure visualization completed. Thank you for learning!\n";
    return 0;
}
