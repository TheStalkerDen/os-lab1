#pragma once
#include <iostream>
#include <iomanip>

template<typename T> void printTableElement(T t, const int& width)
{
    std::cout << std::setw(width) << std::setfill(' ') << t << "|";
}