/* 
 * File:   ContecstHuffmanCoder.h
 * Author: tanya
 *
 * Created on 18 Январь 2017 г., 0:49
 */

#ifndef CONTECSTHUFFMANCODER_H
#define	CONTECSTHUFFMANCODER_H

#include "ConNode.h"
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>

using namespace std;
class ContecstHuffmanCoder {
public:
    vector<bool> code;                
    map<int, map<char,vector<bool> > > con_table;  
    map<int, list<ConNode*> >con_tree;
    map<char,vector<bool> > table;  
    list<ConNode*>tree;
    ContecstHuffmanCoder();
    void buildTree(float p_s[5][5]);
    void buildTableTree(ConNode *root, int index);
    void encode(vector<unsigned char>&str, vector<unsigned char>&str_encod, char *file);
    void decode(vector<unsigned char>&str_enc, vector<unsigned char>&str_dec, char *file, char *file2);
    virtual ~ContecstHuffmanCoder();
private:

};

#endif	/* CONTECSTHUFFMANCODER_H */

