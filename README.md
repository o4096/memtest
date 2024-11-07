# memtest
---

A small test program designed to allocate a specified amount of RAM and fill it with random data for testing and benchmarking purposes. This tool is useful for developers and system administrators who need to evaluate memory performance, stability, and behavior under various conditions.

## Use Cases

- Allocates a user-defined amount of memory.
- Fills the allocated memory with random data.
- Useful for stress testing and diagnosing memory-related issues.
- Could be used as template code for benchmarking.

---
## Compile & Run

Since it's a single C file you can just compile it with gcc as follows:
```
gcc memtest.c -o memtest
./memtest -h
```
or you can use cmake with the provided CMakeLists.txt:
```
mkdir build
cd build
cmake ..
make .
```
