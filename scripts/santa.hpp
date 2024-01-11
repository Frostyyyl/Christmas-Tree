#pragma once
#include <random>
#include <thread>
#include <atomic>
#include "christmas-tree.hpp"

class Santa{
private:
    int maxNumberOfDecorations;
public:
    Santa(int maxNumberOfDecorations);
    ~Santa();
    
    void deliverDecorations(std::atomic<int> &decorations);
};