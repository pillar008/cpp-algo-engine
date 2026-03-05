#ifndef PARALLEL_ENGINE_H
#define PARALLEL_ENGINE_H

#include <string>
#include <vector>

class ParallelEngine
{
public:
    // Takes the pattern, text, and how many CPU cores you want to use
    static std::vector<int> parallelSearchKMP(const std::string &pattern, const std::string &text, int numThreads);
};

#endif // PARALLEL_ENGINE_H