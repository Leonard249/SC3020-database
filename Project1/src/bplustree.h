#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <vector>
#include "record.h"

// Define the structure of a B+ tree node
struct BPlusTreeNode
{
    bool isLeaf;
    std::vector<float> keys;
    std::vector<BPlusTreeNode *> children;
    std::vector<Record> records; // Only for leaf nodes
    BPlusTreeNode *next;         // Pointer to the next leaf node

    BPlusTreeNode() : isLeaf(false), next(nullptr) {}
};

// Define the B+ tree class
class BPlusTree
{
public:
    BPlusTree(int degree);

    // Insert a record into the B+ tree
    void insert(const Record &record);

    // Search for records within a range
    std::vector<Record> search(float minKey, float maxKey);

private:
    int degree;          // Degree of the B+ tree
    BPlusTreeNode *root; // Root node of the B+ tree

    // Helper function to split a node
    void splitNode(BPlusTreeNode *parent, int index, BPlusTreeNode *node);

    // Helper function to insert into a non-full node
    void insertNonFull(BPlusTreeNode *node, const Record &record);

    // Helper function to find the parent of a node
    BPlusTreeNode *findParent(BPlusTreeNode *root, BPlusTreeNode *child);
};

#endif // BPLUSTREE_H
