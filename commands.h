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

    void cd(File **currentDir, string nextDir);

    void cp(File *currentDir, string fileName);

    void type(File *file);
};

#endif // COMMANDS_H
