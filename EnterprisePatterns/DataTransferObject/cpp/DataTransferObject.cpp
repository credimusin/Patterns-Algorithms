#include <iostream>
#include <string>
#include <vector>

/**
 * Data Transfer Object (DTO) Pattern
 * 
 * Intent:
 * An object that carries data between processes to reduce the number of method calls.
 * Often used to aggregate data from multiple entities into one flat structure.
 * 
 * Components:
 * - UserDTO: Simple structure to hold user data (no business logic).
 * - UserWebService: Service that returns a DTO to minimize remote calls.
 */

struct UserDTO {
    int id;
    std::string fullName;
    std::string email;
    std::string role;
};

class UserWebService {
public:
    // Returns a single object with all needed data, instead of 4 separate calls.
    UserDTO getUserDetails(int userId) {
        std::cout << "    [WebService] Remote call: Fetching aggregated data for user " << userId << "\n";
        return UserDTO{userId, "John Doe", "john@example.com", "Admin"};
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "       DATA TRANSFER OBJECT (DTO)\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: Bundle data into a single object for transport.\n";
    std::cout << "This reduces network latency by minimizing round trips.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    UserWebService service;

    std::cout << "1. Fetching user details (one call, all data returned).\n";
    UserDTO dto = service.getUserDetails(1);
    std::cin.get();

    std::cout << "2. Displaying user information from the DTO.\n";
    std::cout << "   - ID: " << dto.id << "\n";
    std::cout << "   - Name: " << dto.fullName << "\n";
    std::cout << "   - Email: " << dto.email << "\n";
    std::cout << "   - Role: " << dto.role << "\n";

    std::cout << "\n[✓] DTO simplifies communication between different system layers.\n";
    std::cout << "==========================================\n";

    return 0;
}
