#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono> // The benchmarking library
#include "StringMatcher.h"
#include "AlgoEngine.h"
#include "ParallelEngine.h"

int main()
{
    std::cout << "--- ALGO ENGINE BOOTING ---\n\n";

    //  Base File
    std::string filePath = "../data/sample_text.txt";
    std::ifstream file(filePath);
    std::string textContent;

    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        textContent = buffer.str();
    }
    else
    {
        textContent = "THIS IS A FALLBACK STRING FOR TESTING EXACT MATCHING.";
    }

    //  Stress Test Setup (Inflating the data)
    std::cout << "[SYSTEM] Inflating dataset for stress testing...\n";
    std::string massiveText = textContent;
    // Duplicate the string 16 times (2^16 multiplier) to create a massive payload
    for (int i = 0; i < 16; ++i)
    {
        massiveText += massiveText;
    }
    std::cout << "[SUCCESS] Dataset inflated to " << massiveText.length() << " characters.\n\n";

    std::string pattern = "ING";

    // BENCHMARK 1: Single-Threaded KMP
    std::cout << "Running Single-Threaded KMP...\n";
    auto startSingle = std::chrono::high_resolution_clock::now();

    std::vector<int> kmp_matches = StringMatcher::searchKMP(pattern, massiveText);

    auto endSingle = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> singleTime = endSingle - startSingle;
    std::cout << "-> Found " << kmp_matches.size() << " matches in " << singleTime.count() << " ms.\n\n";

    //  BENCHMARK 2: Multi-Threaded KMP
    int numThreads = 4;
    std::cout << "Running Multi-Threaded KMP (" << numThreads << " Threads)...\n";
    auto startMulti = std::chrono::high_resolution_clock::now();

    std::vector<int> parallel_matches = ParallelEngine::parallelSearchKMP(pattern, massiveText, numThreads);

    auto endMulti = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> multiTime = endMulti - startMulti;
    std::cout << "-> Found " << parallel_matches.size() << " matches in " << multiTime.count() << " ms.\n\n";

    // The Interview Metric
    std::cout << "========================================\n";
    std::cout << "PERFORMANCE GAIN: " << singleTime.count() / multiTime.count() << "x faster\n";
    std::cout << "========================================\n\n";

    // Test DP Module
    std::cout << "--- TESTING DP MODULE ---\n";
    std::vector<int> matrix_dims = {10, 20, 30, 40, 30};
    std::cout << "Matrix Chain Min Multiplications: " << AlgoEngine::matrixChainMultiplication(matrix_dims) << "\n";

    std::vector<int> rod_prices = {1, 5, 8, 9, 10, 17, 17, 20};
    int rod_length = 8;
    std::cout << "Rod Cutting Max Profit for length " << rod_length << ": " << AlgoEngine::rodCutting(rod_prices, rod_length) << "\n";

    return 0;
}