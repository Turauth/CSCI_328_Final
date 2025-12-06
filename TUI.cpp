#include "Tree.h"
#include "commandLogic.h"
#include <thread>

int main() {
    bool masterLoopSwitch{ true };
    bool firstIterStatus{ true };
    string command{};
    string name{};
    Tree laurelin( "root" );
    Dir* currentDirectoryPtr{ laurelin.rootPtr };

    // Utilize a master loop that takes user input from the command line then branches depending on the 
    // command input.
    while (masterLoopSwitch == true) {

        if (firstIterStatus == true) {
            firstIterStatus = false;
            cout << "Type 'help' for a list of commands and their functionalities.\n" << endl;
        }
        cout << currentDir(currentDirectoryPtr);
        getline(cin, command);

        // Use if/else logic to perform the command inputted in the terminal.

        // After finishing the logic, I tried to figure out for a few hours how I might be able to 
        // separate user interface meaningfully from the background processes. After extensive Claude
        // reading, looking at classmates' work, and looking at documentation, I conclude that it
        // would take extensive restructuring to meaningfully parallelize the two.
        if (command == "create" || command == "mkdir") {
            thread t(create, laurelin, currentDirectoryPtr, command, name);
            t.join();
        }

        else if (command == "read") {
            cout << "Enter file name to read: ";
            getline(cin, name);
            thread t(read, currentDirectoryPtr, name);
            t.join();
        }
        
        else if (command == "update") {
            cout << "Enter file name to update: ";
            getline(cin, name);
            thread t(update, currentDirectoryPtr, name);
            t.join();
        }
     
        else if (command == "delete") {
            cout << "Enter file or folder name to delete: ";
            getline(cin, name);
            thread t(del, currentDirectoryPtr, name);
            t.join();
        }
        
        else if (command == "help") {
            thread t(help);
            t.join();
        }

        else if (command == "quit") {
            masterLoopSwitch = false;
        }

        else if (command == "cd") {
            cout << "Enter name of the subdirectory to enter or '..' to navigate up one directory: " << endl;
            getline(cin, name);
            currentDirectoryPtr = cd(currentDirectoryPtr, name);            
        }

        else if (command == "ls") {
            thread t(ls, currentDirectoryPtr);
            t.join();
        }

        else {
            cout << "The last input was invalid." << endl;
        }
    }
    return 0;
}