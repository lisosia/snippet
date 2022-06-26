#include <memory>
#include <mutex>
#include <stack>

// Default Allocator
template <typename T>
struct DefaultAllocator {
    static T* allocate() { return new T(); }
};

// Object pool class
// get object by acquire() and return to pool by release()
// if no object pooled when acquire(), new object will be allocated by Allocator
template <typename T, typename Allocator = DefaultAllocator<T>>
class ObjectPool {
public:
    ObjectPool() {}

    // get object from pool
    std::unique_ptr<T> acquire() {
        std::lock_guard<std::mutex> l(lock_);

        if (pool_.empty()) {
            std::unique_ptr<T> obj(Allocator::allocate());
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
