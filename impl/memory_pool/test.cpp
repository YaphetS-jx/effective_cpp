#include "memory_pool.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <atomic>
#include <new>
#include <thread>
#include <vector>

struct alignas(CACHE_LINE_SIZE) MyStruct {
    int id;
    float values[12];  // 12 × 4B = 48B
    MyStruct(int i) : id(i) {
        for (int j = 0; j < 12; ++j)
            values[j] = j * 1.1f;
    }

    void print() const {
        std::cout << "ID: " << id << " Values: ";
        for (float v : values) std::cout << v << " ";
        std::cout << '\n';
        std::fflush(stdout);
    }
};

int main() {
    constexpr int NumThreads = 8;
    AlignedMemoryPool<MyStruct, NumThreads> pool;
    constexpr int OpsPerThread = 1;

    using AlignedMyStruct = AlignedBlock<MyStruct>;
    auto pool_deleter = [&pool](AlignedMyStruct* p) {
        pool.destroy(p);
    };
    using AlignedMyStruct_holder = std::unique_ptr<AlignedMyStruct, decltype(pool_deleter)>;

    auto worker = [&](int thread_id) {
        std::vector<AlignedMyStruct_holder> ptrs;
        for (int i = 0; i < OpsPerThread; ++i) {
            AlignedMyStruct* obj = pool.create(thread_id * OpsPerThread + i);
            if (obj) {
                obj->get()->print();
                ptrs.emplace_back(obj, pool_deleter);
            }
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < NumThreads; ++i) {
        threads.emplace_back(worker, i);
    }
    for (auto& t : threads) t.join();
    return 0;
}
