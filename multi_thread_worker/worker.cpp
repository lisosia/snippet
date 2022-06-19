#include "worker.h"

Worker::Worker(int num_thread) {
    for (int i = 0; i < num_thread; ++i) {
        threads_.push_back(std::thread(&Worker::do_work_func, this, i));
    }
}

Worker::~Worker() {
    quit_all();
}

void Worker::do_work_func(const int thread_index) {
    while (true) {
        // wait till task enqueued or quit
        std::unique_lock<std::mutex> mlock(tasks_mutex_);
        tasks_cond_.wait(mlock, [&]{return (quit_ || !tasks_.empty());});

        if (quit_) { break; }

        // get task and unlock
        int task_input = tasks_.front();
        tasks_.pop();
        mlock.unlock();

        // do work you want
        printf("do working... from thread %d: sleep %d\n", thread_index, task_input);
        std::this_thread::sleep_for(std::chrono::seconds(task_input));

        // finalize
        num_undone_task_--;
    }
}

void Worker::enqueue_work(int task_data) {
    std::unique_lock<std::mutex> mlock(tasks_mutex_);
    tasks_.push(task_data);
    num_undone_task_++;

    // ref: https://en.cppreference.com/w/cpp/thread/condition_variable
    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    mlock.unlock();
    tasks_cond_.notify_one();
}

void Worker::quit_all() {
    int n = threads_.size();
    {
        std::unique_lock<std::mutex> mlock(tasks_mutex_);

        // avoid double quit
        if (quit_) { return; }

        quit_ = true;

        // manual unlocking
        mlock.unlock();
        tasks_cond_.notify_all();
    }
    for (int i = 0; i < n; ++i) {
        if (threads_[i].joinable()) {
            threads_[i].join();
        }
    }
}

int Worker::num_undone_task() {
    return num_undone_task_;
}
