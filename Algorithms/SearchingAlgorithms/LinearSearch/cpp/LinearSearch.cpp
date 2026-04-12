#include <iostream>
#include <vector>

/**
 * LinearSearch Algorithm
 * 
 * Concept:
 * Linear Search is the simplest search algorithm that checks every element in the list
 * sequentially from the beginning until the target value is found or the end of the list is reached.
 * 
 * Complexity:
 * - Time: O(n) - Worst and Average case. O(1) - Best case (target is at the beginning).
 * - Space: O(1) - Auxiliary space.
 */

class LinearSearch {
public:
    /**
     * @brief Searches for a target value in a vector using Linear Search and explains each step.
     * 
     * @param arr The vector to be searched.
     * @param target The value to find.
     * @return int The index of the target if found, otherwise -1.
     */
    int search(const std::vector<int>& arr, int target) {
        int n = arr.size();

        std::cout << "Starting Linear Search for target: " << target << " in: ";
        printArray(arr);
        std::cout << "------------------------------------------\n";

        for (int i = 0; i < n; i++) {
            // Highlight the element being checked
            printStep(arr, i);

            std::cout << ">>> Step " << (i + 1) << ": Checking element at index " << i << " (" << arr[i] << ")\n";

            if (arr[i] == target) {
                std::cout << "    [✓] Found target " << target << " at index " << i << "!\n";
                return i;
            } else {
                std::cout << "    [ ] " << arr[i] << " is not " << target << ". Moving to the next element.\n";
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
     * @brief Prints the array with highlighting the element currently being checked.
     */
    void printStep(const std::vector<int>& arr, int currentIdx) {
        std::cout << "    Current: [ ";
        for (int i = 0; i < arr.size(); i++) {
            if (i == currentIdx) {
                std::cout << "(" << arr[i] << ") "; // Highlight current element with parentheses
            } else {
                std::cout << arr[i] << " ";
            }
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "      LINEAR SEARCH INTERACTIVE\n";
    std::cout << "==========================================\n";

    std::vector<int> data = {12, 45, 7, 23, 9, 56, 31};
    int target = 23;

    LinearSearch searcher;
    searcher.search(data, target);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
