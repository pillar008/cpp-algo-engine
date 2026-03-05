#include "ParallelEngine.h"
#include "StringMatcher.h"
#include <thread>
#include <mutex>
#include <cmath>
#include <algorithm>

std::vector<int> ParallelEngine::parallelSearchKMP(const std::string &pattern, const std::string &text, int numThreads)
{
    std::vector<int> global_matches;
    std::mutex mtx; // The lock to prevent race conditions
    std::vector<std::thread> threads;

    int n = text.length();
    int m = pattern.length();
    if (n == 0 || m == 0 || m > n)
        return global_matches;

    // Calculate how big each thread's chunk of text should be
    int chunkSize = std::ceil((double)n / numThreads);

    for (int i = 0; i < numThreads; ++i)
    {
        int startIdx = i * chunkSize;

        // THE INTERVIEW WINNER: Overlapping the end index by (pattern length - 1)
        int endIdx = std::min(startIdx + chunkSize + m - 1, n);

        if (startIdx >= n)
            break; // Stop if we've covered the whole string

        // Spin up a new thread using a lambda function
        threads.push_back(std::thread([&, startIdx, endIdx]()
                                      {
            // Extract the specific chunk for this thread
            std::string subtext = text.substr(startIdx, endIdx - startIdx);
            
            // Run our single-threaded KMP on just this chunk
            std::vector<int> local_matches = StringMatcher::searchKMP(pattern, subtext);
            
            // Lock the global vector, add our local results, and unlock
            std::lock_guard<std::mutex> lock(mtx);
            for (int match : local_matches) {
                // Adjust the local index back to the global file index
                global_matches.push_back(startIdx + match); 
            } }));
    }

    // Wait for all worker threads to finish before returning
    for (auto &t : threads)
    {
        t.join();
    }

    // Sort the matches since threads might finish out of order
    std::sort(global_matches.begin(), global_matches.end());

    // Remove duplicates caused by the overlapping boundaries
    global_matches.erase(std::unique(global_matches.begin(), global_matches.end()), global_matches.end());

    return global_matches;
}