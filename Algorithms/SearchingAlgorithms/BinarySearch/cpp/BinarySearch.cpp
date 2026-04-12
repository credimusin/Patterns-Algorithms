#include <iostream>
#include <vector>
#include <algorithm>

/**
 * BinarySearch Algorithm
 * 
 * Concept:
 * Binary search is an efficient search algorithm that finds the position of a target value
 * within a sorted array. It repeatedly divides the search interval in half.
 * 
 * Complexity:
 * - Time: O(log n) - Average and Worst case. O(1) - Best case (middle element).
 * - Space: O(1) - Iterative approach.
 */

class BinarySearch {
public:
    /**
     * @brief Searches for a target value in a sorted vector using Binary Search and explains each step.
     * 
     * @param arr The vector to be searched (must be sorted).
     * @param target The value to find.
     * @return int The index of the target if found, otherwise -1.
     */
    int search(const std::vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;

        std::cout << "Starting Binary Search for target: " << target << " in (sorted array): ";
        printArray(arr);
        std::cout << "------------------------------------------\n";

        int step = 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            std::cout << "\n>>> Step " << step++ << ": Range [" << left << ", " << right << "], Middle index: " << mid << " (" << arr[mid] << ")\n";
            printStep(arr, left, right, mid);

            if (arr[mid] == target) {
                std::cout << "    [✓] " << arr[mid] << " is the target! Found at index " << mid << ".\n";
                return mid;
            }

            if (arr[mid] < target) {
                std::cout << "    [>] " << arr[mid] << " < " << target << ". Target is in the right half.\n";
                left = mid + 1;
            } else {
                std::cout << "    [<] " << arr[mid] << " > " << target << ". Target is in the left half.\n";
                right = mid - 1;
            }

            // Interactive pause
            std::cout << "    (Press Enter to continue...)";
            std::cin.get();
        }

        std::cout << "------------------------------------------\n";
        std::cout << "[!] Target " << target << " was not found in the array.\n";
        return -1;
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
     * @brief Prints the array with highlighting the search range and current middle.
     */
    void printStep(const std::vector<int>& arr, int left, int right, int mid) {
        std::cout << "    Current: ";
        for (int i = 0; i < arr.size(); i++) {
            if (i == mid) {
                std::cout << "(" << arr[i] << ") "; // Highlight middle with parentheses
            } else if (i >= left && i <= right) {
                std::cout << "[" << arr[i] << "] "; // Highlight active range with brackets
            } else {
                std::cout << " .  "; // Dim inactive elements
            }
        }
        std::cout << "\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "      BINARY SEARCH INTERACTIVE\n";
    std::cout << "==========================================\n";

    // Data must be sorted for Binary Search
    std::vector<int> data = {11, 22, 34, 45, 56, 67, 89, 101};
    int target = 67;

    BinarySearch searcher;
    searcher.search(data, target);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
