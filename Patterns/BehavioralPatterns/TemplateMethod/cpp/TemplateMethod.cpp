#include <iostream>
#include <string>
#include <memory>

/**
 * Template Method Design Pattern
 * 
 * Intent:
 * Defines the skeleton of an algorithm in the superclass but lets 
 * subclasses override specific steps of the algorithm without 
 * changing its structure.
 * 
 * Components:
 * - Abstract Class: Defines the template method and the primitive 
 *   steps as abstract or default methods.
 * - Concrete Classes: Implement or override the primitive steps to 
 *   specialize the algorithm.
 */

// Abstract Class
class DataMiner {
public:
    virtual ~DataMiner() = default;

    // The Template Method
    void mineData(std::string path) {
        std::cout << "    [Miner] Opening file at: " << path << "\n";
        openFile(path);
        
        std::cout << "    [Miner] Extracting raw data...\n";
        extractData();
        
        std::cout << "    [Miner] Parsing raw data into common format...\n";
        parseData();
        
        if (shouldAnalyze()) {
            std::cout << "    [Miner] Analyzing parsed data...\n";
            analyzeData();
        }

        std::cout << "    [Miner] Closing file...\n";
        closeFile();
        std::cout << "    [Miner] Done!\n";
    }

    // Primitive steps
    virtual void openFile(std::string path) = 0;
    virtual void extractData() = 0;
    virtual void parseData() = 0;
    virtual void analyzeData() = 0;
    virtual void closeFile() = 0;

    // Hook
    virtual bool shouldAnalyze() { return true; }
};

// Concrete Classes
class PDFDataMiner : public DataMiner {
public:
    void openFile(std::string path) override { std::cout << "    [PDF] Opening PDF file...\n"; }
    void extractData() override { std::cout << "    [PDF] Extracting text and images from PDF...\n"; }
    void parseData() override { std::cout << "    [PDF] Parsing PDF data structure...\n"; }
    void analyzeData() override { std::cout << "    [PDF] Analyzing PDF content...\n"; }
    void closeFile() override { std::cout << "    [PDF] Closing PDF...\n"; }
};

class CSVDataMiner : public DataMiner {
public:
    void openFile(std::string path) override { std::cout << "    [CSV] Opening CSV file...\n"; }
    void extractData() override { std::cout << "    [CSV] Extracting rows and columns from CSV...\n"; }
    void parseData() override { std::cout << "    [CSV] Parsing CSV commas and headers...\n"; }
    void analyzeData() override { std::cout << "    [CSV] Analyzing CSV statistics...\n"; }
    void closeFile() override { std::cout << "    [CSV] Closing CSV...\n"; }

    // Override hook
    bool shouldAnalyze() override { return false; } // CSV skips analysis
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        TEMPLATE METHOD INTERACTIVE\n";
    std::cout << "==========================================\n";

    std::cout << "--- Action 1: Mining a PDF file ---\n";
    PDFDataMiner pdfMiner;
    pdfMiner.mineData("report.pdf");
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 2: Mining a CSV file (No analysis) ---\n";
    CSVDataMiner csvMiner;
    csvMiner.mineData("data.csv");
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\nTemplate Method Pattern demonstration complete.\n";
    return 0;
}
