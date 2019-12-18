#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool
{
private:
    std::vector< std::thread > pool;
    std::queue< std::function<void()> > Queue;
    std::mutex Qmutex;
    std::condition_variable cond;
    bool terminate;
public:
    void func_loop();
    explicit ThreadPool(size_t poolSize)
    :   terminate(false)
    {
        for(int i=0; i<poolSize; i++)
            pool.emplace_back([this](){func_loop();});
    }

    ~ThreadPool();

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};
