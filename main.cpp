/*

*/
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <ctype.h>
#include <chrono>
#include <vector>
std::vector<unsigned long long> factCache;
std::vector<int> fibCache;

/*
    Factorial Implementations
*/
unsigned long long factorial(int n, int acc)
{
    if (n <= 0)
    {
        return 1;
    }
    return factorial(n - 1, acc) * n;
}

unsigned long long loopFact(int n, int acc)
{
    unsigned long long ac;
    for (int i = 1; i <= n; i++)
    {
        ac *= i;
    }
    return ac;
}

unsigned long long tailFact(int n, int acc)
{
    if (n == 0)
    {
        return acc;
    }
    return tailFact(n - 1, acc * n);
}

unsigned long long memoFact(int n, int acc)
{
    if (factCache.size() - 1 >= n)
    {
        return factCache[n];
    }
    factCache.push_back(memoFact(n - 1, acc) * n);
    return factCache[factCache.size() - 1];
}

unsigned long long tailMemoFact(int n, int val)
{
    if (factCache.size() - 1 >= n)
    {
        return factCache[n];
    }
    if (factCache.size() - 1 < val)
    {
        factCache.push_back(factCache[val - 1] * val);
    }
    if (val == n)
    {
        return factCache[val];
    }
    return tailMemoFact(n, factCache.size());
}

auto getTime()
{
    return std::chrono::high_resolution_clock::now();
}

unsigned long long (*(functions[5]))(int, int) = {factorial, loopFact, tailFact, memoFact, tailMemoFact};

void testFactorials()
{
    // factCache.empty();
    // factCache.push_back(1);
    // printf("%i\n%i\n%i\n%i\n", factorial(5, 1), tailFact(5, 1), memoFact(5, 1), tailMemoFact(5, 1));
    std::vector<std::chrono::duration<double, std::milli>> times;
    auto start = getTime();
    std::chrono::duration<double, std::milli> durationSum = start - start;
    int target = 0;
    unsigned long long val;
    for (int i = 0; i < 5; i++)
    {
        factCache.empty();
        factCache.push_back(1);
        int trials = 100;
        for (int j = 0; j < trials; j++)
        {
            auto t1 = getTime();
            val = functions[i](5, 1);
            auto t2 = getTime();
            std::chrono::duration<double, std::milli> ms_double = t2 - t1;
            durationSum += ms_double;
        }
        times.push_back(durationSum / trials);
        durationSum -= durationSum;
    }
    for (int i = 0; i < times.size(); i++)
    {
        printf("Duration Sum for function %i: %f\n", i, times[i]);
    }
}

int main()
{
    testFactorials();
    return 0;
}