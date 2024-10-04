#ifndef BPLUSTREE_H
#define BPLUSTREE_H


#include "disk.h"
using namespace std;
extern int NumberofNodes;
extern int layers;
extern int NumberofIO;
class Node
{
public:
    // Declare Variable
    bool isLeaf;                     // True if the node is a leaf, false if internal
    int currkeysize;                 // Current number of keys
    int maxkeysize;                  // Max number of keys in a node
    vector<float> keys;              // Array of keys
    vector<Node *> pointers;         // For internal nodes, pointers to children
    vector<Record *> recordPointers; // For leaf nodes, pointers to records
    Node *nextnode;
    int minkeysize;
    int minleafkeysize;

    // Methods
    Node(int maxkeysize, bool isLeaf);
    ~Node();
};

class Bplustree
{
public:
    // Declare Variable
    Disk* disk; 
    Node *root = nullptr; // Initialise Empty Tree
    int maxkeysize;

    // Constructor
    Bplustree(int maxkeysize,Disk* disk);
    ;
    ~Bplustree();
    // Methods
    Node *search(Node *root, float key);
    void insertKey(float key, Record *record);
    void splitLeafNode(Node *cursor, float key, Record *record);
    void insertInternal(float key, Node *cursor, Node *leftchild, Node *rightchild);
    void splitInternalNode(Node *cursor, float key, Node *leftchild, Node *rightchild);
    Node *findParent(Node *cursor, Node *child);
    vector<Record> searchKey(float minKey, float maxKey);
    void Print(void);
    void Display(vector<Record> results);
};

#endif