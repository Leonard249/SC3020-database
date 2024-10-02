#include <iostream>
#include <string>
#include <vector>    //Used for initialising keys and pointers
#include <algorithm> //Used for sorting arrays

using namespace std;

class Node
{
public:
    bool isLeaf;             // Determined whether node is leaf
    int currkeysize;         // Current number of keys
    int maxkeysize;          // Max number of keys in a node
    vector<int> keys;        // Array of Keys
    vector<Node *> pointers; // Array of Pointers
    Node *nextnode;

    Node(int maxkeysize, bool isLeaf)
    { // Constructor
        this->isLeaf = isLeaf;
        this->maxkeysize = maxkeysize;
        this->currkeysize = 0;                    // Initially, no keys are in the node
        keys.resize(maxkeysize);                  // Pre-allocate space for the keys
        pointers.resize(maxkeysize + 1, nullptr); // Pre-allocate for pointers (maxkeysize + 1)
    }

    ~Node() {}
};

class Bplustree
{
public:
    Node *root;

    // Constructor
    Bplustree();

    // Functions
    void delete();
    void searchKey();

    Node *search(Node *root, int key)
    {
        Node *cursor = root;
        while (!cursor->isLeaf)
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

    void insert(int key)
    {
        Node *cursor = search(root, key);
        if (cursor->currkeysize < maxkeysize)
        {
            int i = 0;
            while (key > cursor->keys[i] && i < cursor->currkeysize)
                i++;
            cursor->keys.insert(cursor->keys.begin() + i, key); // vector insertion
            cursor->currkeysize++;
        }
        else
        {
            splitLeafNode(cursor, key);
        }
    }

    void splitLeafNode(Node *cursor, int key)
    {
        vector<int> virtualKey(cursor->keys);
        virtualKey.push_back(key);
        sort(virtualKey.begin(), virtualKey.end());

        int split = (maxkeysize + 1) / 2;
        Node *newLeaf = new Node(maxkeysize, true);
        cursor->currkeysize = split;
        for (int i = 0; i < split; i++)
        {
            cursor->keys[i] = virtualKey[i];
        }
        for (int i = split, j = 0; i < virtualKey.size(); i++, j++)
        {
            newLeaf->keys[j] = virtualKey[i];
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

        for (int j = split, k = 0; j < maxkeysize + 1; j++, k++)
        {
            newInternal->keys[k] = virtualKey[j];
            newInternal->pointers[k] = virtualPointer[j];
            newInternal->currkeysize++;
        }
        newInternal->pointers[newInternal->currkeysize] = virtualPointer[maxkeysize + 1];

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

    void updateParent(Node *cursor, Node *child, int key)
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
};

Bplustree::Bplustree(/* args */)
{
}

Bplustree::~Bplustree()
{
}
