#include "santa.hpp"

// Assign value to santa's time beetwen delivers
const std::chrono::milliseconds Santa::TIME_BEETWEN_DELIVERS = std::chrono::milliseconds(900);

Santa::~Santa(){}

Santa::Santa(int maxNumberOfDecorations) : maxNumberOfDecorations{maxNumberOfDecorations}{}

void Santa::deliverDecorations(std::atomic<int> &decorations){
    std::random_device seed;
    std::mt19937 generator(seed());
    // Modifiable range of how many decorations santa can deliver
    std::uniform_int_distribution<int> random(1, std::max(1, maxNumberOfDecorations / 2)); 
    int producedDecorations = 0;

    while (true){
        std::this_thread::sleep_for(TIME_BEETWEN_DELIVERS);
        producedDecorations = random(generator);

        if (decorations + producedDecorations <= maxNumberOfDecorations)
            decorations += producedDecorations;
    }
}