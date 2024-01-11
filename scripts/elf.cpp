#include "elf.hpp"

Elf::~Elf(){}

Elf::Elf(){}

std::mutex Elf::decorationsGuard;

void Elf::decorate(ChristmasTree &christmasTree, std::atomic<int> &decorations, std::vector<std::vector<std::mutex>> &treeAccessGuard){
    while (true){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        decorationsGuard.lock();
        if (decorations > 0){
            decorations--;
            std::cout << std::this_thread::get_id() << ": " << decorations << '\n';
        }
        decorationsGuard.unlock();
    }
}

void Elf::increaseSemaphore(int index, ChristmasTree &christmasTree, std::vector<std::vector<std::mutex>> &treeAccessGuard){
}