#ifndef FILE_H
#define FILE_H

#include <string>
#include <ctime>
#include "directory_table.h"

typedef struct tm* date;

using namespace std;

typedef struct FileType {
    bool readOnly = false;
    bool hidden = false;
    bool directory = false;
} FileType;

class DirectoryTable; //foward declaration

class File
{
public:
    File();

    string getFile_name() const;
    void setFile_name(const string &value);

    string getFile_name_extension() const;
    void setFile_name_extension(const string &value);

    int getStarting_cluster() const;
    void setStarting_cluster(int value);

    unsigned int getFile_size() const;
    void setFile_size(unsigned int value);

    FileType getFile_type() const;
    void setFile_type(const FileType &value);

    date getCreation_date() const;
    void setCreation_date(const date &value);

    DirectoryTable *getDirectoryTable() const;
    void setDirectoryTable(DirectoryTable *value);

    File *getParent() const;
    void setParent(File *value);

private:
    string file_name;
    string file_name_extension;
    FileType file_type;
    date creation_date;
    int starting_cluster;
    unsigned long file_size;
    DirectoryTable *directoryTable;
    File *parent;

};

#endif // FILE_H
