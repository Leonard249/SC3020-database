#include <iostream>
#include <string>
#include <vector>    //Used for initialising keys and pointers
#include <algorithm> //Used for sorting arrays

using namespace std;

class Node
{
public:
    bool isLeaf;                 // Determined whether node is leaf
    int currkeysize;             // Current number of keys
    int maxkeysize;              // Max number of keys in a node
    vector<int> keys;            // Array of Keys
    vector<Node *> pointers;     // Array of Pointers
    vector<int *> recordpointer; // RecordPointers
    Node *nextnode;
    int minkeysize;
    int minleafkeysize;

    // Constructor
    Node(int maxkeysize, bool isLeaf)
    {
        this->isLeaf = isLeaf;
        this->maxkeysize = maxkeysize;
        this->currkeysize = 0;                       // Initially, no keys are in the node
        this->minleafkeysize = (maxkeysize + 1) / 2; // MINLEAFKEYSIZE
        this->minkeysize = maxkeysize / 2;           // minkeysize
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
};

Bplustree::Bplustree(/* args */)
{
}

Bplustree::~Bplustree()
{
}

Node **Bplustree::findNode(int key)
{
    Node *CurrNode = root;
    Node *ParentNode = nullptr;
    while (!CurrNode->isLeaf) // Traverse to leaf node
    {
        ParentNode = CurrNode;
        auto UpperBound = upper_bound(CurrNode->keys.begin(), CurrNode->keys.end(), key);
        int index = UpperBound - CurrNode->keys.begin();
        CurrNode = CurrNode->pointers[index];
    }
    Node **result = new Node *[2];
    result[0] = ParentNode;
    result[1] = CurrNode;
    return result; // return the leaf node
};

void Bplustree::deleteKey(int key)
{
    Node **ResultNode = this->findNode(key);
    Node *ParentNode = ResultNode[0];
    Node *LeadNode = ResultNode[1];

    // Delete from node
    bool found = false;
    for (int i = 0; i < TargetNode->currkeysize; i++)
    {
        if (TargetNode->keys[i] == key)
        {
            TargetNode->keys.erase(i);
            TargetNode->recordpointer.erase(i);
            TargetNode->currkeysize = TargetNode->keys.size();
            found = true;
            break;
        }
    }

    if (found)
    {
        // check for violation
        if (TargetNode->currkeysize < TargetNode->minleafkeysize)
        {
            // check if neighbour can borrow
        }
    }
    else
    {
        cout << "Key not found no key to delete" << endl;
    }

    // Can borrow from left or right
};

void Bplustree::BorrowNode(Node *Node)
{
}

void Bplustree::MergeNode(Node *Node1, Node *Node2)
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
