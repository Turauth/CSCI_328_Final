#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include "File.h"

// Define a class for directories with a pointer to its parent directory and vectors to contain child
// files and subfolders.
class Dir {
    public:
        string name{};
        Dir* parent;
        vector<File> files{};
        vector<Dir*> subfolders{};
};

// Define a tree class to define a root directory and make linked directories.
class Tree {
    public:
        Dir* rootPtr;

        // Make a default constructor with the name of the root directory as a parameter.
        Tree (string name) {
            rootPtr = new Dir;
            rootPtr->name = name;
        }

        // Make a function to add directories to the tree (https://www.geeksforgeeks.org/cpp/cpp-binary-search-tree/).
        Dir* mkdir(string name, Dir* parent) {
            Dir* newDir = new Dir;
            newDir->name = name;
            newDir->parent = parent;
            parent->subfolders.push_back(newDir);
            return newDir;
        }
};