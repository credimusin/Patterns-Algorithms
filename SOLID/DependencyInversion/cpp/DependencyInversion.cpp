#include <iostream>
#include <string>
#include <memory>

/**
 * Dependency Inversion Principle (DIP)
 * 
 * Intent:
 * High-level modules should not depend on low-level modules. Both should depend on abstractions.
 * 
 * Components:
 * - MessageService: Abstraction (Interface).
 * - EmailService: Low-level module (implementation).
 * - SMS_Service: Another low-level module (implementation).
 * - Notification: High-level module (depends on abstraction).
 */

class IMessageService {
public:
    virtual ~IMessageService() = default;
    virtual void sendMessage(const std::string& message) const = 0;
};

class EmailService : public IMessageService {
public:
    void sendMessage(const std::string& message) const override {
        std::cout << "    [EmailService] Sending email: " << message << "\n";
    }
};

class SMSService : public IMessageService {
public:
    void sendMessage(const std::string& message) const override {
        std::cout << "    [SMSService] Sending SMS: " << message << "\n";
    }
};

class Notification {
public:
    // High-level module depends on IMessageService abstraction, NOT concrete EmailService.
    Notification(std::unique_ptr<IMessageService> service) : service(std::move(service)) {}

    void notify(const std::string& message) {
        service->sendMessage(message);
    }

private:
    std::unique_ptr<IMessageService> service;
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "     DEPENDENCY INVERSION PRINCIPLE (DIP)\n";
    std::cout << "==========================================\n";

    std::cout << "Concept: High-level modules should depend on abstractions.\n";
    std::cout << "We decouple 'Notification' from specific delivery mechanisms.\n";
    std::cout << "\n(Press Enter to continue...)";
    std::cin.get();

    std::cout << "1. Sending notification via EMAIL.\n";
    Notification emailNotif(std::make_unique<EmailService>());
    emailNotif.notify("Hello via Email!");
    std::cin.get();

    std::cout << "2. Sending notification via SMS.\n";
    Notification smsNotif(std::make_unique<SMSService>());
    smsNotif.notify("Hello via SMS!");

    std::cout << "\n[✓] DIP allows us to swap low-level services without changing the high-level logic.\n";
    std::cout << "==========================================\n";

    return 0;
}
