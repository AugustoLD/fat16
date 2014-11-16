#ifndef FAT_H
#define FAT_H

#define MAX_CLUSTER 65536

typedef struct cluster {
    int index;
} cluster;

class Fat
{
public:
    Fat();

private:
    cluster empty;
    cluster table[MAX_CLUSTER];
};

#endif //FAT_H
