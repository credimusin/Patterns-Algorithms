#include <iostream>
#include <string>
#include <memory>

/**
 * Chain of Responsibility Design Pattern
 * 
 * Intent:
 * Lets you pass requests along a chain of handlers. Upon receiving a request,
 * each handler decides either to process the request or to pass it to the
 * next handler in the chain.
 * 
 * Components:
 * - Handler Interface: Declares a method for handling requests.
 * - Base Handler: (Optional) Implements the boilerplate code for chaining.
 * - Concrete Handlers: Process the requests they are responsible for.
 * - Client: Configures the chain and sends requests.
 */

// Request object
enum class LogLevel { INFO, WARNING, ERROR, CRITICAL };

class LogMessage {
public:
    LogLevel level;
    std::string message;

    LogMessage(LogLevel l, std::string m) : level(l), message(m) {}
};

// Handler Interface
class Logger {
protected:
    std::shared_ptr<Logger> nextLogger;

public:
    virtual ~Logger() = default;

    void setNext(std::shared_ptr<Logger> next) {
        nextLogger = next;
    }

    virtual void handle(const LogMessage& msg) {
        if (nextLogger) {
            std::cout << "    [-] Passing request to the next handler...\n";
            nextLogger->handle(msg);
        } else {
            std::cout << "    [!] Reached end of chain. Request could not be handled.\n";
        }
    }
};

// Concrete Handlers
class InfoLogger : public Logger {
public:
    void handle(const LogMessage& msg) override {
        std::cout << "    [InfoLogger] Checking request (Level: INFO)...\n";
        if (msg.level == LogLevel::INFO) {
            std::cout << "    [✓] InfoLogger: Handling INFO message: " << msg.message << "\n";
        } else {
            std::cout << "    [ ] InfoLogger: Cannot handle this level. Passing on.\n";
            Logger::handle(msg);
        }
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }
};

class WarningLogger : public Logger {
public:
    void handle(const LogMessage& msg) override {
        std::cout << "    [WarningLogger] Checking request (Level: WARNING)...\n";
        if (msg.level == LogLevel::WARNING) {
            std::cout << "    [✓] WarningLogger: Handling WARNING message: " << msg.message << "\n";
        } else {
            std::cout << "    [ ] WarningLogger: Cannot handle this level. Passing on.\n";
            Logger::handle(msg);
        }
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }
};

class ErrorLogger : public Logger {
public:
    void handle(const LogMessage& msg) override {
        std::cout << "    [ErrorLogger] Checking request (Level: ERROR)...\n";
        if (msg.level == LogLevel::ERROR) {
            std::cout << "    [✓] ErrorLogger: Handling ERROR message: " << msg.message << "\n";
        } else {
            std::cout << "    [ ] ErrorLogger: Cannot handle this level. Passing on.\n";
            Logger::handle(msg);
        }
        std::cout << "    (Press Enter to continue...)";
        std::cin.get();
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "    CHAIN OF RESPONSIBILITY INTERACTIVE\n";
    std::cout << "==========================================\n";

    // Build the chain
    auto info = std::make_shared<InfoLogger>();
    auto warning = std::make_shared<WarningLogger>();
    auto error = std::make_shared<ErrorLogger>();

    info->setNext(warning);
    warning->setNext(error);

    std::cout << "Chain setup: InfoLogger -> WarningLogger -> ErrorLogger\n\n";

    LogMessage msg1(LogLevel::INFO, "System started.");
    LogMessage msg2(LogLevel::ERROR, "Database connection failed!");
    LogMessage msg3(LogLevel::CRITICAL, "Nuclear meltdown imminent!");

    std::cout << "--- Sending Request 1: INFO message ---\n";
    info->handle(msg1);

    std::cout << "\n--- Sending Request 2: ERROR message ---\n";
    info->handle(msg2);

    std::cout << "\n--- Sending Request 3: CRITICAL message (Unhandled) ---\n";
    info->handle(msg3);

    std::cout << "\nChain of Responsibility demonstration complete.\n";
    return 0;
}
