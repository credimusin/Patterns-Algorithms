#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * Iterator Design Pattern
 * 
 * Intent:
 * Lets you traverse elements of a collection without exposing its 
 * underlying representation (list, stack, tree, etc.).
 * 
 * Components:
 * - Iterator Interface: Declares methods for traversing (next, hasNext, currentItem).
 * - Concrete Iterator: Implements the traversal algorithm.
 * - Aggregate (Collection) Interface: Declares method for creating an iterator.
 * - Concrete Aggregate: Implements the creation and stores the actual collection.
 */

// Simple Item
struct Item {
    std::string name;
    int price;
};

// Iterator Interface
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

// Aggregate Interface
template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator<T>> createIterator() = 0;
};

// Concrete Iterator for std::vector
class InventoryIterator : public Iterator<Item> {
    const std::vector<Item>& items;
    size_t index = 0;

public:
    InventoryIterator(const std::vector<Item>& i) : items(i) {}

    bool hasNext() override {
        return index < items.size();
    }

    Item next() override {
        return items[index++];
    }
};

// Concrete Aggregate
class Inventory : public Aggregate<Item> {
    std::vector<Item> items;

public:
    void addItem(std::string name, int price) {
        items.push_back({name, price});
    }

    std::unique_ptr<Iterator<Item>> createIterator() override {
        return std::make_unique<InventoryIterator>(items);
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "           ITERATOR INTERACTIVE\n";
    std::cout << "==========================================\n";

    Inventory inventory;
    inventory.addItem("Laptop", 1200);
    inventory.addItem("Mouse", 25);
    inventory.addItem("Keyboard", 75);
    inventory.addItem("Monitor", 300);

    std::cout << "Inventory created with 4 items.\n\n";

    auto iterator = inventory.createIterator();

    std::cout << "--- Starting Traversal ---\n";
    while (iterator->hasNext()) {
        Item current = iterator->next();
        std::cout << "    [Iterator] Current Item: " << current.name 
                  << " ($" << current.price << ")\n";

        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }

    std::cout << "\nEnd of collection reached.\n";
    std::cout << "Iterator Pattern demonstration complete.\n";
    return 0;
}
