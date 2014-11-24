#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <fstream>
#include "file.h"

class File; //foward declaration

namespace commands
{
    std::list<string>* parseCommand(string command);

    void mkdir(File *currentDir, string dirName);

    void dir(File *currentDir);

    void cd(File **currentDir, string nextDir);

    void cp(File *currentDir, string fileName);

    void type(File *file);
};

#endif // COMMANDS_H
