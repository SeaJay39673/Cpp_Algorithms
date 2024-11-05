/*
    Author: Christopher Edmunds
    Last Updated: 11/5/2024
    Description:
        Helper functions to share between algorithms
*/
#pragma once
#include <chrono>

// Get current time
auto getTime()
{
    return std::chrono::high_resolution_clock::now();
}