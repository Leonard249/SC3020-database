#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
#include "record.h"

class Block
{
public:
    Block(size_t blockSize);

    bool readFromDisk(const std::string &filename, size_t blockIndex);
    bool writeToDisk(const std::string &filename, size_t blockIndex);

    bool addRecord(const Record &record);

    // Getters
    const std::vector<Record> &getRecords() const;
    size_t getBlockSize() const;

private:
    std::vector<Record> records;
    size_t blockSize; // Size of the block in bytes
};

#endif
