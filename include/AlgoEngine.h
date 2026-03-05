#ifndef ALGO_ENGINE_H
#define ALGO_ENGINE_H

#include <string>
#include <vector>

class AlgoEngine
{
public:
    // Module 1: Exact String Matching (I/O Focus)
    static std::vector<int> searchRabinKarp(const std::string &pattern, const std::string &text);
    static std::vector<int> searchKMP(const std::string &pattern, const std::string &text);

    // Module 2: Dynamic Programming (Memory Focus)
    static int matrixChainMultiplication(const std::vector<int> &dimensions);
    static int rodCutting(const std::vector<int> &prices, int n);

private:
    // Helper function for KMP
    static void computeLPSArray(const std::string &pattern, int M, std::vector<int> &lps);
};

#endif // ALGO_ENGINE_H