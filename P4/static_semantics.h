//Author: Jamie Wyatt
//Date: 10/22/2018
//Program Translation P4


#ifndef STATIC_SEMANTICS_H_
#define STATIC_SEMANTICS_H_

#include "node.h" 
#include <fstream>
void SemanticError(int, struct node*);
void PreorderTraversal(struct node*, ofstream&);

#endif
