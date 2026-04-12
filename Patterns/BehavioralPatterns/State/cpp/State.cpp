#include <iostream>
#include <string>
#include <memory>

/**
 * State Design Pattern
 * 
 * Intent:
 * Lets an object alter its behavior when its internal state changes. 
 * The object will appear to change its class.
 * 
 * Components:
 * - Context: Defines the interface of interest to clients and maintains 
 *   an instance of a ConcreteState.
 * - State Interface: Declares the state-specific methods.
 * - Concrete States: Each implementation of the interface provides 
 *   behavior associated with a state of the Context.
 */

// Forward declaration
class VendingMachine;

// State Interface
class State {
public:
    virtual ~State() = default;
    virtual void insertMoney(VendingMachine& machine) = 0;
    virtual void ejectMoney(VendingMachine& machine) = 0;
    virtual void pushButton(VendingMachine& machine) = 0;
    virtual void dispense(VendingMachine& machine) = 0;
    virtual std::string toString() const = 0;
};

// Context
class VendingMachine {
    std::unique_ptr<State> state;
    int stock = 0;

public:
    VendingMachine(int s);

    void setState(std::unique_ptr<State> newState) {
        state = std::move(newState);
        std::cout << "    [VendingMachine] Transitioning to: " << state->toString() << "\n";
    }

    void insertMoney() { state->insertMoney(*this); }
    void ejectMoney() { state->ejectMoney(*this); }
    void pushButton() { state->pushButton(*this); }
    void dispense() { state->dispense(*this); }

    void releaseItem() {
        if (stock > 0) {
            stock--;
            std::cout << "    [VendingMachine] A product was dispensed. Stock left: " << stock << "\n";
        }
    }

    int getStock() const { return stock; }
};

// Concrete States
class NoMoneyState : public State {
public:
    void insertMoney(VendingMachine& machine) override;
    void ejectMoney(VendingMachine& machine) override { std::cout << "    [NoMoneyState] You haven't inserted any money!\n"; }
    void pushButton(VendingMachine& machine) override { std::cout << "    [NoMoneyState] You must insert money first.\n"; }
    void dispense(VendingMachine& machine) override { std::cout << "    [NoMoneyState] Insert money before you get a product!\n"; }
    std::string toString() const override { return "NoMoneyState"; }
};

class HasMoneyState : public State {
public:
    void insertMoney(VendingMachine& machine) override { std::cout << "    [HasMoneyState] Money is already inserted.\n"; }
    void ejectMoney(VendingMachine& machine) override;
    void pushButton(VendingMachine& machine) override;
    void dispense(VendingMachine& machine) override { std::cout << "    [HasMoneyState] You must push the button first!\n"; }
    std::string toString() const override { return "HasMoneyState"; }
};

class SoldState : public State {
public:
    void insertMoney(VendingMachine& machine) override { std::cout << "    [SoldState] Please wait, we're already giving you a product!\n"; }
    void ejectMoney(VendingMachine& machine) override { std::cout << "    [SoldState] Sorry, you already pushed the button.\n"; }
    void pushButton(VendingMachine& machine) override { std::cout << "    [SoldState] Pushing twice doesn't get you two products!\n"; }
    void dispense(VendingMachine& machine) override;
    std::string toString() const override { return "SoldState"; }
};

class OutOfStockState : public State {
public:
    void insertMoney(VendingMachine& machine) override { std::cout << "    [OutOfStockState] Machine is empty, cannot accept money.\n"; }
    void ejectMoney(VendingMachine& machine) override { std::cout << "    [OutOfStockState] You haven't inserted any money.\n"; }
    void pushButton(VendingMachine& machine) override { std::cout << "    [OutOfStockState] Out of stock.\n"; }
    void dispense(VendingMachine& machine) override { std::cout << "    [OutOfStockState] No item to dispense.\n"; }
    std::string toString() const override { return "OutOfStockState"; }
};

// VendingMachine Implementation
VendingMachine::VendingMachine(int s) : stock(s) {
    if (stock > 0) state = std::make_unique<NoMoneyState>();
    else state = std::make_unique<OutOfStockState>();
}

// State Implementation details (need VendingMachine and other States)
void NoMoneyState::insertMoney(VendingMachine& machine) {
    std::cout << "    [NoMoneyState] Money inserted.\n";
    machine.setState(std::make_unique<HasMoneyState>());
}

void HasMoneyState::ejectMoney(VendingMachine& machine) {
    std::cout << "    [HasMoneyState] Money returned.\n";
    machine.setState(std::make_unique<NoMoneyState>());
}

void HasMoneyState::pushButton(VendingMachine& machine) {
    std::cout << "    [HasMoneyState] Button pushed.\n";
    machine.setState(std::make_unique<SoldState>());
}

void SoldState::dispense(VendingMachine& machine) {
    machine.releaseItem();
    if (machine.getStock() > 0) {
        machine.setState(std::make_unique<NoMoneyState>());
    } else {
        std::cout << "    [!] Oops, out of stock!\n";
        machine.setState(std::make_unique<OutOfStockState>());
    }
}

int main() {
    std::cout << "==========================================\n";
    std::cout << "            STATE INTERACTIVE\n";
    std::cout << "==========================================\n";

    VendingMachine machine(2);

    std::cout << "Vending Machine initialized with 2 items.\n\n";

    std::cout << "--- Transaction 1: Simple Purchase ---\n";
    machine.insertMoney();
    machine.pushButton();
    machine.dispense();
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Transaction 2: Inserting & Ejecting ---\n";
    machine.insertMoney();
    machine.ejectMoney();
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Transaction 3: Final Purchase ---\n";
    machine.insertMoney();
    machine.pushButton();
    machine.dispense();
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\n--- Transaction 4: Trying to buy from empty machine ---\n";
    machine.insertMoney();
    std::cout << "    (Press Enter to continue...)";
    std::cin.get();

    std::cout << "\nState Pattern demonstration complete.\n";
    return 0;
}
