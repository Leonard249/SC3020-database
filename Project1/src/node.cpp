#include <iostream>
#include <string> 
#include <vector>     //Used for initialising keys and pointers
#include <algorithm>  //Used for sorting vector

using namespace std;
class Node {
private:
    bool isLeaf;                    //Determined whether node is leaf
    int currkeysize;                //Current number of keys               
    int maxsize;                    //Max number of keys in a node    
    vector<int> keys;          //Array of Keys 
    vector<Node*> pointers;    //Array of pointers pointing to child nodes/records

public:
    Node(bool isLeaf, int maxsize) : isLeaf(isLeaf), currsize(0), maxsize(0), keys(), pointers() {}   //Constructor

    bool isLeafNode() const {           //isLeafNode
        return isLeaf;
    }

    void setLeafNode(bool Leaf) {       
        isLeaf = Leaf;
    }

    vector<int>& getKeys() {
        return keys;
    }

    void addKey(int key) {
        if (currsize < maxsize)  //if node not empty 
        {               
            for(int i=0;i<currsizei++){

            }
        } 
        else 
        {
            cout << "Cannot add key: node is full." << endl;
        }
    }

    vector<Node*>& getPointers() {
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
