#include "AlgoEngine.h"
#include <iostream>
#include <climits>
#include <algorithm>

// --- MODULE 1: STRING MATCHING ---

std::vector<int> AlgoEngine::searchRabinKarp(const std::string &pattern, const std::string &text)
{
    std::vector<int> matches;
    int M = pattern.length();
    int N = text.length();
    if (M == 0 || N == 0 || M > N)
        return matches;

    int d = 256; // Number of characters in the input alphabet
    int q = 101; // A prime number for the hash module
    int p = 0;   // Hash value for pattern
    int t = 0;   // Hash value for text
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (int i = 0; i < M - 1; i++)
    {
        h = (h * d) % q;
    }

    // Calculate initial hash values
    for (int i = 0; i < M; i++)
    {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text
    for (int i = 0; i <= N - M; i++)
    {
        if (p == t)
        {
            bool match = true;
            for (int j = 0; j < M; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
                matches.push_back(i);
        }

        // Calculate hash value for next window
        if (i < N - M)
        {
            t = (d * (t - text[i] * h) + text[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
    return matches;
}

std::vector<int> AlgoEngine::searchKMP(const std::string &pattern, const std::string &text)
{
    std::vector<int> matches;
    int M = pattern.length();
    int N = text.length();
    if (M == 0 || N == 0 || M > N)
        return matches;

    std::vector<int> lps(M, 0);
    computeLPSArray(pattern, M, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern
    while ((N - i) >= (M - j))
    {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }
        if (j == M)
        {
            matches.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < N && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i = i + 1;
            }
        }
    }
    return matches;
}

void AlgoEngine::computeLPSArray(const std::string &pattern, int M, std::vector<int> &lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < M)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// --- MODULE 2: DYNAMIC PROGRAMMING ---

int AlgoEngine::matrixChainMultiplication(const std::vector<int> &p)
{
    int n = p.size() - 1;
    // Flattened 2D array for better cache locality (Size: n x n)
    std::vector<int> m(n * n, 0);

    // Access macro/lambda for 2D abstraction over 1D array
    auto get = [&m, n](int i, int j) -> int &
    { return m[i * n + j]; };

    for (int L = 2; L <= n; L++)
    {
        for (int i = 0; i < n - L + 1; i++)
        {
            int j = i + L - 1;
            get(i, j) = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int q = get(i, k) + get(k + 1, j) + p[i] * p[k + 1] * p[j + 1];
                if (q < get(i, j))
                {
                    get(i, j) = q;
                }
            }
        }
    }
    return get(0, n - 1);
}

int AlgoEngine::rodCutting(const std::vector<int> &prices, int n)
{
    std::vector<int> val(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        int max_val = INT_MIN;
        for (int j = 0; j < i; j++)
        {
            max_val = std::max(max_val, prices[j] + val[i - j - 1]);
        }
        val[i] = max_val;
    }
    return val[n];
}