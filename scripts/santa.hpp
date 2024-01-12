#pragma once
#include <random>
#include <thread>
#include <atomic>
#include "christmas-tree.hpp"

class Santa{
private:
    static const std::chrono::milliseconds TIME_BEETWEN_DELIVERS; 
    int maxNumberOfDecorations;
public:
    std::atomic<int> broughtDecorations = 0;
    Santa(int maxNumberOfDecorations);
    ~Santa();
    
    void deliverDecorations(std::atomic<int> &decorations);
};