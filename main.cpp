#include <ctime>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "fat.h"
#include "file.h"

using namespace std;

int main()
{
    /*time_t t = time(0); // get time now
    struct tm * now = localtime(& t);*/

    Fat *fat = new Fat;

    File *file = new File;

    file->setFile_size(160000);

    fat->allocateFile(file);
    for(int i = file->getStarting_cluster(); fat->table[i].nextCluster < MAX_CLUSTER ; i = fat->table[i].nextCluster) {
        cout << i << endl;
        usleep(1000000);
    }

    return 0;
}
