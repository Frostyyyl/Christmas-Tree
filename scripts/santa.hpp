#pragma once
#include <random>
#include <thread>
#include <atomic>
#include <iostream>

class Santa{
private:
    int maxDecorations;
public:
    Santa(int maxDecorations);
    ~Santa();
    
    void deliverDecorations(std::atomic<int> &decorations);
};