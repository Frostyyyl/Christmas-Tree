#include "santa.hpp"

Santa::~Santa(){}

Santa::Santa(int maxDecorations) : maxDecorations{maxDecorations}{}

void Santa::deliverDecorations(ChristmasTree &christmasTree, std::atomic<int> &decorations){
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<int> random(1, maxDecorations / 2);

    while (!christmasTree.isDecorated()){
        int producedDecorations = random(generator);

        if (decorations + producedDecorations <= maxDecorations){
            decorations += producedDecorations;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}