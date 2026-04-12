#include <iostream>
#include <vector>
#include <algorithm>

/**
 * QuickSort Algorithm
 * 
 * Concept:
 * QuickSort is a Divide and Conquer algorithm. It picks an element as pivot
 * and partitions the given array around the picked pivot.
 * This implementation uses the last element as the pivot.
 * 
 * Complexity:
 * - Time: O(n log n) - Average and Best case. O(n^2) - Worst case.
 * - Space: O(log n) - Stack space (due to recursion).
 */

class QuickSort {
public:
    /**
     * @brief Sorts a vector using Quick Sort and explains each step.
     * 
     * @param arr The vector to be sorted.
     */
    void sort(std::vector<int>& arr) {
        std::cout << "Starting Quick Sort on: ";
        printArray(arr);
        std::cout << "------------------------------------------\n";

        quickSort(arr, 0, arr.size() - 1);

        std::cout << "------------------------------------------\n";
        std::cout << "Final sorted array: ";
        printArray(arr);
    }

private:
    /**
     * @brief The main QuickSort function.
     */
    void quickSort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            std::cout << "\n>>> Partitioning from index " << low << " to " << high << "\n";
            
            // pi is partitioning index, arr[pi] is now at right place
            int pi = partition(arr, low, high);

            std::cout << "    [✓] Pivot placed at index " << pi << ".\n";
            printArray(arr);
            std::cout << "    (Press Enter to continue to next partitions...)";
            std::cin.get();

            // Separately sort elements before partition and after partition
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    /**
     * @brief This function takes last element as pivot, places the pivot element 
     *        at its correct position in sorted array, and places all smaller 
     *        (smaller than pivot) to left of pivot and all greater elements to right.
     */
    int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high]; // pivot
        int i = (low - 1); // Index of smaller element

        std::cout << "    Current Pivot: " << pivot << " (at index " << high << ")\n";

        for (int j = low; j <= high - 1; j++) {
            printStep(arr, j, high, i + 1);
            std::cout << "    [ ] Comparing " << arr[j] << " with pivot " << pivot << "\n";

            // If current element is smaller than or equal to pivot
            if (arr[j] <= pivot) {
                i++; // increment index of smaller element
                std::cout << "    [!] " << arr[j] << " <= " << pivot << ". Swapping with index " << i << ".\n";
                std::swap(arr[i], arr[j]);
            }
        }
        
        std::cout << "    [!] Finalizing pivot: swapping " << arr[i + 1] << " with pivot " << arr[high] << ".\n";
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
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
     * @brief Prints the array with highlighting pivot, current comparison, and partition point.
     */
    void printStep(const std::vector<int>& arr, int current, int pivotIdx, int partitionIdx) {
        std::cout << "    Current: [ ";
        for (int i = 0; i < arr.size(); i++) {
            if (i == pivotIdx) {
                std::cout << "{" << arr[i] << "} "; // Pivot in braces
            } else if (i == current) {
                std::cout << "(" << arr[i] << ") "; // Current element in parentheses
            } else if (i == partitionIdx) {
                std::cout << "|" << arr[i] << " "; // Potential partition point
            } else {
                std::cout << arr[i] << " ";
            }
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "         QUICK SORT INTERACTIVE\n";
    std::cout << "==========================================\n";

    std::vector<int> data = {10, 7, 8, 9, 1, 5};

    QuickSort sorter;
    sorter.sort(data);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
