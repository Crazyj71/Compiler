//Author: Jamie Wyatt
//Date: 10/22/2018
//Program Translation P4

#include "token.h"
#include "scanner.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;


/////////////////////////////////////////////////////////////LIST OF TOKENS
 vector<string> tokenInstanceList =
        {"BEGINtk","ENDtk","ITERtk","VOIDtk","VARtk",
        "RETURNtk","READtk","PRINTtk","PROGRAMtk","CONDtk",
        "THENtk","LETtk","EQUALtk","LESStk","GREATERtk",
        "COLONtk","PLUStk","MINUStk","MULTItk","DIVtk",
        "MODtk","PERIODtk","LEFTPARtk","RIGHTPARtk",
        "COMMAtk","LEFTBRACEtk","RIGHTBRACEtk","SEMICOLONtk",
        "LEFTBRACKETtk","RIGHTBRACKETtk","IDtk", "EOFtk", "INTtk", "SPACEtk"};

//////////////////////////////////////////////////////////LIST OF IDENTIFIERS
 vector<string> keywordList =      
        {"begin","end","iter","void","var","return","read",
        "print","program","cond","then","let"};

//    lc  Uc  Digit etc
int STATE_TABLE[][24]=
   {
   {   1, -1, 2, EQUAL,    LESS,    GREATER,   COLON,    PLUS,     MINUS, MULTI,    DIV,      MOD,      PERIOD,   LEFTPAR,  RIGHTPAR, COMMA,    LEFTBRACE, RIGHTBRACE,SEMICOLON,LEFTBRACKET,RIGHTBRACKET, SPACE, END_OF_FILE, NEWLINE},
   {   1,  1, 1, IDENTIFIER,IDENTIFIER,IDENTIFIER,IDENTIFIER,IDENTIFIER,IDENTIFIER, IDENTIFIER, IDENTIFIER,IDENTIFIER,IDENTIFIER,IDENTIFIER,IDENTIFIER,IDENTIFIER,IDENTIFIER,IDENTIFIER,  IDENTIFIER,IDENTIFIER,  IDENTIFIER,IDENTIFIER, IDENTIFIER, IDENTIFIER},
   {   -1, -1, 2, INTEGER  ,INTEGER,  INTEGER,  INTEGER,  INTEGER,   INTEGER, INTEGER,  INTEGER,INTEGER,  INTEGER,  INTEGER,  INTEGER,   INTEGER,  INTEGER,   INTEGER,   INTEGER,  INTEGER,   INTEGER, INTEGER, INTEGER, INTEGER}
   };

/////////////////////////////////////////////////////////DRIVER FUNCTION
int FATableDriver(char c){
int STATE = 0;

if(c >= 'a' && c <= 'z')STATE = 0;
else if(c >= 'A' && c <= 'Z') STATE = 1;
else if(c >= '0' && c <= '9') STATE = 2;
else
switch (c)
{
case '=': STATE = 3; 
	break;
 case '<':  STATE = 4;                        
        break;
 case '>': STATE = 5;                             
        break;
 case ':':  STATE = 6;                             
        break;
 case '+':  STATE = 7;                             
        break;
 case '-':  STATE = 8;                             
        break;
 case '*':  STATE = 9;                             
        break;
 case '/':  STATE = 10;                             
        break;
 case '%':  STATE = 11;                             
        break;
 case '.':  STATE = 12;                             
        break;
 case '(':  STATE = 13;                             
        break;
 case ')':  STATE = 14;                             
        break;
 case ',':  STATE = 15;                             
        break;
 case '{':  STATE = 16;                             
        break;
 case '}':  STATE = 17;                             
        break;
 case ';':  STATE = 18;                             
        break;
 case '[':  STATE = 19;                             
        break;
 case ']':  STATE = 20;                             
        break;
 case ' ': STATE = 21;
	break;
 case '\n': STATE = 23;
	break;
 case '\t': STATE = 21;
	break;
 case EOF: STATE = 22;
	break;
    default: return -1;
}

return STATE;
}

//////////////////////////////////////////////////////ERROR FUNCTION
void ErrorFunction(int lineNumber){
cout << "Scanner Error: line: " <<  lineNumber << endl;
exit(0);
}

///////////////////////////////////////////////////GETTOKEN() FUNCTION
string getToken(int t){
return tokenInstanceList[t];
}

/////////////////////////////////////////////////GETEOFTOKEN FUNCTION
vector<struct token> getEOF(int lineNumber){
	
	vector<struct token> tokenList;
	token eofToken;
	eofToken.tokenInstance = "";
	eofToken.tokenId = getToken(31);
	eofToken.lineNumber = lineNumber;
	tokenList.push_back(eofToken);
	return tokenList;
}

//////////////////////////////////////////////////////MAIN SCANNER
vector<struct token> scanFile(stringstream& input, int line_number){
	
	//Define Error as -1
	int Error = -1;

	//States of the Each Pass
	int state, nextState = 0;

	//List of tokens in each line to return
	vector<struct token> tokenList;

	//Characters used for token generation
	char prevChar;
	char curChar;
        char lookAhead;

	string tokenInstance = "";
	//Core Loop, while the line is not empty
	while(lookAhead!=EOF){

		 //To fill token struct     
		token nextToken;
		string tokenId;		

                prevChar = curChar;
		input.get(curChar);
		lookAhead = input.peek();

		//Refer to State Table
		nextState = STATE_TABLE[state][FATableDriver(curChar)];

		//Go back for identifiers with variable length
		if(nextState == IDENTIFIER || nextState == INTEGER){
				input.unget();
		}
		
		//Skip Spaces
		if(nextState == SPACE) continue;

		//Check for Errors
		if(nextState==Error){
			ErrorFunction(line_number);
		}

		//FINAL STATE
		if(nextState>=1000){
		if(nextState==IDENTIFIER){
				//Check if the identifier is in the list of keywords
				if(std::find(keywordList.begin(), keywordList.end(), tokenInstance) != keywordList.end())
				{
					vector<string>::iterator it = std::find(keywordList.begin(), keywordList.end(), tokenInstance);
					tokenId = tokenInstanceList[std::distance(keywordList.begin(), it)];
					//tokenId = 1000 + std::distance(keywordList.begin(), it);
				}
				else
				{	//plain identifier
					tokenId = tokenInstanceList[nextState-1000];
					//tokenId = nextState;
				}
			}else{
				if(nextState>LET && nextState<IDENTIFIER) tokenInstance += curChar;
				//NOT IDENTIFIER
       		                 tokenId = tokenInstanceList[nextState-1000];
				 //tokenId =  nextState;
		}

		//Load token variables into nextToken struct
		nextToken.tokenInstance = tokenInstance;
		nextToken.tokenId = tokenId;
		nextToken.lineNumber = line_number;
		tokenList.push_back(nextToken);

		//Reset Vars for next Token
		state = 0;
		tokenInstance = "";

		}else{

		//NOT FINAL STATE
			state = nextState;						
			tokenInstance += curChar;
		}
	}
return tokenList;
}
