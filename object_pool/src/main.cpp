#include "object_pool.h"

static ObjectPool<int> pool;

int main() {
    auto o1 = pool.acquire();
    auto o2 = pool.acquire();
    auto o3 = pool.acquire();

    printf("=> get obj 3 times\n");
    printf("o1: %p\n", o1.get());
    printf("o2: %p\n", o2.get());
    printf("o3: %p\n", o3.get());
    printf("obj in pool: %ld\n", pool.size());

    printf("=> release 2nd obj\n");
    pool.release(std::move(o2));
    printf("o2: %p\n", o2.get());
    printf("obj in pool: %ld\n", pool.size());

    printf("=> get another obj\n");
    auto o4 = pool.acquire();
    printf("o4: %p\n", o4.get());
    printf("obj in pool: %ld\n", pool.size());

    return 0;
}