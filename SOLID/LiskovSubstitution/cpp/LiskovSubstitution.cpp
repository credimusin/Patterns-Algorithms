#include <iostream>
#include <string>
#include <vector>

/**
 * Liskov Substitution Principle (LSP)
 * 
 * Intent:
 * Objects in a program should be replaceable with instances of their subtypes 
 * without altering the correctness of that program.
 * 
 * Components:
 * - Bird: Base class with general bird behavior.
 * - FlyingBird: Subtype for birds that can fly.
 * - NonFlyingBird: Subtype for birds that cannot fly.
 * - Duck: Concrete FlyingBird (LSP compliant).
 * - Penguin: Concrete NonFlyingBird (LSP compliant).
 */

class Bird {
public:
    virtual ~Bird() = default;
    virtual std::string getName() const = 0;
};

class FlyingBird : public Bird {
public:
    virtual void fly() const {
        std::cout << "    [Fly] I am flying!\n";
    }
};

class NonFlyingBird : public Bird {
public:
    virtual void walk() const {
        std::cout << "    [Walk] I am walking!\n";
    }
};

class Duck : public FlyingBird {
public:
    std::string getName() const override { return "Duck"; }
};

class Penguin : public NonFlyingBird {
public:
    std::string getName() const override { return "Penguin"; }
};

void makeFlyingBirdFly(const FlyingBird& bird) {
    std::cout << "    Attempting to make " << bird.getName() << " fly...\n";
    bird.fly();
}

int main() {
    std::cout << "==========================================\n";
    std::cout << "     LISKOV SUBSTITUTION PRINCIPLE (LSP)\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: Subtypes must be substitutable for their base types.\n";
    std::cout << "Instead of forcing Penguins to fly, we separate Flying and Non-Flying birds.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    std::cout << "1. Creating a Duck (A FlyingBird).\n";
    Duck duck;
    makeFlyingBirdFly(duck);
    std::cin.get();

    std::cout << "2. Creating a Penguin (A NonFlyingBird).\n";
    Penguin penguin;
    std::cout << "   - Penguin is a Bird, but NOT a FlyingBird.\n";
    std::cout << "   - This prevents us from incorrectly calling .fly() on a Penguin.\n";
    penguin.walk();

    std::cout << "\n[✓] LSP ensures that inheritance hierarchies are conceptually sound.\n";
    std::cout << "==========================================\n";

    return 0;
}
