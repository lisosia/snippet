#include <atomic>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class Worker {
public:
    Worker(int num_thread);

    ~Worker();

    void enqueue_work(int task_data);

    int num_undone_task();

    void quit_all();

private:
    void do_work_func(const int thread_index);

    std::vector<std::thread> threads_;

    // task queue
    std::queue<int> tasks_;
    std::mutex tasks_mutex_;
    std::condition_variable tasks_cond_;

    // quit flag
    bool quit_;

    // active thread
    std::atomic_int num_undone_task_;
};