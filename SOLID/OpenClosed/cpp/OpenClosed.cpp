#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * Open/Closed Principle (OCP)
 * 
 * Intent:
 * Software entities (classes, modules, functions, etc.) should be open for extension, 
 * but closed for modification.
 * 
 * Components:
 * - Shape: Abstract base class (closed for modification, open for extension).
 * - Circle, Square: Concrete implementations (extensions).
 * - AreaCalculator: Operates on Shape abstraction.
 */

class Shape {
public:
    virtual ~Shape() = default;
    virtual double calculateArea() const = 0;
    virtual std::string getName() const = 0;
};

class Circle : public Shape {
public:
    Circle(double radius) : radius(radius) {}
    double calculateArea() const override { return 3.14159 * radius * radius; }
    std::string getName() const override { return "Circle"; }
private:
    double radius;
};

class Square : public Shape {
public:
    Square(double side) : side(side) {}
    double calculateArea() const override { return side * side; }
    std::string getName() const override { return "Square"; }
private:
    double side;
};

// We can add a NEW shape without modifying AreaCalculator or Shape!
class Triangle : public Shape {
public:
    Triangle(double base, double height) : base(base), height(height) {}
    double calculateArea() const override { return 0.5 * base * height; }
    std::string getName() const override { return "Triangle"; }
private:
    double base, height;
};

class AreaCalculator {
public:
    void printArea(const Shape& shape) {
        std::cout << "    [AreaCalculator] Calculating area for: " << shape.getName() << "\n";
        std::cout << "    Result: " << shape.calculateArea() << "\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "       OPEN/CLOSED PRINCIPLE (OCP)\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: Open for extension, closed for modification.\n";
    std::cout << "In this example, AreaCalculator works with the Shape abstraction.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    AreaCalculator calculator;

    std::cout << "\n1. Using Circle and Square (existing extensions).\n";
    Circle circle(5.0);
    Square square(4.0);

    calculator.printArea(circle);
    calculator.printArea(square);
    std::cin.get();

    std::cout << "\n2. Adding a Triangle WITHOUT modifying AreaCalculator.\n";
    std::cout << "   - This demonstrates extension without modification.\n";
    Triangle triangle(3.0, 6.0);
    calculator.printArea(triangle);

    std::cout << "\n[✓] OCP allows us to add new shapes without touching existing code.\n";
    std::cout << "==========================================\n";

    return 0;
}
