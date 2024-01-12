#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <memory>
#include "christmas-tree.hpp"
#include "santa.hpp"
#include "elf.hpp"

void handleInput(int &christmasTreeHeight, int &numberOfElves, int &maxNumberOfDecorations, std::string &screenClear);
void clearScreen();

int main(){
    int christmasTreeHeight = 0;
    int numberOfElves = 0;
    int maxNumberOfDecorations = 0;
    std::string screenClear = "";

    // Display info and request variable values
    handleInput(christmasTreeHeight, numberOfElves, maxNumberOfDecorations, screenClear);

    ChristmasTree christmasTree(christmasTreeHeight);
    std::string screenDivider((christmasTree.tree[0].size() * 2 + christmasTree.scaffolding[0].size() * 2 + 5), '-');
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
        if (screenClear == "yes" || screenClear == "Yes" || screenClear == "y")
            clearScreen();
        std::cout << screenDivider << std::endl;
        christmasTree.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
    
    // Show the result
    if (screenClear == "yes" || screenClear == "Yes" || screenClear == "y")
        clearScreen();
    std::cout << screenDivider << std::endl;
    christmasTree.display();
    std::cout << screenDivider << std::endl;
    

    // Join threads to complete the program
    santaThread.detach();
    for (auto &elfThread : elfThreads){
        elfThread.detach();
    }

    return 0;
}



void handleInput(int &christmasTreeHeight, int &numberOfElves, int &maxNumberOfDecorations, std::string &screenClear){
    clearScreen();
    std::cout   << "---------------------------------------------\n"
                << "-         Christmas Tree Decorating         -\n"
                << "---------------------------------------------\n"
                << "Symbols:\n"
                << "c - elf is climbing\n"
                << "d - elf is descending\n"
                << "w - elf is working\n"
                << "s - elf is waiting\n"
                << "---------------------------------------------\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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
    std::cout << "Should the screen be cleared? (Yes/No): ";
    std::cin >> screenClear;
}

void clearScreen(){
    std::cout << "\033[2J\033[H";
}