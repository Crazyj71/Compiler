//Author: Jamie Wyatt
//Date: 10/22/2018
//Program Translation P4

#ifndef SCANNER_H_
#define SCANNER_H_

#include <vector>
#include <fstream>

int FATableDriver(char);
void ErrorFunction(int);
string getToken(int);
std::vector<struct token> getEOF(int);
std::vector<struct token> scanFile(stringstream&, int);

#endif
