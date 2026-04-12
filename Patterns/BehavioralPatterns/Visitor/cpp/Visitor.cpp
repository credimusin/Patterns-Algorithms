#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * Visitor Design Pattern
 * 
 * Intent:
 * Lets you separate algorithms from the objects on which they operate.
 * 
 * Components:
 * - Element Interface: Declares an accept() method that takes the 
 *   visitor interface as an argument.
 * - Concrete Elements: Implement the accept() method.
 * - Visitor Interface: Declares a set of visiting methods for each 
 *   concrete element class.
 * - Concrete Visitors: Implement several versions of the same 
 *   algorithm, tailored for all concrete element classes.
 */

// Forward declarations
class Circle;
class Rectangle;

// Visitor Interface
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visitCircle(const Circle& c) = 0;
    virtual void visitRectangle(const Rectangle& r) = 0;
};

// Element Interface
class Shape {
public:
    virtual ~Shape() = default;
    virtual void accept(Visitor& v) const = 0;
};

// Concrete Elements
class Circle : public Shape {
    float radius;
public:
    Circle(float r) : radius(r) {}
    float getRadius() const { return radius; }

    void accept(Visitor& v) const override {
        v.visitCircle(*this);
    }
};

class Rectangle : public Shape {
    float width, height;
public:
    Rectangle(float w, float h) : width(w), height(h) {}
    float getWidth() const { return width; }
    float getHeight() const { return height; }

    void accept(Visitor& v) const override {
        v.visitRectangle(*this);
    }
};

// Concrete Visitor 1: Area Calculator
class AreaVisitor : public Visitor {
public:
    void visitCircle(const Circle& c) override {
        float area = 3.14159f * c.getRadius() * c.getRadius();
        std::cout << "    [AreaVisitor] Circle area: " << area << "\n";
    }

    void visitRectangle(const Rectangle& r) override {
        float area = r.getWidth() * r.getHeight();
        std::cout << "    [AreaVisitor] Rectangle area: " << area << "\n";
    }
};

// Concrete Visitor 2: X-Ray (JSON) Exporter
class ExportVisitor : public Visitor {
public:
    void visitCircle(const Circle& c) override {
        std::cout << "    [ExportVisitor] Exporting Circle: { \"radius\": " << c.getRadius() << " }\n";
    }

    void visitRectangle(const Rectangle& r) override {
        std::cout << "    [ExportVisitor] Exporting Rectangle: { \"w\": " << r.getWidth() 
                  << ", \"h\": " << r.getHeight() << " }\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "            VISITOR INTERACTIVE\n";
    std::cout << "==========================================\n";

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0f));
    shapes.push_back(std::make_unique<Rectangle>(4.0f, 6.0f));

    std::cout << "Created a collection of shapes (1 Circle, 1 Rectangle).\n\n";

    std::cout << "--- Action 1: Calculate Areas ---\n";
    AreaVisitor areaCalc;
    for (const auto& shape : shapes) {
        shape->accept(areaCalc);
    }
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 2: Export to JSON ---\n";
    ExportVisitor exporter;
    for (const auto& shape : shapes) {
        shape->accept(exporter);
    }
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\nVisitor Pattern demonstration complete.\n";
    return 0;
}
