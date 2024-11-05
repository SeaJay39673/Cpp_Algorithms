/*
    Author: Christopher Edmunds
    Last Updated: 11/5/2024
    Description:
        Various factorial implementations to benchmark their speed.
*/
#include <vector>
#include <chrono>
#include <string>
#include "helpers.cpp"

std::vector<unsigned long long> factCacheArray[2];
unsigned long long factorial(int n, unsigned long long acc)
{
    return n <= 0 ? 1 : factorial(n - 1, acc) * n;
}

unsigned long long loopFact(int n, unsigned long long acc)
{
    for (int i = 1; i <= n; i++)
    {
        acc *= i;
    }
    return acc;
}

unsigned long long tailFact(int n, unsigned long long acc)
{
    return n == 0 ? acc : tailFact(n - 1, acc * n);
}

unsigned long long memoFact(int n, unsigned long long acc)
{
    if (factCacheArray[0].size() - 1 >= n)
    {
        return factCacheArray[0][n];
    }
    factCacheArray[0].push_back(memoFact(n - 1, acc) * n);
    return factCacheArray[0][factCacheArray[0].size() - 1];
}

unsigned long long tailMemoFact(int n, unsigned long long val)
{
    if (factCacheArray[1].size() - 1 < val)
    {
        factCacheArray[1].push_back(factCacheArray[1][val - 1] * val);
    }
    return factCacheArray[1].size() - 1 >= n ? factCacheArray[1][n] : val == n ? factCacheArray[1][val]
                                                                               : tailMemoFact(n, factCacheArray[1].size());
}

unsigned long long (*(functions[5]))(int, unsigned long long) = {factorial, loopFact, tailFact, memoFact, tailMemoFact};
std::string names[5] = {"factorial", "loop factorial", "tail recursive factorial", "memoized factorial", "tail recursive and memoized factorial"};

void testFactorials()
{
    std::string avg = "Average time for: ";
    std::string result = "Result for: ";
    std::string spaces = "";
    for (int i = 0; i < avg.length() - result.length(); i++)
    {
        spaces += " ";
    }
    result += spaces;
    std::string bar = "";
    for (int i = 0; i < 96; i++)
    {
        bar += '=';
    }
    std::vector<std::chrono::duration<double, std::milli>> times;
    auto start = getTime();
    std::chrono::duration<double, std::milli> durationSum = start - start;
    int trials = 10000;
    int target;
    unsigned long long val;
    factCacheArray[0].push_back(1);
    factCacheArray[1].push_back(1);
    printf("FACTORIAL BENCHMARKING:\nTRIALS: %i\n", trials);
    for (int i = 0; i < 4; i++) // For each target value
    {
        times.clear();
        target = i * 3;
        printf("%s\nFactorial(%i):\n\n", bar.c_str(), target);
        for (int j = 0; j < 5; j++) // For each function
        {
            for (int k = 0; k < trials; k++) // For each trial per value
            {
                auto t1 = getTime();
                val = functions[j](target, 1);
                auto t2 = getTime();
                std::chrono::duration<double, std::milli> ms_double = t2 - t1;
                durationSum += ms_double;
            }
            printf("%s%50s: %10i\n", result.c_str(), names[j].c_str(), val);
            times.push_back(durationSum / trials);
            durationSum -= durationSum;
        }
        printf("\n");
        for (int k = 0; k < times.size(); k++)
        {
            printf("%s%50s: %10f\n", avg.c_str(), names[k].c_str(), times[k]);
        }
        printf("\n");
    }
}