/*
    Author: Christopher Edmunds
    Last Updated: 11/5/2024
    Description:
        Various fibonacci implementations to benchmark their speed
*/
#include <vector>
#include "helpers.cpp"

std::vector<unsigned long long> fibCache[2];

unsigned long long fibonacci(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

unsigned long long tailFibHelper(int n, unsigned long long acc1 = 1, unsigned long long acc2 = 1)
{
    if (n == 0 || n == 1)
    {
        return acc2;
    }
    return tailFibHelper(n - 1, acc2, acc1 + acc2);
}
unsigned long long tailFib(int n)
{
    return tailFibHelper(n);
}

unsigned long long memoFib(int n)
{
    if (fibCache[0].size() - 1 >= n)
    {
        return fibCache[0][n];
    }
    fibCache[0].push_back(memoFib(n - 1) + memoFib(n - 2));
    return fibCache[0][fibCache[0].size() - 1];
}

unsigned long long tailMemoFibHelper(int n, unsigned long long acc1 = 1, unsigned long long acc2 = 1)
{
    if (fibCache[1].size() - 1 < acc1)
    {
        fibCache[1].push_back(fibCache[1][acc1 - 1] + fibCache[1][acc1 - 2]);
    }
    return fibCache[1].size() - 1 >= n ? fibCache[1][n] : tailMemoFibHelper(n, acc1 + 1, acc2);
}
unsigned long long tailMemoFib(int n)
{
    return tailMemoFibHelper(n);
}

unsigned long long (*(FibFuncs[4]))(int) = {fibonacci, tailFib, memoFib, tailMemoFib};
std::string FibNames[4] = {"fibonacci", "tail recursive fibonacci", "memoized fibonacci", "tail recursive memoized fibonacci"};

void getFibVariables(std::string &type, int &max, int &size, std::string *(&names), unsigned long long((**(&functions))(int)))
{
    for (int i = 0; i < 2; i++)
    {
        fibCache[i].push_back(1);
        fibCache[i].push_back(1);
    }
    type = "FIBONACCI";
    max = 30;
    size = 4;
    names = FibNames;
    functions = FibFuncs;
}