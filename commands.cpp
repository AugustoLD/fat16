#include "commands.h"
#include <iostream>
#include <list>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "globals.h"

void commands::mkdir(File *currentDir, string dirName)
{
    File *temp;
    for(unsigned int i = 0; i < currentDir->getDirectoryTable()->getChildren()->size(); i++) {
        temp = currentDir->getDirectoryTable()->getChildren()->at(i);
        if(dirName.compare(temp->getFile_name()) == 0) {
            std::cout << "Directory already exists!" << std::endl;
            return;
        }
    }
    File *newDir = new File;
    newDir->setFile_name(dirName);
    FileType fileType;
    fileType.directory=true;
    time_t t = time(0); // get time now
    date now = localtime(&t);

    newDir->setFile_type(fileType);
    newDir->setCreation_date(now);
    newDir->setDirectoryTable(new DirectoryTable);
    newDir->setParent(currentDir);

    currentDir->getDirectoryTable()->getChildren()->push_back(newDir);
}

void commands::dir(File *currentDir)
{
    File *temp;
    for(unsigned int i = 0; i < currentDir->getDirectoryTable()->getChildren()->size(); i++) {
        temp = currentDir->getDirectoryTable()->getChildren()->at(i);
        if(temp->getFile_type().directory) {
            std::cout << "<" << temp->getFile_name() << ">" << std::endl;
        } else {
            std::cout << temp->getFile_name() << std::endl;
        }
    }
}

void commands::cd(File **currentDir, string nextDir)
{
    //string::compare returns 0 if equal
    if(nextDir.compare("..") == 0) {
        if ((*currentDir)->getParent() == NULL) {
            std::cout << "Already in root directory!" << std::endl;
        } else {
            *currentDir = (*currentDir)->getParent();
        }
    } else {
        File *temp;
        for(unsigned int i = 0; i < (*currentDir)->getDirectoryTable()->getChildren()->size(); i++) {
            temp = (*currentDir)->getDirectoryTable()->getChildren()->at(i);
            if(temp->getFile_type().directory && !temp->getFile_name().compare(nextDir)) {
                *currentDir = temp;
                return;
            }
        }
        std::cout << "Directory " << nextDir <<  " not found!" << std::endl;
    }
}

std::vector<string>* commands::parseCommand(string command)
{
    std::vector<string> *tokens = new std::vector<string>;
    string temp = "";
    for(unsigned int i = 0; i < command.length(); i++) {
        if(command.at(i) == ' ') {
            tokens->push_back(temp);
            temp = "";
        } else {
            temp += command.at(i);
        }
    }
    if(temp != "") tokens->push_back(temp);
    return tokens;
}

void commands::cp(File *currentDir, string fileName)
{
    ifstream file;
    file.open(fileName, ios::ate | ios::binary);
    if(file.is_open()) {;

        File *newFile = new File;
        newFile->setFile_size(file.tellg());
        newFile->setFile_name(fileName.substr(fileName.find_last_of('/')+1, 255));
        time_t t = time(0); // get time now
        date now = localtime(&t);
        newFile->setCreation_date(now);

        currentDir->getDirectoryTable()->getChildren()->push_back(newFile);

        fat->allocateFile(newFile);

        char *block;
        block = new char[CLUSTER_SIZE];
        file.seekg(0, ios::beg);
        int i;
        for(i = newFile->getStarting_cluster(); fat->table[i].nextCluster < MAX_CLUSTER; i = fat->table[i].nextCluster) {
            file.read(block, CLUSTER_SIZE);
            disc.seekp(i*CLUSTER_SIZE, ios::beg);
            disc.write(block, CLUSTER_SIZE);
        }
        file.read(block, CLUSTER_SIZE);
        disc.seekp(i*CLUSTER_SIZE, ios::beg);
        disc.write(block, CLUSTER_SIZE);
        file.close();
    } else {
        std::cout << "File not found!" << std::endl;
    }
}

void commands::type(File *file)
{
    char *block;
    block = new char[CLUSTER_SIZE];
    int i;
    for(i = file->getStarting_cluster(); fat->table[i].nextCluster < MAX_CLUSTER; i = fat->table[i].nextCluster) {
        disc.seekg(i*CLUSTER_SIZE, ios::beg);
        disc.read(block,CLUSTER_SIZE);
        std::cout << block << std::endl;
    }
    disc.seekg(i*CLUSTER_SIZE, ios::beg);
    disc.read(block,CLUSTER_SIZE);
    std::cout << block << std::endl;
}


File *commands::startRoot()
{
    /*  Iniciate root directory  */
    File *rootDir = new File;
    FileType rootType;
    rootType.directory = true;
    rootDir->setFile_type(rootType);
    rootDir->setFile_name("/");
    rootDir->setDirectoryTable(new DirectoryTable);
    rootDir->setParent(NULL);

    return rootDir;
}
