#pragma once
#include <vector>
#include <iostream>

class ChristmasTree{
public:
    static const char UNDECORATED_SYMBOL = '^';
    static const char DECORATED_SYMBOL = 'o';
    static const char EMPTY_SCAFFOLDING_SYMBOL = '_';
    int height;
    std::vector<std::vector<char>> tree;
    std::vector<std::vector<char>> scaffolding;

    ChristmasTree(int treeHeight);
    ~ChristmasTree();
    
    void display();
    bool isDecorated();
};
