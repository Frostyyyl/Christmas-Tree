#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <memory>
#include "christmas-tree.hpp"
#include "santa.hpp"
#include "elf.hpp"

void handleInput(int &christmasTreeHeight, int &numberOfElves, int &maxNumberOfDecorations);
void clearScreen();

int main(){
    int christmasTreeHeight = 5;
    int numberOfElves = 5;
    int maxNumberOfDecorations = 5;
    ChristmasTree christmasTree(christmasTreeHeight);
    Santa santa(maxNumberOfDecorations);
    std::atomic<int> decorations = 0;
    std::vector<Elf> elves(numberOfElves);
    std::vector<std::vector<std::unique_ptr<std::mutex>>> treeAccessGuard(christmasTreeHeight);
    std::vector<std::vector<std::unique_ptr<std::mutex>>> scaffoldingAccessGuard(christmasTreeHeight);

    // Resize the access guards to match the size of the christmas tree and scaffolding
    for (int i = 0; i < christmasTreeHeight; i++){
        for (int j = 0; j < christmasTree.tree[i].size(); j++){
            std::unique_ptr<std::mutex> mutex{ new std::mutex };
            treeAccessGuard[i].push_back(std::move(mutex));
        }
        for (int j = 0; j < christmasTree.scaffolding[i].size(); j++){
            std::unique_ptr<std::mutex> mutex{ new std::mutex };
            scaffoldingAccessGuard[i].push_back(std::move(mutex));
        }
    }

    // Create threads
    std::thread santaThread([&santa, &christmasTree, &decorations]{ 
        santa.deliverDecorations(decorations); 
    });
    std::vector<std::thread> elfThreads;
    for (int i = 0; i < numberOfElves; i++){
        std::thread thread([i, &elves, &christmasTree, &decorations, &treeAccessGuard, &scaffoldingAccessGuard]{
            elves[i].decorate(christmasTree, decorations, treeAccessGuard, scaffoldingAccessGuard);
        });
        elfThreads.push_back(std::move(thread));
    }

    // Main program loop
    while (!christmasTree.isDecorated()){
        clearScreen();
        christmasTree.display();
        std::cout << "Current decorations: " << decorations << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    // Show the result
    clearScreen();
    christmasTree.display();
    

    // Join threads to complete the program
    santaThread.detach();
    for (auto &elfThread : elfThreads){
        elfThread.detach();
    }

    return 0;
}



void handleInput(int &christmasTreeHeight, int &numberOfElves, int &maxNumberOfDecorations){
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