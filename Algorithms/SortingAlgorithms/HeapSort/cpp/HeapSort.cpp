#include <iostream>
#include <vector>
#include <algorithm>

/**
 * HeapSort Algorithm
 * 
 * Concept:
 * Heap Sort is a comparison-based sorting technique based on a Binary Heap data structure.
 * It is similar to selection sort where we first find the maximum element and place it at the end.
 * We repeat the same process for the remaining elements.
 * 
 * Complexity:
 * - Time: O(n log n) - Worst, Average, and Best case.
 * - Space: O(1) - Auxiliary space.
 */

class HeapSort {
public:
    /**
     * @brief Sorts a vector using Heap Sort and explains each step.
     * 
     * @param arr The vector to be sorted.
     */
    void sort(std::vector<int>& arr) {
        int n = arr.size();

        std::cout << "Starting Heap Sort on: ";
        printArray(arr);
        std::cout << "------------------------------------------\n";

        // Step 1: Build a max heap
        std::cout << "\n>>> Phase 1: Building a Max Heap\n";
        for (int i = n / 2 - 1; i >= 0; i--) {
            std::cout << "    [!] Heapifying from index " << i << "\n";
            heapify(arr, n, i);
        }

        std::cout << "    [✓] Max Heap built: ";
        printArray(arr);
        std::cout << "    (Press Enter to continue to Phase 2...)";
        std::cin.get();

        // Step 2: One by one extract an element from the heap
        std::cout << "\n>>> Phase 2: Extracting elements from the heap one by one\n";
        for (int i = n - 1; i > 0; i--) {
            std::cout << "\n    >>> Iteration " << (n - i) << " (extracting " << arr[0] << " to position " << i << ")\n";
            printStep(arr, 0, i);

            // Move current root to end
            std::swap(arr[0], arr[i]);
            std::cout << "    [!] Swapped root with last element.\n";
            printArray(arr);

            // call max heapify on the reduced heap
            std::cout << "    [!] Re-heapifying the reduced heap of size " << i << ".\n";
            heapify(arr, i, 0);

            std::cout << "    (Press Enter to continue...)";
            std::cin.get();
        }

        std::cout << "------------------------------------------\n";
        std::cout << "Final sorted array: ";
        printArray(arr);
    }

private:
    /**
     * @brief To heapify a subtree rooted with node i which is an index in arr[]. 
     *        n is size of heap.
     */
    void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i; // Initialize largest as root
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (l < n && arr[l] > arr[largest])
            largest = l;

        // If right child is larger than largest so far
        if (r < n && arr[r] > arr[largest])
            largest = r;

        // If largest is not root
        if (largest != i) {
            std::swap(arr[i], arr[largest]);

            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }

    /**
     * @brief Prints the entire array.
     */
    void printArray(const std::vector<int>& arr) {
        std::cout << "[ ";
        for (int x : arr) {
            std::cout << x << " ";
        }
        std::cout << "]\n";
    }

    /**
     * @brief Prints the array with highlighting the elements currently being swapped.
     */
    void printStep(const std::vector<int>& arr, int idx1, int idx2) {
        std::cout << "    Current: [ ";
        for (int i = 0; i < arr.size(); i++) {
            if (i == idx1 || i == idx2) {
                std::cout << "(" << arr[i] << ") "; // Highlight elements with parentheses
            } else {
                std::cout << arr[i] << " ";
            }
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "         HEAP SORT INTERACTIVE\n";
    std::cout << "==========================================\n";

    std::vector<int> data = {12, 11, 13, 5, 6, 7};

    HeapSort sorter;
    sorter.sort(data);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
