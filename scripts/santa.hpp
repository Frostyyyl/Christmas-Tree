#pragma once
#include <random>
#include <thread>
#include <atomic>
#include <iostream>
#include "christmas-tree.hpp"

class Santa{
private:
    int maxDecorations;
public:
    Santa(int maxDecorations);
    ~Santa();
    
    void deliverDecorations(ChristmasTree &christmasTree, std::atomic<int> &decorations);
};