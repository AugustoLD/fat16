#include "directory_table.h"
#include <iostream>

DirectoryTable::DirectoryTable()
{
    children = new std::list<File*>;
}
std::list<File *> *DirectoryTable::getChildren() const
{
    return children;
}

void DirectoryTable::setChildren(std::list<File *> *value)
{
    children = value;
}

File* DirectoryTable::findFile(string fileName)
{
    File *temp;
    for (std::list<File*>::iterator it=children->begin(); it!=children->end() ; ++it) {
        temp = *it;
        if(temp->getFile_name().compare(fileName) == 0) {
            return temp;
        }
    }
    return NULL;
}

/*
std::string DirectoryTable::getPathName()
{
    File *tempFile = getDirectoryFile();
    std::string pathName = tempFile->getFile_name();
    DirectoryTable *tempDir = this->parent;
    std::cout << parent->getDirectoryFile()->getFile_name() << std::endl;
    while(tempDir != NULL) {
        tempFile = tempDir->getDirectoryFile();
        pathName = tempFile->getFile_name() + '/' + pathName;
        tempDir = tempDir->parent;
    }

    return pathName;
}
*/
