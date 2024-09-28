#include "bplustree.h"
#include <algorithm>
#include <iostream>

// Constructor for BPlusTree
BPlusTree::BPlusTree(int degree) : degree(degree), root(nullptr)
{
    root = new BPlusTreeNode();
    root->isLeaf = true;
}

// Helper function to split a node
void BPlusTree::splitNode(BPlusTreeNode *parent, int index, BPlusTreeNode *node)
{
    int mid = degree / 2;
    BPlusTreeNode *newNode = new BPlusTreeNode();
    newNode->isLeaf = node->isLeaf;
    newNode->next = node->next;
    node->next = newNode;

    // Move the second half of the keys and children to the new node
    newNode->keys.assign(node->keys.begin() + mid, node->keys.end());
    node->keys.resize(mid);

    if (!node->isLeaf)
    {
        newNode->children.assign(node->children.begin() + mid + 1, node->children.end());
        node->children.resize(mid + 1);
    }
    else
    {
        newNode->records.assign(node->records.begin() + mid, node->records.end());
        node->records.resize(mid);
    }

    // Insert the new node into the parent
    parent->keys.insert(parent->keys.begin() + index, newNode->keys.front());
    parent->children.insert(parent->children.begin() + index + 1, newNode);
}

// Helper function to insert into a non-full node
void BPlusTree::insertNonFull(BPlusTreeNode *node, const Record &record)
{
    if (node->isLeaf)
    {
        // Insert the record into the leaf node
        auto it = std::lower_bound(node->records.begin(), node->records.end(), record, {
            return a.FG_PCT_home < b.FG_PCT_home;
        });
        node->records.insert(it, record);

        // Split the node if necessary
        if (node->records.size() > degree)
        {
            BPlusTreeNode *parent = findParent(root, node);
            if (!parent)
            {
                parent = new BPlusTreeNode();
                parent->isLeaf = false;
                parent->children.push_back(root);
                root = parent;
            }
            splitNode(parent, std::distance(parent->children.begin(), std::find(parent->children.begin(), parent->children.end(), node)), node);
        }
    }
    else
    {
        // Find the child to insert into
        auto it = std::upper_bound(node->keys.begin(), node->keys.end(), record.FG_PCT_home);
        int index = std::distance(node->keys.begin(), it);
        BPlusTreeNode *child = node->children[index];

        // Insert into the child
        insertNonFull(child, record);

        // Split the child if necessary
        if (child->keys.size() > degree)
        {
            splitNode(node, index, child);
        }
    }
}

// Insert a record into the B+ tree
void BPlusTree::insert(const Record &record)
{
    if (!root)
    {
        root = new BPlusTreeNode();
        root->isLeaf = true;
    }

    if (root->keys.size() == degree)
    {
        BPlusTreeNode *newRoot = new BPlusTreeNode();
        newRoot->isLeaf = false;
        newRoot->children.push_back(root);
        splitNode(newRoot, 0, root);
        root = newRoot;
    }

    insertNonFull(root, record);
}

// Search for records within a range
std::vector<Record> BPlusTree::search(float minKey, float maxKey)
{
    std::vector<Record> results;
    BPlusTreeNode *node = root;

    // Find the leaf node to start the search
    while (node && !node->isLeaf)
    {
        auto it = std::upper_bound(node->keys.begin(), node->keys.end(), minKey);
        int index = std::distance(node->keys.begin(), it);
        node = node->children[index];
    }

    // Collect records within the range
    while (node)
    {
        for (const auto &record : node->records)
        {
            if (record.FG_PCT_home >= minKey && record.FG_PCT_home <= maxKey)
            {
                results.push_back(record);
            }
        }
        node = node->next;
    }

    return results;
}

// Helper function to find the parent of a node
BPlusTreeNode *BPlusTree::findParent(BPlusTreeNode *root, BPlusTreeNode *child)
{
    if (!root || root->isLeaf)
    {
        return nullptr;
    }

    for (auto &node : root->children)
    {
        if (node == child)
        {
            return root;
        }
        BPlusTreeNode *parent = findParent(node, child);
        if (parent)
        {
            return parent;
        }
    }

    return nullptr;
}
