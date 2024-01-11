#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <memory>
#include "christmas-tree.hpp"
#include "santa.hpp"
#include "elf.hpp"

void handleInput(int &christmasTreeHeight, int &numberOfElves, int &maxNumberOfDecorations);
void handleOutput(ChristmasTree &christmasTree);
void clearScreen();

int main(){
    int christmasTreeHeight = 3;
    int numberOfElves = 3;
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
    std::thread outputThread([&christmasTree]{
        handleOutput(christmasTree);
    });
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


    std::this_thread::sleep_for(std::chrono::seconds(20));

    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    // for (auto &i : christmasTree.tree){
    //     for (auto &j : i){
    //         j = 'o';
    //     }
    // }

    // Join threads to complete the program
    outputThread.detach();
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

void handleOutput(ChristmasTree &christmasTree){
    while (true){        
        // clearScreen();
        christmasTree.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
}

void clearScreen(){
    printf("\033[2J\033[H");
}