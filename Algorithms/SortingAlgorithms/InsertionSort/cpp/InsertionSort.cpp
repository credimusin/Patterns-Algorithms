#include <iostream>
#include <vector>
#include <algorithm>

/**
 * InsertionSort Algorithm
 * 
 * Concept:
 * Insertion sort is a simple sorting algorithm that builds the final sorted array
 * one item at a time. It works by taking the first element of the unsorted part
 * and inserting it into its correct position in the sorted part of the array.
 * 
 * Complexity:
 * - Time: O(n^2) - Worst and Average case. O(n) - Best case (already sorted).
 * - Space: O(1) - Auxiliary space.
 */

class InsertionSort {
public:
    /**
     * @brief Sorts a vector using Insertion Sort and explains each step.
     * 
     * @param arr The vector to be sorted.
     */
    void sort(std::vector<int>& arr) {
        int n = arr.size();

        std::cout << "Starting Insertion Sort on: ";
        printArray(arr);
        std::cout << "------------------------------------------\n";

        for (int i = 1; i < n; i++) {
            int key = arr[i]; // The element we're currently trying to insert
            int j = i - 1;

            std::cout << "\n>>> Pass " << i << " (inserting " << key << " into the sorted portion)\n";
            printStep(arr, i, -1);
            std::cout << "    Current key: " << key << "\n";

            // Move elements of arr[0..i-1], that are greater than key,
            // to one position ahead of their current position
            while (j >= 0 && arr[j] > key) {
                printStep(arr, j, j + 1);
                std::cout << "    [!] " << arr[j] << " > " << key << ". Moving " << arr[j] << " to the right.\n";
                
                arr[j + 1] = arr[j];
                j = j - 1;

                std::cout << "    (Press Enter to continue...)";
                std::cin.get();
            }

            // Insert the key into its correct position
            arr[j + 1] = key;
            std::cout << "    [✓] Inserted " << key << " at position " << (j + 1) << ".\n";
            printArray(arr);
            
            std::cout << "    (Press Enter to continue to next pass...)";
            std::cin.get();
        }

        std::cout << "------------------------------------------\n";
        std::cout << "Final sorted array: ";
        printArray(arr);
    }

private:
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
     * @brief Prints the array with highlighting the elements currently being compared or moved.
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
    std::cout << "      INSERTION SORT INTERACTIVE\n";
    std::cout << "==========================================\n";

    std::vector<int> data = {12, 11, 13, 5, 6};

    InsertionSort sorter;
    sorter.sort(data);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
