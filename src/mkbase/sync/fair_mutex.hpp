#pragma once

#include <condition_variable>
#include <mutex>

namespace monokuma::sync::fair {
    class mutex {
        std::mutex sync_;
        std::condition_variable cv_;
        std::size_t current_ = 0, next_ = 0;

    public:
        mutex() = default;
        ~mutex() = default;

        mutex(const mutex&) = delete;
        mutex& operator=(const mutex&) = delete;

        void lock() {
            std::unique_lock lock(this->sync_);
            const std::size_t request = this->next_++;
            while (request != this->current_) this->cv_.wait(lock);
        }

        bool try_lock() {
            std::lock_guard lock(this->sync_);
            if (this->next_ != this->current_) return false;
            ++this->next_;
            return true;
        }

        void unlock() {
            std::lock_guard lock(this->sync_);
            ++this->current_;
            this->cv_.notify_all();
        }
    };
}