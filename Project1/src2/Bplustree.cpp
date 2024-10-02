#include <iostream>
#include <string> 
#include <vector>     //Used for initialising keys and pointers
#include <algorithm>   //Used for sorting arrays

using namespace std;

class Node
{
    public:
        bool isLeaf;                    //Determined whether node is leaf
        int currkeysize;                //Current number of keys               
        int maxkeysize;                    //Max number of keys in a node    
        vector<int> keys;               //Array of Keys 
        vector<Node*> pointers;         //Array of Pointers
        Node* nextnode;


    Node(int maxkeysize, bool isLeaf) {   //Constructor
        this->isLeaf = isLeaf;
        this->maxkeysize = maxkeysize;
        this->currkeysize = 0;      // Initially, no keys are in the node
        keys.resize(maxkeysize);    // Pre-allocate space for the keys
        pointers.resize(maxkeysize + 1, nullptr); // Pre-allocate for pointers (maxkeysize + 1)
    }

    ~Node(){

    }


};

class Bplustree
{
    public:
        Node* root;

        //Constructor
        Bplustree();    

        //Functions
        void deleteNode();
        void searchKey();
        void display();
        void getRoot();
        void insert();
        


};

Bplustree::Bplustree(/* args */)
{
}

Bplustree::~Bplustree()
{
}


