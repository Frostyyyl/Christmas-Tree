#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <atomic>
#include "christmas-tree.hpp"
#include "santa.hpp"
#include "elf.hpp"

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

    Santa santa(maxDecorations);
    std::vector<Elf> elves(numberOfElves);
    ChristmasTree christmasTree(christmasTreeHeight);
    std::thread santaThread([&santa, &christmasTree, &decorations]{ 
        santa.deliverDecorations(christmasTree, decorations); 
    });


    christmasTree.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    for (auto &i : christmasTree.tree){
        for (auto &j : i){
            j = 'o';
        }
    }
    christmasTree.display();


    santaThread.join();

    return 0;
}