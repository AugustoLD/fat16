#include "fat.h"
#include <iostream>

Fat::Fat()
{
}

void Fat::allocateFile(File *file)
{
    unsigned int cluster_count = file->getFile_size() / CLUSTER_SIZE;
    unsigned int aux[MAX_CLUSTER];
    if(file->getFile_size() % CLUSTER_SIZE) {
        cluster_count++;
    }

    aux[0] = seekFreeCluster(0);
    if(aux[0] == MAX_CLUSTER) {
        std::cout << "error: unavaible cluster!" << std::endl;
        return;
    }
    for(unsigned int i = 1; i < cluster_count; i++) {
        aux[i] = seekFreeCluster(aux[i-1]+1);
        if(aux[i] == MAX_CLUSTER) {
            std::cout << "error: unavaible cluster!" << std::endl;
            return;
        }
    }
    file->setStarting_cluster(aux[0]);
    table[aux[0]].free = false;
    for(unsigned int i = 1; i < cluster_count; i++) {
        table[aux[i-1]].nextCluster = aux[i];
        table[aux[i]].free = false;
    }
    table[aux[cluster_count-1]].nextCluster = MAX_CLUSTER;
}

unsigned int Fat::seekFreeCluster(unsigned int initial)
{
    unsigned int i;
    for(i = initial; i < MAX_CLUSTER && (!table[i].free); i++);

    return i;
}
