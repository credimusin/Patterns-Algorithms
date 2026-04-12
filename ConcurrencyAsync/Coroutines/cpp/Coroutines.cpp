#include <iostream>
#include <coroutine>
#include <string>

/**
 * Coroutines (C++20)
 * 
 * Concept:
 * Coroutines are functions that can suspend execution to be resumed later.
 * They are particularly useful for implementing generators, asynchronous tasks,
 * and state machines. In C++, they use the co_yield, co_return, and co_await keywords.
 * 
 * Key Components:
 * - Promise Object: Defines the behavior of the coroutine (what happens when it starts/stops).
 * - Coroutine Handle: A handle to the coroutine state that allows resuming or destroying it.
 * - Generator: A wrapper that manages the coroutine and provides an interface to access yielded values.
 */

// A simple Generator implementation for C++20
template<typename T>
struct Generator {
    struct promise_type {
        T current_value;

        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::terminate(); }
        void return_void() {}

        std::suspend_always yield_value(T value) {
            current_value = value;
            return {};
        }
    };

    std::coroutine_handle<promise_type> handle;

    Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }

    bool next() {
        if (!handle.done()) {
            handle.resume();
            return !handle.done();
        }
        return false;
    }

    T value() const { return handle.promise().current_value; }
};

// A coroutine that generates a sequence of numbers
Generator<int> sequence_generator(int start, int end) {
    std::cout << "    (Coroutine starting...)\n";
    for (int i = start; i <= end; ++i) {
        std::cout << "    [!] Generator: yielding " << i << "\n";
        co_yield i; // Execution suspends here and returns control to the caller
    }
    std::cout << "    (Coroutine finishing...)\n";
}

int main() {
    std::cout << "==========================================\n";
    std::cout << "        COROUTINES (C++20) INTERACTIVE\n";
    std::cout << "==========================================\n";

    std::cout << "Initializing generator for numbers 1 to 5...\n";
    auto gen = sequence_generator(1, 5);

    std::cout << "Generator initialized. Starting loop.\n";
    std::cout << "------------------------------------------\n";

    while (gen.next()) {
        std::cout << "Main: Received value: " << gen.value() << "\n";
        std::cout << "    (Press Enter to request next value...)";
        std::cin.get();
    }

    std::cout << "------------------------------------------\n";
    std::cout << "Loop finished. The coroutine has reached its end.\n";

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
