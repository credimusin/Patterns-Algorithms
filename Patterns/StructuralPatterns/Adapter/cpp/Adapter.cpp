#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

/**
 * Adapter Pattern
 * 
 * Concept:
 * Adapter pattern allows objects with incompatible interfaces to work together.
 * It acts as a bridge between two incompatible interfaces.
 * 
 * Components:
 * - Target: Interface that the client expects.
 * - Adaptee: The class with the incompatible interface.
 * - Adapter: Implements the Target interface and wraps the Adaptee.
 */

// Target Interface (Client expects this)
class ModernMediaPlayer {
public:
    virtual ~ModernMediaPlayer() {}
    virtual void playAudio(const std::string& filename) = 0;
};

// Adaptee (Incompatible existing class)
class LegacyAudioPlayer {
public:
    void playWav(const std::string& filename) {
        std::cout << "    [LegacyAudioPlayer] Playing .wav file: " << filename << "\n";
    }
};

// Adapter
class AudioAdapter : public ModernMediaPlayer {
private:
    std::unique_ptr<LegacyAudioPlayer> legacyPlayer;
public:
    AudioAdapter() : legacyPlayer(std::make_unique<LegacyAudioPlayer>()) {}

    void playAudio(const std::string& filename) override {
        std::cout << ">>> [Adapter] Converting audio format for the legacy player...\n";
        
        // Simulating adaptation logic: check if it's .mp3 and "convert" it to .wav
        if (filename.find(".mp3") != std::string::npos) {
            std::string converted = filename;
            size_t pos = converted.find(".mp3");
            converted.replace(pos, 4, ".wav");
            
            std::cout << "    Action: Converted " << filename << " to " << converted << "\n";
            legacyPlayer->playWav(converted);
        } else {
            legacyPlayer->playWav(filename);
        }
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "          ADAPTER INTERACTIVE\n";
    std::cout << "==========================================\n\n";

    std::cout << "Scenario: Our modern player expects a ModernMediaPlayer interface.\n";
    std::cout << "But we want to reuse an old LegacyAudioPlayer that only plays .wav files.\n\n";

    std::unique_ptr<ModernMediaPlayer> player = std::make_unique<AudioAdapter>();

    std::cout << "(Press Enter to play 'song.mp3' using the Adapter)";
    std::cin.get();

    player->playAudio("song.mp3");

    std::cout << "\n(Press Enter to play 'audio.wav' using the Adapter)";
    std::cin.get();

    player->playAudio("audio.wav");

    std::cout << "\n------------------------------------------\n";
    std::cout << "Key Takeaway:\n";
    std::cout << "- The Adapter wraps the legacy class and translates calls to its interface.\n";
    std::cout << "- The client is unaware of the conversion logic.\n";
    std::cout << "- It helps in reusing existing classes even if their interfaces are incompatible.\n";
    std::cout << "------------------------------------------\n";

    return 0;
}
