/* 
 * File:   HuffmanCoder.cpp
 * Author: tanya
 * 
 * Created on 16 Январь 2017 г., 23:54
 */

#include "HuffmanCoder.h"
#include "Node.h"

HuffmanCoder::HuffmanCoder() {
}

HuffmanCoder::~HuffmanCoder() {
}

struct compare{
    bool operator()(const Node* l, const Node* r) const { 
        return l->count < r->count;
    }
};

void HuffmanCoder::printTree(Node *root, unsigned depth = 0){
    if (root != NULL){
        printTree(root->left, depth + 3);
        for (unsigned i = 0; i < depth; i++)
            cout << " ";
        if (root->c) cout << root->count << "(" << root->c << ")" << '\n';
        else cout << root->count << '\n';
        printTree(root->right, depth + 3);
    }
}

void HuffmanCoder::buildTree(vector<unsigned char>&str){
    map<char,int> m;	
    for(int i = 0; i < str.size(); i++){
        char c = str[i];
        m[c]++;
    }
    for( map<char,int>::iterator itr=m.begin(); itr!=m.end(); ++itr){  
        Node *p = new Node;
        p->c = itr->first;
        p->count = itr->second;  
        tree.push_back(p);
        cout << itr->first << " - " << itr->second << "; p = " << (float)itr->second/(float)str.size() << '\n';
    }	
    while (tree.size()!=1){  
        tree.sort(compare());
        Node *SonL = tree.front();
        tree.pop_front();
        Node *SonR = tree.front(); 
        tree.pop_front();
        Node *parent = new Node(SonL,SonR); 
        tree.push_back(parent);
    }
}  

void HuffmanCoder::buildTableTree(Node *root){	
    if (root->left!=NULL){
        code.push_back(0);
        buildTableTree(root->left);
    }
    if (root->right!=NULL){
        code.push_back(1);
        buildTableTree(root->right);
    }
    if (root->c!=NULL)
        table[root->c] = code;
    code.pop_back();
}

void HuffmanCoder::encode(vector<unsigned char>&str, vector<unsigned char>&str_encod){
    int count=0;
    char buf=0;
    ofstream g("stream_encode_h.txt", ios::out | ios::binary);
    for (int i = 0; i < str.size(); i++){
        char c = str[i];
        vector<bool> x = table[c];
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

void HuffmanCoder::decode(vector<unsigned char>&str_enc, vector<unsigned char>&str_dec){
    Node *root = tree.front();
    ifstream F("stream_encode_h.txt", ios::in | ios::binary);
    ofstream g("stream_decode_h.txt", ios::out | ios::binary);
    Node *p = root;
    int count = 0;
    char byte = F.get();
    while(!F.eof())
    {   bool b = byte & (1 << (7-count) ) ; 
        if (b) p=p->right; else p=p->left;
        if (p->left==NULL && p->right==NULL) {
            g<<p->c; 
            str_dec.push_back(p->c);
            p=root;
        }  
        count++;
        if (count==8) {count=0; byte = F.get();}
    }
    
    
}