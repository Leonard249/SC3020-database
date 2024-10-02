#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <string>
#include <vector>
#include "Record.h"
extern int NumberofNodes;

class Node
{
public:
    bool isLeaf;                          // True if the node is a leaf, false if internal
    int currkeysize;                      // Current number of keys
    int maxkeysize;                       // Max number of keys in a node
    std::vector<float> keys;              // Array of keys
    std::vector<Node *> pointers;         // For internal nodes, pointers to children
    std::vector<Record *> recordPointers; // For leaf nodes, pointers to records
    Node *nextnode;
    int minkeysize;
    int minleafkeysize;

    // Constructor
    Node(int maxkeysize, bool isLeaf);
};

class Bplustree
{
public:
    Node *root;
    int maxkeysize; // Maximum keys in a node

    // Constructor
    Bplustree(int maxkeysize);

    Node *search(Node *root, float key);
    void insertKey(float key, Record *record);
    void splitLeafNode(Node *cursor, float key, Record *record);
    void insertInternal(float key, Node *cursor, Node *child);
    void splitInternalNode(Node *cursor, float key, Node *child);
    Node *findParent(Node *cursor, Node *child);

    // Destructor
    ~Bplustree();
};

#endif // BPLUSTREE_H