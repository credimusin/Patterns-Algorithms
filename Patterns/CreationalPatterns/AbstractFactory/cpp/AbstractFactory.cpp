#include <iostream>
#include <string>
#include <memory>

/**
 * Abstract Factory Pattern
 * 
 * Concept:
 * Abstract Factory provides an interface for creating families of related or dependent 
 * objects without specifying their concrete classes. It encapsulates a group of individual 
 * factories that have a common theme.
 * 
 * Components:
 * - AbstractFactory: Interface that declares a set of methods for creating abstract products.
 * - ConcreteFactory: Implements the AbstractFactory interface to produce specific products.
 * - AbstractProduct: Interface for a type of product object.
 * - ConcreteProduct: Specific implementation of a product created by a ConcreteFactory.
 * - Client: Uses only interfaces declared by AbstractFactory and AbstractProduct.
 */

// Abstract Products
class Button {
public:
    virtual ~Button() {}
    virtual std::string render() const = 0;
};

class Checkbox {
public:
    virtual ~Checkbox() {}
    virtual std::string render() const = 0;
};

// Concrete Products (Windows Family)
class WinButton : public Button {
public:
    std::string render() const override {
        return "[ Windows Button ]";
    }
};

class WinCheckbox : public Checkbox {
public:
    std::string render() const override {
        return "[ Windows Checkbox ]";
    }
};

// Concrete Products (MacOS Family)
class MacButton : public Button {
public:
    std::string render() const override {
        return "( MacOS Button )";
    }
};

class MacCheckbox : public Checkbox {
public:
    std::string render() const override {
        return "( MacOS Checkbox )";
    }
};

// Abstract Factory
class GUIFactory {
public:
    virtual ~GUIFactory() {}
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
};

// Concrete Factory (Windows)
class WinFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WinButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<WinCheckbox>();
    }
};

// Concrete Factory (MacOS)
class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<MacCheckbox>();
    }
};

// Client code
class Application {
private:
    std::unique_ptr<GUIFactory> factory;
    std::unique_ptr<Button> button;
    std::unique_ptr<Checkbox> checkbox;

public:
    Application(std::unique_ptr<GUIFactory> f) : factory(std::move(f)) {}

    void createUI() {
        std::cout << ">>> Application: Creating UI components using the factory...\n";
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }

    void renderUI() {
        std::cout << "    Rendering: " << button->render() << "\n";
        std::cout << "    Rendering: " << checkbox->render() << "\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "      ABSTRACT FACTORY INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: A UI framework that needs to create components for different Operating Systems.\n";
    std::cout << "The client doesn't know which OS is being used, only that it needs a GUIFactory.\n\n";

    std::cout << "(Press Enter to choose Windows OS)";
    std::cin.get();

    {
        std::cout << "\n[!] System detected: Windows\n";
        std::unique_ptr<GUIFactory> factory = std::make_unique<WinFactory>();
        Application app(std::move(factory));
        
        app.createUI();
        app.renderUI();
    }

    std::cout << "\n(Press Enter to choose MacOS)";
    std::cin.get();

    {
        std::cout << "\n[!] System detected: MacOS\n";
        std::unique_ptr<GUIFactory> factory = std::make_unique<MacFactory>();
        Application app(std::move(factory));
        
        app.createUI();
        app.renderUI();
    }

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- The client code (Application) works with abstract interfaces (GUIFactory, Button, Checkbox).\n";
    std::cout << "- Concrete types (Win/Mac) are decoupled from the client.\n";
    std::cout << "- It's easy to add new OS families (e.g., Linux) without changing existing client code.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
