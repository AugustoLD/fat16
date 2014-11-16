#include "file.h"

File::File()
{
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
string File::getFile_attributes() const
{
    return file_attributes;
}

void File::setFile_attributes(const string &value)
{
    file_attributes = value;
}
tm File::getCreated_date() const
{
    return created_date;
}

void File::setCreated_date(const tm &value)
{
    created_date = value;
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






