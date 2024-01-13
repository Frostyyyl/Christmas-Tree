#pragma once
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include "christmas-tree.hpp"

class Elf{
private:
    static const std::chrono::milliseconds WAITING_TIME;
    static const std::chrono::milliseconds WORKING_TIME;
    static const std::chrono::milliseconds CLIMBING_TIME;
    static const std::chrono::milliseconds DESCENDING_TIME;
    static const std::chrono::milliseconds TAKING_DECORATION_TIME;
    static std::mutex decorationsAccessGuard;
    int currentHeight = -1;
    int currentWidth = 0;
    void getDecoration(std::atomic<int> &decorations);
    void goHigher(ChristmasTree &christmasTree, std::vector<std::vector<std::unique_ptr<std::mutex>>> &scaffoldingAccessGuard);
    void goLower(ChristmasTree &christmasTree, std::vector<std::vector<std::unique_ptr<std::mutex>>> &scaffoldingAccessGuard);
    bool nextFloorIsFull(ChristmasTree &christmasTree);
    bool hangDecoration(ChristmasTree &ChristmasTree, std::vector<std::vector<std::unique_ptr<std::mutex>>> &treeAccessGuard); 
public:
    static const char ELF_WORKING_SYMBOL = 'w';
    static const char ELF_WAITING_SYMBOL = 's';
    static const char ELF_CLIMBING_SYMBOL = 'c';
    static const char ELF_DESCENDING_SYMBOL = 'd';
    Elf();
    ~Elf();

    void decorate(ChristmasTree &christmasTree, std::atomic<int> &decorations, std::vector<std::vector<std::unique_ptr
    <std::mutex>>> &treeAccessGuard, std::vector<std::vector<std::unique_ptr<std::mutex>>> &scaffoldingAccessGuard);
};