#ifndef FILE_H
#define FILE_H

#include <string>
#include <ctime>

using namespace std;

class File
{
public:
    File();

    string getFile_name() const;
    void setFile_name(const string &value);

    string getFile_name_extension() const;
    void setFile_name_extension(const string &value);

    string getFile_attributes() const;
    void setFile_attributes(const string &value);

    tm getCreated_date() const;
    void setCreated_date(const tm &value);

    int getStarting_cluster() const;
    void setStarting_cluster(int value);

    unsigned int getFile_size() const;
    void setFile_size(unsigned int value);

private:
    string file_name;
    string file_name_extension;
    string file_attributes;
    struct tm created_date;
    int starting_cluster;
    unsigned int file_size;

};

#endif // FILE_H
