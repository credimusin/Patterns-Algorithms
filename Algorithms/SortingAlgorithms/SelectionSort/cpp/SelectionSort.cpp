#include <iostream>
#include <vector>
#include <algorithm>

/**
 * SelectionSort Algorithm
 * 
 * Concept:
 * Selection sort is a simple sorting algorithm that repeatedly finds the minimum element
 * from the unsorted part and moves it to the beginning. The algorithm maintains two
 * subarrays: the subarray which is already sorted and the remaining subarray which is unsorted.
 * 
 * Complexity:
 * - Time: O(n^2) - Worst, Average, and Best case.
 * - Space: O(1) - Auxiliary space.
 */

class SelectionSort {
public:
    /**
     * @brief Sorts a vector using Selection Sort and explains each step.
     * 
     * @param arr The vector to be sorted.
     */
    void sort(std::vector<int>& arr) {
        int n = arr.size();

        std::cout << "Starting Selection Sort on: ";
        printArray(arr);
        std::cout << "------------------------------------------\n";

        for (int i = 0; i < n - 1; i++) {
            // Find the minimum element in unsorted array
            int min_idx = i;
            std::cout << "\n>>> Pass " << (i + 1) << " (searching for the minimum from index " << i << " to " << (n - 1) << ")\n";

            for (int j = i + 1; j < n; j++) {
                printStep(arr, min_idx, j);
                std::cout << "    [ ] Comparing " << arr[j] << " with current minimum " << arr[min_idx] << "\n";

                if (arr[j] < arr[min_idx]) {
                    std::cout << "    [!] Found a new minimum: " << arr[j] << " (index " << j << ")\n";
                    min_idx = j;
                }

                std::cout << "    (Press Enter to continue...)";
                std::cin.get();
            }

            // Swap the found minimum element with the first element
            if (min_idx != i) {
                std::cout << "    [✓] Swapping " << arr[i] << " and " << arr[min_idx] << ".\n";
                std::swap(arr[min_idx], arr[i]);
            } else {
                std::cout << "    [ ] Minimum " << arr[i] << " is already in the correct place.\n";
            }

            printArray(arr);
            std::cout << "    (Press Enter for next pass...)";
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
     * @brief Prints the array with highlighting the elements currently being compared or the current minimum.
     */
    void printStep(const std::vector<int>& arr, int idx1, int idx2) {
        std::cout << "    Current: [ ";
        for (int i = 0; i < arr.size(); i++) {
            if (i == idx1) {
                std::cout << "<" << arr[i] << "> "; // Highlight current minimum with angled brackets
            } else if (i == idx2) {
                std::cout << "(" << arr[i] << ") "; // Highlight current comparison with parentheses
            } else {
                std::cout << arr[i] << " ";
            }
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "      SELECTION SORT INTERACTIVE\n";
    std::cout << "==========================================\n";

    std::vector<int> data = {64, 25, 12, 22, 11};

    SelectionSort sorter;
    sorter.sort(data);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
