#include <iostream>
#include <thread>
#include <atomic>

/* memory order: 
   1. relaxed: no synchronization, no ordering constraints
   2. acquire: ensures that operations before the acquire are visible to other threads before the acquire
   3. release: ensures that operations after the release are visible to other threads after the release
   4. acquire-release: ensures that operations before the acquire are visible to other threads before the acquire, and operations after the release are visible to other threads after the release
   5. seq_cst: ensures that operations are executed in a single total order, and that this order is consistent with the program order
*/

std::atomic<int> x{0}, y{0};
int r1 = 0, r2 = 0;

void thread1(std::memory_order order1, std::memory_order order2) {
    x.store(1, order1);
    r1 = y.load(order2); // Could be 0 or 1
}

void thread2(std::memory_order order1, std::memory_order order2) {
    y.store(1, order1);
    r2 = x.load(order2); // Could be 0 or 1
}


int main() {
    // test relaxed memory order
    // this takes some time to see r1 == 0 && r2 == 0, might not happen at all    
    for (int i = 0; i < 1'000'000; ++i) {
        x = 0; y = 0; r1 = r2 = 0;
        std::thread t1(thread1, std::memory_order_relaxed, std::memory_order_relaxed);
        std::thread t2(thread2, std::memory_order_relaxed, std::memory_order_relaxed);
        t1.join();
        t2.join();

        // 🔥 This is the interesting case:
        if (r1 == 0 && r2 == 0) {
            std::cout << "Reordering detected: r1 = " << r1 << ", r2 = " << r2 << "\n";
            break;
        }
    }

    // test acquire-release memory order
    // this should never see r1 == 0 && r2 == 0
    for (int i = 0; i < 1'000'000; ++i) {
        x = 0; y = 0; r1 = r2 = 0;
        std::thread t1(thread1, std::memory_order_release, std::memory_order_acquire);
        std::thread t2(thread2, std::memory_order_release, std::memory_order_acquire);
        t1.join();
        t2.join();

        if (r1 == 0 && r2 == 0) {
            std::cout << "Reordering detected: r1 = " << r1 << ", r2 = " << r2 << "\n";
            break;
        }
    }

    // test memory_order_seq_cst  memory order
    // this should never see r1 == 0 && r2 == 0
    for (int i = 0; i < 1'000'000; ++i) {
        x = 0; y = 0; r1 = r2 = 0;
        std::thread t1(thread1, std::memory_order_seq_cst, std::memory_order_seq_cst);
        std::thread t2(thread2, std::memory_order_seq_cst, std::memory_order_seq_cst);
        t1.join();
        t2.join();

        if (r1 == 0 && r2 == 0) {
            std::cout << "Reordering detected: r1 = " << r1 << ", r2 = " << r2 << "\n";
            break;
        }
    }
    
}

