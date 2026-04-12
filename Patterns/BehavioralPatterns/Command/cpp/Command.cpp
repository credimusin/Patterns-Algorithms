#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>

/**
 * Command Design Pattern
 * 
 * Intent:
 * Turns a request into a stand-alone object that contains all information 
 * about the request. This transformation lets you pass requests as a 
 * method arguments, delay or queue a request's execution, and support 
 * undoable operations.
 * 
 * Components:
 * - Command: Interface that declares a method for executing a command.
 * - ConcreteCommand: Implements the execution by calling operations on the Receiver.
 * - Receiver: The object that performs the actual work.
 * - Invoker: The object that triggers the command.
 * - Client: Creates and configures commands.
 */

// Receiver
class Light {
    bool on = false;
public:
    void turnOn() {
        on = true;
        std::cout << "    [Light] The light is now ON.\n";
    }
    void turnOff() {
        on = false;
        std::cout << "    [Light] The light is now OFF.\n";
    }
};

// Command Interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Concrete Commands
class LightOnCommand : public Command {
    std::shared_ptr<Light> light;
public:
    LightOnCommand(std::shared_ptr<Light> l) : light(l) {}
    void execute() override {
        light->turnOn();
    }
    void undo() override {
        light->turnOff();
    }
};

class LightOffCommand : public Command {
    std::shared_ptr<Light> light;
public:
    LightOffCommand(std::shared_ptr<Light> l) : light(l) {}
    void execute() override {
        light->turnOff();
    }
    void undo() override {
        light->turnOn();
    }
};

// Invoker
class RemoteControl {
    std::stack<std::shared_ptr<Command>> history;
public:
    void submit(std::shared_ptr<Command> cmd) {
        cmd->execute();
        history.push(cmd);
    }
    void undoLast() {
        if (!history.empty()) {
            std::cout << "    [Remote] Undoing last command...\n";
            history.top()->undo();
            history.pop();
        } else {
            std::cout << "    [Remote] No commands to undo.\n";
        }
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "          COMMAND INTERACTIVE\n";
    std::cout << "==========================================\n";

    auto light = std::make_shared<Light>();
    auto lightOn = std::make_shared<LightOnCommand>(light);
    auto lightOff = std::make_shared<LightOffCommand>(light);

    RemoteControl remote;

    std::cout << "--- Action 1: Turn Light ON ---\n";
    remote.submit(lightOn);
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 2: Turn Light OFF ---\n";
    remote.submit(lightOff);
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 3: Undo Last (OFF -> ON) ---\n";
    remote.undoLast();
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 4: Undo Last (ON -> OFF) ---\n";
    remote.undoLast();
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\nCommand Pattern demonstration complete.\n";
    return 0;
}
