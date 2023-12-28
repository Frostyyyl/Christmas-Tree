#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <atomic>
#include "christmas-tree.hpp"
#include "santa.hpp"
#include "elf.hpp"

void clearScreen();

// std::this_thread::sleep_for(std::chrono::milliseconds())

    // std::random_device seed;
    // std::mt19937 generator(seed());
    // std::uniform_int_distribution<int> random(1, 100);

int main(){
    int christmasTreeHeight{};
    int numberOfElves{};
    int maxDecorations{};
    std::atomic<int> decorations{};

    // std::cout << "Enter the tree height: ";
    // std::cin >> christmasTreeHeight;
    // std::cout << "Enter the number of elves: ";
    // std::cin >> numberOfElves;
    christmasTreeHeight = 5;
    numberOfElves = 3;
    maxDecorations = christmasTreeHeight + 1; 
    
    ChristmasTree christmasTree(christmasTreeHeight);
    Santa santa(maxDecorations);
    std::vector<Elf> elves(numberOfElves);
    std::vector<std::thread> elvesThreads;

    std::thread santaThread([&santa, &christmasTree, &decorations]{ 
        santa.deliverDecorations(christmasTree, decorations); 
    });

    for (int i = 0; i < numberOfElves; i++){
        std::thread thread([i, &elves]{
            elves[i].decorate();
        });
        elvesThreads.push_back(std::move(thread));
    }



    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    for (auto &i : christmasTree.tree){
        for (auto &j : i){
            j = 'o';
        }
    }


    santaThread.join();

    for (int i = 0; i < numberOfElves; i++){
        elvesThreads[i].join();
    }

    return 0;
}

void clearScreen(){
    printf("\033[2J\033[H");
}