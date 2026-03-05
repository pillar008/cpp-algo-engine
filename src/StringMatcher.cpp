#include "StringMatcher.h"

std::vector<int> StringMatcher::searchRabinKarp(const std::string &pattern, const std::string &text)
{
    std::vector<int> matches;
    int M = pattern.length();
    int N = text.length();
    if (M == 0 || N == 0 || M > N)
        return matches;

    int d = 256;
    int q = 101;
    int p = 0;
    int t = 0;
    int h = 1;

    for (int i = 0; i < M - 1; i++)
    {
        h = (h * d) % q;
    }

    for (int i = 0; i < M; i++)
    {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

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
        if (i < N - M)
        {
            t = (d * (t - text[i] * h) + text[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }
    return matches;
}

std::vector<int> StringMatcher::searchKMP(const std::string &pattern, const std::string &text)
{
    std::vector<int> matches;
    int M = pattern.length();
    int N = text.length();
    if (M == 0 || N == 0 || M > N)
        return matches;

    std::vector<int> lps(M, 0);
    computeLPSArray(pattern, M, lps);

    int i = 0;
    int j = 0;
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

void StringMatcher::computeLPSArray(const std::string &pattern, int M, std::vector<int> &lps)
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