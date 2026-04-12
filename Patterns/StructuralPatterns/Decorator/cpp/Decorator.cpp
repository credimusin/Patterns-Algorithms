#include <iostream>
#include <string>
#include <memory>

/**
 * Decorator Pattern
 * 
 * Concept:
 * Decorator pattern allows behavior to be added to an individual object, 
 * either statically or dynamically, without affecting the behavior of other 
 * objects from the same class.
 * 
 * Components:
 * - Component: Interface for objects that can have responsibilities added to them.
 * - ConcreteComponent: The original object to which new responsibilities can be added.
 * - Decorator: Interface for decorating components, maintains a reference to a Component.
 * - ConcreteDecorator: Adds responsibilities to the component.
 */

// Component
class Coffee {
public:
    virtual ~Coffee() {}
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
};

// Concrete Component
class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override { return "Simple Coffee"; }
    double cost() const override { return 1.0; }
};

// Decorator
class CoffeeDecorator : public Coffee {
protected:
    std::shared_ptr<Coffee> coffee;
public:
    CoffeeDecorator(std::shared_ptr<Coffee> c) : coffee(c) {}
    std::string getDescription() const override { return coffee->getDescription(); }
    double cost() const override { return coffee->cost(); }
};

// Concrete Decorators
class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::shared_ptr<Coffee> c) : CoffeeDecorator(c) {}
    
    std::string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }
    
    double cost() const override {
        return coffee->cost() + 0.5;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::shared_ptr<Coffee> c) : CoffeeDecorator(c) {}
    
    std::string getDescription() const override {
        return coffee->getDescription() + ", Sugar";
    }
    
    double cost() const override {
        return coffee->cost() + 0.2;
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "           DECORATOR INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: Ordering a coffee and adding toppings dynamically.\n\n";

    std::shared_ptr<Coffee> myCoffee = std::make_shared<SimpleCoffee>();
    
    std::cout << "(Press Enter to start with a Simple Coffee)";
    std::cin.get();
    
    std::cout << ">>> Current: " << myCoffee->getDescription() << " | Cost: $" << myCoffee->cost() << "\n";

    std::cout << "\n(Press Enter to add Milk)";
    std::cin.get();
    
    myCoffee = std::make_shared<MilkDecorator>(myCoffee);
    std::cout << ">>> Added Milk: " << myCoffee->getDescription() << " | Cost: $" << myCoffee->cost() << "\n";

    std::cout << "\n(Press Enter to add Sugar)";
    std::cin.get();
    
    myCoffee = std::make_shared<SugarDecorator>(myCoffee);
    std::cout << ">>> Added Sugar: " << myCoffee->getDescription() << " | Cost: $" << myCoffee->cost() << "\n";

    std::cout << "\n(Press Enter to add another serving of Milk)";
    std::cin.get();
    
    myCoffee = std::make_shared<MilkDecorator>(myCoffee);
    std::cout << ">>> Added extra Milk: " << myCoffee->getDescription() << " | Cost: $" << myCoffee->cost() << "\n";

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- Decorators wrap a component to add functionality.\n";
    std::cout << "- They have the same interface as the component.\n";
    std::cout << "- You can stack decorators to combine behaviors dynamically.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
