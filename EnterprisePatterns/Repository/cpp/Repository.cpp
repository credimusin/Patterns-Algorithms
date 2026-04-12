#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

/**
 * Repository Pattern
 * 
 * Intent:
 * Mediates between the domain and data mapping layers using a collection-like 
 * interface for accessing domain objects.
 * 
 * Components:
 * - User: Domain object.
 * - IUserRepository: Interface for data access.
 * - SqlUserRepository: Concrete implementation for a database.
 */

class User {
public:
    User(int id, std::string name) : id(id), name(name) {}
    int getId() const { return id; }
    std::string getName() const { return name; }
private:
    int id;
    std::string name;
};

class IUserRepository {
public:
    virtual ~IUserRepository() = default;
    virtual void add(const User& user) = 0;
    virtual std::unique_ptr<User> get(int id) = 0;
    virtual std::vector<User> getAll() = 0;
};

class SqlUserRepository : public IUserRepository {
public:
    void add(const User& user) override {
        std::cout << "    [Repo] Executing INSERT INTO users (id, name) VALUES (" << user.getId() << ", '" << user.getName() << "')\n";
        users.push_back(user);
    }

    std::unique_ptr<User> get(int id) override {
        std::cout << "    [Repo] Executing SELECT * FROM users WHERE id = " << id << "\n";
        for (const auto& u : users) {
            if (u.getId() == id) return std::make_unique<User>(u);
        }
        return nullptr;
    }

    std::vector<User> getAll() override {
        std::cout << "    [Repo] Executing SELECT * FROM users\n";
        return users;
    }

private:
    std::vector<User> users;
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "           REPOSITORY PATTERN\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: Treat data storage like an in-memory collection.\n";
    std::cout << "Domain logic works with an interface, not raw SQL.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    SqlUserRepository repo;

    std::cout << "1. Adding users to the repository.\n";
    repo.add(User(1, "Alice"));
    repo.add(User(2, "Bob"));
    std::cin.get();

    std::cout << "2. Retrieving a specific user by ID.\n";
    auto user = repo.get(1);
    if (user) {
        std::cout << "   - Found User: " << user->getName() << "\n";
    }
    std::cin.get();

    std::cout << "3. Listing all users.\n";
    auto allUsers = repo.getAll();
    std::cout << "   - Repository contains " << allUsers.size() << " users.\n";

    std::cout << "\n[✓] Repository abstracts data access away from business logic.\n";
    std::cout << "==========================================\n";

    return 0;
}
