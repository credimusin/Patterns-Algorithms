#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

/**
 * Flyweight Pattern
 * 
 * Concept:
 * Flyweight pattern minimizes memory usage by sharing as much data as possible 
 * with other similar objects. It's a way to use objects in large numbers when a 
 * simple repeated representation would use an unacceptable amount of memory.
 * 
 * Components:
 * - Flyweight: Shares common (intrinsic) state between objects.
 * - FlyweightFactory: Manages and shares flyweights.
 * - Client: Maintains the unique (extrinsic) state.
 */

// Flyweight (Intrinsic State)
struct TreeType {
    std::string name;
    std::string color;
    std::string texture;

    TreeType(std::string n, std::string c, std::string t) : name(n), color(c), texture(t) {
        std::cout << "    [Flyweight] Creating new TreeType: " << name << " (" << color << ")\n";
    }

    void draw(int x, int y) const {
        std::cout << "    Drawing tree '" << name << "' at (" << x << ", " << y << ") with color " << color << ".\n";
    }
};

// Flyweight Factory
class TreeFactory {
private:
    static std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes;
public:
    static std::shared_ptr<TreeType> getTreeType(std::string name, std::string color, std::string texture) {
        std::string key = name + "_" + color + "_" + texture;
        if (treeTypes.find(key) == treeTypes.end()) {
            treeTypes[key] = std::make_shared<TreeType>(name, color, texture);
        } else {
            std::cout << "    [Flyweight] Reusing existing TreeType for: " << name << "\n";
        }
        return treeTypes[key];
    }
};

// Initialize static member
std::unordered_map<std::string, std::shared_ptr<TreeType>> TreeFactory::treeTypes;

// Tree Object (Extrinsic State)
class Tree {
private:
    int x, y;
    std::shared_ptr<TreeType> type;
public:
    Tree(int x_coord, int y_coord, std::shared_ptr<TreeType> t) : x(x_coord), y(y_coord), type(t) {}

    void draw() const {
        type->draw(x, y);
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "           FLYWEIGHT INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: Rendering a forest with thousands of trees.\n";
    std::cout << "Each tree has a position (extrinsic) but shares common properties (intrinsic).\n\n";

    std::vector<Tree> forest;

    std::cout << "(Press Enter to plant 2 Oaks at different positions)";
    std::cin.get();

    auto oak = TreeFactory::getTreeType("Oak", "Green", "Rough");
    forest.emplace_back(1, 1, oak);
    forest.emplace_back(10, 20, oak);

    std::cout << "\n(Press Enter to plant 2 Pines)";
    std::cin.get();

    auto pine = TreeFactory::getTreeType("Pine", "Dark Green", "Needles");
    forest.emplace_back(5, 5, pine);
    forest.emplace_back(15, 25, pine);

    std::cout << "\n(Press Enter to plant another Oak)";
    std::cin.get();

    auto anotherOak = TreeFactory::getTreeType("Oak", "Green", "Rough");
    forest.emplace_back(50, 50, anotherOak);

    std::cout << "\n>>> Rendering the forest...\n";
    for (const auto& tree : forest) {
        tree.draw();
    }

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- Shared data (intrinsic) is stored in the Flyweight (TreeType).\n";
    std::cout << "- Unique data (extrinsic) is stored in the individual objects (Tree).\n";
    std::cout << "- FlyweightFactory ensures that shared data is created only once.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
