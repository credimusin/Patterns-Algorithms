#include <iostream>
#include <string>
#include <vector>
#include <memory>

/**
 * Builder Pattern
 * 
 * Concept:
 * The Builder pattern separates the construction of a complex object from its representation,
 * allowing the same construction process to create different representations.
 * 
 * Components:
 * - Product: The complex object being built.
 * - Builder Interface: Declares steps to build the product.
 * - ConcreteBuilder: Implements the builder interface and maintains the product being built.
 * - Director: Defines the order of building steps to create a specific product configuration.
 */

// Product
class Computer {
public:
    std::string cpu;
    std::string motherboard;
    std::string ram;
    std::string gpu;
    std::string storage;

    void displayInfo() const {
        std::cout << "Computer Specs:\n";
        std::cout << "  - CPU: " << cpu << "\n";
        std::cout << "  - Motherboard: " << motherboard << "\n";
        std::cout << "  - RAM: " << ram << "\n";
        std::cout << "  - GPU: " << gpu << "\n";
        std::cout << "  - Storage: " << storage << "\n";
    }
};

// Builder Interface
class ComputerBuilder {
public:
    virtual ~ComputerBuilder() {}
    virtual void buildCPU() = 0;
    virtual void buildMotherboard() = 0;
    virtual void buildRAM() = 0;
    virtual void buildGPU() = 0;
    virtual void buildStorage() = 0;
    virtual std::unique_ptr<Computer> getComputer() = 0;
};

// Concrete Builder for a Gaming Computer
class GamingComputerBuilder : public ComputerBuilder {
private:
    std::unique_ptr<Computer> computer;
public:
    GamingComputerBuilder() { computer = std::make_unique<Computer>(); }

    void buildCPU() override {
        std::cout << "    Adding: High-End CPU (Intel i9)\n";
        computer->cpu = "Intel Core i9-13900K";
    }
    void buildMotherboard() override {
        std::cout << "    Adding: ROG Maximus Z790 Motherboard\n";
        computer->motherboard = "ASUS ROG Maximus Z790";
    }
    void buildRAM() override {
        std::cout << "    Adding: 64GB DDR5 RAM\n";
        computer->ram = "64GB DDR5-6000MHz";
    }
    void buildGPU() override {
        std::cout << "    Adding: NVIDIA GeForce RTX 4090\n";
        computer->gpu = "NVIDIA GeForce RTX 4090";
    }
    void buildStorage() override {
        std::cout << "    Adding: 2TB NVMe Gen5 SSD\n";
        computer->storage = "2TB NVMe Gen5 SSD";
    }
    std::unique_ptr<Computer> getComputer() override {
        return std::move(computer);
    }
};

// Concrete Builder for an Office Computer
class OfficeComputerBuilder : public ComputerBuilder {
private:
    std::unique_ptr<Computer> computer;
public:
    OfficeComputerBuilder() { computer = std::make_unique<Computer>(); }

    void buildCPU() override {
        std::cout << "    Adding: Power-Efficient CPU (Intel i3)\n";
        computer->cpu = "Intel Core i3-12100";
    }
    void buildMotherboard() override {
        std::cout << "    Adding: Basic B660 Motherboard\n";
        computer->motherboard = "GIGABYTE B660M DS3H";
    }
    void buildRAM() override {
        std::cout << "    Adding: 8GB DDR4 RAM\n";
        computer->ram = "8GB DDR4-3200MHz";
    }
    void buildGPU() override {
        std::cout << "    Adding: Integrated Graphics\n";
        computer->gpu = "Intel UHD Graphics 730";
    }
    void buildStorage() override {
        std::cout << "    Adding: 256GB SSD\n";
        computer->storage = "256GB SATA SSD";
    }
    std::unique_ptr<Computer> getComputer() override {
        return std::move(computer);
    }
};

// Director
class Director {
private:
    ComputerBuilder* builder;
public:
    void setBuilder(ComputerBuilder* b) {
        builder = b;
    }

    void buildMinimalComputer() {
        std::cout << ">>> Director: Building a minimal configuration...\n";
        builder->buildCPU();
        builder->buildMotherboard();
        builder->buildRAM();
    }

    void buildFullComputer() {
        std::cout << ">>> Director: Building a full-performance configuration...\n";
        builder->buildCPU();
        builder->buildMotherboard();
        builder->buildRAM();
        builder->buildGPU();
        builder->buildStorage();
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "         BUILDER PATTERN INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    Director director;

    std::cout << "Scenario: Building different types of computers using builders.\n\n";

    std::cout << "(Press Enter to build a Gaming Computer)";
    std::cin.get();

    {
        std::cout << "[!] Constructing Gaming PC...\n";
        GamingComputerBuilder gamingBuilder;
        director.setBuilder(&gamingBuilder);
        director.buildFullComputer();
        
        std::unique_ptr<Computer> pc = gamingBuilder.getComputer();
        pc->displayInfo();
    }

    std::cout << "\n(Press Enter to build an Office Computer)";
    std::cin.get();

    {
        std::cout << "[!] Constructing Office PC...\n";
        OfficeComputerBuilder officeBuilder;
        director.setBuilder(&officeBuilder);
        director.buildMinimalComputer(); // Only minimal for office
        
        std::unique_ptr<Computer> pc = officeBuilder.getComputer();
        pc->displayInfo();
    }

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- The Director controls the construction steps.\n";
    std::cout << "- Concrete Builders (Gaming/Office) handle the implementation details.\n";
    std::cout << "- Complex objects are built step-by-step.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
