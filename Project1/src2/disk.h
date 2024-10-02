#ifndef DISK_H
#define DISK_H

#include "record.h"
#include <string>
#include <math.h>
#include <vector>

class Disk
{
private:
    unsigned char *startAddress;
    size_t diskSize;
    size_t blockSize;
    size_t recordSize;
    unsigned int numberOfUsedBlocks;
    size_t curBlockUsedMemory;

    bool canAllocateBlock();

public:
    Disk(size_t diskSize, size_t blockSize, size_t recordSize);

    ~Disk();

    Record *writeRecord(Record record);

    void deleteRecord(Record *address);

    int getNumberOfBlocks() { return numberOfUsedBlocks; }

    int getBlockSize() { return blockSize; }

    int getBLockMaxRecords() { return floor(blockSize / recordSize); }

    int getBlockID(Record *record);

    Record *getRecord(int blockIDx, size_t recordOffset);
};

#endif