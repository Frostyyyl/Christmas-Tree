#include "elf.hpp"

// Assign values to times of elves activities
const std::chrono::milliseconds Elf::WAITING_TIME = std::chrono::milliseconds(200);
const std::chrono::milliseconds Elf::TAKING_DECORATION_TIME = std::chrono::milliseconds(500);
const std::chrono::milliseconds Elf::WORKING_TIME = std::chrono::milliseconds(2000);
const std::chrono::milliseconds Elf::CLIMBING_TIME = std::chrono::milliseconds(1200);
const std::chrono::milliseconds Elf::DESCENDING_TIME = std::chrono::milliseconds(1000);

std::mutex Elf::decorationsAccessGuard;

Elf::~Elf(){}

Elf::Elf(){}

void Elf::decorate(ChristmasTree &christmasTree, std::atomic<int> &decorations, std::vector<std::vector<std::unique_ptr
<std::mutex>>> &treeAccessGuard, std::vector<std::vector<std::unique_ptr<std::mutex>>> &scaffoldingAccessGuard){
    // Delay in order to display empty christmas tree
    std::this_thread::sleep_for(WAITING_TIME);

    while (true){
        getDecoration(decorations);
        while (currentHeight != christmasTree.height - 1){
            goHigher(christmasTree, scaffoldingAccessGuard);
            if (hangDecoration(christmasTree, treeAccessGuard)){
                break;
            }
        }
        // Go to the bottom
        while (currentHeight != -1){
            goLower(christmasTree, scaffoldingAccessGuard);
        }
    }
}

void Elf::goHigher(ChristmasTree &christmasTree, std::vector<std::vector<std::unique_ptr<std::mutex>>> &scaffoldingAccessGuard){
    if (currentHeight == christmasTree.height - 1){
        std::cerr << "ERROR: Tried going higher while at the top\n";
        return;
    }
    
    while (true){
        for (int i = 0; i < christmasTree.scaffolding[currentHeight + 1].size(); i++){
            if (scaffoldingAccessGuard[currentHeight + 1][i]->try_lock()){
                if (currentHeight != -1){
                    christmasTree.scaffolding[currentHeight][currentWidth] = ChristmasTree::EMPTY_SCAFFOLDING_SYMBOL;
                    scaffoldingAccessGuard[currentHeight][currentWidth]->unlock();
                }
                currentHeight++;
                currentWidth = i;
                christmasTree.scaffolding[currentHeight][currentWidth] = ELF_CLIMBING_SYMBOL;
                std::this_thread::sleep_for(CLIMBING_TIME);
                christmasTree.scaffolding[currentHeight][currentWidth] = ELF_WAITING_SYMBOL;
                return;
            }
        }
        std::this_thread::sleep_for(WAITING_TIME);
        // If the next floor is full of waiting elves, go down, wait and try to go up again 
        if (nextFloorIsFull(christmasTree)){
            if (currentHeight != -1){
                goLower(christmasTree, scaffoldingAccessGuard);
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                goHigher(christmasTree, scaffoldingAccessGuard);
            }
        }
    }
}

void Elf::goLower(ChristmasTree &christmasTree, std::vector<std::vector<std::unique_ptr<std::mutex>>> &scaffoldingAccessGuard){
    if (currentHeight == -1){
        std::cerr << "ERROR: Tried going lower while at the bottom\n";
        return;
    } else if (currentHeight == 0){
        christmasTree.scaffolding[currentHeight][currentWidth] = ChristmasTree::EMPTY_SCAFFOLDING_SYMBOL;
        scaffoldingAccessGuard[currentHeight][currentWidth]->unlock();
        currentHeight--;
        std::this_thread::sleep_for(DESCENDING_TIME);
        return;
    }
    
    while (true){
        for (int i = 0; i < christmasTree.scaffolding[currentHeight - 1].size(); i++){
            if (scaffoldingAccessGuard[currentHeight - 1][i]->try_lock()){
                christmasTree.scaffolding[currentHeight][currentWidth] = ChristmasTree::EMPTY_SCAFFOLDING_SYMBOL;
                scaffoldingAccessGuard[currentHeight][currentWidth]->unlock();
                currentHeight--;
                currentWidth = i;
                christmasTree.scaffolding[currentHeight][currentWidth] = ELF_DESCENDING_SYMBOL;
                std::this_thread::sleep_for(DESCENDING_TIME);
                christmasTree.scaffolding[currentHeight][currentWidth] = ELF_WAITING_SYMBOL;
                return;
            }
        }
        std::this_thread::sleep_for(WAITING_TIME);
    }
}

void Elf::getDecoration(std::atomic<int> &decorations){
    if (currentHeight != -1){
        std::cerr << "ERROR: Tried grabing decoration while not at the bottom\n";
        return; 
    }

    while (true){
        if (decorationsAccessGuard.try_lock()){
            if (decorations > 0){
                decorations--;
                std::this_thread::sleep_for(TAKING_DECORATION_TIME); // NOTE: To be decided if should be kept, moved or removed
                decorationsAccessGuard.unlock();
                return;
            }
            decorationsAccessGuard.unlock();
        }
        std::this_thread::sleep_for(WAITING_TIME);
    }     
}

bool Elf::nextFloorIsFull(ChristmasTree &christmasTree){
    for (auto &i : christmasTree.scaffolding[currentHeight + 1]){
        if (i != ELF_WAITING_SYMBOL){
            return false;
        }
    }
    return true;
}

bool Elf::hangDecoration(ChristmasTree &christmasTree, std::vector<std::vector<std::unique_ptr<std::mutex>>> &treeAccessGuard){
    for (int i = 0; i < christmasTree.tree[currentHeight].size(); i++){
        if (treeAccessGuard[currentHeight][i]->try_lock()){
            if (christmasTree.tree[currentHeight][i] == ChristmasTree::UNDECORATED_SYMBOL){
                christmasTree.scaffolding[currentHeight][currentWidth] = ELF_WORKING_SYMBOL;
                std::this_thread::sleep_for(WORKING_TIME);
                christmasTree.tree[currentHeight][i] = ChristmasTree::DECORATED_SYMBOL;
                christmasTree.scaffolding[currentHeight][currentWidth] = ELF_WAITING_SYMBOL;
                treeAccessGuard[currentHeight][i]->unlock();
                return true;
            }
            treeAccessGuard[currentHeight][i]->unlock();
        }
    }
    return false;
}