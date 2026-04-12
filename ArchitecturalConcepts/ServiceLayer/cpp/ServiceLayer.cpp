#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * Service Layer Pattern
 * 
 * Concept:
 * The service layer is an architectural pattern that defines a set of interfaces for 
 * business logic. It separates the presentation (UI) or delivery (Controller) 
 * logic from the core business rules and data access logic.
 * 
 * Components:
 * - Controller/UI: Interacts with the user.
 * - Service: Contains the main business logic (e.g., calculations, validation).
 * - Repository: Handles data persistence (e.g., database, file storage).
 * - Domain Model: Represents the core data entity.
 */

struct User {
    int id;
    std::string name;
    std::string email;
};

// Data Access Layer (Repository)
class UserRepository {
public:
    void save(const User& user) {
        std::cout << "[Repository] Saving user '" << user.name << "' to the database.\n";
    }
};

// Business Logic Layer (Service)
class UserService {
    UserRepository repo;
public:
    bool registerUser(int id, std::string name, std::string email) {
        std::cout << "[Service] Validating user data...\n";
        
        // Simple business rule validation
        if (email.find('@') == std::string::npos) {
            std::cout << "    [!] Invalid email format: " << email << "\n";
            return false;
        }

        std::cout << "    [✓] User data is valid. Proceeding to save.\n";
        std::cout << "    (Press Enter to continue to Repository...)";
        std::cin.get();

        User newUser{id, name, email};
        repo.save(newUser);
        return true;
    }
};

// Presentation Layer (Controller/UI)
class UserController {
    UserService service;
public:
    void onCreateUser() {
        std::cout << "[Controller] User creation request received.\n";
        
        std::string name = "John Doe";
        std::string email = "john@example.com";
        
        std::cout << "    Calling Service: registerUser(" << name << ", " << email << ")\n";
        std::cout << "    (Press Enter to continue to Service...)";
        std::cin.get();

        if (service.registerUser(1, name, email)) {
            std::cout << "[Controller] User created successfully!\n";
        } else {
            std::cout << "[Controller] User creation failed.\n";
        }
    }

    void onInvalidUser() {
        std::cout << "\n[Controller] Request with invalid data received.\n";
        std::string email = "invalid_email";
        
        if (service.registerUser(2, "Jane Doe", email)) {
            std::cout << "[Controller] User created successfully!\n";
        } else {
            std::cout << "[Controller] User creation failed.\n";
        }
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        SERVICE LAYER PATTERN INTERACTIVE\n";
    std::cout << "==========================================\n";

    UserController controller;
    
    std::cout << "Scenario 1: Valid User Registration\n";
    controller.onCreateUser();

    std::cout << "------------------------------------------\n";
    std::cout << "Scenario 2: Invalid User Registration\n";
    controller.onInvalidUser();

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
