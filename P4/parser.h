//Author: Jamie Wyatt
//Date: 10/22/2018
//Program Translation P4

#ifndef PARSER_H_
#define PARSER_H_
#include <fstream>
#include <vector>
#include <string>

string removeComments(ifstream&);
struct node* parser(ifstream&);

void parseError(string);

struct node* program();

struct node* block();

struct node* vars();

struct node* expr();

struct node* A();

struct node* M();

struct node* R();

struct node* stats();

struct node* mStat();

struct node* stat();

struct node* in();

struct node* out();

struct node* ifSt();

struct node* loop();

struct node* assign();

struct node* RO();


#endif
