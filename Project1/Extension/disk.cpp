
#include "disk.h"
#include "Record.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


//declare disk
Disk::Disk (size_t diskSize, size_t blockSize, size_t recordSize) {
    startAddress = (unsigned char*)malloc(diskSize);
    this -> diskSize = diskSize;
    this -> blockSize = blockSize;
    this -> recordSize = recordSize;
    numberOfUsedBlocks = 0;
    curBlockUsedMemory = 0;
}


Disk::~Disk(){
    free(startAddress);
}


//Check if there is space to allocate a new block of memory
//If yes, increament number of used blocks and reset current block used memory
//If not, print disk memory is full and return false
bool Disk::canAllocateBlock (){
    //Check if any more space in entire disk
    if (blockSize * (numberOfUsedBlocks + 1) > diskSize) {
        cout << "Disk Memory Full" << endl;
        return false;
    }
    numberOfUsedBlocks++;
    curBlockUsedMemory = 0;
    return true;
    
}

//Write record to a block in the disk and return address of record
Record* Disk::writeRecord (Record record){
    //Check if there is sufficient space in current block
    if ((curBlockUsedMemory + recordSize) >blockSize){
        if (!canAllocateBlock())
            return nullptr;
    }
    Record* recordAddress = reinterpret_cast<Record*>(startAddress + numberOfUsedBlocks * blockSize + curBlockUsedMemory);
    if (numberOfUsedBlocks == 0)
        numberOfUsedBlocks++;
    curBlockUsedMemory += recordSize;
    *recordAddress = record;
    return recordAddress;
}

void Disk::deleteRecord(Record* address){
    delete address;
}

//Return blockID by taking a pointer to the record
int Disk::getBlockID(Record* record){
    unsigned char* recordBytes = reinterpret_cast<unsigned char*>(record);
    ptrdiff_t offset = recordBytes-startAddress;
    int blockID = offset/blockSize;
    return blockID;
}

//Use position of blockID and recordOffset to get address of specific record
Record* Disk::getRecord(int BlockIDX, size_t recordOffset){
    size_t offset = BlockIDX * blockSize + recordOffset;
    return reinterpret_cast<Record *> (startAddress + offset);
}