//
//  concurrency_driver.h
//  splashkit
//
//  Created by James Armstrong on 21/08/2016
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef sgsdl2_SGSDL2ConcurrencyUtils_h
#define sgsdl2_SGSDL2ConcurrencyUtils_h

#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>

using std::mutex;
using std::thread;
using std::condition_variable;
using std::unique_lock;
using std::lock_guard;
using std::queue;

namespace splashkit_lib
{
    class semaphore
    {
    private:
        std::mutex _mutex;
        std::condition_variable _cv;
        int _tokens;

    public:
        semaphore()
        {
            _tokens = 0;
        }

        explicit semaphore(int tokens)
        {
            _tokens = tokens;
        }

        void acquire()
        {
            std::unique_lock<std::mutex> lock(_mutex);
            while (_tokens <= 0)
            {
                _cv.wait(lock);
            }
            _tokens--;
        }

        bool try_acquire()
        {
            std::lock_guard<std::mutex> lock(_mutex);
            if (_tokens == 0) {
                return false;
            }

            _tokens--;
            return true;
        }

        void release(int num = 1)
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _tokens += num;
            _cv.notify_all();
        }
    };

    template <typename T>
    class channel
    {
    private:
        std::queue<T> _queue;
        semaphore _take_permission;
        std::mutex _mutex;

        T dequeue()
        {
            T data = _queue.front();
            _queue.pop();
            return data;
        }

    public:
        void put(T data)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _queue.push(data);
            lock.unlock();

            _take_permission.release();
        }

        T take()
        {
            _take_permission.acquire();

            std::lock_guard<std::mutex> lock(_mutex);
            return dequeue();
        }

        bool try_take(T& data)
        {
            if (_take_permission.try_acquire())
            {
                std::lock_guard<std::mutex> lock(_mutex);
                data = dequeue();
                return true;
            }

            return false;
        }

    };
}
#endif // sgsdl2_SGSDL2ConcurrencyUtils_h
