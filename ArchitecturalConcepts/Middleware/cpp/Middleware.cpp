#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>

/**
 * Middleware Pattern
 * 
 * Concept:
 * Middleware is a pattern where processing logic is organized into a pipeline of components.
 * Each component (middleware) can process a request, modify it, or decide to halt the chain.
 * It is commonly used in web frameworks for logging, authentication, and error handling.
 * 
 * Components:
 * - Request: The data being passed through the pipeline.
 * - Middleware: An interface or base class for components in the pipeline.
 * - Pipeline: The container that manages and executes the middleware chain.
 */

struct Request {
    std::string path;
    bool isAuthenticated = false;
    bool hasError = false;
    std::string log;
};

class Middleware {
public:
    virtual ~Middleware() = default;
    virtual void handle(Request& req, std::function<void(Request&)> next) = 0;
};

class LoggerMiddleware : public Middleware {
public:
    void handle(Request& req, std::function<void(Request&)> next) override {
        std::cout << "[Logger] Request received for path: " << req.path << "\n";
        req.log += "Logged | ";
        std::cout << "    (Press Enter to pass to next middleware...)";
        std::cin.get();
        next(req);
    }
};

class AuthMiddleware : public Middleware {
public:
    void handle(Request& req, std::function<void(Request&)> next) override {
        std::cout << "[Auth] Checking authentication...\n";
        if (req.path == "/admin") {
            std::cout << "    [!] Authentication required for /admin. Access denied.\n";
            req.isAuthenticated = false;
            req.hasError = true;
            req.log += "Auth Failed | ";
            return; // Halt the chain
        } else {
            std::cout << "    [✓] Authentication not required or valid for " << req.path << ".\n";
            req.isAuthenticated = true;
            req.log += "Auth OK | ";
            std::cout << "    (Press Enter to pass to next middleware...)";
            std::cin.get();
            next(req);
        }
    }
};

class FinalHandler : public Middleware {
public:
    void handle(Request& req, std::function<void(Request&)> next) override {
        std::cout << "[FinalHandler] Successfully processed request for " << req.path << ".\n";
        req.log += "Handled | ";
        // next(req) would usually do nothing here or call a default final action
    }
};

class Pipeline {
    std::vector<std::shared_ptr<Middleware>> middlewares;
public:
    void add(std::shared_ptr<Middleware> m) {
        middlewares.push_back(m);
    }

    void execute(Request& req) {
        executeStep(req, 0);
    }

private:
    void executeStep(Request& req, size_t index) {
        if (index < middlewares.size()) {
            middlewares[index]->handle(req, [this, index](Request& r) {
                this->executeStep(r, index + 1);
            });
        }
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        MIDDLEWARE PATTERN INTERACTIVE\n";
    std::cout << "==========================================\n";

    Pipeline pipeline;
    pipeline.add(std::make_shared<LoggerMiddleware>());
    pipeline.add(std::make_shared<AuthMiddleware>());
    pipeline.add(std::make_shared<FinalHandler>());

    std::cout << "Scenario 1: Accessing public path '/home'\n";
    Request req1{"/home"};
    pipeline.execute(req1);
    std::cout << "Final Request State: " << req1.log << "\n\n";

    std::cout << "------------------------------------------\n";
    std::cout << "Scenario 2: Accessing protected path '/admin'\n";
    Request req2{"/admin"};
    pipeline.execute(req2);
    std::cout << "Final Request State: " << req2.log << "\n";

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
