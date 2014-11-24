#ifndef DIRECTORY_TABLE_H
#define DIRECTORY_TABLE_H

#include <list>
#include <string>
#include "file.h"
#include "directory_table.h"

class File; //foward declaration

class DirectoryTable
{
public:
    DirectoryTable();

    std::list<File *> *getChildren() const;
    void setChildren(std::list<File *> *value);

    File *findFile(std::string fileName);
    //std::string getPathName();

private:
    std::list<File *> *children;
};

#endif // DIRECTORY_TABLE_H
