#include <iostream>
#include <string>
#include <memory>
#include <map>

/**
 * Interpreter Design Pattern
 * 
 * Intent:
 * Defines a representation for a language's grammar along with an 
 * interpreter that uses the representation to evaluate sentences in the language.
 * 
 * Components:
 * - AbstractExpression: Interface defining the interpret() method.
 * - TerminalExpression: Implements interpret() for terminal symbols in the grammar.
 * - NonTerminalExpression: Implements interpret() for non-terminal symbols (e.g., operations).
 * - Context: Contains information global to the interpreter (e.g., variables).
 */

// Context
class Context {
    std::map<std::string, int> variables;
public:
    void set(std::string name, int value) {
        variables[name] = value;
    }
    int get(std::string name) {
        return variables[name];
    }
};

// Abstract Expression
class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret(Context& context) = 0;
};

// Terminal Expressions
class Constant : public Expression {
    int value;
public:
    Constant(int v) : value(v) {}
    int interpret(Context& context) override {
        return value;
    }
};

class Variable : public Expression {
    std::string name;
public:
    Variable(std::string n) : name(n) {}
    int interpret(Context& context) override {
        return context.get(name);
    }
};

// Non-Terminal Expression (Operation)
class AddExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
public:
    AddExpression(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r) 
        : left(std::move(l)), right(std::move(r)) {}

    int interpret(Context& context) override {
        int lVal = left->interpret(context);
        int rVal = right->interpret(context);
        std::cout << "    [Add] Adding " << lVal << " and " << rVal << "...\n";
        return lVal + rVal;
    }
};

class MultiplyExpression : public Expression {
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
public:
    MultiplyExpression(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r) 
        : left(std::move(l)), right(std::move(r)) {}

    int interpret(Context& context) override {
        int lVal = left->interpret(context);
        int rVal = right->interpret(context);
        std::cout << "    [Mul] Multiplying " << lVal << " and " << rVal << "...\n";
        return lVal * rVal;
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "          INTERPRETER INTERACTIVE\n";
    std::cout << "==========================================\n";

    Context context;
    context.set("x", 10);
    context.set("y", 5);

    std::cout << "Context: x = 10, y = 5\n";
    std::cout << "Expression: (x + 2) * y\n\n";

    // Represent (x + 2) * y
    // MultiplyExpression( AddExpression(Variable("x"), Constant(2)), Variable("y") )
    auto expr = std::make_unique<MultiplyExpression>(
        std::make_unique<AddExpression>(
            std::make_unique<Variable>("x"),
            std::make_unique<Constant>(2)
        ),
        std::make_unique<Variable>("y")
    );

    std::cout << "--- Interpreting step-by-step ---\n";
    int result = expr->interpret(context);

    std::cout << "\nResult: " << result << "\n";
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\nInterpreter Pattern demonstration complete.\n";
    return 0;
}
