#include <iostream>
#include <string>
#include <mutex>

/**
 * Singleton Pattern
 * 
 * Concept:
 * Singleton ensures that a class has only one instance and provides a global 
 * point of access to it.
 * 
 * Components:
 * - Singleton: A class that manages its own single instance and prevents 
 *   other objects from creating their own instances.
 */

class Database {
private:
    static Database* instance;
    static std::mutex mutex;
    std::string data;

    // Private constructor prevents direct instantiation
    Database(const std::string& name) : data(name) {
        std::cout << ">>> [Singleton] Initializing the Database instance...\n";
    }

public:
    // Delete copy constructor and assignment operator
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    // Static method for getting the single instance
    static Database* getInstance(const std::string& name) {
        // Double-checked locking for thread safety
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr) {
                instance = new Database(name);
            }
        }
        return instance;
    }

    void query(const std::string& sql) {
        std::cout << "    Executing query on [" << data << "]: " << sql << "\n";
    }

    std::string getData() const { return data; }
};

// Initialize static members
Database* Database::instance = nullptr;
std::mutex Database::mutex;

void simulateUser(const std::string& userId, const std::string& dbName) {
    std::cout << "[User " << userId << "] Requesting Database access...\n";
    Database* db = Database::getInstance(dbName);
    db->query("SELECT * FROM users WHERE id = '" + userId + "';");
    std::cout << "[User " << userId << "] DB pointer address: " << db << "\n";
}

int main() {
    std::cout << "==========================================\n";
    std::cout << "          SINGLETON INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: Multiple parts of the application need to use the same database connection.\n\n";

    std::cout << "(Press Enter to request the first instance)";
    std::cin.get();

    simulateUser("Alice", "MainDB");

    std::cout << "\n(Press Enter to request another instance)";
    std::cin.get();

    simulateUser("Bob", "OtherDB"); // Bob tries to use "OtherDB" but will get the same "MainDB" instance

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- The first call creates the instance.\n";
    // Observe that Bob gets the same instance address as Alice and the name is still "MainDB"
    std::cout << "- Subsequent calls return the SAME instance, regardless of parameters.\n";
    std::cout << "- Thread safety is crucial for implementing Singletons in a concurrent environment.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
