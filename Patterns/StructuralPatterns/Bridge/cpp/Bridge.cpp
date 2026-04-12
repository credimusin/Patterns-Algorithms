#include <iostream>
#include <string>
#include <memory>

/**
 * Bridge Pattern
 * 
 * Concept:
 * Bridge pattern decouples an abstraction from its implementation so that the 
 * two can vary independently. It uses composition instead of inheritance.
 * 
 * Components:
 * - Abstraction: The higher-level interface.
 * - Implementor: The lower-level interface.
 * - Refined Abstraction: Extends the Abstraction.
 * - Concrete Implementor: Specific implementation of the Implementor.
 */

// Implementor
class Device {
public:
    virtual ~Device() {}
    virtual bool isEnabled() const = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual int getVolume() const = 0;
    virtual void setVolume(int percent) = 0;
    virtual std::string getName() const = 0;
};

// Concrete Implementors
class TV : public Device {
private:
    bool on = false;
    int volume = 30;
public:
    bool isEnabled() const override { return on; }
    void enable() override { on = true; }
    void disable() override { on = false; }
    int getVolume() const override { return volume; }
    void setVolume(int percent) override { volume = percent; }
    std::string getName() const override { return "TV"; }
};

class Radio : public Device {
private:
    bool on = false;
    int volume = 10;
public:
    bool isEnabled() const override { return on; }
    void enable() override { on = true; }
    void disable() override { on = false; }
    int getVolume() const override { return volume; }
    void setVolume(int percent) override { volume = percent; }
    std::string getName() const override { return "Radio"; }
};

// Abstraction
class RemoteControl {
protected:
    std::shared_ptr<Device> device;
public:
    RemoteControl(std::shared_ptr<Device> d) : device(d) {}
    virtual ~RemoteControl() {}

    void togglePower() {
        if (device->isEnabled()) {
            std::cout << ">>> Remote: Powering OFF the " << device->getName() << "...\n";
            device->disable();
        } else {
            std::cout << ">>> Remote: Powering ON the " << device->getName() << "...\n";
            device->enable();
        }
    }

    void volumeUp() {
        std::cout << ">>> Remote: Volume UP (+10%)\n";
        device->setVolume(device->getVolume() + 10);
    }
    
    void displayStatus() {
        std::cout << "    Device: " << device->getName() 
                  << " | State: " << (device->isEnabled() ? "ON" : "OFF")
                  << " | Volume: " << device->getVolume() << "%\n";
    }
};

// Refined Abstraction
class AdvancedRemoteControl : public RemoteControl {
public:
    AdvancedRemoteControl(std::shared_ptr<Device> d) : RemoteControl(d) {}

    void mute() {
        std::cout << ">>> Remote: Muting the device...\n";
        device->setVolume(0);
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "            BRIDGE INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: Abstraction (Remotes) and Implementation (Devices) are decoupled.\n";
    std::cout << "A basic remote can control any device, and an advanced remote can too.\n\n";

    auto tv = std::make_shared<TV>();
    auto radio = std::make_shared<Radio>();

    std::cout << "(Press Enter to control the TV with a Basic Remote)";
    std::cin.get();

    {
        RemoteControl basicRemote(tv);
        basicRemote.displayStatus();
        basicRemote.togglePower();
        basicRemote.volumeUp();
        basicRemote.displayStatus();
    }

    std::cout << "\n(Press Enter to control the Radio with an Advanced Remote)";
    std::cin.get();

    {
        AdvancedRemoteControl advancedRemote(radio);
        advancedRemote.displayStatus();
        advancedRemote.togglePower();
        advancedRemote.mute();
        advancedRemote.displayStatus();
    }

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- The Bridge pattern uses composition instead of inheritance.\n";
    // Observe how we can add new devices (implementations) or new remotes (abstractions) independently.
    std::cout << "- Abstraction and Implementation can vary independently.\n";
    std::cout << "- It helps avoid a 'class explosion' of all possible combinations.\n";
    // e.g. BasicRemoteTV, AdvancedRemoteTV, BasicRemoteRadio, AdvancedRemoteRadio...
    std::cout << "------------------------------------------\n";

    return 0;
}
