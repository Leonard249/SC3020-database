#include "block.h"
#include <fstream>
#include <iostream>

Block::Block(size_t blockSize) : blockSize(blockSize) {}

bool Block::readFromDisk(const std::string &filename, size_t blockIndex)
{
    std::ifstream infile(filename, std::ios::binary);
    if (!infile)
    {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }

    infile.seekg(blockIndex * blockSize, std::ios::beg);
    if (!infile)
    {
        std::cerr << "Error seeking to block index: " << blockIndex << std::endl;
        return false;
    }

    records.clear();
    size_t recordSize = sizeof(Record);
    size_t numRecords = blockSize / recordSize;
    for (size_t i = 0; i < numRecords; ++i)
    {
        Record record;
        infile.read(reinterpret_cast<char *>(&record), recordSize);
        if (infile)
        {
            records.push_back(record);
        }
        else
        {
            break;
        }
    }

    infile.close();
    return true;
}

bool Block::writeToDisk(const std::string &filename, size_t blockIndex)
{
    std::ofstream outfile(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!outfile)
    {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return false;
    }

    outfile.seekp(blockIndex * blockSize, std::ios::beg);
    if (!outfile)
    {
        std::cerr << "Error seeking to block index: " << blockIndex << std::endl;
        return false;
    }

    size_t recordSize = sizeof(Record);
    for (const auto &record : records)
    {
        outfile.write(reinterpret_cast<const char *>(&record), recordSize);
        if (!outfile)
        {
            std::cerr << "Error writing record to disk" << std::endl;
            return false;
        }
    }

    outfile.close();
    return true;
}

bool Block::addRecord(const Record &record)
{
    size_t recordSize = sizeof(Record);
    if (records.size() * recordSize < blockSize)
    {
        records.push_back(record);
        return true;
    }
    else
    {
        std::cerr << "Block is full, cannot add more records" << std::endl;
        return false;
    }
}

const std::vector<Record> &Block::getRecords() const
{
    return records;
}

size_t Block::getBlockSize() const
{
    return blockSize;
}
