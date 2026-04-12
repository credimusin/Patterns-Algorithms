#include <iostream>
#include <string>
#include <vector>

/**
 * ActiveRecord Pattern
 * 
 * Intent:
 * An object that wraps a row in a database table, encapsulates database access, 
 * and adds domain logic on that data.
 * 
 * Components:
 * - UserRecord: Represents a row in the 'Users' table and provides CRUD methods (Save, Delete, Update).
 */

class UserRecord {
public:
    UserRecord(int id, std::string name, std::string email) 
        : id(id), name(name), email(email) {}

    // Static finder (part of AR)
    static UserRecord findById(int id) {
        std::cout << "    [Database] Finding user with ID: " << id << "\n";
        return UserRecord(id, "John Doe", "john@example.com");
    }

    // Instance method to save (inserts or updates)
    void save() {
        std::cout << "    [Database] SAVING user: " << name << " (ID: " << id << ")\n";
    }

    // Instance method to delete
    void remove() {
        std::cout << "    [Database] DELETING user: " << name << " (ID: " << id << ")\n";
    }

    // Domain logic
    void updateEmail(const std::string& newEmail) {
        std::cout << "    [Domain] Updating email for " << name << " from " << email << " to " << newEmail << "\n";
        email = newEmail;
    }

    void display() const {
        std::cout << "    [UserRecord] ID: " << id << ", Name: " << name << ", Email: " << email << "\n";
    }

private:
    int id;
    std::string name;
    std::string email;
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "         ACTIVE RECORD PATTERN\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: The object handles both its data and its database persistence.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    std::cout << "1. Finding a user in the database.\n";
    UserRecord user = UserRecord::findById(101);
    user.display();
    std::cin.get();

    std::cout << "2. Modifying the user record and saving changes.\n";
    user.updateEmail("john.updated@example.com");
    user.save(); // Persistence is handled by the object itself
    std::cin.get();

    std::cout << "3. Deleting the user record.\n";
    user.remove();

    std::cout << "\n[✓] ActiveRecord is simple and ties data directly to its storage logic.\n";
    std::cout << "==========================================\n";

    return 0;
}
