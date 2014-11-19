#ifndef FILE_H
#define FILE_H

#include <string>
#include <ctime>

typedef struct tm date;

using namespace std;

typedef struct FileType {
    bool readOnly;
    bool hidden;
    bool system;
    bool directory;
} FileType;

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

private:
    string file_name;
    string file_name_extension;
    FileType file_type;
    date creation_date;
    int starting_cluster;
    unsigned long file_size;

};

#endif // FILE_H
