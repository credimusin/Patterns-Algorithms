#include <iostream>
#include <vector>
#include <algorithm>

/**
 * MergeSort Algorithm
 * 
 * Concept:
 * MergeSort is a Divide and Conquer algorithm. It divides the input array
 * into two halves, calls itself for the two halves, and then merges the
 * two sorted halves.
 * 
 * Complexity:
 * - Time: O(n log n) - Worst, Average, and Best case.
 * - Space: O(n) - Auxiliary space.
 */

class MergeSort {
public:
    /**
     * @brief Sorts a vector using Merge Sort and explains each step.
     * 
     * @param arr The vector to be sorted.
     */
    void sort(std::vector<int>& arr) {
        std::cout << "Starting Merge Sort on: ";
        printArray(arr, 0, arr.size() - 1);
        std::cout << "------------------------------------------\n";

        mergeSort(arr, 0, arr.size() - 1);

        std::cout << "------------------------------------------\n";
        std::cout << "Final sorted array: ";
        printArray(arr, 0, arr.size() - 1);
    }

private:
    /**
     * @brief The main MergeSort function that recursively divides the array.
     */
    void mergeSort(std::vector<int>& arr, int l, int r) {
        if (l < r) {
            // Same as (l+r)/2, but avoids overflow for large l and h
            int m = l + (r - l) / 2;

            std::cout << "\n>>> Dividing: [ ";
            printArrayRange(arr, l, r);
            std::cout << " ] into [ ";
            printArrayRange(arr, l, m);
            std::cout << " ] and [ ";
            printArrayRange(arr, m + 1, r);
            std::cout << " ]\n";
            std::cout << "    (Press Enter to continue dividing...)";
            std::cin.get();

            // Sort first and second halves
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);

            merge(arr, l, m, r);
        }
    }

    /**
     * @brief Merges two subarrays of arr[].
     *        First subarray is arr[l..m]
     *        Second subarray is arr[m+1..r]
     */
    void merge(std::vector<int>& arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;

        // Create temp arrays
        std::vector<int> L(n1), R(n2);

        // Copy data to temp arrays L[] and R[]
        for (int i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        std::cout << "\n>>> Merging: [ ";
        printArrayRange(L, 0, n1 - 1);
        std::cout << " ] and [ ";
        printArrayRange(R, 0, n2 - 1);
        std::cout << " ]\n";

        // Merge the temp arrays back into arr[l..r]
        int i = 0; // Initial index of first subarray
        int j = 0; // Initial index of second subarray
        int k = l; // Initial index of merged subarray

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                std::cout << "    [!] " << L[i] << " <= " << R[j] << ". Taking " << L[i] << " from Left.\n";
                arr[k] = L[i];
                i++;
            } else {
                std::cout << "    [!] " << L[i] << " > " << R[j] << ". Taking " << R[j] << " from Right.\n";
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of L[], if there are any
        while (i < n1) {
            std::cout << "    [!] Taking remaining " << L[i] << " from Left.\n";
            arr[k] = L[i];
            i++;
            k++;
        }

        // Copy the remaining elements of R[], if there are any
        while (j < n2) {
            std::cout << "    [!] Taking remaining " << R[j] << " from Right.\n";
            arr[k] = R[j];
            j++;
            k++;
        }

        std::cout << "    [✓] Result: ";
        printArray(arr, l, r);
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

    /**
     * @brief Prints the entire array with a highlighted range.
     */
    void printArray(const std::vector<int>& arr, int l, int r) {
        std::cout << "[ ";
        for (int i = 0; i < arr.size(); i++) {
            if (i >= l && i <= r) {
                std::cout << "(" << arr[i] << ") ";
            } else {
                std::cout << arr[i] << " ";
            }
        }
        std::cout << "]\n";
    }

    /**
     * @brief Prints only a range of the array.
     */
    void printArrayRange(const std::vector<int>& arr, int l, int r) {
        for (int i = l; i <= r; i++) {
            std::cout << arr[i] << (i == r ? "" : " ");
        }
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "         MERGE SORT INTERACTIVE\n";
    std::cout << "==========================================\n";

    std::vector<int> data = {38, 27, 43, 3, 9, 82, 10};

    MergeSort sorter;
    sorter.sort(data);

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
