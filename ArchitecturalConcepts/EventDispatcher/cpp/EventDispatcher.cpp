#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>

/**
 * Event Dispatcher Pattern
 * 
 * Intent:
 * A centralized point to register event listeners and dispatch events to them.
 * Decouples the source of an event from its consumers.
 * 
 * Components:
 * - Event: Simple data object.
 * - Listener: Callback function (or object).
 * - EventDispatcher: Manages registrations and routing.
 */

struct Event {
    std::string name;
    std::string data;
};

using EventListener = std::function<void(const Event&)>;

class EventDispatcher {
public:
    void addListener(const std::string& eventName, EventListener listener) {
        listeners[eventName].push_back(listener);
    }

    void dispatch(const Event& event) {
        std::cout << "    [Dispatcher] Dispatching event: " << event.name << "\n";
        if (listeners.count(event.name)) {
            for (auto& listener : listeners[event.name]) {
                listener(event);
            }
        }
    }

private:
    std::map<std::string, std::vector<EventListener>> listeners;
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "          EVENT DISPATCHER PATTERN\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: A central hub for event communication.\n";
    std::cout << "Decouples components from each other.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    EventDispatcher dispatcher;

    std::cout << "1. Registering listeners for events.\n";
    dispatcher.addListener("user_logged_in", [](const Event& e) {
        std::cout << "    [AuditLog] Logged event: " << e.data << "\n";
    });
    dispatcher.addListener("user_logged_in", [](const Event& e) {
        std::cout << "    [EmailService] Sending welcome email for: " << e.data << "\n";
    });
    std::cin.get();

    std::cout << "2. Dispatching an event.\n";
    Event loginEvent{"user_logged_in", "UserAlice123"};
    dispatcher.dispatch(loginEvent);

    std::cout << "\n[✓] Event Dispatcher allows multiple listeners to react to a single event independently.\n";
    std::cout << "==========================================\n";

    return 0;
}
