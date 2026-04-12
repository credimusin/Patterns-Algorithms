#include <iostream>
#include <string>
#include <memory>

/**
 * Facade Pattern
 * 
 * Concept:
 * Facade pattern provides a simplified interface to a complex system of classes, 
 * library, or framework. It hides the complexities of the system and provides 
 * an easy-to-use interface to the client.
 * 
 * Components:
 * - Facade: High-level class that simplifies access to the complex subsystems.
 * - Subsystems: Multiple classes with complex interactions.
 */

// Complex Subsystem 1
class CPU {
public:
    void freeze() { std::cout << "    [CPU] Freezing processor...\n"; }
    void jump(long position) { std::cout << "    [CPU] Jumping to memory position: " << position << "...\n"; }
    void execute() { std::cout << "    [CPU] Executing commands...\n"; }
};

// Complex Subsystem 2
class Memory {
public:
    void load(long position, std::string data) {
        std::cout << "    [Memory] Loading data '" << data << "' to position " << position << "...\n";
    }
};

// Complex Subsystem 3
class HardDrive {
public:
    std::string read(long lba, int size) {
        std::cout << "    [HardDrive] Reading " << size << " sectors from LBA " << lba << "...\n";
        return "BOOT_DATA";
    }
};

// Facade
class ComputerFacade {
private:
    CPU cpu;
    Memory memory;
    HardDrive hardDrive;
public:
    void start() {
        std::cout << ">>> [Facade] Starting the computer...\n";
        cpu.freeze();
        std::string bootData = hardDrive.read(0, 512);
        memory.load(0x000, bootData);
        cpu.jump(0x000);
        cpu.execute();
        std::cout << ">>> [Facade] Computer started successfully!\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "            FACADE INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: Starting a computer requires complex interactions between the CPU, Memory, and Hard Drive.\n";
    std::cout << "Instead of managing these manually, we use a ComputerFacade.\n\n";

    ComputerFacade computer;

    std::cout << "(Press Enter to start the computer via Facade)";
    std::cin.get();

    computer.start();

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- The Facade hides the complexity of subsystems.\n";
    std::cout << "- The client only needs to call a simple method (start()).\n";
    std::cout << "- Subsystems are still accessible if the client needs more control, but they aren't forced to use them.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
