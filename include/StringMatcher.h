#ifndef STRING_MATCHER_H
#define STRING_MATCHER_H

#include <string>
#include <vector>

class StringMatcher
{
public:
    static std::vector<int> searchRabinKarp(const std::string &pattern, const std::string &text);
    static std::vector<int> searchKMP(const std::string &pattern, const std::string &text);

private:
    static void computeLPSArray(const std::string &pattern, int M, std::vector<int> &lps);
};

#endif // STRING_MATCHER_H