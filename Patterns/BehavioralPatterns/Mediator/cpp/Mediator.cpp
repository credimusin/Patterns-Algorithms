#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * Mediator Design Pattern
 * 
 * Intent:
 * Reduces chaotic dependencies between objects. The pattern restricts 
 * direct communications between the objects and forces them to 
 * collaborate only via a mediator object.
 * 
 * Components:
 * - Mediator: Interface that declares a method used by components 
 *   to notify the mediator about events.
 * - Concrete Mediator: Implements the interface and coordinates the 
 *   components by calling their methods in response to events.
 * - Components (Colleagues): Base class for components that reference 
 *   the mediator.
 */

// Forward declaration
class Mediator;

// Component Base
class Colleague {
protected:
    Mediator* mediator;
    std::string name;

public:
    Colleague(Mediator* m, std::string n) : mediator(m), name(n) {}
    virtual ~Colleague() = default;
    virtual void receive(std::string from, std::string message) = 0;
    std::string getName() { return name; }
};

// Mediator Interface
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void notify(Colleague* sender, std::string message) = 0;
};

// Concrete Components
class User : public Colleague {
public:
    User(Mediator* m, std::string n) : Colleague(m, n) {}

    void send(std::string message) {
        std::cout << "    [" << name << "] Sends: " << message << "\n";
        mediator->notify(this, message);
    }

    void receive(std::string from, std::string message) override {
        std::cout << "    [" << name << "] Received from " << from << ": " << message << "\n";
    }
};

// Concrete Mediator
class ChatRoom : public Mediator {
    std::vector<Colleague*> users;

public:
    void addUser(Colleague* u) {
        users.push_back(u);
    }

    void notify(Colleague* sender, std::string message) override {
        std::cout << "    [ChatRoom] Relaying message from " << sender->getName() << "...\n";
        for (auto user : users) {
            // Don't send the message back to the sender
            if (user != sender) {
                user->receive(sender->getName(), message);
            }
        }
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "           MEDIATOR INTERACTIVE\n";
    std::cout << "==========================================\n";

    ChatRoom chat;

    User alice(&chat, "Alice");
    User bob(&chat, "Bob");
    User charlie(&chat, "Charlie");

    chat.addUser(&alice);
    chat.addUser(&bob);
    chat.addUser(&charlie);

    std::cout << "Chatroom setup with Alice, Bob, and Charlie.\n\n";

    std::cout << "--- Action 1: Alice sends a message ---\n";
    alice.send("Hi everyone!");
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 2: Bob responds ---\n";
    bob.send("Hey Alice, how are you?");
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 3: Charlie sends a message ---\n";
    charlie.send("I'm late to the party!");
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\nMediator Pattern demonstration complete.\n";
    return 0;
}
