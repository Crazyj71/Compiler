//Author: Jamie Wyatt
//Date: 10/22/2018
//Program Translation P4

#include "node.h"
#include <string>

//Making a new Node, called in parser

struct node* NewNode(string label){
        struct node* p = new node;
        
	p->label = label;
        p->child1 = NULL;
        p->child2 = NULL;
        p->child3 = NULL;
        p->child4 = NULL;


return p;
}

