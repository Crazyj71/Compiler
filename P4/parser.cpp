//JAMIE WYATT
//Program translation P4
//Date: 10/22/2018

#include "node.h"
#include "token.h"
#include "parser.h"
#include "scanner.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <unistd.h>

static vector<struct token>tokenList;
static int INCREMENT;
static struct token TK;

//////////////////////////////////////////////////////REMOVE COMMENTS FUNCTION//(edited from geeksForGeeks.com)
string removeComments(ifstream& raw_input){

	//Convert input stream into string
	string raw_line = "";
	string raw_input_string = "";
	while(getline(raw_input, raw_line)){
		raw_input_string += (raw_line + "\n");
	}

	//new string without comments	
	string fixed_input_string = "";

	//Program length
	int n = raw_input_string.length();

	//Iterate through each character, removing areas contained by #'s.
	bool comment = false;
   	for (int i=0; i<n; i++)
   	{
		if (comment == true && raw_input_string[i] == '#') {
			comment = false, i++;
		}

	       	else if (comment){
        		continue;
      	 	}
		else if (raw_input_string[i] == '#') {
			comment = true, i++;
		}
        	else  fixed_input_string += raw_input_string[i];
    	}

	return fixed_input_string;
}

/////////////////////////////////////////////////////////GET NEXT TOKEN FUNCTION
void getNextToken(){
	TK = tokenList[INCREMENT];
	INCREMENT +=1;
}

///////////////////////////////////////////////////////////ERROR FUNCTION
void parseError(string expected){

	//Print line number and the expected token
	cout << "Parse Error on line: " << TK.lineNumber << ",\tExpected \"" << expected << "\"" << endl;      

	//Print what was found that caused the error to occur
	cout << "Instead found \"" << TK.tokenInstance << "\"" << endl;

	//Exit on Failure
	exit(0);
}


void printToken(string s){
cout << endl <<  "on tk " << s << endl;
}

//////////////////////////////////////////////////////PARSER FUNCTION
struct node* parser(ifstream& raw_input){

	INCREMENT = 0;

	//Token list to be returned
	//vector<struct token> tokenList;
	vector<struct token> tokenLineList;

	stringstream input;
	input << removeComments(raw_input);

	//For Each Line
	string str;
	int lineNumber = 0;

	//Get each line, send it to scanner, increment line number, load tokens from scanner
	while(getline(input, str)){	
		//vars
		stringstream line;
		str += " ";
		line << str;	

		//Call the Scanner for individual words
		string word;
		while(line >> word)
		{
			//vars
			stringstream s_word;
			word += " ";
			s_word << word;

			//SCANNER CALL
			tokenLineList = scanFile(s_word, lineNumber);
			tokenList.insert(tokenList.end(), tokenLineList.begin(), tokenLineList.end());
		}

		//add line
		lineNumber++;
	}
	
	//Call the Scanner for EOF TOKEN and add it
	tokenLineList = getEOF(lineNumber-1);
	tokenList.insert(tokenList.end(), tokenLineList.begin(), tokenLineList.end());

	//Get first token
	getNextToken();

	//Initialize tree start
	struct node* root = NULL;
	root = program();
	if(TK.tokenId == "EOFtk"){
		
	}else parseError("End of File");

	//return the tree pointer
	return root;
}
////////////////////////////////////////////////////
struct node* program(){

	//Make a new node
	struct node* p = NewNode("program");	

	//Verify if its correct syntax
	if(TK.tokenId == "VOIDtk"){

		//Grab next token
		getNextToken();

		//Set children
		p->child1 = vars();
		p->child2 = block();

	//Error if false
	}else parseError("void");
	
	//Connect branch of tree
	return p;
}
////////////////////////////////////////////////////

struct node* block(){

        struct node* p = NewNode("block");       

	if(TK.tokenId == "BEGINtk"){
		getNextToken();
		p->child1 = vars();
		p->child2 = stats();
		if(TK.tokenId == "ENDtk"){
			getNextToken();
			return p;
		}else parseError("end");
	}else parseError("begin");

	return p;
}
////////////////////////////////////////////////////

struct node* vars(){

        struct node* p = NewNode("vars");       

	if(TK.tokenId == "LETtk"){
		getNextToken();
		if(TK.tokenId == "IDtk"){
			p->token1 = TK;
			getNextToken();
			if(TK.tokenId == "EQUALtk"){
				getNextToken();
				if(TK.tokenId == "INTtk"){
					p->token2 = TK;
					getNextToken();
					p->child1 = vars();
					return p;
				}else parseError("Integer Value");
			}else parseError("=");
		}else parseError("Identifier Value");
	}else return p;
return p;
}
////////////////////////////////////////////////////

struct node* expr(){

        struct node* p = NewNode("expr");       

	p->child1 = A();
	if(TK.tokenId == "DIVtk"){
		p->token1 = TK;
		getNextToken();
		p->child2 = expr();
	}else if(TK.tokenId == "MULTItk"){
		p->token1 = TK;
		getNextToken();
		p->child2 = expr();
	}

	return p;
}
////////////////////////////////////////////////////

struct node* A(){

        struct node* p = NewNode("A");       

    p->child1 = M();
    if(TK.tokenId == "PLUStk"){
                p->token1 = TK;
		getNextToken();
                p->child2 = A();
    }else if(TK.tokenId == "MINUStk"){
                p->token1 = TK;

		getNextToken();
                p->child2 = A();
    }

	return p;
}
////////////////////////////////////////////////////

struct node* M(){

        struct node* p = NewNode("M");       

	if(TK.tokenId == "MINUStk"){
		p->token1 = TK; 
		getNextToken();
		p->child1 =M();
		return p;
	}else p->child1 = R();
	
	return p;
}
////////////////////////////////////////////////////

struct node* R(){

        struct node* p = NewNode("R");       

	if(TK.tokenId == "LEFTPARtk"){
		getNextToken();
		p->child1 = expr();
		if(TK.tokenId == "RIGHTPARtk"){
		getNextToken();
			return p;
		}else parseError(")");
	}
	else if(TK.tokenId == "IDtk"){
		p->token1 = TK; 
		getNextToken();
	return p;
	}
	else if(TK.tokenId == "INTtk"){
		p->token1 = TK; 
		getNextToken();
	return p;
	}
	else parseError("( or Integer or Identifier");
}
////////////////////////////////////////////////////

struct node* stats(){

        struct node* p = NewNode("stats");       

	p->child1 = stat();
	p->child2 = mStat();
	return p;
}
////////////////////////////////////////////////////

struct node* mStat(){

        struct node* p = NewNode("mStat");       

	if(TK.tokenId == "ENDtk"){
		return p;
	}else{
		p->child1 = stat();
		p->child2 = mStat();
		return p;
	}
}
////////////////////////////////////////////////////

struct node* stat(){

        struct node* p = NewNode("stat");       

	if(TK.tokenId == "READtk"){
		getNextToken();
		p->child1 = in();
		return p;
	}else if(TK.tokenId == "PRINTtk"){
		getNextToken();
		p->child1 = out();
		return p;
	}else if (TK.tokenId == "BEGINtk"){
		p->child1 = block();
		return p;
	}else if (TK.tokenId == "CONDtk"){
		getNextToken();
		p->child1 = ifSt();
		return p;
	}else if (TK.tokenId == "ITERtk"){
		getNextToken();
		p->child1 = loop();
		return p;
	}else if (TK.tokenId == "IDtk"){
		p->child1 = assign();
		return p;
	}else parseError("a statement");

	return p;
}
////////////////////////////////////////////////////

struct node* in(){

        struct node* p = NewNode("in");       

	if(TK.tokenId == "LEFTPARtk"){
		getNextToken();
		if(TK.tokenId == "IDtk"){
			p->token1 = TK; 
			getNextToken();
			if(TK.tokenId == "RIGHTPARtk"){
				getNextToken();
				if(TK.tokenId == "COLONtk"){
					getNextToken();
				}else parseError(":");
			}else parseError(")");
		}else parseError("Identifier");
	}else parseError("(");

	return p;
}
////////////////////////////////////////////////////

struct node* out(){

        struct node* p = NewNode("out");       
	if(TK.tokenId == "LEFTPARtk"){
		getNextToken();
		p->child1 = expr();
		if(TK.tokenId == "RIGHTPARtk"){
			getNextToken();
			if(TK.tokenId == "COLONtk"){
				getNextToken();
				return p;
			}else parseError(":");
		}else parseError(")");
	}else parseError("(");

	return p;
}
////////////////////////////////////////////////////

struct node* ifSt(){

        struct node* p = NewNode("ifSt");       

		if(TK.tokenId == "LEFTPARtk"){
			getNextToken();
			p->child1 = expr();
			p->child2 = RO();
			p->child3 = expr();
			if(TK.tokenId == "RIGHTPARtk"){
				getNextToken();
				p->child4 = stat();
			}else parseError(")");
		}else parseError("(");
	return p;
}
////////////////////////////////////////////////////

struct node* loop(){

        struct node* p = NewNode("loop");       

		if(TK.tokenId == "LEFTPARtk"){ 
			getNextToken();
			p->child1 = expr();
			p->child2 = RO();
			p->child3 = expr();
			if(TK.tokenId == "RIGHTPARtk"){
				getNextToken();
				p->child4 = stat();
			}else parseError(")");
		}else parseError("(");

	return p;
}
////////////////////////////////////////////////////

struct node* assign(){

        struct node* p = NewNode("assign");       

	if(TK.tokenId == "IDtk"){
		p->token1 = TK; 
		getNextToken();		
		if(TK.tokenId == "EQUALtk"){
			getNextToken();
			p->child1 = expr();
			if(TK.tokenId == "COLONtk"){
				getNextToken();
			}else parseError(":");
		}else parseError("=");
	}else parseError("Identifier");

	return p;
}
////////////////////////////////////////////////////

struct node* RO(){

        struct node* p = NewNode("RO");       

	if(TK.tokenId == "LESStk"){
		p->token1 = TK; 
		getNextToken();
		if(TK.tokenId == "EQUALtk"){
			p->token2 = TK; 
			getNextToken();
		}else return p;
	return p;
	}

	if(TK.tokenId == "EQUALtk"){
		p->token1 = TK; 
		getNextToken();
		if(TK.tokenId == "EQUALtk"){ 
        		p->token2 = TK; 
			getNextToken();
			return p;
		}else return p;
	return p;
	}

	if(TK.tokenId == "GREATERtk"){
		p->token1 = TK; 
		getNextToken();
		if(TK.tokenId == "EQUALtk"){ 
        		p->token2 = TK; 
			getNextToken();
			return p;
		}else return p;
		return p;

	}

	return p;
}
////////////////////////////////////////////////////

