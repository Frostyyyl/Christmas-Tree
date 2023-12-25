#pragma once
#include <vector>
#include <iostream>
#include "santa.hpp"
#include "elf.hpp"


class ChristmasTree{
private:
    static const char NOT_DECORATED_MARK = '^';
    static const char DECORATED_MARK = 'o';
    static const char EMPTY_SCAFFOLDING_MARK = '_';
    static const char ELF_MARK = 'e';
public:
    int treeHeight;
    std::vector<std::vector<char>> tree;
    std::vector<std::vector<char>> scaffolding;

    ChristmasTree(int treeHeight);
    ~ChristmasTree();
    
    void display();
    bool isDecorated();
};
