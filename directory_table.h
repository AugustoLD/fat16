#ifndef DIRECTORY_TABLE_H
#define DIRECTORY_TABLE_H

#include <vector>
#include <string>
#include "file.h"
#include "directory_table.h"

class File; //foward declaration

class DirectoryTable
{
public:
    DirectoryTable();
    ~DirectoryTable();

    File *findFile(std::string fileName);
    //std::string getPathName();

    std::vector<File *> *getChildren() const;
    void setChildren(std::vector<File *> *value);

private:
    std::vector<File *> *children;
};

#endif // DIRECTORY_TABLE_H
