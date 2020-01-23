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
    std::atomic<bool> terminate;
public:
    void func_loop()
    {
        std::function<void()> task;
        while(true)
        {
            {
                std::unique_lock<std::mutex> lock(Qmutex);
                cond.wait(lock, [this]{return !Queue.empty() || terminate;});
                if(terminate && Queue.empty())
                    return;
                task = Queue.front();
                Queue.pop();
            }
            task();
        }
    }

    explicit ThreadPool(size_t poolSize)
    :   terminate(false)
    {
        for(int i=0; i<poolSize; i++)
            pool.emplace_back([this](){func_loop();});
    }

    ~ThreadPool()
    {
        terminate = true;
        cond.notify_all();
        for(std::thread &thread: pool)
            thread.join();
    }

     // pass arguments by value
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        using type = decltype(func(args...));
        auto task = std::make_shared< std::packaged_task<type()> >(std::bind(func, args...));
        std::future<type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(Qmutex);

            if(terminate)
                throw std::runtime_error("Thread pool has been terminated.");

            Queue.push([task](){(*task)();});
        }
        cond.notify_one();
        return res;
    }
};
