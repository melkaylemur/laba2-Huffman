#include "Node.h"
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>

using namespace std;

class HuffmanCoder {
public:
    vector<bool> code;                
    map<char,vector<bool> > table;  
    list<Node*>tree;
    HuffmanCoder();
    virtual ~HuffmanCoder();
    void buildTree(vector<unsigned char>&str);
    void printTree(Node *root, unsigned depth);
    void buildTableTree(Node *root);
    void encode(vector<unsigned char>&str, vector<unsigned char>&str_encod);
    void decode(vector<unsigned char>&str_enc, vector<unsigned char>&str_dec);
};

