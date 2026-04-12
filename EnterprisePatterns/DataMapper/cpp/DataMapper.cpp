#include <iostream>
#include <string>
#include <memory>

/**
 * Data Mapper Pattern
 * 
 * Intent:
 * A layer of mappers that moves data between objects and a database while 
 * keeping them independent of each other and the mapper itself.
 * 
 * Components:
 * - User: Domain object (no knowledge of persistence).
 * - UserMapper: Handles moving User objects to/from the database.
 */

class User {
public:
    User(int id, std::string name) : id(id), name(name) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

private:
    int id;
    std::string name;
};

class UserMapper {
public:
    // Move user data TO database
    void insert(const User& user) {
        std::cout << "    [DataMapper] Writing " << user.getName() << " (ID: " << user.getId() << ") to 'users' table...\n";
    }

    // Move user data FROM database
    std::unique_ptr<User> findById(int id) {
        std::cout << "    [DataMapper] Executing: SELECT * FROM users WHERE id = " << id << "\n";
        // Simulate database result
        return std::make_unique<User>(id, "Jane Doe");
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "         DATA MAPPER PATTERN\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: Separating domain objects from their persistence logic.\n";
    std::cout << "The 'User' object knows nothing about the database.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    UserMapper mapper;

    std::cout << "1. Finding a user by ID.\n";
    auto user = mapper.findById(42);
    std::cout << "   - User loaded: " << user->getName() << " (ID: " << user->getId() << ")\n";
    std::cin.get();

    std::cout << "2. Modifying the User domain object (memory-only change).\n";
    user->setName("Jane Smith");
    std::cout << "   - User updated in memory to: " << user->getName() << "\n";
    std::cin.get();

    std::cout << "3. Using the mapper to SAVE the modified object.\n";
    mapper.insert(*user);

    std::cout << "\n[✓] Data Mapper decouples domain objects from the database structure.\n";
    std::cout << "==========================================\n";

    return 0;
}
