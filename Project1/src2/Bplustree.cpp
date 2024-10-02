#include <iostream>
#include <string>
#include <vector>    //Used for initialising keys and pointers
#include <algorithm> //Used for sorting arrays
#include <record.h>

using namespace std;

class Node
{
public:
    bool isLeaf;                 // Determined whether node is leaf
    int currkeysize;             // Current number of keys
    int maxkeysize;              // Max number of keys in a node
    vector<int> keys;            // Array of Keys
    vector<Node *> pointers;     // Array of Pointers
    vector<record *> recordpointer; // RecordPointers
    Node *nextnode;
    int minkeysize;
    int minleafkeysize;

    // Constructor
    Node(int maxkeysize, bool isLeaf)
    {
        this->isLeaf = isLeaf;
        this->maxkeysize = maxkeysize;
        this->currkeysize = 0;                       // Initially, no keys are in the node
        this->minleafkeysize = (maxkeysize + 1) / 2; // minkeysize for leaf node
        this->minkeysize = maxkeysize / 2;           // minkeysize for internal node
        keys.resize(maxkeysize);                     // Pre-allocate space for the keys
        pointers.resize(maxkeysize + 1, nullptr);    // Pre-allocate for pointers (maxkeysize + 1)
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
