#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include "christmas-tree.hpp"
#include "santa.hpp"
#include "elf.hpp"

void loadVariables(int &christmasTreeHeight, int &numberOfElves, int &maxNumberOfDecorations);
void clearScreen();

// std::this_thread::sleep_for(std::chrono::milliseconds())
// std::random_device seed;
// std::mt19937 generator(seed());
// std::uniform_int_distribution<int> random(1, 100);
    

int main(){
    int christmasTreeHeight = 5;
    int numberOfElves = 5;
    int maxNumberOfDecorations = 5;
    std::atomic<int> decorations = 0;
    ChristmasTree christmasTree(christmasTreeHeight);
    std::vector<std::vector<std::mutex>> treeAccessGuard(christmasTreeHeight);
    Santa santa(maxNumberOfDecorations);
    std::vector<Elf> elves(numberOfElves);
    std::vector<std::thread> elfThreads;

    // Create threads
    std::thread santaThread([&santa, &christmasTree, &decorations]{ 
        santa.deliverDecorations(decorations); 
    });
    for (int i = 0; i < numberOfElves; i++){
        std::thread thread([i, &elves, &christmasTree, &decorations, &treeAccessGuard]{
            elves[i].decorate(christmasTree, decorations, treeAccessGuard);
        });
        elfThreads.push_back(std::move(thread));
    }

    christmasTree.display();

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    // for (auto &i : christmasTree.tree){
    //     for (auto &j : i){
    //         j = 'o';
    //     }
    // }

    // Join threads to complete the program // FIXME: change join to detach
    santaThread.detach();
    for (int i = 0; i < numberOfElves; i++){
        elfThreads[i].detach();
    }

    return 0;
}

void loadVariables(int &christmasTreeHeight, int &numberOfElves, int &maxNumberOfDecorations){
    do {
        std::cout << "Enter the christmas tree height: ";
        std::cin >> christmasTreeHeight;
    } while (christmasTreeHeight < 1);
    do {
        std::cout << "Enter the number of elves: ";
        std::cin >> numberOfElves;
    } while (numberOfElves < 1);
    do {
        std::cout << "Enter the maximum number of decorations: ";
        std::cin >> maxNumberOfDecorations;
    } while (maxNumberOfDecorations < 1);
}

void clearScreen(){
    printf("\033[2J\033[H");
}