#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream> // For file handling

#include "Record.h"
#include "Bplustree.h"

using namespace std;
int NumberofNodes = 0;
int layers = 0;
int NumberofIO = 0;
// Node Class Constructor
Node::Node(int maxkeysize, bool isLeaf)
{
    this->isLeaf = isLeaf;
    this->maxkeysize = maxkeysize;
    this->currkeysize = 0;
    this->minkeysize = (maxkeysize / 2);
    this->minleafkeysize = (maxkeysize + 1) / 2;
    this->nextnode = nullptr;
    NumberofNodes++;
    /*
    this->keys.resize(0);
    if (isLeaf)
    {
        recordPointers.resize(maxkeysize);
    }
    else if (!isLeaf)
    {
        pointers.resize(maxkeysize + 1);
    }
    */
}

// Node Class Destructor
Node::~Node() {};

// B+ Tree Class Constructor
Bplustree::Bplustree(int maxkeysize) : maxkeysize(maxkeysize),
                                       root(nullptr) {}

// B+ Tree Class Destructor
Bplustree::~Bplustree() {}

// search for Leaf Node of target
Node *Bplustree::search(Node *root, float key)
{
    Node *cursor = root;
    while (cursor && !cursor->isLeaf)
    {
        // cout << "Traversing" << endl;
        for (int i = 0; i < cursor->currkeysize; i++)
        {
            // cout << "Search  " << cursor->currkeysize << endl;
            if (cursor->keys[i] >= key)
            {
                cursor = cursor->pointers[i]; // Go to lower bound of cursor->keys[i]
                // cout << "Search2  " << cursor->currkeysize << endl;
                break;
            }
            else if (i >= cursor->currkeysize - 1)
            {
                cursor = cursor->pointers[i + 1];
                // cout << "Search3  " << cursor->currkeysize << endl;
                break;
            }
        }
    }

    return cursor;
}

void Bplustree::insertKey(float key, Record *record)
{
    if (root == nullptr)
    {
        // Create a new root if it doesn't exist
        root = new Node(this->maxkeysize, true);
        root->keys.push_back(key);              // Use push_back to add the key
        root->recordPointers.push_back(record); // Assuming the first record pointer
        root->currkeysize = root->keys.size();
        // cout << "Inserted first key: " << key << endl;
        layers++;
    }
    else
    {
        // cout << "Searching" << endl;
        Node *cursor = search(root, key);
        // cout << "Search done" << endl;

        if (cursor->isLeaf)
        {
            // cout << "Handle insertion" << " SIZE " << cursor->keys.size() << endl;

            // Handle insertion in the leaf node
            if (cursor->currkeysize < maxkeysize)
            {
                int i = 0;
                while (key > cursor->keys[i] && i < cursor->currkeysize)
                    i++;
                cursor->keys.insert(cursor->keys.begin() + i, key);
                cursor->recordPointers.insert(cursor->recordPointers.begin() + i, record);
                cursor->currkeysize++;
                // cout << "test10" << cursor->currkeysize << endl;
            }
            else
            {
                // cout << "Split" << " SIZE " << cursor->currkeysize << endl;
                splitLeafNode(cursor, key, record);
                // cout << "test11" << endl;
            }
        }
    }
}

void Bplustree::splitLeafNode(Node *cursor, float key, Record *record)
{
    vector<float> virtualKey(cursor->keys);
    // cout << "sizecursor: " << cursor->keys.size() << endl;
    // cout << "sIZE4: " << virtualKey.size() << endl;
    vector<Record *> virtualRecordPointers(cursor->recordPointers);
    // cout << "sIZE4.5: " << virtualRecordPointers.size() << endl;
    bool insert = false;

    // Inserting the new key in the virtual key vector
    for (int i = 0; i < virtualKey.size(); i++)
    {
        // cout << "i = " << i << endl;
        if (virtualKey[i] >= key)
        {
            virtualKey.insert(virtualKey.begin() + i, key);                          // Insert key at position i
            virtualRecordPointers.insert(virtualRecordPointers.begin() + i, record); // Insert record pointer
            insert = true;
            break;
        }
    }

    // If the key is the largest, push it at the end
    if (!insert)
    {
        virtualKey.push_back(key);
        virtualRecordPointers.push_back(record);
    }

    // cout << "sIZE3: " << virtualKey.size() << endl;
    // cout << "sIZE3.5: " << virtualRecordPointers.size() << endl;

    int splitIndex = (maxkeysize + 1) / 2; // Split index for the leaf node
    Node *newLeaf = new Node(maxkeysize, true);

    // Move keys and record pointers to the original node
    cursor->keys.clear();
    cursor->recordPointers.clear();

    for (int i = 0; i < splitIndex; i++)
    {
        cursor->keys.push_back(virtualKey[i]);                      // Use push_back to insert the key
        cursor->recordPointers.push_back(virtualRecordPointers[i]); // Use push_back to insert the record
    }

    cursor->currkeysize = splitIndex; // Update the current key size of the cursor

    // Move the remaining keys and record pointers to the new leaf
    for (int i = splitIndex; i < virtualKey.size(); i++)
    {
        newLeaf->keys.push_back(virtualKey[i]);                      // Use push_back to insert the key
        newLeaf->recordPointers.push_back(virtualRecordPointers[i]); // Use push_back to insert the record
        newLeaf->currkeysize++;
    }

    // Link the new leaf node
    newLeaf->nextnode = cursor->nextnode;
    cursor->nextnode = newLeaf;

    // Check if cursor is the root node
    if (cursor == root)
    {
        cout << "Creating new root" << endl;
        Node *newRoot = new Node(maxkeysize, false);
        newRoot->keys.push_back(newLeaf->keys[0]); // Use push_back to add the first key
        newRoot->pointers.push_back(cursor);       // Link to the current leaf
        newRoot->pointers.push_back(newLeaf);      // Link to the new leaf
        newRoot->currkeysize = 1;
        root = newRoot; // Update the root
        layers++;
    }
    else
    {

        insertInternal(newLeaf->keys[0], findParent(root, cursor), cursor, newLeaf);
    }
}

/*void Bplustree::splitLeafNode(Node* cursor,float key,Record* record)
{
    vector<float> virtualKey(cursor->keys);
    cout << "sizecursor " << cursor->keys.size() << endl;
    cout << "sIZE4 "<<  virtualKey.size() << endl;
    vector<Record *> virtualRecordPointers(cursor->recordPointers);
    bool insert = false;
    for(int i=0;i<virtualKey.size();i++)
    {
        cout << "i = " << i <<endl;
        if(virtualKey[i]>key)
        {
            virtualKey.insert(virtualKey.begin()+i,key);  //insert at position i+1 and shift everything else back
            virtualRecordPointers.insert(virtualRecordPointers.begin()+i,record);
            insert = true;
            break;
        }
    }
    cout << "sIZE2 "<<  virtualKey.size() << endl;
    if(insert==false)
    {
        virtualKey.push_back(key);
        virtualRecordPointers.push_back(record);

    }
    cout << "sIZE3 "<<  virtualKey.size() << endl;
    int split = (maxkeysize + 1) / 2;
    Node *newLeaf = new Node(maxkeysize, true);
    cout<< "split value" <<split <<endl;
    cursor->currkeysize = split;
    cout<< "split value" << cursor->currkeysize <<endl;
    for (int i = 0; i < split; i++)
    {
        cursor->keys[i] = virtualKey[i];
        cursor->recordPointers[i] = virtualRecordPointers[i];
    }

    cursor->keys.resize(split);                          //Resize vector array
    cursor->recordPointers.resize(split);
    cout << "sIZE "<<  virtualKey.size() << endl;
    for (int i = split, j = 0; i < virtualKey.size(); i++, j++)
    {
        cout<< i << endl;
        newLeaf->keys[j] = virtualKey[i];
        newLeaf->recordPointers[j] = virtualRecordPointers[i];
        newLeaf->currkeysize++;
    }

    newLeaf->nextnode = cursor->nextnode;
    cursor->nextnode = newLeaf;

    if (cursor == root)
    {
        cout << "test12" <<endl;
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
}*/

/*void Bplustree::insertInternal(float key,Node* cursor, Node* child)
{
    cout << "insert internal" << endl;
    if (cursor->currkeysize < maxkeysize)
    {
        cout<< 123454 << endl;
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
}*/

void Bplustree::insertInternal(float key, Node *cursor, Node *leftchild, Node *rightchild)
{
    //cout << "insert internal" << endl;
    if (cursor == nullptr)
    {
        cout << "parent is nulll" << endl;
    }
    // Check if there's still space in the node for a new key
    if (cursor->currkeysize < maxkeysize)
    {
        cout << "Inserting key without splitting" << endl;

        // Find the correct position to insert the new key
        auto it = find(cursor->pointers.begin(), cursor->pointers.end(), leftchild);
        if (it == cursor->pointers.end())
            cout << "leftchild not found" << endl;
        int index = std::distance(cursor->pointers.begin(), it);
        cursor->keys.insert(cursor->keys.begin() + index, key);
        cursor->pointers.insert(cursor->pointers.begin() + index + 1, rightchild); // Ensure correct position for child pointer
        cursor->currkeysize++;
        /*
        int i = 0;
        while (i < cursor->currkeysize && key >= cursor->keys[i])
        {
            i++;
        }
        // Insert the key and child pointer
        cursor->keys.insert(cursor->keys.begin() + i, key);
        cursor->pointers.insert(cursor->pointers.begin() + i + 1, child); // Ensure correct position for child pointer
        cursor->currkeysize++;
        */
        // Increment the current key size
    }
    else
    {
        // If full, split the node
        cout << "Node is full, splitting" << endl;
        splitInternalNode(cursor, key, leftchild, rightchild);
    }
}

void Bplustree::splitInternalNode(Node *cursor, float key, Node *leftchild, Node *rightchild)
{
    //cout << "SPLITTING INTERNAL" << endl;
    vector<float> virtualKey(cursor->keys);
    vector<Node *> virtualPointer(cursor->pointers);
    int i = 0;
    // cout << "sIZE4: " << virtualKey.size() << endl;
    // cout << "sIZE4.5: " << virtualPointer.size() << endl;
    // cout << "currkeysize: " << cursor->currkeysize << endl;
    /*
    while (key >= virtualKey[i] && i < cursor->currkeysize)
        i++;
    */
    // Insert the new key and child pointer
    auto it = find(cursor->pointers.begin(), cursor->pointers.end(), leftchild);
    if (it == cursor->pointers.end())
        cout << "leftchild not found" << endl;
    int index = std::distance(cursor->pointers.begin(), it);
    virtualKey.insert(virtualKey.begin() + index, key);
    virtualPointer.insert(virtualPointer.begin() + index + 1, rightchild);
    // cout << "sIZE5: " << virtualKey.size() << endl;
    // cout << "sIZE5.5: " << virtualPointer.size() << endl;
    int split = (maxkeysize + 1) / 2;
    Node *newInternal = new Node(maxkeysize, false);

    // Update the current node
    cursor->currkeysize = split - 1;
    // clear
    cursor->keys.clear();
    cursor->pointers.clear();
    for (int j = 0; j < cursor->currkeysize; j++)
    {
        cursor->keys.push_back(virtualKey[j]);
        cursor->pointers.push_back(virtualPointer[j]);
    }
    cursor->pointers.push_back(virtualPointer[cursor->currkeysize]);

    // Fill the new internal node
    for (int j = split; j < virtualKey.size(); j++)
    {
        newInternal->keys.push_back(virtualKey[j]);
        newInternal->pointers.push_back(virtualPointer[j]);
        newInternal->currkeysize++;
    }
    newInternal->pointers.push_back(virtualPointer[virtualPointer.size() - 1]); // Last child pointer

    // If cursor is the root, create a new root
    if (cursor == root)
    {
        cout << "Creating new root" << endl;
        Node *newRoot = new Node(maxkeysize, false);
        newRoot->keys.push_back(virtualKey[split - 1]); // Use push_back to add the first key
        newRoot->pointers.push_back(cursor);            // Link to the current leaf
        newRoot->pointers.push_back(newInternal);       // Link to the new leaf
        newRoot->currkeysize = 1;
        root = newRoot;
        layers++;
    }
    else
    {
        insertInternal(virtualKey[split - 1], findParent(root, cursor), cursor, newInternal);
    }
}

Node *Bplustree::findParent(Node *cursor, Node *child)
{
    if (cursor->isLeaf)
        return nullptr; // No parent if we're at the root or at a leaf node //|| cursor->pointers[0]->isLeaf

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

vector<Record> Bplustree::searchKey(float minKey, float maxKey)
{
    std::vector<Record> results;
    Node *node = root;
    NumberofIO++; //access the root
    // Find the leaf node to start the search
    while (node && !node->isLeaf)
    {
        auto it = std::lower_bound(node->keys.begin(), node->keys.end(), minKey);
        int index = std::distance(node->keys.begin(), it);
        node = node->pointers[index];
        NumberofIO++; // everytime it traverse to another node....
        /*
        if (node->keys[index] == minKey)
        {
            node = node->pointers[index - 1];
        }
        else
        {
            node = node->pointers[index];
        }*/
    }

    // Collect records within the range
    while (node)
    {
        for (const auto &Record : node->recordPointers)
        {
            if (Record->FG_PCT_home > maxKey)
            {
                cout << "More than key : " << Record->FG_PCT_home << endl;
                return results; // Exit the function or break out of the loop
            }
            if (Record->FG_PCT_home >= minKey && Record->FG_PCT_home <= maxKey)
            {
                results.push_back(*Record);
            }
        }
        node = node->nextnode;
        NumberofIO++; //go to next leaf node
    }
    return results;
}

void Bplustree::Print(void)
{
    Node *node = root; // Start at the root of the B+ tree

    // Traverse down the tree by following the leftmost child pointer
    while (node && !node->isLeaf) // Stop when we reach a leaf node
    {
        node = node->pointers[0]; // Always go to the leftmost child
    }
    while (node)
    {
        for (const auto &Record : node->recordPointers)
        {
            cout << "Game Date: " << Record->GAME_DATE_EST
                 << ", Team ID: " << Record->TEAM_ID_home
                 << ", Points: " << Record->PTS_home
                 << ", FG%: " << Record->FG_PCT_home
                 << std::endl;
        }
        cout << "new node" << endl;
        node = node->nextnode;
    }
}
void Bplustree::Display(vector<Record> results)
{
    std::cout << "GAME_DATE_SET " << "Team_ID_Home " << "PTS_home " << "FG_PCT_home " << "FT_PCT_home " << "FG3_PCT_home " << "AST_home " << "REB_home " << "HOME_TEAM_WINS" << std::endl;
    for (const auto &Record : results)
    {
        std::cout << Record.GAME_DATE_EST << Record.TEAM_ID_home << Record.PTS_home << Record.FG_PCT_home << Record.FT_PCT_home << Record.FG3_PCT_home << Record.AST_home << Record.REB_home << Record.HOME_TEAM_WINS << std::endl;
    }
}