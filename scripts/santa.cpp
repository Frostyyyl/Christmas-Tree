#include "santa.hpp"
#include <iostream>

Santa::~Santa(){}

Santa::Santa(int maxNumberOfDecorations) : maxNumberOfDecorations{maxNumberOfDecorations}{}

void Santa::deliverDecorations(std::atomic<int> &decorations){
    std::random_device seed;
    std::mt19937 generator(seed());
    // Modifiable range of how many decorations santa can deliver
    std::uniform_int_distribution<int> random(1, std::max(1, maxNumberOfDecorations / 2)); 
    int producedDecorations = 0;

    while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        producedDecorations = random(generator);

        if (decorations + producedDecorations <= maxNumberOfDecorations){
            decorations += producedDecorations;
            std::cout << producedDecorations << std::endl;
        }
    }
}