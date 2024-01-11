#include "elf.hpp"

Elf::~Elf(){}

Elf::Elf(){}

std::mutex Elf::decorationsGuard;

void Elf::decorate(ChristmasTree &christmasTree, std::atomic<int> &decorations, std::vector<std::vector<std::unique_ptr<std::mutex>>> &treeAccessGuard){
    
    while (true){
        for (int i = 0; i < christmasTree.height; i++){
            for (int j = 0; j < christmasTree.tree[i].size(); j++){
                if (treeAccessGuard[i][j]->try_lock()){
                    if (i == 0 && j == 0){
                        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                        std::cout << "ZERO: " << i << ", " << j << ", id: " <<std::this_thread::get_id() << std::endl;
                        treeAccessGuard[i][j]->unlock();
                        break;
                    } else if (i == 0 && j == 1){
                        std::cout << "ONE: " << i << ", " << j << ", id: " <<std::this_thread::get_id() << std::endl;
                        treeAccessGuard[i][j]->unlock();
                        break;
                    } else {
                        std::cout << "Something else: " << i << ", " << j << ", id: " <<std::this_thread::get_id() << std::endl;
                        treeAccessGuard[i][j]->unlock();
                        break;
                    }
                }
            }          
        }
        break;
    }
}

void Elf::goHigher(int index, ChristmasTree &christmasTree, std::vector<std::vector<std::unique_ptr<std::mutex>>> &treeAccessGuard){
}