#include <iostream>
#include <string>

/**
 * Hide Delegate Refactoring
 * 
 * Concept:
 * Hide Delegate is a refactoring technique that helps follow the "Law of Demeter"
 * (don't talk to strangers). It reduces coupling between objects by hiding 
 * access to another object's collaborator.
 * 
 * Why?
 * - Reduces the number of objects a client needs to know about.
 * - If the structure of the internal collaborator changes, only the 
 *   containing class needs adjustment, not every client.
 */

// A simple Department class
class Department {
    std::string name;
    std::string manager;
public:
    Department(std::string n, std::string m) : name(n), manager(m) {}
    std::string getManager() const { return manager; }
};

// A Person class that belongs to a Department
class Person {
    Department* department;
public:
    Person(Department* dept) : department(dept) {}

    // --- BEFORE REFACTORING ---
    // The client would have to do: person->getDepartment()->getManager()
    Department* getDepartment() const { return department; }

    // --- AFTER REFACTORING ---
    // The client can simply do: person->getManager()
    std::string getManager() const {
        return department->getManager();
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        HIDE DELEGATE REFACTORING\n";
    std::cout << "==========================================\n";

    Department* engineering = new Department("Engineering", "Sarah Connor");
    Person* employee = new Person(engineering);

    std::cout << "1. Using delegate explicitly (Before Refactoring):\n";
    std::cout << "    [Client]: I need the manager's name for this person.\n";
    std::cout << "    [Client]: employee->getDepartment()->getManager()\n";
    std::cout << "    Manager: " << employee->getDepartment()->getManager() << "\n";

    std::cout << "\n    (Notice how the client must know about both Person AND Department.)\n";
    std::cout << "    (Press Enter to see the Hidden Delegate in action...)";
    std::cin.get();

    std::cout << "2. Using Hidden Delegate (After Refactoring):\n";
    std::cout << "    [Client]: I need the manager's name for this person.\n";
    std::cout << "    [Client]: employee->getManager()\n";
    std::cout << "    Manager: " << employee->getManager() << "\n";

    std::cout << "------------------------------------------\n";
    std::cout << "By hiding the 'Department' delegate inside 'Person', we've\n";
    std::cout << "simplified the interface for the client and reduced coupling.\n";

    delete employee;
    delete engineering;

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
