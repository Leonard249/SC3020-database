#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
<<<<<<< Updated upstream
#include <vector>    //Used for initialising keys and pointers
#include <algorithm> //Used for sorting arrays
#include <record.h>
=======
#include <vector>
#include <algorithm>
#include <fstream> // For file handling
>>>>>>> Stashed changes

using namespace std;

// Define the record structure
struct Record
{
    std::string GAME_DATE_EST;
    int TEAM_ID_home;
    int PTS_home;
    float FG_PCT_home;
    float FT_PCT_home;
    float FG3_PCT_home;
    int AST_home;
    int REB_home;
    bool HOME_TEAM_WINS;
    void print() const
    {
        std::cout << "GAME_DATE_EST: " << GAME_DATE_EST << ", "
                  << "TEAM_ID_home: " << TEAM_ID_home << ", "
                  << "PTS_home: " << PTS_home << ", "
                  << "FG_PCT_home: " << FG_PCT_home << ", "
                  << "FT_PCT_home: " << FT_PCT_home << ", "
                  << "FG3_PCT_home: " << FG3_PCT_home << ", "
                  << "AST_home: " << AST_home << ", "
                  << "REB_home: " << REB_home << ", "
                  << "HOME_TEAM_WINS: " << HOME_TEAM_WINS << std::endl;
    };
};

// Node class representing a B+ tree node
class Node
{
public:
<<<<<<< Updated upstream
    bool isLeaf;                 // Determined whether node is leaf
    int currkeysize;             // Current number of keys
    int maxkeysize;              // Max number of keys in a node
    vector<int> keys;            // Array of Keys
    vector<Node *> pointers;     // Array of Pointers
    vector<record *> recordpointer; // RecordPointers
=======
    bool isLeaf;                     // True if the node is a leaf, false if internal
    int currkeysize;                 // Current number of keys
    int maxkeysize;                  // Max number of keys in a node
    vector<int> keys;                // Array of keys
    vector<Node *> pointers;         // For internal nodes, pointers to children
    vector<Record *> recordPointers; // For leaf nodes, pointers to records
>>>>>>> Stashed changes
    Node *nextnode;
    int minkeysize;
    int minleafkeysize;

    // Constructor
    Node(int maxkeysize, bool isLeaf)
    {
        this->isLeaf = isLeaf;
        this->maxkeysize = maxkeysize;
<<<<<<< Updated upstream
        this->currkeysize = 0;                       // Initially, no keys are in the node
        this->minleafkeysize = (maxkeysize + 1) / 2; // minkeysize for leaf node
        this->minkeysize = maxkeysize / 2;           // minkeysize for internal node
        keys.resize(maxkeysize);                     // Pre-allocate space for the keys
        pointers.resize(maxkeysize + 1, nullptr);    // Pre-allocate for pointers (maxkeysize + 1)
=======
        this->currkeysize = 0;
        keys.resize(maxkeysize);
        if (isLeaf)
        {
            recordPointers.resize(maxkeysize); // For leaf nodes only
        }
        else
        {
            pointers.resize(maxkeysize + 1, nullptr); // For internal nodes
        }
>>>>>>> Stashed changes
    }
};

class Bplustree
{
public:
    Node *root;
    int maxkeysize; // Maximum keys in a node

<<<<<<< Updated upstream
    // Constructor
    Bplustree();

    // Functions
    Node *findNode(int);
    void deleteKey(int);
    Node *searchKey();
    void insert(int);
    bool BorrowNode(Node *, Node *);
    void MergeNode(Node *, Node *);
};

Bplustree::Bplustree(/* args */)
{
}

Bplustree::~Bplustree()
{
}

Node *Bplustree::findNode(int key)
{
    Node *CurrNode = root;
    while (!CurrNode->isLeaf) // Traverse to leaf node
    {
        auto UpperBound = upper_bound(CurrNode->keys.begin(), CurrNode->keys.end(), key);
        int index = UpperBound - CurrNode->keys.begin();
        CurrNode = CurrNode->pointers[index];
    }

    return CurrNode; // return the leaf node
};

void Bplustree::deleteKey(int key)
{
    Node *LeafNode = this->findNode(key);
    Node *ParentNode = this.FindParent(this.root, LeafNode);

    // Delete from node
    bool found = false;
    for (int i = 0; i < LeafNode->currkeysize; i++)
    {
        if (LeafNode->keys[i] == key)
        {
            LeafNode->keys.erase(i);
            LeafNode->recordpointer.erase(i);
            LeafNode->currkeysize = LeafNode->keys.size();
            found = true;
            break;
        }
    }

    if (found)
    {
        bool success;
        // check for violation
        if (LeafNode->currkeysize < LeafNode->minleafkeysize)
        {
            success = this.BorrowNode(ParentNode, LeafNode);

            if (!success)
            {
                this.MergeNode(ParentNode, LeafNode);
            }
        }
    }
    else
    {
        cout << "Key not found no key to delete" << endl;
    }

    // Can borrow from left or right
};

void Bplustree::BorrowNode(Node *ParentNode, Node *LeafNode)
{
    // CheckIfLeft&RightExist

    Node *RightNode = LeafNode->nextnode;
    if (RightNode->currkeysize > RightNode->minleafkeysize)
    {
        int borrowedkey = RightNode->keys[0];
        int *borrowedPointer = RightNode->recordpointer[0];
    }
    else if
    {
        // Check Left
    }
}

void Bplustree::MergeNode(Node *ParentNode, Node *LeadNode)
{

}

Node *Bplustree::findParent(Node *cursor, Node *child)
{
    if (cursor->isLeaf || cursor->pointers[0]->isLeaf)
        return nullptr;
    for (int i = 0; i < cursor->currkeysize + 1; i++)
    {
        if (cursor->pointers[i] == child)
            return cursor;
        else
        {
            Node *parent = findParent(cursor->pointers[i], child);
            if (parent != nullptr)
                return parent;
        }
    }
    return nullptr;
}
=======
    Bplustree(int maxkeysize) : maxkeysize(maxkeysize)
    {
        root = nullptr;
    }
    Node *search(Node *root, int key)
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

    void insertKey(int key, Record *record)
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
    void splitLeafNode(Node *cursor, int key, Record *record)
    {
        vector<int> virtualKey(cursor->keys);
        vector<Record *> virtualRecordPointers(cursor->recordPointers);
        virtualKey.push_back(key);
        virtualRecordPointers.push_back(record);
        sort(virtualKey.begin(), virtualKey.end());

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

    void insertInternal(int key, Node *cursor, Node *child)
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
    void splitInternalNode(Node *cursor, int key, Node *child)
    {
        vector<int> virtualKey(cursor->keys);
        vector<Node *> virtualPointer(cursor->pointers);
        int i = 0;
        while (key > virtualKey[i] && i < cursor->currkeysize)
            i++;

        // Insert the new key and child pointer
        virtualKey.insert(virtualKey.begin() + i, key);
        virtualPointer.insert(virtualPointer.begin() + i + 1, child);

        int split = (maxkeysize + 1) / 2;
        Node *newInternal = new Node(maxkeysize, false);

        // Update the current node
        cursor->currkeysize = split - 1;
        for (int j = 0; j < cursor->currkeysize; j++)
        {
            cursor->keys[j] = virtualKey[j];
            cursor->pointers[j] = virtualPointer[j];
        }
        cursor->pointers[cursor->currkeysize] = virtualPointer[cursor->currkeysize];

        // Fill the new internal node
        for (int j = split, k = 0; j < virtualKey.size(); j++, k++)
        {
            newInternal->keys[k] = virtualKey[j];
            newInternal->pointers[k] = virtualPointer[j];
            newInternal->currkeysize++;
        }
        newInternal->pointers[newInternal->currkeysize] = virtualPointer[virtualPointer.size() - 1]; // Last child pointer

        // If cursor is the root, create a new root
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

    Node *findParent(Node *cursor, Node *child)
    {
        if (cursor->isLeaf || cursor->pointers[0]->isLeaf)
            return nullptr; // No parent if we're at the root or at a leaf node

        for (int i = 0; i < cursor->currkeysize + 1; i++)
        {
            if (cursor->pointers[i] == child)
            {
                return cursor; // Found the parent
            }
            else
            {
                Node *parent = findParent(cursor->pointers[i], child);
                if (parent != nullptr)
                    return parent; // Return the found parent
            }
        }
        return nullptr; // Not found
    }

    ~Bplustree()
    {
    }
};
>>>>>>> Stashed changes
