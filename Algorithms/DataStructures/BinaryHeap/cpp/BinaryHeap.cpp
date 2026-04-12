#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

/**
 * Binary Heap (Max-Heap) Implementation
 * 
 * Concept:
 * A Binary Heap is a complete binary tree where each node satisfies the heap property.
 * In a Max-Heap, the value of each node is greater than or equal to the values of its children.
 * This ensures that the root of the tree always contains the maximum element of the heap.
 * 
 * Complexity:
 * - Insert: O(log n) - Elements are added at the bottom and moved up to restore the heap property.
 * - Extract Max: O(log n) - The root is replaced by the last element and moved down.
 * - Get Max: O(1) - The maximum element is always at the root.
 * - Space: O(n) - Elements are stored in a contiguous array (std::vector).
 */

class BinaryHeap {
private:
    std::vector<int> heap;

    /**
     * @brief Returns the index of the parent of the node at index i.
     */
    int parent(int i) { return (i - 1) / 2; }

    /**
     * @brief Returns the index of the left child of the node at index i.
     */
    int left(int i) { return (2 * i + 1); }

    /**
     * @brief Returns the index of the right child of the node at index i.
     */
    int right(int i) { return (2 * i + 2); }

    /**
     * @brief Restores the heap property by moving the element at index i down the tree.
     * This is used after the root has been replaced by the last element during extraction.
     * 
     * @param i The index of the element to move down.
     */
    void heapifyDown(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        // Check if left child is larger than current largest
        if (l < heap.size() && heap[l] > heap[largest])
            largest = l;

        // Check if right child is larger than current largest
        if (r < heap.size() && heap[r] > heap[largest])
            largest = r;

        // If a child is larger, swap and continue heapifying down
        if (largest != i) {
            std::cout << "    [!] Violation: Node " << heap[i] << " at index " << i 
                      << " is smaller than child " << heap[largest] << " at index " << largest << ".\n";
            std::cout << "        Swapping " << heap[i] << " with " << heap[largest] << ".\n";
            
            std::swap(heap[i], heap[largest]);
            printHeap();
            
            std::cout << "    (Press Enter to continue heapifying down...)";
            std::cin.get();
            
            heapifyDown(largest);
        } else {
            std::cout << "    [✓] Heap property restored at this level. Node " << heap[i] << " is in the correct position.\n";
        }
    }

    /**
     * @brief Restores the heap property by moving the element at index i up the tree.
     * This is used after a new element has been inserted at the end of the vector.
     * 
     * @param i The index of the element to move up.
     */
    void heapifyUp(int i) {
        // While not the root and the parent is smaller than the current node
        while (i != 0 && heap[parent(i)] < heap[i]) {
            std::cout << "    [!] Violation: Parent " << heap[parent(i)] << " at index " << parent(i)
                      << " is smaller than child " << heap[i] << " at index " << i << ".\n";
            std::cout << "        Swapping " << heap[i] << " with " << heap[parent(i)] << ".\n";
            
            std::swap(heap[i], heap[parent(i)]);
            printHeap();
            
            i = parent(i);
            
            std::cout << "    (Press Enter to continue heapifying up...)";
            std::cin.get();
        }
        
        if (i == 0) {
            std::cout << "    [✓] Node reached the root. Heap property satisfied.\n";
        } else {
            std::cout << "    [✓] Parent " << heap[parent(i)] << " is >= " << heap[i] << ". Heap property satisfied.\n";
        }
    }

public:
    /**
     * @brief Inserts a new value into the heap.
     * 
     * @param value The value to be inserted.
     */
    void insert(int value) {
        std::cout << "\n>>> OPERATION: Insert " << value << "\n";
        std::cout << "    1. Adding " << value << " to the end of the vector.\n";
        
        heap.push_back(value);
        printHeap();
        
        std::cout << "    2. Restoring Max-Heap property (heapifyUp)...\n";
        std::cout << "    (Press Enter to start heapifyUp...)";
        std::cin.get();
        
        heapifyUp(heap.size() - 1);
    }

    /**
     * @brief Removes and returns the maximum value (the root) from the heap.
     * 
     * @return The maximum value, or -1 if the heap is empty.
     */
    int extractMax() {
        if (heap.empty()) {
            std::cout << "\n>>> OPERATION: Extract Max\n";
            std::cout << "    [!] Error: Heap is empty!\n";
            return -1;
        }

        int maxVal = heap[0];
        std::cout << "\n>>> OPERATION: Extract Max (Value: " << maxVal << ")\n";
        
        if (heap.size() == 1) {
            std::cout << "    Heap has only one element. Removing it.\n";
            heap.pop_back();
            return maxVal;
        }

        std::cout << "    1. Replacing root " << maxVal << " with last element " << heap.back() << ".\n";
        heap[0] = heap.back();
        heap.pop_back();
        printHeap();

        std::cout << "    2. Restoring Max-Heap property (heapifyDown)...\n";
        std::cout << "    (Press Enter to start heapifyDown...)";
        std::cin.get();

        heapifyDown(0);

        return maxVal;
    }

    /**
     * @brief Visualizes the heap as both a vector and a simple level-order tree.
     */
    void printHeap() {
        std::cout << "    Current Vector: [ ";
        for (size_t i = 0; i < heap.size(); ++i) {
            std::cout << heap[i] << (i == heap.size() - 1 ? "" : ", ");
        }
        std::cout << " ]\n";

        if (!heap.empty()) {
            std::cout << "    Tree Visualization:\n";
            int n = heap.size();
            int levels = std::log2(n) + 1;
            int current_idx = 0;

            for (int i = 0; i < levels; ++i) {
                int level_nodes = std::pow(2, i);
                std::cout << "      L" << i << ": ";
                for (int j = 0; j < level_nodes && current_idx < n; ++j) {
                    std::cout << std::setw(3) << heap[current_idx++] << " ";
                }
                std::cout << "\n";
            }
        }
    }

    /**
     * @brief Returns true if the heap is empty.
     */
    bool isEmpty() const {
        return heap.empty();
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        BINARY HEAP INTERACTIVE (MAX-HEAP)\n";
    std::cout << "==========================================\n";
    std::cout << "This interactive example demonstrates how a Max-Heap\n";
    std::cout << "maintains its structure during insertions and extractions.\n";
    std::cout << "Press Enter to progress through each step.\n";
    std::cout << "==========================================\n";

    BinaryHeap myHeap;

    // Phase 1: Insertions
    std::vector<int> valuesToInsert = {15, 10, 20, 8, 25};
    std::cout << "\n--- PHASE 1: INSERTIONS ---\n";
    for (int val : valuesToInsert) {
        myHeap.insert(val);
    }

    std::cout << "\n--- PHASE 2: EXTRACTIONS ---\n";
    std::cout << "We will now extract the maximum element until the heap is empty.\n";
    std::cout << "(Press Enter to start extraction phase...)";
    std::cin.get();

    while (!myHeap.isEmpty()) {
        myHeap.extractMax();
        if (!myHeap.isEmpty()) {
            std::cout << "\n    (Press Enter for next extraction...)";
            std::cin.get();
        }
    }

    std::cout << "\n==========================================\n";
    std::cout << "Binary Heap demonstration completed!\n";
    std::cout << "==========================================\n";

    return 0;
}
