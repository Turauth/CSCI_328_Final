#pragma once
using namespace std;
#include "Tree.h"
#include <chrono>
#include <ctime>

string currentDir(Dir* currentDirPtr) {
    string currentDirLocation{ currentDirPtr->name };

    // Add ancestral directories to the file location until all ancestral directories are part of the
    // directory location string.
    while (currentDirPtr->parent != nullptr) {
        currentDirPtr = currentDirPtr->parent;
        currentDirLocation = currentDirPtr->name + "/" + currentDirLocation;
    }
    currentDirLocation = currentDirLocation + "/ ";
    return currentDirLocation;
}

void create(Tree tree, Dir* currentDirPtr, string command, string name) {
    if (size(currentDirPtr->files) + size(currentDirPtr->subfolders) >= 8) {
            cout << "There are more than eight files or folders in this directory. Update existing "
            << "files or delete files or folders to add more.\n" << endl;
        }
    else {

        // For file generation, add metadata to a File object before adding it to the current
        // directory's file vector.
        if (command == "create") {
            cout << "Enter new file name: ";
            getline(cin, name);
            string location{ currentDir(currentDirPtr) };
            time_t currentTime{ chrono::system_clock::to_time_t(chrono::system_clock::now()) };

            cout << "Enter file contents: ";
            string contents{};
            getline(cin, contents);

            File createdFile(name, currentTime, location, contents);
            currentDirPtr->files.push_back(createdFile);
        }
        else if (command == "mkdir") {
            cout << "Enter new directory name: ";
            getline(cin, name);
            tree.mkdir(name, currentDirPtr);
        }
    }
}


// The rest of these functions except the help function iterate through file or subfolder vectors to 
// perform the desired operation.
void read(Dir* curDirPtr, string name) {
    bool relativeFound{ false };
    for (File& i : curDirPtr->files) {
        if (name == i.m_name) {
            cout << "\nName: " << i.m_name << endl;
            cout << "Contents: " << i.m_contents << endl;
            cout << "Creation time: " << ctime(&i.m_creationTime);
            cout << "Location: " << i.m_location << "\n\n";
            relativeFound = true;
        }
    }
    if (relativeFound == false) {
        cout << "The inputted file name '" << name << "' was not found." << endl;
    }
}

void update(Dir* curDirPtr, string name) {
    bool relativeFound{ false };
    for (File& i : curDirPtr->files) {
        if (name == i.m_name) {
            cout << "Here are the current contents of this file: " << i.m_contents << 
            "\nEnter new contents for this file: ";
            getline(cin, i.m_contents);
            relativeFound = true;
        }
    }
    if (relativeFound == false) {
        cout << "The inputted file name '" << name << "' was not found." << endl;
    }
}

void del(Dir* curDirPtr, string name) {
    
    bool relativeFound{ false };
    int j{ 0 };
    for (File& i : curDirPtr->files) {
        if (name == i.m_name) {
            curDirPtr->files.erase(curDirPtr->files.begin() + j);
            relativeFound = true;
        }
        j+=1;
    }

    j = 0;
    if (relativeFound == false) {
        for (Dir* i : curDirPtr->subfolders) {
            if (name == i->name) {
                delete i;
                curDirPtr->subfolders.erase(curDirPtr->subfolders.begin() + j);
                relativeFound = true;
            }
            j+=1;
        }
    }

    if (relativeFound == false) {
        cout << "No files or folder with the name '" << name << "' were found." << endl;
    }
}

Dir* cd(Dir* curDirPtr, string name) {
    bool relativeFound{ false };
    for (Dir* i : curDirPtr->subfolders) {
        if (name == i->name) {
            curDirPtr = i;            
            return curDirPtr;
        }
    }
    if (name == ".." && curDirPtr->parent != nullptr) {
        curDirPtr = curDirPtr->parent;
        return curDirPtr;
    }
    
    if (relativeFound == false) {
        cout << "\nThe inputted folder name ('" << name << "') was not found. If '..' was entered,"
        << " this is the root folder and there is no directory to navigate up to.\n" << endl;
    }
    return curDirPtr;
}

void ls(Dir* currentDirPtr) {
    for (File& i : currentDirPtr->files) {
        cout << i.m_name << endl;
    }
    for (Dir* i : currentDirPtr->subfolders) {
        cout << i->name << " (folder)" << endl;
    }
    cout << "\n";
}

void help() {
    cout << "For all functions, type the keyword and press enter. Then, if applicable, type a file or" <<
    "folder name and press enter." << endl;
    cout << "create\tThis function allows files to be made with contents and metadata." << endl;
    cout << "read\tThis function prints the contents and metadata of a specified file." << endl;
    cout << "update\tThis function allows the the contents of a specified file to be updated." << endl;
    cout << "delete\tThis function allows a specified file or folder to be deleted." << endl;
    cout << "mkdir\tThis function allows a specified folder to be made." << endl;
    cout << "ls\tThis function outputs the names of all the files and folders in the current directory. Folder names are followed by" <<
    "' (folder)'." << endl;
    cout << "quit\tThis function exits the file system simulation.\n" << endl;
}