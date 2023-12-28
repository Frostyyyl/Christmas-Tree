#pragma once
#include <vector>
#include <iostream>

class ChristmasTree{
public:
    static const char NOT_DECORATED_MARK = '^';
    static const char DECORATED_MARK = 'o';
    static const char EMPTY_SCAFFOLDING_MARK = '_';
    static const char ELF_MARK = 'e';
    static const char ELF_WORKING_MARK = 'w';
    int treeHeight;
    std::vector<std::vector<char>> tree;
    std::vector<std::vector<char>> scaffolding;

    ChristmasTree(int treeHeight);
    ~ChristmasTree();
    
    void display();
    const bool isDecorated();
};
