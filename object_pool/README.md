### Object Pool Class

##### run sample program

```
mkdir build && cd build
cmake ..
./src/main
```

##### run googletest integrated with cmake's ctest

```
$ ctest 
Test project /home/haito/work/snippet/object_pool/build
    Start 1: ObjPool.reuse
1/2 Test #1: ObjPool.reuse ....................   Passed    0.00 sec
    Start 2: ObjPool.reuse2
2/2 Test #2: ObjPool.reuse2 ...................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.00 sec
```