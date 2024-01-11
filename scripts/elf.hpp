#pragma once
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include "christmas-tree.hpp"

#define WORKING_TIME 1000
#define CLIMBING_TIME 500
#define DESCENDING_TIME 400

class Elf{
private:
    int currentLevel = 0;
    int currentSpace = 0;
    static std::mutex decorationsGuard;
public:
    Elf();
    ~Elf();

    void decorate(ChristmasTree &christmasTree, std::atomic<int> &decorations, std::vector<std::vector<std::mutex>> &treeAccessGuard);
    void increaseSemaphore(int index, ChristmasTree &christmasTree, std::vector<std::vector<std::mutex>> &treeAccessGuard);
};