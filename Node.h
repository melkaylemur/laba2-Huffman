#ifndef NODE_H
#define	NODE_H

#include<stdio.h>
#include<stdlib.h>
#include <iostream>

using namespace std;

class Node {
    public:
	int count;
	char c;
	Node *left = NULL;
	Node *right = NULL;

	Node() { left=right=NULL; }
	
	/*Node(char new_c, int new_count){
            c = new_c;
            count = new_count;
	}*/

	Node(Node *l, Node *r){
            left = l;
            right = r;
            count = l->count + r->count;
	}

};

#endif	/* NODE_H */

