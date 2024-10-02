#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <string>
#include <vector>
#include "Record.h"

class Node
{
public:
    bool isLeaf;                          // True if the node is a leaf, false if internal
    int currkeysize;                      // Current number of keys
    int maxkeysize;                       // Max number of keys in a node
    std::vector<int> keys;                // Array of keys
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

    Node *search(Node *root, int key);
    void insertKey(int key, Record *record);
    void splitLeafNode(Node *cursor, int key, Record *record);
    void insertInternal(int key, Node *cursor, Node *child);
    void splitInternalNode(Node *cursor, int key, Node *child);
    Node *findParent(Node *cursor, Node *child);

    // Destructor
    ~Bplustree();
};

#endif // BPLUSTREE_H