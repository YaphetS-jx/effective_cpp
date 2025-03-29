// cache_aligned_pool.h
#pragma once
#include <cstdlib>
#include <cstdint>
#include <cstddef>
#include <atomic>
#include <new>

constexpr size_t CACHE_LINE_SIZE = 64;

inline constexpr size_t align_up(size_t size, size_t alignment) {    
    return (size + alignment - 1) & ~(alignment - 1);
}

// Generic aligned memory block
template <typename T>
struct alignas(CACHE_LINE_SIZE) AlignedBlock {
    alignas(CACHE_LINE_SIZE) std::byte data[align_up(sizeof(T), CACHE_LINE_SIZE)];

    T* get() { return reinterpret_cast<T*>(data); }
};

// Simple aligned memory pool
template <typename T, size_t BlockCount>
class AlignedMemoryPool {
    static constexpr size_t BlockSize = align_up(sizeof(AlignedBlock<T>), CACHE_LINE_SIZE);    

    struct BlockNode {
        BlockNode* next;
    };

    alignas(CACHE_LINE_SIZE) std::byte pool[BlockCount * BlockSize];
    std::atomic<BlockNode*> freeList;

public:
    AlignedMemoryPool() {
        // Initialize free list
        freeList.store(nullptr);
        for (size_t i = 0; i < BlockCount; ++i) {
            void* blockPtr = pool + i * BlockSize;            
            deallocate(reinterpret_cast<AlignedBlock<T>*>(blockPtr));
        }
    }

    void* allocate() {
        BlockNode* head = freeList.load(std::memory_order_acquire);
        while (head && !freeList.compare_exchange_weak(head, head->next, std::memory_order_acq_rel)) {}
        return head ? reinterpret_cast<void*>(head) : nullptr;
    }

    void deallocate(void* ptr) {
        auto* node = reinterpret_cast<BlockNode*>(ptr);
        BlockNode* head = freeList.load(std::memory_order_acquire);
        do {
            node->next = head;
        } while (!freeList.compare_exchange_weak(head, node, std::memory_order_acq_rel));
    }

    template <typename... Args>
    AlignedBlock<T>* create(Args&&... args) {
        void* mem = allocate();
        if (!mem) return nullptr;
        AlignedBlock<T>* block = reinterpret_cast<AlignedBlock<T>*>(mem);
        new (block->get()) T(std::forward<Args>(args)...);
        return block;
    }

    void destroy(AlignedBlock<T>* block) {
        if (!block) return;
        block->get()->~T();
        deallocate(reinterpret_cast<void*>(block));
    }
};
