#include <iostream>
#include <string>
#include <vector>

/**
 * Extract Method Refactoring
 * 
 * Concept:
 * Extract Method is a refactoring technique where a block of code within a 
 * larger function is moved into its own separate method.
 * 
 * Why?
 * - Improves readability by naming complex logic.
 * - Reduces code duplication.
 * - Makes the original function shorter and easier to understand.
 * - Facilitates easier testing of the extracted logic.
 */

class OrderProcessor {
public:
    // --- BEFORE REFACTORING ---
    void printOrderBefore(std::string customer, double price, int quantity) {
        // Print header
        std::cout << "**************************\n";
        std::cout << "      ORDER SUMMARY       \n";
        std::cout << "**************************\n";

        // Calculate total
        double total = price * quantity;
        double tax = total * 0.1;
        double finalPrice = total + tax;

        // Print details
        std::cout << "Customer: " << customer << "\n";
        std::cout << "Total Price: $" << finalPrice << "\n";
    }

    // --- AFTER REFACTORING ---
    void printOrderAfter(std::string customer, double price, int quantity) {
        printHeader();
        double finalPrice = calculateTotal(price, quantity);
        printDetails(customer, finalPrice);
    }

private:
    void printHeader() {
        std::cout << "**************************\n";
        std::cout << "      ORDER SUMMARY       \n";
        std::cout << "**************************\n";
    }

    double calculateTotal(double price, int quantity) {
        double total = price * quantity;
        double tax = total * 0.1;
        return total + tax;
    }

    void printDetails(std::string customer, double finalPrice) {
        std::cout << "Customer: " << customer << "\n";
        std::cout << "Total Price: $" << finalPrice << "\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        EXTRACT METHOD REFACTORING\n";
    std::cout << "==========================================\n";

    OrderProcessor processor;

    std::cout << "1. Executing printOrderBefore()...\n";
    std::cout << "    (Logic for header, calculation, and details is all in one place.)\n";
    processor.printOrderBefore("Alice", 50.0, 2);

    std::cout << "\n    (Press Enter to see the refactored printOrderAfter()...)";
    std::cin.get();

    std::cout << "2. Executing printOrderAfter()...\n";
    std::cout << "    (The function now delegates tasks to smaller, well-named methods.)\n";
    processor.printOrderAfter("Bob", 30.0, 3);

    std::cout << "------------------------------------------\n";
    std::cout << "By extracting logic into printHeader(), calculateTotal(), and printDetails(),\n";
    std::cout << "we made the main function more declarative and easier to maintain.\n";

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
