#include <iostream>
#include <fstream>
#include <sstream>
#include "StringMatcher.h"
#include "AlgoEngine.h"
#include "ParallelEngine.h"

int main()
{
    std::cout << "--- ALGO ENGINE BOOTING ---\n\n";

    // 1. Test File I/O and String Matching
    std::string filePath = "../data/sample_text.txt"; // Path relative to the build folder
    std::ifstream file(filePath);
    std::string textContent;

    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        textContent = buffer.str();
        std::cout << "[SUCCESS] Loaded sample_text.txt (" << textContent.length() << " characters)\n";
    }
    else
    {
        std::cerr << "[ERROR] Could not open " << filePath << ". Make sure the file exists!\n";
        // Fallback text if file isn't found
        textContent = "THIS IS A FALLBACK STRING FOR TESTING EXACT MATCHING.";
    }

    std::string pattern = "ING";

    std::cout << "\nRunning Rabin-Karp Search for pattern: '" << pattern << "'\n";
    std::vector<int> rk_matches = StringMatcher::searchRabinKarp(pattern, textContent);
    for (int idx : rk_matches)
        std::cout << "Match found at index: " << idx << "\n";

    std::cout << "\nRunning KMP Search for pattern: '" << pattern << "'\n";
    std::vector<int> kmp_matches = StringMatcher::searchKMP(pattern, textContent);
    for (int idx : kmp_matches)
        std::cout << "Match found at index: " << idx << "\n";
    std::cout << "\nRunning MULTITHREADED KMP Search (4 Threads) for pattern: '" << pattern << "'\n";
    std::vector<int> parallel_matches = ParallelEngine::parallelSearchKMP(pattern, textContent, 4);
    for (int idx : parallel_matches)
        std::cout << "Match found at index: " << idx << "\n";

    // 2. Test Dynamic Programming
    std::cout << "\n--- TESTING DP MODULE ---\n";

    std::vector<int> matrix_dims = {10, 20, 30, 40, 30}; // Dimensions for 4 matrices
    std::cout << "Matrix Chain Min Multiplications: "
              << AlgoEngine::matrixChainMultiplication(matrix_dims) << "\n";

    std::vector<int> rod_prices = {1, 5, 8, 9, 10, 17, 17, 20};
    int rod_length = 8;
    std::cout << "Rod Cutting Max Profit for length " << rod_length << ": "
              << AlgoEngine::rodCutting(rod_prices, rod_length) << "\n";

    return 0;
}