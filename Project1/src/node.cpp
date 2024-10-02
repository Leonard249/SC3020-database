#include <iostream>
#include <string> 
#include <vector>     //Used for initialising keys and pointers
#include <algorithm>  //Used for sorting vector


class Node {
private:
    bool isLeaf;                    //Determined whether node is leaf
    int currkeysize;                   //Current number of keys               
    int maxsize;                    //Max number of keys in a node    
    std::vector<int> keys;          //Array of Keys 
    std::vector<Node*> pointers;    //Array of pointers pointing to child nodes/records

public:
    Node(bool isLeaf, int maxsize) : isLeaf(isLeaf), currsize(0), maxsize(0), keys(), pointers() {}   //Constructor

    bool isLeafNode() const {           //isLeafNode
        return isLeaf;
    }

    void setLeafNode(bool Leaf) {       
        isLeaf = Leaf;
    }

    std::vector<int>& getKeys() {
        return keys;
    }

    void addKey(int key) {
        if (currsize < maxsize) {                // Check if there is space for more keys
            keys.push_back(key);
            currsize++;                          // Increment the number of keys
            std::sort(keys.begin(), keys.end()); // Sort the keys (optional)
        } else {
            std::cout << "Cannot add key: node is full." << std::endl;
        }
    }

    std::vector<Node*>& getPointers() {
        return pointers;
    }

    void addPointer(Node* ptr) {
        
    }

    // Destructor
    ~Node() {
        // Clean up, if necessary
        for (auto ptr : pointers) {
            delete ptr;
        }
    }
};
