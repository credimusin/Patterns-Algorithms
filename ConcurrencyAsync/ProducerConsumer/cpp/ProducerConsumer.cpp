#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

/**
 * Producer-Consumer Pattern
 * 
 * Concept:
 * The producer-consumer pattern describes a common synchronization problem.
 * A producer generates data and adds it to a shared buffer (e.g., a queue).
 * A consumer removes data from the buffer and processes it.
 * 
 * Synchronization:
 * - A mutex protects access to the shared buffer.
 * - Condition variables signal when the buffer is no longer empty (for the consumer)
 *   or no longer full (for the producer, though we'll use an unbounded queue here).
 */

class SharedBuffer {
    std::queue<int> buffer;
    std::mutex mtx;
    std::condition_variable cv;
    bool finished = false;

public:
    void produce(int value) {
        std::lock_guard<std::mutex> lock(mtx);
        buffer.push(value);
        std::cout << "[Producer] Generated value: " << value << "\n";
        cv.notify_one(); // Signal consumer that data is available
    }

    int consume() {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait until buffer is not empty or we're finished
        cv.wait(lock, [this]() { return !buffer.empty() || finished; });

        if (buffer.empty() && finished) {
            return -1; // Special value to indicate termination
        }

        int value = buffer.front();
        buffer.pop();
        std::cout << "[Consumer] Processed value: " << value << "\n";
        return value;
    }

    void setFinished() {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
        cv.notify_all(); // Wake up any waiting consumers to finish
    }
};

int main() {
    std::cout << "==========================================\n";
    std::cout << "        PRODUCER-CONSUMER INTERACTIVE\n";
    std::cout << "==========================================\n";

    SharedBuffer buffer;

    // We'll simulate the threads in a more interactive, step-by-step way
    // instead of just letting them run wild.

    std::cout << "1. Producer: Generating data...\n";
    buffer.produce(10);
    buffer.produce(20);

    std::cout << "    (Press Enter to see Consumer in action...)";
    std::cin.get();

    std::cout << "2. Consumer: Starting consumption...\n";
    buffer.consume();
    
    std::cout << "    (Press Enter to produce more data...)";
    std::cin.get();

    buffer.produce(30);

    std::cout << "3. Consumer: Finishing up...\n";
    buffer.consume();
    buffer.consume();

    std::cout << "------------------------------------------\n";
    std::cout << "All data processed. Threads would normally join here.\n";

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
