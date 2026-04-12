#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

/**
 * Dependency Injection Container Pattern
 * 
 * Intent:
 * A container that manages the creation and injection of dependencies 
 * into high-level modules, reducing coupling.
 * 
 * Components:
 * - IDatabase: Abstraction.
 * - MySqlDatabase: Concrete service.
 * - AppConfig: High-level service requiring a database.
 * - DI_Container: Central registry for service creation.
 */

class IDatabase {
public:
    virtual ~IDatabase() = default;
    virtual void connect() = 0;
};

class MySqlDatabase : public IDatabase {
public:
    void connect() override {
        std::cout << "    [MySqlDatabase] Connecting to MySQL...\n";
    }
};

class AppConfig {
public:
    AppConfig(std::shared_ptr<IDatabase> db) : db(db) {}
    void start() {
        std::cout << "    [AppConfig] Starting application...\n";
        db->connect();
    }
private:
    std::shared_ptr<IDatabase> db;
};

class DIContainer {
public:
    // Simple container logic to demonstrate manual wiring vs DI
    void registerDatabase(std::shared_ptr<IDatabase> db) {
        services["database"] = db;
    }

    std::shared_ptr<AppConfig> buildAppConfig() {
        std::cout << "    [DIContainer] Creating AppConfig and injecting Database dependency.\n";
        return std::make_shared<AppConfig>(std::static_pointer_cast<IDatabase>(services["database"]));
    }

private:
    std::unordered_map<std::string, std::shared_ptr<void>> services;
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "      DEPENDENCY INJECTION CONTAINER\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: Centralize service creation and dependency resolution.\n";
    std::cout << "The application doesn't know HOW to create its dependencies.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    DIContainer container;

    std::cout << "1. Registering services in the container.\n";
    container.registerDatabase(std::make_shared<MySqlDatabase>());
    std::cin.get();

    std::cout << "2. Requesting AppConfig from the container.\n";
    auto app = container.buildAppConfig();
    std::cin.get();

    std::cout << "3. Running the application.\n";
    app->start();

    std::cout << "\n[✓] DI Containers help manage complex object graphs and decoupling.\n";
    std::cout << "==========================================\n";

    return 0;
}
