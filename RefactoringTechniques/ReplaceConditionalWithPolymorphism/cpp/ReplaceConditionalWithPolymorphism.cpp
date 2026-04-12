#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * Replace Conditional with Polymorphism Refactoring
 * 
 * Concept:
 * Large switch statements or if-else ladders often indicate that an object 
 * is behaving differently based on its type. Polymorphism allows you to 
 * define these behaviors in separate classes that share a common interface.
 * 
 * Why?
 * - Easier to add new types (no need to update a giant switch statement).
 * - Follows the Open/Closed Principle (classes are open for extension, 
 *   but closed for modification).
 * - Improves code structure and readability.
 */

// --- BEFORE REFACTORING ---
enum class EmployeeType { Engineer, Manager, Salesperson };

struct EmployeeRecord {
    EmployeeType type;
    double baseSalary;
    double bonus;
    double commission;

    double getPay() const {
        switch (type) {
            case EmployeeType::Engineer:
                return baseSalary;
            case EmployeeType::Manager:
                return baseSalary + bonus;
            case EmployeeType::Salesperson:
                return baseSalary + commission;
            default:
                return 0;
        }
    }
};

// --- AFTER REFACTORING ---
class Employee {
public:
    virtual ~Employee() = default;
    virtual double getPay() const = 0;
    virtual std::string getType() const = 0;
};

class Engineer : public Employee {
    double salary;
public:
    Engineer(double s) : salary(s) {}
    double getPay() const override { return salary; }
    std::string getType() const override { return "Engineer"; }
};

class Manager : public Employee {
    double salary;
    double bonus;
public:
    Manager(double s, double b) : salary(s), bonus(b) {}
    double getPay() const override { return salary + bonus; }
    std::string getType() const override { return "Manager"; }
};

class Salesperson : public Employee {
    double salary;
    double commission;
public:
    Salesperson(double s, double c) : salary(s), commission(c) {}
    double getPay() const override { return salary + commission; }
    std::string getType() const override { return "Salesperson"; }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << " REPLACE CONDITIONAL WITH POLYMORPHISM\n";
    std::cout << "==========================================\n";

    std::cout << "1. Using Giant Switch (Before Refactoring):\n";
    EmployeeRecord rec{EmployeeType::Manager, 5000, 1500, 0};
    std::cout << "    Manager Pay: " << rec.getPay() << "\n";
    std::cout << "    (Logic for all types is hardcoded in one switch statement.)\n";

    std::cout << "\n    (Press Enter to see the Polymorphic version...)";
    std::cin.get();

    std::cout << "2. Using Polymorphism (After Refactoring):\n";
    std::vector<std::unique_ptr<Employee>> employees;
    employees.push_back(std::make_unique<Engineer>(4000));
    employees.push_back(std::make_unique<Manager>(5000, 1500));
    employees.push_back(std::make_unique<Salesperson>(3000, 2000));

    for (const auto& emp : employees) {
        std::cout << "    " << emp->getType() << " Pay: " << emp->getPay() << "\n";
    }

    std::cout << "------------------------------------------\n";
    std::cout << "Adding a new employee type now only requires creating a\n";
    std::cout << "new class, rather than modifying the core pay calculation logic.\n";

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
