#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include "fat.h"
#include "file.h"
#include "commands.h"
#include "globals.h"

using namespace std;

int main()
{
    /*  Iniciate root directory  */
    File *rootDir = commands::startRoot();
    disc.open("../disc.dat", ios::binary | ios::out | ios::in);
    fat = new Fat;
    File **currentDir = &rootDir;

    vector<string> *command_args;

    while(true) {
        cout << "[" << (*currentDir)->getFile_name() << "] => ";

        string input;
        getline(std::cin, input);
        command_args = commands::parseCommand(input);
        input = command_args->front();
        if(input.compare("mkdir") == 0) {
            if(command_args->size() > 1) commands::mkdir(*currentDir, command_args->at(1));
            else cout << "missing directory name" << endl;
        } else if(input.compare("dir") == 0) {
            if(command_args->size() > 1) {
                File *file;
                file = (*currentDir)->getDirectoryTable()->findFile(command_args->at(1));
                if(file == NULL) {
                    cout << command_args->at(1) << ": file not found" << endl;
                } else {
                    commands::dirFile(file);
                }
            } else {
                commands::dir(*currentDir);
            }
        } else if(input.compare("cd") == 0) {
            if(command_args->size() > 1) commands::cd(currentDir, command_args->at(1));
            else cout << "missing directory name" << endl;
        } else if(input.compare("cp") == 0) {
            if(command_args->size() > 1) commands::cp(*currentDir, command_args->at(1));
            else cout << "missing file path" << endl;
        } else if(input.compare("type") == 0) {
            if(command_args->size() > 1) {
                File *file;
                file = (*currentDir)->getDirectoryTable()->findFile(command_args->at(1));
                if(file == NULL) {
                    cout << command_args->at(1) << ": file not found" << endl;
                } else {
                    if(file->getFile_type().directory) {
                        cout << file->getFile_name() << " is a directory" << endl;
                    } else {
                        commands::type(file);
                    }
                }
            } else {
                cout << "missing file name" << endl;
            }
        } else if(input.compare("format") == 0) {
            delete fat;
            disc.close();
            delete rootDir;
            rootDir = commands::startRoot();
            disc.open("../disc.dat", ios::binary | ios::out | ios::in | ios::trunc);
            fat = new Fat;
            currentDir = &rootDir;
            cout << "system successfully formated" << endl;
        } else {
            cout << command_args->front() << ": command not found!" << endl;
        }

    }

    return 0;
}
