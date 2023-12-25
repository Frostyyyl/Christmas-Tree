#include "christmas-tree.hpp"

ChristmasTree::~ChristmasTree(){}

ChristmasTree::ChristmasTree(int treeHeight) : treeHeight{treeHeight}{
    tree.resize(treeHeight);
    for (int i = 0; i < treeHeight; i++){
        tree[i].resize((treeHeight - i) * 2 - 1);
        for (auto &j : tree[i]){
            j = NOT_DECORATED_MARK;
        }
    }

    scaffolding.resize(treeHeight);
    for (int i = 0; i < treeHeight; i++){
        scaffolding[i].resize(treeHeight - i);
        for (auto &j : scaffolding[i]){
            j = EMPTY_SCAFFOLDING_MARK;
        }
    }
}

void ChristmasTree::display(){
    for (int i = 0; i < treeHeight; i++){
        // Displaing christmas tree
        for (int j = 0; j < ((treeHeight - (i + 1)) * 2); j++){
            std::cout << " ";
        }
        for (auto& j : tree[treeHeight - 1 - i]){
            std::cout << j << " ";
        }
        for (int j = 0; j < ((treeHeight - (i + 1)) * 2); j++){
            std::cout << " ";
        }

        // Displaing scaffolding
        std::cout << "  ├";
        for (int j = 0; j < ((treeHeight - (i + 1))); j++){
            std::cout << "─";
        }
        std::cout << " ";
        for (auto& j : scaffolding[treeHeight - 1 - i]){
            std::cout << j << " ";
        }
        for (int j = 0; j < ((treeHeight - (i + 1))); j++){
            std::cout << "─";
        }

        std::cout << "┤" << std::endl;
    }
}

bool ChristmasTree::isDecorated(){
    for (auto &i : tree){
        for (auto &j : i){
            if (j != DECORATED_MARK){
                return false;
            }
        }
    }
    return true;
}


