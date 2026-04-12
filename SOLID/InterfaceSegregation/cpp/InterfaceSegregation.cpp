#include <iostream>
#include <string>

/**
 * Interface Segregation Principle (ISP)
 * 
 * Intent:
 * Clients should not be forced to depend upon interfaces that they do not use.
 * 
 * Components:
 * - Printer: Interface for basic printing.
 * - Scanner: Interface for scanning.
 * - BasicPrinter: Implements only Printer.
 * - MultiFunctionPrinter: Implements both Printer and Scanner.
 */

class IPrinter {
public:
    virtual ~IPrinter() = default;
    virtual void print() const = 0;
};

class IScanner {
public:
    virtual ~IScanner() = default;
    virtual void scan() const = 0;
};

class BasicPrinter : public IPrinter {
public:
    void print() const override {
        std::cout << "    [BasicPrinter] Printing document...\n";
    }
};

class MultiFunctionPrinter : public IPrinter, public IScanner {
public:
    void print() const override {
        std::cout << "    [MFP] Printing document...\n";
    }
    void scan() const override {
        std::cout << "    [MFP] Scanning document...\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "    INTERFACE SEGREGATION PRINCIPLE (ISP)\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: Clients should not be forced to depend on unused interfaces.\n";
    std::cout << "We split the 'Machine' interface into 'Printer' and 'Scanner'.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    std::cout << "1. Using BasicPrinter (Implements IPrinter only).\n";
    BasicPrinter basic;
    basic.print();
    // basic.scan(); // This won't even compile! ISP success.
    std::cin.get();

    std::cout << "2. Using MultiFunctionPrinter (Implements both).\n";
    MultiFunctionPrinter mfp;
    mfp.print();
    mfp.scan();

    std::cout << "\n[✓] ISP keeps our interfaces small and focused, reducing dependencies.\n";
    std::cout << "==========================================\n";

    return 0;
}
