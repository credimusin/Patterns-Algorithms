#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

/**
 * Prototype Pattern
 * 
 * Concept:
 * Prototype pattern specifies the kinds of objects to create using a prototypical 
 * instance, and creates new objects by copying this prototype.
 * 
 * Components:
 * - Prototype: Interface for cloning itself.
 * - ConcretePrototype: Implements cloning by copying itself.
 * - Client: Creates a new object by asking a prototype to clone itself.
 */

// Prototype Interface
class Shape {
public:
    virtual ~Shape() {}
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
    virtual void setInfo(const std::string& info) = 0;
};

// Concrete Prototypes
class Circle : public Shape {
private:
    std::string info;
    int radius;
public:
    Circle(int r) : radius(r), info("Circle") {}
    
    // Copy constructor used for cloning
    Circle(const Circle& other) : radius(other.radius), info(other.info + " (clone)") {}

    std::unique_ptr<Shape> clone() const override {
        std::cout << "    [Prototype] Cloning Circle with radius " << radius << ".\n";
        return std::make_unique<Circle>(*this);
    }

    void draw() const override {
        std::cout << "    Drawing: " << info << " with radius " << radius << ".\n";
    }

    void setInfo(const std::string& new_info) override {
        info = new_info;
    }
};

class Rectangle : public Shape {
private:
    std::string info;
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h), info("Rectangle") {}

    // Copy constructor used for cloning
    Rectangle(const Rectangle& other) : width(other.width), height(other.height), info(other.info + " (clone)") {}

    std::unique_ptr<Shape> clone() const override {
        std::cout << "    [Prototype] Cloning Rectangle " << width << "x" << height << ".\n";
        return std::make_unique<Rectangle>(*this);
    }

    void draw() const override {
        std::cout << "    Drawing: " << info << " " << width << "x" << height << ".\n";
    }

    void setInfo(const std::string& new_info) override {
        info = new_info;
    }
};

// Prototype Registry (Optional, often used with Prototype)
class ShapeRegistry {
private:
    std::unordered_map<std::string, std::unique_ptr<Shape>> prototypes;
public:
    void addPrototype(const std::string& key, std::unique_ptr<Shape> s) {
        prototypes[key] = std::move(s);
    }

    std::unique_ptr<Shape> create(const std::string& key) {
        if (prototypes.count(key)) {
            return prototypes[key]->clone();
        }
        return nullptr;
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "          PROTOTYPE INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: A graphics editor with a registry of pre-configured shapes.\n";
    std::cout << "Instead of creating shapes from scratch, we clone existing ones.\n\n";

    ShapeRegistry registry;
    registry.addPrototype("red_circle", std::make_unique<Circle>(10));
    registry.addPrototype("blue_rect", std::make_unique<Rectangle>(20, 30));

    std::cout << "(Press Enter to clone the 'red_circle' prototype)";
    std::cin.get();

    {
        std::cout << ">>> Client: Requesting a circle clone from registry...\n";
        auto shape1 = registry.create("red_circle");
        shape1->draw();

        std::cout << "\n    Modifying the clone's info...\n";
        shape1->setInfo("Modified Red Circle");
        shape1->draw();
    }

    std::cout << "\n(Press Enter to clone the 'blue_rect' prototype)";
    std::cin.get();

    {
        std::cout << ">>> Client: Requesting a rectangle clone from registry...\n";
        auto shape2 = registry.create("blue_rect");
        shape2->draw();
    }

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- Cloning avoids the cost of complex initialization.\n";
    std::cout << "- The client code is decoupled from the concrete classes being instantiated.\n";
    std::cout << "- It's a great way to store and reuse 'template' objects.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
