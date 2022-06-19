#include <thread>
#include <chrono>

#include "worker.h"

int main () {
    Worker w(2);

    auto start = std::chrono::system_clock::now();

    w.enqueue_work(1);
    w.enqueue_work(5);
    w.enqueue_work(2);
    w.enqueue_work(3);
    w.enqueue_work(4);

#if 0  // early return test
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    w.quit_all();

#else  // wait all task complete

    while (true) {
        if (w.num_undone_task() == 0) { break; }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    auto end = std::chrono::system_clock::now();
    float elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        end - start).count() / 1000.0;
    printf("tasks finished in %.1f seconds\n", elapsed);

    w.quit_all();
#endif

    return 0;
}
