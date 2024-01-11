#include "christmas-tree.hpp"

ChristmasTree::~ChristmasTree(){}

ChristmasTree::ChristmasTree(int treeHeight) : height{treeHeight}{
    char symbol = UNDECORATED_SYMBOL;
    tree.resize(treeHeight);
    for (int i = 0; i < treeHeight; i++){
        for (int j = 0; j < (treeHeight - i) * 2 - 1; j++){
            tree[i].push_back(symbol);
        }
    }
    symbol = EMPTY_SCAFFOLDING_SYMBOL;
    scaffolding.resize(treeHeight);
    for (int i = 0; i < treeHeight; i++){
        for (int j = 0; j < treeHeight - i; j++){
            scaffolding[i].push_back(symbol);
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
        std::cout << "  ├";
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

        std::cout << "┤" << '\n';
    }
}

bool ChristmasTree::isDecorated(){
    for (auto &i : tree){
        for (auto &j : i){
            if (j != DECORATED_SYMBOL){
                return false;
            }
        }
    }
    return true;
}


