/* 
 * File:   ContecstHuffmanCoder.cpp
 * Author: tanya
 * 
 * Created on 18 Январь 2017 г., 0:49
 */

#include "ContecstHuffmanCoder.h"

ContecstHuffmanCoder::ContecstHuffmanCoder() {
}

ContecstHuffmanCoder::~ContecstHuffmanCoder() {
}

struct compare{
    bool operator()(const ConNode* l, const ConNode* r) const { 
        return l->count < r->count;
    }
};

void ContecstHuffmanCoder::buildTableTree(ConNode *root, int index){	
    if (root->left!=NULL){
        code.push_back(0);
        buildTableTree(root->left, index);
    }
    if (root->right!=NULL){
        code.push_back(1);
        buildTableTree(root->right, index);
    }
    if (root->c!=NULL)
        table[root->c] = code;
    code.pop_back();
}

void ContecstHuffmanCoder::buildTree(float p_s[5][5]){
    for (int i = 0; i < 5; i++){
        if (i == 1)
            int fgh=4567;
        for (int j = 0; j < 5; j++){
            ConNode *p = new ConNode;
            p->c = j + '0';
            p->count = p_s[i][j];
            tree.push_back(p);
            cout << p->c << " - " << p->count << "; p = " << p->count << '\n';
        }
        
        while (tree.size()!=1){  
            tree.sort(compare());
            ConNode *SonL = tree.front();
            tree.pop_front();
            ConNode *SonR = tree.front(); 
            tree.pop_front();
            ConNode *parent = new ConNode(SonL,SonR); 
            tree.push_back(parent);
        }
        ConNode *root = tree.front();
        buildTableTree(root, i);
        code.clear();
        con_table[i] = table;
        table.clear();
        for (map<char,vector<bool> >::iterator itr = con_table[i].begin(); itr != con_table[i].end(); ++itr){
            for (vector<bool>::iterator it_b = itr->second.begin(); it_b != itr->second.end(); ++it_b){
                cout << *it_b;
            }
            cout << " - " << itr->first << '\n';
        }
        con_tree[i] = tree;
        tree.clear();
    }
} 
void ContecstHuffmanCoder::encode(vector<unsigned char>&str, vector<unsigned char>&str_encod, char *file){
    int count=0;
    char buf=0;
    ofstream g(file, ios::out | ios::binary);
    g<<str[0]-'0';
    for (int i = 1; i < str.size(); i++){
        char c = str[i];
        int index = str[i-1]-'0';
        map<char,vector<bool> > vr_table = con_table[index];
        vector<bool> x = vr_table[c];
	for(int n = 0; n < x.size(); n++){
            buf = buf | x[n]<<(7-count);   
	    count++;   
	    if (count==8){
                count=0;
                g << buf;
                str_encod.push_back(buf); 
                buf=0; 
            } 
       }
    }
}
void ContecstHuffmanCoder::decode(vector<unsigned char>&str_enc, vector<unsigned char>&str_dec, char *file, char *file2){
    ifstream F(file, ios::in | ios::binary);
    ofstream g(file2, ios::out | ios::binary);
    int count = 0;
    char byte = F.get();
    int index = byte - '0';g<<byte;
    str_dec.push_back(byte);
    list<ConNode*> vr_tree = con_tree[index];
    ConNode *root = vr_tree.front();
    ConNode *p = root;
    byte = F.get();
    while(!F.eof()){
        bool b = byte & (1 << (7-count) ) ; 
        if (b) 
            p=p->right; 
        else 
            p=p->left;
        if (p->left==NULL && p->right==NULL) {
            g<<p->c;
            index = p->c - '0';
            vr_tree = con_tree[index];
            str_dec.push_back(p->c);
            p=vr_tree.front();
        }  
        count++;
        if (count==8) {count=0; byte = F.get();}
    }  
}