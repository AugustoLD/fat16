#include "commands.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "globals.h"

void commands::mkdir(File *currentDir, string dirName)
{
    if(currentDir->getDirectoryTable()->findFile(dirName) != NULL) {
        std::cout << dirName << ": directory already exists" << std::endl;
        return;
    }
    if(currentDir->getFile_type().root && currentDir->getDirectoryTable()->getChildren()->size() == 255) {
        std::cout << "root directory is full (255 files)" << std::endl;
    } else {
        File *newDir = new File;
        newDir->setFile_name(dirName);
        FileType fileType;
        fileType.directory=true;
        time_t t = time(0); // get time now
        date now = localtime(&t);

        newDir->setFile_type(fileType);
        newDir->setCreation_date(asctime(now));
        newDir->setDirectoryTable(new DirectoryTable);
        newDir->setParent(currentDir);

        currentDir->getDirectoryTable()->getChildren()->push_back(newDir);
    }
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

void commands::dirFile(File *file)
{
    std::cout << "Name: " << file->getFile_name() << std::endl;
    std::cout << "Real Size: " << std::setprecision(2) << file->getFile_size() / 1000.0 << " KB (" << file->getFile_size() << " bytes)" << std::endl;
    unsigned int cluster_count = file->getFile_size() / CLUSTER_SIZE;
    if(file->getFile_size() % CLUSTER_SIZE) cluster_count++;
    std::cout << "Size in memory: " << cluster_count * CLUSTER_SIZE / 1000.0 << " KB (" << cluster_count << " cluster(s))" << std::endl;
    std::cout << "Creation Date: " << file->getCreation_date();
}

void commands::cd(File **currentDir, string nextDir)
{
    //string::compare returns 0 if equal
    if(nextDir.compare("..") == 0) {
        if ((*currentDir)->getParent() == NULL) {
            std::cout << "already in root directory!" << std::endl;
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
        std::cout << nextDir <<  ": directory not found" << std::endl;
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

void commands::copyFile(File *currentDir, string fileName, string newFileName)
{
    if(currentDir->getDirectoryTable()->findFile(newFileName) == NULL) {
        ifstream file;
        file.open(fileName, ios::ate | ios::binary);
        if(file.is_open()) {
            File *newFile = new File;
            newFile->setFile_size(file.tellg());
            newFile->setFile_name(newFileName);
            time_t t = time(0); // get time now
            date now = localtime(&t);
            newFile->setCreation_date(asctime(now));

            if(fat->allocateFile(newFile) ) {
                currentDir->getDirectoryTable()->getChildren()->push_back(newFile);
                disc.open("../disc.dat", ios::binary | ios::out | ios::in);

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
                disc.close();
            } else {
                std::cout << "error: no disk space avaible" << std::endl;
            }
        } else {
            copyFromFat(currentDir, fileName, newFileName);
        }
    } else {
        std::cout << newFileName << ": file already exists in current directory" << std::endl;
    }
}

void commands::type(File *file)
{
    char *block;
    block = new char[CLUSTER_SIZE];
    disc.open("../disc.dat", ios::binary | ios::out | ios::in);
    int i;
    for(i = file->getStarting_cluster(); fat->table[i].nextCluster < MAX_CLUSTER; i = fat->table[i].nextCluster) {
        disc.seekg(i*CLUSTER_SIZE, ios::beg);
        disc.read(block,CLUSTER_SIZE);
        std::cout << block << std::endl;
    }
    disc.seekg(i*CLUSTER_SIZE, ios::beg);
    disc.read(block,CLUSTER_SIZE);
    disc.close();
    std::cout << block << std::endl;
}


File *commands::startRoot()
{
    /*  Iniciate root directory  */
    File *rootDir = new File;
    FileType rootType;
    rootType.directory = true;
    rootType.root = true;
    rootDir->setFile_type(rootType);
    rootDir->setFile_name("/");
    rootDir->setDirectoryTable(new DirectoryTable);
    rootDir->setParent(NULL);

    return rootDir;
}


void commands::cp(File *currentDir, string fileName)
{
    string newFileName = fileName.substr(fileName.find_last_of('/')+1, 255);
    if(newFileName.compare(fileName) == 0) {
        std::cout << "missing new file name" << std::endl;
    } else {
        copyFile(currentDir, fileName, newFileName);
    }
}

void commands::cp(File *currenDir, string fileName, string newFileName)
{
    copyFile(currenDir, fileName, newFileName);
}

void commands::copyFromFat(File *currentDir, string fileName, string newFileName)
{
    File *file = currentDir->getDirectoryTable()->findFile(fileName);
    if(file != NULL) {
        File *newFile = new File;
        newFile->setFile_name(newFileName);
        newFile->setFile_size(file->getFile_size());
        time_t t = time(0); // get time now
        date now = localtime(&t);
        newFile->setCreation_date(asctime(now));

        if(fat->allocateFile(newFile) ) {
            currentDir->getDirectoryTable()->getChildren()->push_back(newFile);
            disc.open("../disc.dat", ios::binary | ios::out | ios::in);

            char *block;
            block = new char[CLUSTER_SIZE];
            int i, j;
            for(i = file->getStarting_cluster(), j = newFile->getStarting_cluster(); fat->table[i].nextCluster < MAX_CLUSTER; i = fat->table[i].nextCluster, j = fat->table[j].nextCluster) {
                disc.seekg(i*CLUSTER_SIZE, ios::beg);
                disc.read(block, CLUSTER_SIZE);
                disc.seekp(j*CLUSTER_SIZE, ios::beg);
                disc.write(block, CLUSTER_SIZE);
            }
            disc.seekg(i*CLUSTER_SIZE, ios::beg);
            disc.read(block, CLUSTER_SIZE);
            disc.seekp(j*CLUSTER_SIZE, ios::beg);
            disc.write(block, CLUSTER_SIZE);
            disc.close();
        } else {
            std::cout << "error: no disk space avaible" << std::endl;
        }
    } else {
        std::cout << fileName << ": file not found" << std::endl;
    }
}


void commands::help()
{
    std::cout << "help   -> display this help" << std::endl << std::endl;
    std::cout << "format -> format the whole system, be careful" << std::endl << std::endl;
    std::cout << "mkdir directory_name  -> create a new directory inside the current one" << std::endl << std::endl;
    std::cout << "cd new_directory_name -> change from current direcoty to directory_name. cd .. goes to the\n"
               << "parent directory" << std::endl << std::endl;
    std::cout << "dir [file_name]  -> display all files that belong to the current directory. If a file name is given,\n"
              << "display all informations about that file" << std::endl << std::endl;
    std::cout << "cp file_to_copy new_file_name -> copy a file from outside or inside fat to current directory. If the\nfile_to_copy"
              << " is from outside fat, the whole path must be given and the new_file_name is optional" << std::endl << std::endl;
    std::cout << "type file_name  -> display the content of file_name" << std::endl;
}
