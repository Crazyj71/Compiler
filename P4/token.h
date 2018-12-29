//Author: Jamie Wyatt
//Date: 9/20/2018
//Program Translation P4

//FILE CONTAINING NODE STRUCTURE

#ifndef TOKEN_H_
#define TOKEN_H_

#include <set>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

using namespace std;
/*
 vector<string> tokenInstanceList = 
        {"BEGINtk","ENDtk","ITERtk","VOIDtk","VARtk",
	"RETURNtk","READtk","PRINTtk","PROGRAMtk","CONDtk",
	"THENtk","LETtk","EQUALtk","LESStk","GREATERtk",
	"COLONtk","PLUStk","MINUStk","MULTItk","DIVtk",
	"MODtk","PERIODtk","LEFTPARtk","RIGHTPARtk",
	"COMMAtk","LEFTBRACEtk","RIGHTBRACEtk","SEMICOLONtk",
	"LEFTBRACKETtk","RIGHTBRACKETtk","IDtk", "EOFtk", "INTtk", "SPACEtk"};

 vector<string> keywordList = 
	{"begin","end","iter","void","var","return","read",
	"print","program","cond","then","let"};

*/
struct token{
	string tokenId;
	string tokenInstance;
	int lineNumber;
};

//STATES
const int START = 0;
const int BEGIN = 1000;
const int END = 1001;
const int ITER = 1002;
const int VOID = 1003;
const int VAR = 1004;
const int RETURN = 1005;
const int READ = 1006;
const int PRINT = 1007;
const int PROGRAM = 1008;
const int COND = 1009;
const int THEN = 1010;
const int LET = 1011;
const int EQUAL = 1012;
const int LESS = 1013;
const int GREATER = 1014;
const int COLON = 1015;
const int PLUS = 1016;
const int MINUS = 1017;
const int MULTI = 1018;
const int DIV = 1019;
const int MOD = 1020;
const int PERIOD = 1021;
const int LEFTPAR = 1022;
const int RIGHTPAR = 1023;
const int COMMA = 1024;
const int LEFTBRACE = 1025;
const int RIGHTBRACE = 1026;
const int SEMICOLON = 1027;
const int LEFTBRACKET = 1028;
const int RIGHTBRACKET = 1029;
const int IDENTIFIER = 1030;
const int END_OF_FILE = 1031;
const int INTEGER = 1032;
const int SPACE = 1033;
const int NEWLINE = 1034;

#endif
