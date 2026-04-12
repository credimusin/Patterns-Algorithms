#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * Memento Design Pattern
 * 
 * Intent:
 * Lets you save and restore the previous state of an object 
 * without revealing the details of its implementation.
 * 
 * Components:
 * - Originator: The object whose state is being saved. It creates a memento 
 *   containing its current state and uses the memento to restore its state.
 * - Memento: A simple object that stores the state of the Originator.
 * - Caretaker: Manages the mementos. It never operates on or examines 
 *   the contents of a memento.
 */

// Memento (State container)
class Memento {
    std::string state;
    friend class Editor; // Only Originator can access the state

    Memento(std::string s) : state(s) {}
    std::string getState() const { return state; }
};

// Originator
class Editor {
    std::string content;

public:
    void type(std::string text) {
        content += text;
        std::cout << "    [Editor] Typed: \"" << text << "\". Current content: \"" << content << "\"\n";
    }

    std::shared_ptr<Memento> save() {
        std::cout << "    [Editor] Saving current state...\n";
        // Using new since Memento constructor is private but Editor is a friend
        return std::shared_ptr<Memento>(new Memento(content));
    }

    void restore(std::shared_ptr<Memento> memento) {
        content = memento->getState();
        std::cout << "    [Editor] State restored. Current content: \"" << content << "\"\n";
    }

    std::string getContent() { return content; }
};

// Caretaker
class History {
    std::vector<std::shared_ptr<Memento>> states;

public:
    void push(std::shared_ptr<Memento> m) {
        states.push_back(m);
    }

    std::shared_ptr<Memento> pop() {
        if (states.empty()) return nullptr;
        auto m = states.back();
        states.pop_back();
        return m;
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "           MEMENTO INTERACTIVE\n";
    std::cout << "==========================================\n";

    Editor editor;
    History history;

    std::cout << "--- Action 1: Type something ---\n";
    editor.type("Hello ");
    history.push(editor.save());
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 2: Type more ---\n";
    editor.type("World!");
    history.push(editor.save());
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 3: Type even more (but don't save) ---\n";
    editor.type(" This will be lost.");
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 4: Undo (Restore to 'Hello World!') ---\n";
    auto lastState = history.pop();
    if (lastState) editor.restore(lastState);
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 5: Undo again (Restore to 'Hello ') ---\n";
    auto firstState = history.pop();
    if (firstState) editor.restore(firstState);
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\nMemento Pattern demonstration complete.\n";
    return 0;
}
