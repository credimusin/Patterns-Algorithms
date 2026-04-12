#include <iostream>
#include <queue>
#include <vector>

/**
 * Queue Data Structure
 * 
 * Concept:
 * A Queue is a linear data structure that follows the First-In-First-Out (FIFO) principle.
 * Elements are added at the back (enqueue) and removed from the front (dequeue).
 * 
 * Complexity:
 * - Access: O(n)
 * - Search: O(n)
 * - Insertion: O(1) - (Push to the back)
 * - Deletion: O(1) - (Pop from the front)
 */

class InteractiveQueue {
public:
    /**
     * @brief Adds an element to the back of the queue.
     * 
     * @param value The value to add.
     */
    void enqueue(int value) {
        std::cout << "\n>>> Enqueue: Adding " << value << " to the back.\n";
        q.push(value);
        vec_q.push_back(value); // Mirror to a vector for visualization

        printQueue();
        std::cout << "    [✓] " << value << " is now the newest element in line.\n";
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

    /**
     * @brief Removes the element from the front of the queue.
     */
    void dequeue() {
        if (q.empty()) {
            std::cout << "\n[!] Queue is empty. Nothing to dequeue.\n";
            return;
        }

        int frontValue = q.front();
        std::cout << "\n>>> Dequeue: Removing " << frontValue << " from the front.\n";
        q.pop();
        vec_q.erase(vec_q.begin()); // Remove from the mirrored vector

        printQueue();
        std::cout << "    [✓] " << frontValue << " has been removed. The next element is now at the front.\n";
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

private:
    std::queue<int> q;
    std::vector<int> vec_q; // Mirrored for easy printing

    /**
     * @brief Prints the current state of the queue.
     */
    void printQueue() {
        std::cout << "    [ Front ] ";
        for (size_t i = 0; i < vec_q.size(); i++) {
            std::cout << vec_q[i] << (i == vec_q.size() - 1 ? "" : " | ");
        }
        std::cout << " [ Back ]\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "          QUEUE INTERACTIVE\n";
    std::cout << "==========================================\n";

    InteractiveQueue myQueue;

    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);

    myQueue.dequeue();
    myQueue.dequeue();

    myQueue.enqueue(40);
    myQueue.dequeue();

    std::cout << "\nStructure visualization completed. Thank you for learning!\n";
    return 0;
}
