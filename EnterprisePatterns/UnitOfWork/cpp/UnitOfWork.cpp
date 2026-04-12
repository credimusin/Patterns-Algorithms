#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * Unit of Work Pattern
 * 
 * Intent:
 * Maintains a list of objects affected by a business transaction and 
 * coordinates the writing out of changes.
 * 
 * Components:
 * - Entity: Domain object.
 * - UnitOfWork: Tracks New, Dirty (changed), and Removed objects, then commits them.
 */

class Entity {
public:
    Entity(int id, std::string name) : id(id), name(name) {}
    int getId() const { return id; }
    std::string getName() const { return name; }
private:
    int id;
    std::string name;
};

class UnitOfWork {
public:
    void registerNew(const Entity& e) {
        std::cout << "    [UoW] Tracking NEW: " << e.getName() << "\n";
        newEntities.push_back(e);
    }

    void registerDirty(const Entity& e) {
        std::cout << "    [UoW] Tracking DIRTY (modified): " << e.getName() << "\n";
        dirtyEntities.push_back(e);
    }

    void registerRemoved(const Entity& e) {
        std::cout << "    [UoW] Tracking REMOVED: " << e.getName() << "\n";
        removedEntities.push_back(e);
    }

    void commit() {
        std::cout << "\n    --- STARTING COMMIT ---\n";
        for (auto& e : newEntities) 
            std::cout << "    [DB] INSERT INTO table VALUES (" << e.getName() << ")\n";
        for (auto& e : dirtyEntities) 
            std::cout << "    [DB] UPDATE table SET ... WHERE id = " << e.getId() << "\n";
        for (auto& e : removedEntities) 
            std::cout << "    [DB] DELETE FROM table WHERE id = " << e.getId() << "\n";
        
        newEntities.clear();
        dirtyEntities.clear();
        removedEntities.clear();
        std::cout << "    --- COMMIT SUCCESSFUL ---\n";
    }

private:
    std::vector<Entity> newEntities;
    std::vector<Entity> dirtyEntities;
    std::vector<Entity> removedEntities;
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "          UNIT OF WORK PATTERN\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: Batch all database changes into a single transaction.\n";
    std::cout << "This avoids multiple database trips and ensures atomicity.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    UnitOfWork uow;

    std::cout << "1. Making various changes in memory.\n";
    uow.registerNew(Entity(1, "Alice"));
    uow.registerDirty(Entity(2, "Bob"));
    uow.registerRemoved(Entity(3, "Charlie"));
    std::cin.get();

    std::cout << "2. Committing the changes (one transaction).\n";
    uow.commit();

    std::cout << "\n[✓] Unit of Work manages complex transactions and optimizes DB access.\n";
    std::cout << "==========================================\n";

    return 0;
}
