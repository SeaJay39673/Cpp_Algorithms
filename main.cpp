/*

*/
#include <string>
#include <cstdio>
#include <vector>
#include "factorial.cpp"
#include "fibonacci.cpp"

std::vector<unsigned long long> cache;

void testFunc(std::string type, int max, int size, std::string *names, unsigned long long (**funcs)(int))
{
    /*
        Formatting strings:
    */
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

    /*
        Time related variables
    */
    std::vector<std::chrono::duration<double, std::milli>> times;
    auto start = getTime();
    std::chrono::duration<double, std::milli> durationSum = start - start;

    /*

    */
    int trials = 10000;
    int target = 0;
    unsigned long long val;
    printf("%s BENCHMARKING:\nTRIALS: %i\n", type.c_str(), trials);
    for (int i = 0; target <= max; i++) // For each target value
    {
        times.clear();
        printf("%s\n%s(%i):\n\n", bar.c_str(), type.c_str(), target);
        for (int j = 0; j < size; j++) // For each function
        {
            for (int k = 0; k < trials; k++) // For each trial per value
            {
                auto t1 = getTime();
                val = funcs[j](target);
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
        target = i * 3;
    }
}

int main()
{
    std::string type;
    int max;
    int size;
    std::string *names;
    unsigned long long (**functions)(int);
    // getFactVariables(type, max, size, names, functions);
    getFibVariables(type, max, size, names, functions);
    testFunc(type, max, size, names, functions);

    return 0;
}