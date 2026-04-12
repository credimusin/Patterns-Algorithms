#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

/**
 * Observer Design Pattern
 * 
 * Intent:
 * Lets you define a subscription mechanism to notify multiple objects 
 * about any events that happen to the object they're observing.
 * 
 * Components:
 * - Subject (Publisher): Stores the state and notifies observers when it changes.
 * - Observer (Subscriber): Interface that defines an update() method.
 * - Concrete Observers: React to notifications from the subject.
 */

// Observer Interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(float price) = 0;
};

// Subject
class Product {
    std::vector<Observer*> observers;
    std::string name;
    float price;

public:
    Product(std::string n, float p) : name(n), price(p) {}

    void attach(Observer* o) {
        observers.push_back(o);
    }

    void detach(Observer* o) {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }

    void setPrice(float newPrice) {
        std::cout << "    [Product] " << name << " price changed from $" << price << " to $" << newPrice << "\n";
        price = newPrice;
        notify();
    }

    void notify() {
        std::cout << "    [Product] Notifying " << observers.size() << " observers...\n";
        for (auto observer : observers) {
            observer->update(price);
        }
    }
};

// Concrete Observers
class ShoppingApp : public Observer {
    std::string userName;

public:
    ShoppingApp(std::string u) : userName(u) {}

    void update(float price) override {
        std::cout << "    [" << userName << "'s App] Notification: Price updated to $" << price << "!\n";
    }
};

class PriceTracker : public Observer {
public:
    void update(float price) override {
        std::cout << "    [PriceTracker] Logging new price: $" << price << "\n";
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "           OBSERVER INTERACTIVE\n";
    std::cout << "==========================================\n";

    Product iphone("iPhone 15", 999.0f);

    ShoppingApp user1("Alice");
    ShoppingApp user2("Bob");
    PriceTracker tracker;

    iphone.attach(&user1);
    iphone.attach(&user2);
    iphone.attach(&tracker);

    std::cout << "Product created. 3 observers attached.\n\n";

    std::cout << "--- Action 1: First price change ---\n";
    iphone.setPrice(899.0f);
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 2: Bob unsubscribes ---\n";
    iphone.detach(&user2);
    std::cout << "    [!] Bob's App will no longer receive updates.\n";
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Action 3: Second price change ---\n";
    iphone.setPrice(799.0f);
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\nObserver Pattern demonstration complete.\n";
    return 0;
}
