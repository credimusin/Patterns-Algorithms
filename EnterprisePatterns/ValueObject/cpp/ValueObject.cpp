#include <iostream>
#include <string>

/**
 * Value Object Pattern
 * 
 * Intent:
 * A small simple object, like money or a date range, whose equality is 
 * based on the value rather than identity. They are usually immutable.
 * 
 * Components:
 * - Money: Value object holding currency and amount.
 * - Logic: Equality operator to compare values.
 */

class Money {
public:
    Money(double amount, std::string currency) 
        : amount(amount), currency(currency) {}

    // Equality based on values, not memory address
    bool operator==(const Money& other) const {
        return amount == other.amount && currency == other.currency;
    }

    void display() const {
        std::cout << "    [Money] " << amount << " " << currency << "\n";
    }

private:
    double amount;
    std::string currency;
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "          VALUE OBJECT PATTERN\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: Identity comes from the values, not the instance.\n";
    std::cout << "Two 'Money' objects with 50 USD are equal even if they are different instances.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    std::cout << "1. Creating two different instances with same values.\n";
    Money m1(50.0, "USD");
    Money m2(50.0, "USD");
    m1.display();
    m2.display();
    std::cin.get();

    std::cout << "2. Checking for equality (value comparison).\n";
    if (m1 == m2) {
        std::cout << "    [✓] m1 and m2 are equal (same values).\n";
    } else {
        std::cout << "    [X] m1 and m2 are not equal.\n";
    }
    std::cin.get();

    std::cout << "3. Changing value and checking again.\n";
    Money m3(60.0, "USD");
    m3.display();
    if (m1 == m3) {
        std::cout << "    [X] m1 and m3 are equal.\n";
    } else {
        std::cout << "    [✓] m1 and m3 are NOT equal (different amounts).\n";
    }

    std::cout << "\n[✓] Value objects simplify logic by treating objects as values (like primitive types).\n";
    std::cout << "==========================================\n";

    return 0;
}
