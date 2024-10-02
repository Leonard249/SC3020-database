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
       
};

