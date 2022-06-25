#include <memory>
#include <mutex>
#include <stack>

// Object Pool Class
// All object must be returned to pool before pool deleted
template <typename T>
class ObjectPool {
public:
    ObjectPool() {}

    // get object from pool
    std::unique_ptr<T> acquire() {
        std::lock_guard<std::mutex> l(lock_);

        if (pool_.empty()) {
            std::unique_ptr<T> obj(new T());
            return obj;
        } else {
            std::unique_ptr<T> obj(std::move(pool_.top()));
            pool_.pop();
            return obj;
        }
    }

    // return object to pool
    void release(std::unique_ptr<T> obj) {
        std::lock_guard<std::mutex> l(lock_);
        pool_.push(obj.release());
    }

    size_t size() const {
        return pool_.size();
    }

private:
    std::stack<T*> pool_;
    std::mutex lock_;
};