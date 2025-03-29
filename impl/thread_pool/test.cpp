#include <iostream>
#include <vector>
#include <future>
#include <numeric>
#include "thread_pool.hpp"
#include <chrono>

// Function to calculate sum of a vector range
int sum_range(const std::vector<int>& vec, size_t start, size_t end) {
    return std::accumulate(vec.begin() + start, vec.begin() + end, 0);
}

int main() {
    // Create test data
    const size_t vec_size = 1000000;
    std::vector<int> numbers(vec_size, 1);

    auto start = std::chrono::high_resolution_clock::now();
    {
        // Create thread pool
        Thread_Pool pool(2);
        auto thread_count = pool.get_thread_count();
        std::cout << "Thread count: " << thread_count << std::endl;

        // Split work into thread_count tasks
        std::vector<std::future<int>> results;
        const size_t chunk_size = vec_size / thread_count;

        for (size_t i = 0; i < thread_count; ++i) {
            size_t start = i * chunk_size;
            size_t end = (i == thread_count - 1) ? vec_size : (i + 1) * chunk_size;
            results.push_back(pool.add_task(sum_range, numbers, start, end));
        }

        // Get results and calculate final sum
        int total = 0;
        for (auto& result : results) {
            total += result.get();
        }

        // Verify result
        std::cout << "Total sum: " << total << std::endl;
        std::cout << "Expected sum: " << vec_size << std::endl;
        std::cout << "Test " << (total == vec_size ? "PASSED" : "FAILED") << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

    // Test with serial execution
    start = std::chrono::high_resolution_clock::now();
    {
        int total = std::accumulate(numbers.begin(), numbers.end(), 0);
        std::cout << "Total sum: " << total << std::endl;
        std::cout << "Expected sum: " << vec_size << std::endl;
        std::cout << "Test " << (total == vec_size ? "PASSED" : "FAILED") << std::endl;
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

    return 0;
}
