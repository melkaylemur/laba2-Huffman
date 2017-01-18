/* 
 * File:   ConNode.h
 * Author: tanya
 *
 * Created on 18 Январь 2017 г., 1:26
 */

#ifndef CONNODE_H
#define	CONNODE_H

#include<stdio.h>
#include<stdlib.h>
#include <iostream>

using namespace std;

class ConNode {
public:
    public:
	float count;
	char c;
	ConNode *left = NULL;
	ConNode *right = NULL;

	ConNode() { left=right=NULL; }
	
	/*Node(char new_c, int new_count){
            c = new_c;
            count = new_count;
	}*/

	ConNode(ConNode *l, ConNode *r){
            left = l;
            right = r;
            count = l->count + r->count;
	}

};

#endif	/* CONNODE_H */

