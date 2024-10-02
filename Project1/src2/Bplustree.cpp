#include "Bplustree.h"
#include <algorithm>
#include <fstream>
int NumberofNodes = 0;
// Node constructor
Node::Node(int maxkeysize, bool isLeaf)
{
    this->isLeaf = isLeaf;
    this->maxkeysize = maxkeysize;
    this->currkeysize = 0;
    keys.resize(maxkeysize);
    NumberofNodes++;
    if (isLeaf)
    {
        recordPointers.resize(maxkeysize); // For leaf nodes only
    }
    else
    {
        pointers.resize(maxkeysize + 1, nullptr); // For internal nodes
    }
}

// B+ Tree constructor
Bplustree::Bplustree(int maxkeysize) : maxkeysize(maxkeysize)
{
    root = nullptr;
}

// Search for a node that contains the key
Node *Bplustree::search(Node *root, float key)
{
    Node *cursor = root;
    while (cursor && !cursor->isLeaf)
    {
        for (int i = 0; i < cursor->currkeysize; i++)
        {
            if (key < cursor->keys[i])
            {
                cursor = cursor->pointers[i];
                break;
            }
            if (i == cursor->currkeysize - 1)
            {
                cursor = cursor->pointers[i + 1];
                break;
            }
        }
    }
    return cursor;
}

// Insert a key and record into the B+ Tree
void Bplustree::insertKey(float key, Record *record)
{
    Node *cursor = search(root, key);
    if (cursor->isLeaf)
    {
        // Handle insertion in the leaf node
        if (cursor->currkeysize < maxkeysize)
        {
            int i = 0;
            while (key > cursor->keys[i] && i < cursor->currkeysize)
                i++;
            cursor->keys.insert(cursor->keys.begin() + i, key);
            cursor->recordPointers.insert(cursor->recordPointers.begin() + i, record);
            cursor->currkeysize++;
        }
        else
        {
            splitLeafNode(cursor, key, record);
        }
    }
}

// Split a leaf node
void Bplustree::splitLeafNode(Node *cursor, float key, Record *record)
{
    std::vector<float> virtualKey(cursor->keys);
    std::vector<Record *> virtualRecordPointers(cursor->recordPointers);
    virtualKey.push_back(key);
    virtualRecordPointers.push_back(record);
    std::sort(virtualKey.begin(), virtualKey.end());

    int split = (maxkeysize + 1) / 2;
    Node *newLeaf = new Node(maxkeysize, true);
    cursor->currkeysize = split;

    for (int i = 0; i < split; i++)
    {
        cursor->keys[i] = virtualKey[i];
        cursor->recordPointers[i] = virtualRecordPointers[i];
    }
    for (int i = split, j = 0; i < virtualKey.size(); i++, j++)
    {
        newLeaf->keys[j] = virtualKey[i];
        newLeaf->recordPointers[j] = virtualRecordPointers[i];
        newLeaf->currkeysize++;
    }

    newLeaf->nextnode = cursor->nextnode;
    cursor->nextnode = newLeaf;

    if (cursor == root)
    {
        Node *newRoot = new Node(maxkeysize, false);
        newRoot->keys[0] = newLeaf->keys[0];
        newRoot->pointers[0] = cursor;
        newRoot->pointers[1] = newLeaf;
        newRoot->currkeysize = 1;
        root = newRoot;
    }
    else
    {
        insertInternal(newLeaf->keys[0], findParent(root, cursor), newLeaf);
    }
}

// Insert into an internal node
void Bplustree::insertInternal(float key, Node *cursor, Node *child)
{
    if (cursor->currkeysize < maxkeysize)
    {
        int i = 0;
        while (key > cursor->keys[i] && i < cursor->currkeysize)
            i++;
        cursor->keys.insert(cursor->keys.begin() + i, key);
        cursor->pointers.insert(cursor->pointers.begin() + i + 1, child);
        cursor->currkeysize++;
    }
    else
    {
        splitInternalNode(cursor, key, child);
    }
}

// Split an internal node
void Bplustree::splitInternalNode(Node *cursor, float key, Node *child)
{
    std::vector<float> virtualKey(cursor->keys);
    std::vector<Node *> virtualPointer(cursor->pointers);
    int i = 0;
    while (key > virtualKey[i] && i < cursor->currkeysize)
        i++;

    virtualKey.insert(virtualKey.begin() + i, key);
    virtualPointer.insert(virtualPointer.begin() + i + 1, child);

    int split = (maxkeysize + 1) / 2;
    Node *newInternal = new Node(maxkeysize, false);
    cursor->currkeysize = split - 1;
    for (int j = 0; j < cursor->currkeysize; j++)
    {
        cursor->keys[j] = virtualKey[j];
        cursor->pointers[j] = virtualPointer[j];
    }
    cursor->pointers[cursor->currkeysize] = virtualPointer[cursor->currkeysize];

    for (int j = split, k = 0; j < virtualKey.size(); j++, k++)
    {
        newInternal->keys[k] = virtualKey[j];
        newInternal->pointers[k] = virtualPointer[j];
        newInternal->currkeysize++;
    }
    newInternal->pointers[newInternal->currkeysize] = virtualPointer[virtualPointer.size() - 1];

    if (cursor == root)
    {
        Node *newRoot = new Node(maxkeysize, false);
        newRoot->keys[0] = virtualKey[split - 1];
        newRoot->pointers[0] = cursor;
        newRoot->pointers[1] = newInternal;
        newRoot->currkeysize = 1;
        root = newRoot;
    }
    else
    {
        insertInternal(virtualKey[split - 1], findParent(root, cursor), newInternal);
    }
}

// Find the parent of a given node
Node *Bplustree::findParent(Node *cursor, Node *child)
{
    if (cursor->isLeaf || cursor->pointers[0]->isLeaf)
        return nullptr;

    for (int i = 0; i < cursor->currkeysize + 1; i++)
    {
        if (cursor->pointers[i] == child)
        {
            return cursor;
        }
        else
        {
            Node *parent = findParent(cursor->pointers[i], child);
            if (parent != nullptr)
                return parent;
        }
    }
    return nullptr;
}

// Destructor (optional for cleanup)
Bplustree::~Bplustree()
{
    // You can implement a cleanup routine here if necessary.
}