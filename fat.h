#ifndef FAT_H
#define FAT_H

#include "file.h"

#define MAX_CLUSTER 65536   // unities
#define CLUSTER_SIZE 32000U // bytes

typedef struct cluster {
    bool free = true;
    unsigned int nextCluster;
} cluster;

class Fat
{
public:
    Fat();
    bool allocateFile(File *file);

//private:
    cluster table[MAX_CLUSTER];

    unsigned int seekFreeCluster(unsigned int initial);

};

#endif //FAT_H
