#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <future>
#include <queue>
#include <mutex>
#include <condition_variable>


class Thread_Pool {
public:
    explicit Thread_Pool(size_t num_threads = std::thread::hardware_concurrency());
    ~Thread_Pool();

    Thread_Pool(const Thread_Pool&) = delete;
    Thread_Pool& operator=(const Thread_Pool&) = delete;
    Thread_Pool& operator=(Thread_Pool&&) = delete;

    // Template method to add a task that can take any input arguments and return any type
    template<typename F, typename... Args>
    auto add_task(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using return_type = decltype(f(args...)); // Deduce the return type

        // Create a packaged task
        // shared_ptr is used to manage the task object
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            // use perfect forwarding to forward the function and arguments to the task
            // std::bind is used to bind the function and arguments together
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> result = task->get_future();

        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            tasks.emplace([task]() { (*task)(); }); // Wrap the task in a lambda
        }

        condition.notify_one(); // Notify a waiting thread
        return result; // Return the future
    }

    unsigned int get_thread_count() const {
        return threads.size();
    }

    unsigned int get_task_count() const {
        return tasks.size();
    }

private: 
    // worker threads
    std::vector<std::thread> threads;
    // task queue
    std::queue<std::packaged_task<void()>> tasks;
    // mutex for task queue
    std::mutex queue_mutex;
    // condition variable for task queue
    std::condition_variable condition;
    // flag to stop all threads
    bool stop_all;
    // Worker function for threads
    void worker();
};