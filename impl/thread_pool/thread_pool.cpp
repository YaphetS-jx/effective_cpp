#include "thread_pool.hpp"

// Constructor to initialize the thread pool
Thread_Pool::Thread_Pool(size_t num_threads) : stop_all(false) {
    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back([this] { worker(); });
    }
}

// Destructor to clean up the thread pool
Thread_Pool::~Thread_Pool() {
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        stop_all = true; // Set the flag to stop all threads
    }
    condition.notify_all(); // Notify all threads to wake up and exit

    for (std::thread &thread : threads) {
        if (thread.joinable()) {
            thread.join(); // Wait for all threads to finish
        }
    }
}

// Worker function that processes tasks from the queue
void Thread_Pool::worker() {
    while (true) {
        std::packaged_task<void()> task;

        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this] { return stop_all || !tasks.empty(); });

            if (stop_all && tasks.empty()) {
                return; // Exit if stopping and no tasks are left
            }

            task = std::move(tasks.front()); // Get the next task
            tasks.pop(); // Remove the task from the queue
        }

        task(); // Execute the task
    }
}