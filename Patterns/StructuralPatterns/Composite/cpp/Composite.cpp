#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <numeric>

/**
 * Composite Pattern
 * 
 * Concept:
 * Composite pattern lets you compose objects into tree structures to represent 
 * part-whole hierarchies. It allows clients to treat individual objects and 
 * compositions of objects uniformly.
 * 
 * Components:
 * - Component: Interface for all objects in the composition.
 * - Leaf: Individual objects that have no children.
 * - Composite: Objects that can contain other components (leaves or other composites).
 */

// Component
class FileSystemItem {
public:
    virtual ~FileSystemItem() {}
    virtual void print(int depth = 0) const = 0;
    virtual long long getSize() const = 0;
    virtual std::string getName() const = 0;
};

// Leaf
class File : public FileSystemItem {
private:
    std::string name;
    long long size;
public:
    File(const std::string& n, long long s) : name(n), size(s) {}

    void print(int depth = 0) const override {
        std::cout << std::string(depth * 2, ' ') << " - [File] " << name << " (" << size << " bytes)\n";
    }

    long long getSize() const override { return size; }
    std::string getName() const override { return name; }
};

// Composite
class Directory : public FileSystemItem {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemItem>> children;
public:
    Directory(const std::string& n) : name(n) {}

    void add(std::shared_ptr<FileSystemItem> item) {
        children.push_back(item);
    }

    void print(int depth = 0) const override {
        std::cout << std::string(depth * 2, ' ') << " + [Dir] " << name << "/\n";
        for (const auto& child : children) {
            child->print(depth + 1);
        }
    }

    long long getSize() const override {
        long long total = 0;
        for (const auto& child : children) {
            total += child->getSize();
        }
        return total;
    }

    std::string getName() const override { return name; }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "           COMPOSITE INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: Building a file system tree with files (leaves) and directories (composites).\n";
    std::cout << "Both are treated uniformly as FileSystemItems.\n\n";

    auto root = std::make_shared<Directory>("root");
    auto bin = std::make_shared<Directory>("bin");
    auto home = std::make_shared<Directory>("home");
    auto user = std::make_shared<Directory>("alice");

    root->add(bin);
    root->add(home);
    home->add(user);

    bin->add(std::make_shared<File>("ls", 102400));
    bin->add(std::make_shared<File>("cp", 51200));
    user->add(std::make_shared<File>("photo.jpg", 2048000));
    user->add(std::make_shared<File>("notes.txt", 1024));

    std::cout << "(Press Enter to print the file system structure)";
    std::cin.get();

    root->print();

    std::cout << "\n(Press Enter to calculate the total size of the root directory)";
    std::cin.get();

    std::cout << ">>> Calculating total size of 'root'...\n";
    std::cout << "    Total size: " << root->getSize() << " bytes.\n";

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- The client treats files and directories the same via the FileSystemItem interface.\n";
    std::cout << "- It's easy to build complex trees and traverse them recursively.\n";
    std::cout << "- New component types can be added without modifying existing code.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
