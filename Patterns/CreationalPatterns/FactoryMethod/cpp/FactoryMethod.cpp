#include <iostream>
#include <string>
#include <memory>
#include <vector>

/**
 * Factory Method Pattern
 * 
 * Concept:
 * Factory Method defines an interface for creating an object, but let subclasses 
 * decide which class to instantiate. It lets a class defer instantiation to subclasses.
 * 
 * Components:
 * - Product: Interface for objects the factory method creates.
 * - ConcreteProduct: Implementation of the Product interface.
 * - Creator: Declares the factory method, which returns an object of type Product.
 * - ConcreteCreator: Overrides the factory method to return an instance of a ConcreteProduct.
 */

// Product
class Transport {
public:
    virtual ~Transport() {}
    virtual std::string deliver() const = 0;
};

// Concrete Products
class Truck : public Transport {
public:
    std::string deliver() const override {
        return "Delivering by land in a box. [Truck]";
    }
};

class Ship : public Transport {
public:
    std::string deliver() const override {
        return "Delivering by sea in a container. [Ship]";
    }
};

// Creator
class Logistics {
public:
    virtual ~Logistics() {}
    
    // The Factory Method
    virtual std::unique_ptr<Transport> createTransport() const = 0;

    void planDelivery() const {
        std::cout << ">>> Logistics: Planning delivery...\n";
        std::unique_ptr<Transport> transport = createTransport();
        std::cout << "    Action: " << transport->deliver() << "\n";
    }
};

// Concrete Creators
class RoadLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() const override {
        std::cout << "    [FactoryMethod] RoadLogistics creating a Truck.\n";
        return std::make_unique<Truck>();
    }
};

class SeaLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() const override {
        std::cout << "    [FactoryMethod] SeaLogistics creating a Ship.\n";
        return std::make_unique<Ship>();
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "       FACTORY METHOD INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: A logistics company needs to deliver goods.\n";
    std::cout << "Depending on the context, they use Road or Sea logistics.\n\n";

    std::cout << "(Press Enter to use Road Logistics)";
    std::cin.get();

    {
        std::cout << "[!] Initializing Road Logistics...\n";
        std::unique_ptr<Logistics> logistics = std::make_unique<RoadLogistics>();
        logistics->planDelivery();
    }

    std::cout << "\n(Press Enter to use Sea Logistics)";
    std::cin.get();

    {
        std::cout << "[!] Initializing Sea Logistics...\n";
        std::unique_ptr<Logistics> logistics = std::make_unique<SeaLogistics>();
        logistics->planDelivery();
    }

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- The creator (Logistics) doesn't know which concrete product it will create.\n";
    std::cout << "- Subclasses (Road/Sea) override the factory method to return different products.\n";
    std::cout << "- It follows the Open/Closed Principle: you can add new transport types without breaking client code.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
