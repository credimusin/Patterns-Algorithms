#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

/**
 * BubbleSort Algorithm
 * 
 * Concept:
 * Bubble sort is a simple sorting algorithm that repeatedly steps through the list,
 * compares adjacent elements and swaps them if they are in the wrong order.
 * The pass through the list is repeated until the list is sorted.
 * 
 * Complexity:
 * - Time: O(n^2) - Worst and Average case. O(n) - Best case (already sorted).
 * - Space: O(1) - Auxiliary space.
 */

class BubbleSort {
public:
    /**
     * @brief Sorts a vector using Bubble Sort and explains each step.
     * 
     * @param arr The vector to be sorted.
     */
    void sort(std::vector<int>& arr) {
        int n = arr.size();
        
        // This boolean 'swapped' helps us optimize the algorithm.
        // If no two elements were swapped by the inner loop, then the list is sorted.
        bool swapped;

        std::cout << "Starting Bubble Sort on: ";
        printArray(arr);
        std::cout << "------------------------------------------\n";

        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            std::cout << "\n>>> Pass " << (i + 1) << " (checking the first " << (n - i) << " elements)\n";

            for (int j = 0; j < n - i - 1; j++) {
                // Highlight the elements being compared
                printStep(arr, j, j + 1);

                // Compare adjacent elements
                if (arr[j] > arr[j + 1]) {
                    std::cout << "    [!] " << arr[j] << " > " << arr[j + 1] << ". Swapping them.\n";
                    
                    // The swap function exchanges the values of two variables.
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                } else {
                    std::cout << "    [ ] " << arr[j] << " <= " << arr[j + 1] << ". No swap needed.\n";
                }

                // Small pause or wait for user input for "interactive" feel
                // In this example, we'll just wait for user to press Enter to continue to the next comparison.
                std::cout << "    (Press Enter to continue...)";
                std::cin.get();
            }

            // If no elements were swapped, the array is already sorted.
            if (!swapped) {
                std::cout << "\n[✓] No swaps occurred in this pass. The array is already sorted!\n";
                break;
            }
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
     * @brief Prints the array with highlighting the elements currently being compared.
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
    std::cout << "        BUBBLE SORT INTERACTIVE\n";
    std::cout << "==========================================\n";

    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};

    BubbleSort sorter;
    sorter.sort(data);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
