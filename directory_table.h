#ifndef DIRECTORY_TABLE_H
#define DIRECTORY_TABLE_H

#include <vector>
#include "file.h"

class directory_table
{
public:
    directory_table(bool is_root);

private:
    bool is_root;
    vector<File> children;
};

#endif // DIRECTORY_TABLE_H
