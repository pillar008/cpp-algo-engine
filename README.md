# High-Performance C++ Algorithmic Engine

A high-performance, multithreaded algorithmic library engineered in modern C++17. This project demonstrates system-level memory management, concurrent execution architecture, and CPU cache optimization through the implementation of heavy string-matching and dynamic programming algorithms.

## ⚙️ Core Architecture & Features

This engine is divided into two primary execution modules, designed to showcase different facets of C++ systems engineering:

### 1. The Concurrency Module (I/O & String Matching)

Processes massive text payloads by distributing the workload across multiple CPU cores.

- **Algorithms:** Knuth-Morris-Pratt (KMP) and Rabin-Karp.
- **Thread Safety (`std::thread`, `std::mutex`):** Implements a thread-safe data pipeline that chunks massive file streams into equal segments for parallel execution, utilizing mutex locks to prevent race conditions during global index aggregation.
- **The Boundary Overlap Solution:** Solves the classic concurrency problem of "split patterns" by intelligently calculating overlapping boundaries (`startIdx + chunkSize + patternLength - 1`), ensuring zero data loss across thread boundaries.

### 2. The Memory Optimization Module (Dynamic Programming)

Engineered specifically to maximize L1/L2 CPU cache hit rates during heavy recursive calculations.

- **Algorithms:** Matrix Chain Multiplication and Rod Cutting.
- **Cache Locality (`std::vector`):** Abandons standard 2D arrays (pointer-to-pointer arrays) which fragment heap memory. Instead, it utilizes a flattened, contiguous 1D vector mapped via lambda expressions `[row * width + col]`. This guarantees spatial locality and prevents CPU cache misses during intensive matrix operations.

### 3. The Profiling Engine (`<chrono>`)

Includes a custom benchmarking suite that stress-tests algorithms against inflated memory payloads (2.5MB+) and measures execution time down to the microsecond to calculate exact multi-core performance gains.

---

## 🛠️ Build & Execution (Cross-Platform)

This project uses **CMake** to ensure clean, cross-platform compilation without IDE lock-in.

### Prerequisites

- A C++17 compliant compiler (GCC, Clang, or MSVC)
- CMake (3.10 or higher)

### Build Instructions

```bash
# Clone the repository
git clone [https://github.com/pillar008/cpp-algo-engine.git](https://github.com/pillar008/cpp-algo-engine.git)
cd cpp-algo-engine

# Generate the build files
mkdir build
cd build
cmake ..

# Compile the engine
cmake --build .

# Execute the benchmarking suite
./engine
```
