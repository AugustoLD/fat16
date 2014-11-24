#include "file.h"

File::File()
{
}

File::~File()
{
    if(directoryTable != NULL) delete directoryTable;
}
string File::getFile_name() const
{
    return file_name;
}

void File::setFile_name(const string &value)
{
    file_name = value;
}
string File::getFile_name_extension() const
{
    return file_name_extension;
}

void File::setFile_name_extension(const string &value)
{
    file_name_extension = value;
}
int File::getStarting_cluster() const
{
    return starting_cluster;
}

void File::setStarting_cluster(int value)
{
    starting_cluster = value;
}
unsigned int File::getFile_size() const
{
    return file_size;
}

void File::setFile_size(unsigned int value)
{
    file_size = value;
}
FileType File::getFile_type() const
{
    return file_type;
}

void File::setFile_type(const FileType &value)
{
    file_type = value;
}
date File::getCreation_date() const
{
    return creation_date;
}

void File::setCreation_date(const date &value)
{
    creation_date = value;
}
DirectoryTable *File::getDirectoryTable() const
{
    return directoryTable;
}

void File::setDirectoryTable(DirectoryTable *value)
{
    directoryTable = value;
}
File *File::getParent() const
{
    return parent;
}

void File::setParent(File *value)
{
    parent = value;
}


