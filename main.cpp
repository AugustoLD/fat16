#include <iostream>
#include <fstream>
#include <unistd.h>
#include "fat.h"
#include "file.h"
#include "commands.h"
#include "globals.h"

using namespace std;

int main()
{

    //truncate("/home/augusto/c++/disc.dat", MAX_CLUSTER*CLUSTER_SIZE);

    /*  Iniciate root directory  */
    File *rootDir = new File;
    FileType rootType;
    rootType.directory = true;
    rootDir->setFile_type(rootType);
    rootDir->setFile_name("/");
    rootDir->setDirectoryTable(new DirectoryTable);
    rootDir->setParent(NULL);
    disc.open("/home/augusto/c++/disc.dat", ios::binary | ios::out | ios::in);

    File **currentDir = &rootDir;
    fat = new Fat;

    list<string> *command_args;

    while(true) {
        cout << "[" << (*currentDir)->getFile_name() << "] => ";

        string input;
        getline(std::cin, input);
        command_args = commands::parseCommand(input);
        input = command_args->front();
        if(input.compare("mkdir") == 0) {
            if(command_args->size() > 1) commands::mkdir(*currentDir, command_args->back());
            else cout << "Missing directory name!" << endl;
        } else if(input.compare("dir") == 0) {
            commands::dir(*currentDir);
        } else if(input.compare("cd") == 0) {
            if(command_args->size() > 1) commands::cd(currentDir, command_args->back());
            else cout << "Missing directory name!" << endl;
        } else if(input.compare("cp") == 0) {
            if(command_args->size() > 1) commands::cp(*currentDir, command_args->back());
            else cout << "Missing arguments!" << endl;
        } else if(input.compare("type") == 0) {
            if(command_args->size() > 1) {
                File *file;
                file = (*currentDir)->getDirectoryTable()->findFile(command_args->back());
                if(file == NULL) {
                    cout << "File not found!" << endl;
                } else {
                    commands::type(file);
                }
            }
        }

    }

    return 0;
}
