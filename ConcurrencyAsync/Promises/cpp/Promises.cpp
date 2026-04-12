#include <iostream>
#include <thread>
#include <future>
#include <chrono>

/**
 * Promises and Futures
 * 
 * Concept:
 * A promise is an object that can store a value to be retrieved asynchronously.
 * A future is an object that can retrieve the value from a promise.
 * They provide a way for one thread to pass a result or exception to another thread.
 * 
 * Components:
 * - std::promise<T>: Used by the 'provider' thread to set the result.
 * - std::future<T>: Used by the 'consumer' thread to get the result.
 */

void asyncTask(std::promise<int> p) {
    std::cout << "    [Thread] Starting intensive calculation...\n";
    
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    int result = 42;
    std::cout << "    [Thread] Calculation complete. Setting promise value to: " << result << "\n";
    
    // Fulfill the promise
    p.set_value(result);
}

int main() {
    std::cout << "==========================================\n";
    std::cout << "        PROMISES & FUTURES INTERACTIVE\n";
    std::cout << "==========================================\n";

    // 1. Create a promise and get its future
    std::promise<int> myPromise;
    std::future<int> myFuture = myPromise.get_future();

    std::cout << "1. Created promise and future. Ready to start thread.\n";
    std::cout << "    (Press Enter to start the worker thread...)";
    std::cin.get();

    // 2. Start a thread and move the promise into it
    std::thread t(asyncTask, std::move(myPromise));

    std::cout << "2. Worker thread started. We can continue doing other work.\n";
    std::cout << "    Wait, let's try to get the result now (this will block until ready).\n";
    std::cout << "    (Press Enter to block on future.get()...)";
    std::cin.get();

    // 3. Retrieve the value from the future (this blocks until set_value is called)
    int value = myFuture.get();

    std::cout << "3. Received value from future: " << value << "\n";
    
    t.join(); // Always join or detach threads before exiting

    std::cout << "------------------------------------------\n";
    std::cout << "The promise has been fulfilled and the future has retrieved the result.\n";

    std::cout << "\nAlgorithm completed. Thank you for learning!\n";
    return 0;
}
