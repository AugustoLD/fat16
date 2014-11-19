#ifndef DIRECTORY_TABLE_H
#define DIRECTORY_TABLE_H

#include <list>
#include "file.h"
#include "directory_table.h"

class DirectoryTable
{
public:
    DirectoryTable(bool is_root);

private:
    bool is_root;
    list<File*> children;
    DirectoryTable *father;
};

#endif // DIRECTORY_TABLE_H
