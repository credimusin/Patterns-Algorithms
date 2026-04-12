#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/**
 * Single Responsibility Principle (SRP)
 * 
 * Intent:
 * A class should have one, and only one, reason to change.
 * This means a class should only have one job or responsibility.
 * 
 * Components:
 * - UserProfile: Handles user data.
 * - UserPersistence: Handles saving/loading user data (separating storage from data model).
 * - UserReport: Handles formatting user data for display.
 */

class UserProfile {
public:
    UserProfile(std::string name, std::string email) : name(name), email(email) {}

    std::string getName() const { return name; }
    std::string getEmail() const { return email; }

private:
    std::string name;
    std::string email;
};

class UserPersistence {
public:
    void saveToFile(const UserProfile& user) {
        std::cout << "    [Persistence] Saving user " << user.getName() << " to database/file...\n";
        // In a real app, this would write to a file or database.
    }
};

class UserReport {
public:
    void generateReport(const UserProfile& user) {
        std::cout << "\n    [Report] --- User Report ---\n";
        std::cout << "    Name: " << user.getName() << "\n";
        std::cout << "    Email: " << user.getEmail() << "\n";
        std::cout << "    ---------------------------\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "   SINGLE RESPONSIBILITY PRINCIPLE (SRP)\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: A class should have one reason to change.\n";
    std::cout << "In this example, we split User data, Persistence, and Reporting.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n1. Creating a UserProfile object (Handles data only).\n";
    UserProfile user("Alice Smith", "alice@example.com");
    std::cout << "   - User Profile created for: " << user.getName() << "\n";
    std::cin.get();

    std::cout << "2. Using UserPersistence (Handles storage only).\n";
    UserPersistence persistence;
    persistence.saveToFile(user);
    std::cin.get();

    std::cout << "3. Using UserReport (Handles formatting only).\n";
    UserReport report;
    report.generateReport(user);

    std::cout << "\n[✓] SRP allows us to change how we SAVE or REPORT without affecting the UserProfile class itself.\n";
    std::cout << "==========================================\n";

    return 0;
}
