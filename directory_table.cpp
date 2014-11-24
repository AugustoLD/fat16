#include "directory_table.h"
#include <iostream>

DirectoryTable::DirectoryTable()
{
    children = new std::vector<File*>;
}
File* DirectoryTable::findFile(string fileName)
{
    File *temp;
    for(unsigned int i = 0; i < children->size(); i++) {
        temp = children->at(i);
        if(temp->getFile_name().compare(fileName) == 0) {
            return temp;
        }
    }
    return NULL;
}

DirectoryTable::~DirectoryTable()
{
    delete children;
}

std::vector<File *> *DirectoryTable::getChildren() const
{
    return children;
}

void DirectoryTable::setChildren(std::vector<File *> *value)
{
    children = value;
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
