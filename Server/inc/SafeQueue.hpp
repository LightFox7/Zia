#pragma once

#include <mutex>
#include <queue>

template <typename T>
class SafeQueue
{
    public:
        SafeQueue() = default;
        ~SafeQueue() = default;

        std::size_t size() const
        {
            return this->_queue.size();
        };

        void push(const T &value)
        {
            std::unique_lock<std::mutex> lock(this->_mutex);

            this->_queue.push(value);
        };

        T waitPop()
        {
            T ret;

            while (!this->pop(ret));

            return ret;
        };

        bool pop(T &holder)
        {
            std::unique_lock<std::mutex> lock(this->_mutex);

            if (this->_queue.empty())
                return false;

            holder = this->_queue.front();
            this->_queue.pop();
            return true;
        };

    private:
        std::queue<T> _queue;
        std::mutex _mutex;
};