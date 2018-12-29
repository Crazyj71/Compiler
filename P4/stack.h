#ifndef STACK_H_
#define STACK_H_

#include "token.h"
#include <vector>
#include <string>

void StackError(string);
void push(struct token);
void pop();
int find(string);

#endif
