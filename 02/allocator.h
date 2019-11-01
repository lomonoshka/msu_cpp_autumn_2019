#pragma once
#include <cstdlib>

class LinearAllocator
{
    size_t total_memory;
    size_t free_memory;
    char* initial_ptr;
    char* current_ptr;

    public:

        const size_t get_total_memory();

        const size_t get_free_memory();

        const char* get_init();

        const char* get_cur();

        LinearAllocator(size_t maxSize);

        char* alloc(size_t size);

        void reset();

        ~LinearAllocator();
};
