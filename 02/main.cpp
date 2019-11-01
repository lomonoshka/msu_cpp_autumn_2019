#include "allocator.cpp"
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char const **argv)
{
    if (argv[1] != nullptr)
    {
        LinearAllocator allocator(strtoul(argv[1],NULL,0));
        std::cout << allocator.get_total_memory()  << std::endl;
        for(int i = 2;i<argc;++i)
        {
            if (!strcmp(argv[i],"--reset"))
            {
                allocator.reset();
                std::cout << allocator.get_free_memory() << std::endl;
            }
            else if (allocator.alloc(strtoul(argv[i],NULL,0)) != nullptr)
            {
                std::cout <<  allocator.get_free_memory()  << std::endl;
            }
            else
            {
                std::cout << "!" << strtoul(argv[i],NULL,0) << std::endl;
            }
        }
    }
    else
    {
        std::cout << "No input" << std::endl;
    }
    return 0;
}
