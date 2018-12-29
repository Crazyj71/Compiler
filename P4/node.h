//Author: Jamie Wyatt
//Date: 10/22/2018
//Program Translation P4

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include "token.h"

typedef struct node{

	string label;
	struct token token1;
	struct token token2;

	struct node* child1;
	struct node* child2;
	struct node* child3;
	struct node* child4;

} node_t;


struct node* NewNode(string);

#endif
