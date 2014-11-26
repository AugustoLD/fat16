#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <fstream>
#include <vector>
#include "file.h"

class File; //foward declaration

namespace commands
{
    std::vector<string>* parseCommand(string command);

    File *startRoot();

    void mkdir(File *currentDir, string dirName);

    void dir(File *currentDir);
    void dirFile(File *file);


    void cd(File **currentDir, string nextDir);

    void cp(File *currentDir, string fileName);
    void cp(File *currenDir, string fileName, string newFileName);

    void copyFile(File *currentDir, string fileName, string newFileName);

    void copyFromFat(File *currentDir, string fileName, string newFileName);

    void type(File *file);

    void help();
};

#endif // COMMANDS_H
