#include "allocator.h"
#include <iostream>

LinearAllocator::LinearAllocator(size_t maxSize)
{
  total_memory = maxSize;
  free_memory = maxSize;

  if(maxSize == 0)
  {
    initial_ptr = nullptr;
    current_ptr = nullptr;
  }
  else
  {

    try
    {
      if((initial_ptr = (char*)malloc(maxSize * sizeof(char))) == nullptr)
      {
        throw 1;
      }

    }

    catch(int i)
    {
      std::cout<<"Allocation memory error.";
      initial_ptr = nullptr;
    }

    current_ptr = initial_ptr;
  }
}

char* LinearAllocator::alloc(size_t size)
{
  if(free_memory < size)
  {
    return nullptr;
  }
  else
  {
  free_memory -= size;
  char* tmp_ptr = current_ptr;
  current_ptr += size;
  return tmp_ptr;
  }
}

void LinearAllocator::reset()
{
  current_ptr = initial_ptr;
  free_memory = total_memory;
}

LinearAllocator::~LinearAllocator()
{
  free(initial_ptr);
  initial_ptr = nullptr;
  current_ptr = nullptr;
}

size_t LinearAllocator::get_total_memory()
{
  return this->total_memory;
}

size_t LinearAllocator::get_free_memory()
{
  return this->free_memory;
}
