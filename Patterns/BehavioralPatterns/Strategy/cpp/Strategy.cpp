#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

/**
 * Strategy Design Pattern
 * 
 * Intent:
 * Lets you define a family of algorithms, put each of them into 
 * a separate class, and make their objects interchangeable.
 * 
 * Components:
 * - Strategy Interface: Common interface for all supported algorithms.
 * - Concrete Strategies: Implement the algorithm using the Strategy interface.
 * - Context: Maintains a reference to a Strategy object and communicates 
 *   with it only via the strategy interface.
 */

// Strategy Interface
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual void sort(std::vector<int>& data) = 0;
    virtual std::string getName() const = 0;
};

// Concrete Strategy: Bubble Sort (Simplified for demo)
class BubbleSortStrategy : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "    [BubbleSort] Sorting using bubble sort algorithm...\n";
        for (size_t i = 0; i < data.size(); i++) {
            for (size_t j = 0; j < data.size() - i - 1; j++) {
                if (data[j] > data[j+1]) std::swap(data[j], data[j+1]);
            }
        }
    }
    std::string getName() const override { return "Bubble Sort"; }
};

// Concrete Strategy: Quick Sort (Using std::sort for simplicity)
class QuickSortStrategy : public SortStrategy {
public:
    void sort(std::vector<int>& data) override {
        std::cout << "    [QuickSort] Sorting using quick sort (std::sort) algorithm...\n";
        std::sort(data.begin(), data.end());
    }
    std::string getName() const override { return "Quick Sort"; }
};

// Context
class SortedList {
    std::vector<int> data;
    std::unique_ptr<SortStrategy> strategy;

public:
    void add(int value) { data.push_back(value); }

    void setStrategy(std::unique_ptr<SortStrategy> s) {
        strategy = std::move(s);
        std::cout << "    [Context] Strategy changed to: " << strategy->getName() << "\n";
    }

    void sort() {
        if (strategy) {
            strategy->sort(data);
        } else {
            std::cout << "    [Context] No strategy set!\n";
        }
    }

    void display() {
        std::cout << "    [Data] ";
        for (int x : data) std::cout << x << " ";
        std::cout << "\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "           STRATEGY INTERACTIVE\n";
    std::cout << "==========================================\n";

    SortedList myList;
    myList.add(64);
    myList.add(34);
    myList.add(25);
    myList.add(12);
    myList.add(22);

    std::cout << "Initial data: ";
    myList.display();
    std::cout << "\n";

    std::cout << "--- Action 1: Use Bubble Sort ---\n";
    myList.setStrategy(std::make_unique<BubbleSortStrategy>());
    myList.sort();
    myList.display();
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 2: Use Quick Sort on new data ---\n";
    SortedList myList2;
    myList2.add(5);
    myList2.add(2);
    myList2.add(9);
    myList2.add(1);
    
    myList2.setStrategy(std::make_unique<QuickSortStrategy>());
    myList2.sort();
    myList2.display();
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\nStrategy Pattern demonstration complete.\n";
    return 0;
}
