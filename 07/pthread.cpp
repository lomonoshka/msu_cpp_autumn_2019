#include "pthread.h"

void ThreadPool::func_loop()
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

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(Qmutex);
        terminate = true;
    }
    cond.notify_all();
    for(std::thread &thread: pool)
        thread.join();
}

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>
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
