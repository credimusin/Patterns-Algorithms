#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

/**
 * Proxy Pattern
 * 
 * Concept:
 * Proxy pattern provides a surrogate or placeholder for another object to 
 * control access to it. It can be used for lazy initialization, access 
 * control, logging, or caching.
 * 
 * Components:
 * - Subject: Interface for both the RealSubject and the Proxy.
 * - RealSubject: The real object that the proxy represents.
 * - Proxy: Maintains a reference to the RealSubject and controls access to it.
 */

// Subject
class Image {
public:
    virtual ~Image() {}
    virtual void display() = 0;
};

// RealSubject
class RealImage : public Image {
private:
    std::string filename;
public:
    RealImage(const std::string& name) : filename(name) {
        loadFromDisk();
    }

    void loadFromDisk() {
        std::cout << "    [RealImage] Loading " << filename << " from disk (this is expensive)...\n";
    }

    void display() override {
        std::cout << "    [RealImage] Displaying " << filename << "\n";
    }
};

// Proxy
class ProxyImage : public Image {
private:
    std::string filename;
    std::unique_ptr<RealImage> realImage;
public:
    ProxyImage(const std::string& name) : filename(name), realImage(nullptr) {
        std::cout << ">>> [Proxy] Proxy created for " << filename << ". Real object not loaded yet.\n";
    }

    void display() override {
        // Lazy initialization: load only when display is requested
        if (realImage == nullptr) {
            std::cout << ">>> [Proxy] First access to " << filename << ". Initializing RealImage...\n";
            realImage = std::make_unique<RealImage>(filename);
        } else {
            std::cout << ">>> [Proxy] Subsequent access to " << filename << ". Using cached RealImage.\n";
        }
        realImage->display();
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "             PROXY INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: Loading images from disk is slow. We use a Proxy to defer loading until the image is displayed.\n\n";

    std::unique_ptr<Image> img1 = std::make_unique<ProxyImage>("photo1.jpg");
    std::unique_ptr<Image> img2 = std::make_unique<ProxyImage>("photo2.jpg");

    std::cout << "\n(Press Enter to display img1)";
    std::cin.get();

    img1->display();

    std::cout << "\n(Press Enter to display img1 again)";
    std::cin.get();

    img1->display(); // Observe that it's not loaded from disk again

    std::cout << "\n(Press Enter to display img2)";
    std::cin.get();

    img2->display();

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- The Proxy controls access to the RealSubject.\n";
    std::cout << "- It allows for lazy initialization (Virtual Proxy).\n";
    std::cout << "- The client uses the Proxy the same way it would use the RealSubject.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
