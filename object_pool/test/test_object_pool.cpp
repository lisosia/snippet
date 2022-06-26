#include "gtest/gtest.h"

#include "object_pool.h"


TEST(ObjPool, reuse) {
    ObjectPool<int> pool;

    auto o = pool.acquire();
    int* o_saved = o.get();
    pool.release(std::move(o));

    auto o2 = pool.acquire();
    EXPECT_EQ(o_saved, o2.get());
}

TEST(ObjPool, reuse2) {
    ObjectPool<int> pool;

    auto o1 = pool.acquire();
    auto o2 = pool.acquire();
    auto o3 = pool.acquire();

    EXPECT_EQ(pool.size(), 0);

    int* o2_saved = o2.get();
    pool.release(std::move(o2));

    // o2 is now nullptr
    EXPECT_EQ(o2.get(), nullptr);

    // 1 obj pooled
    EXPECT_EQ(pool.size(), 1);

    auto o4 = pool.acquire();

    // newly acquired obj is last returned obj
    EXPECT_EQ(o2_saved, o4.get());

    // 0 obj pooled
    EXPECT_EQ(pool.size(), 0);
}

struct Int123CustomAllocator {
    static int* allocate() {
         return new int(123);
    }
};

TEST(ObjPool, custom_allocator) {
    ObjectPool<int> pool1;
    auto o1 = pool1.acquire();
    EXPECT_EQ(*o1.get(), 0);

    ObjectPool<int, Int123CustomAllocator> pool2;
    auto o2 = pool2.acquire();
    EXPECT_EQ(*o2.get(), 123);
}
