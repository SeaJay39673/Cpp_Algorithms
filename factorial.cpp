/*
    Author: Christopher Edmunds
    Last Updated: 11/5/2024
    Description:
        Various factorial implementations to benchmark their speed.
*/
#include <string>
#include <vector>
#include <chrono>
#include "helpers.cpp"

std::vector<unsigned long long> factCacheArray[2];
unsigned long long factorial(int n)
{
    return n <= 0 ? 1 : factorial(n - 1) * n;
}

unsigned long long loopFact(int n)
{
    unsigned long long acc = 1;
    for (int i = 1; i <= n; i++)
    {
        acc *= i;
    }
    return acc;
}

unsigned long long tailFactHelper(int n, unsigned long long acc)
{
    return n == 0 ? acc : tailFactHelper(n - 1, acc * n);
}
unsigned long long tailFact(int n)
{
    return tailFactHelper(n, 1);
}

unsigned long long memoFact(int n)
{
    if (factCacheArray[0].size() - 1 >= n)
    {
        return factCacheArray[0][n];
    }
    factCacheArray[0].push_back(memoFact(n - 1) * n);
    return factCacheArray[0][factCacheArray[0].size() - 1];
}

unsigned long long tailMemoFactHelper(int n, unsigned long long val)
{
    if (factCacheArray[1].size() - 1 < val)
    {
        factCacheArray[1].push_back(factCacheArray[1][val - 1] * val);
    }
    return factCacheArray[1].size() - 1 >= n ? factCacheArray[1][n] : val == n ? factCacheArray[1][val]
                                                                               : tailMemoFactHelper(n, factCacheArray[1].size());
}
unsigned long long tailMemoFact(int n)
{
    return tailMemoFactHelper(n, 1);
}

unsigned long long (*(FactFuncs[5]))(int) = {factorial, loopFact, tailFact, memoFact, tailMemoFact};
std::string FactNames[5] = {"factorial", "loop factorial", "tail recursive factorial", "memoized factorial", "tail recursive and memoized factorial"};

void getFactVariables(std::string &type, int &size, std::string *(&names), unsigned long long((**(&functions))(int)))
{
    type = "FACTORIAL";
    size = 5;
    names = FactNames;
    functions = FactFuncs;
}