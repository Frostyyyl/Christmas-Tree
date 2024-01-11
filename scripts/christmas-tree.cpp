#include "christmas-tree.hpp"

ChristmasTree::~ChristmasTree(){}

ChristmasTree::ChristmasTree(int treeHeight) : height{treeHeight}{
    // Inicialize the christmas tree
    tree.resize(treeHeight);
    for (int i = 0; i < treeHeight; i++){
        tree[i].resize((treeHeight - i) * 2 - 1);
        for (auto &j : tree[i]){
            j = UNDECORATED_SYMBOL;
        }
    }
    // Inicialize the scaffolding
    scaffolding.resize(treeHeight);
    for (int i = 0; i < treeHeight; i++){
        scaffolding[i].resize(treeHeight - i);
        for (auto &j : scaffolding[i]){
            j = EMPTY_SCAFFOLDING_SYMBOL;
        }
    }
}

void ChristmasTree::display(){
    for (int i = 0; i < height; i++){
        // Display christmas tree
        for (int j = 0; j < ((height - (i + 1)) * 2); j++){
            std::cout << " ";
        }
        for (auto& j : tree[height - 1 - i]){
            std::cout << j << " ";
        }
        for (int j = 0; j < ((height - (i + 1)) * 2); j++){
            std::cout << " ";
        }

        // Display scaffolding
        std::cout << ((i == 0) ? "  ┌" : "  ├");
        for (int j = 0; j < ((height - (i + 1))); j++){
            std::cout << "─";
        }
        std::cout << " ";
        for (auto& j : scaffolding[height - 1 - i]){
            std::cout << j << " ";
        }
        for (int j = 0; j < ((height - (i + 1))); j++){
            std::cout << "─";
        }
        std::cout << ((i == 0) ? "┐\n" : "┤\n");
    }
}

bool ChristmasTree::isDecorated(){
    for (auto &i : tree){
        for (auto &j : i){
            if (j != DECORATED_SYMBOL)
                return false;
        }
    }
    return true;
}


