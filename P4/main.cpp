//Author: Jamie Wyatt
//Date: 10/22/2018
//Program Translation P4

#include <iostream>
#include "token.h"
#include "parser.h"
#include "static_semantics.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "node.h"

using namespace std;

int main(int argc, char *argv[]){


///////////////////////////////////////////////////PROCESS COMMAND ARGS
//Initialize Variables	
int arg_count = argc;		//number of arguments
string file_name = "";		//input file
string outfile_name = "";	//output file name
vector<string> lines;
vector<struct token> words;		//each word in the file
struct node* root = NULL;

//Check if filename argument is provided or not
if(arg_count == 2){
	file_name = argv[1];

	//Open the file
	ifstream input;
	ifstream lookahead;
	input.open(file_name);

	//Check if File Exists
	if(!input.is_open()){cout << "System Error: File Not Found\nEnding program...\n";
	return 0;
	}

	//Check if file contains .fs18
        if (file_name.find(".fs18") == string::npos) {
                cout << "File does not contain extension .fs18\n";
        	input.close();
	        return 0;
        }

	
	//Call the test scanner
	//words = parser(input);
	root = parser(input);
	
	//close input file
	input.close();
	
	//End Program if no words found
	if (root == NULL) {
		cout << "File contains nothing, ending program...\n";
		return 0;
	}
}

//Check if there are too many args
else if (arg_count > 2) {
	cout << "\n Error, too many args\n";
	return 0;
}

//No File provided: use stdin
else{
	file_name = "out.";
	//User instructions
	cout << "Enter words separated by SPACE, TAB, and/or ENTER...\n";	
	cout << "Type \"Ctrl+D\" to submit\n";
	string word;

	ofstream temp;
	temp.open("TEMPOUT");

	//Load the ifstream from cin
        while(getline(cin,word)){
		word += "\n";
		temp << word;
        }     

	temp.close();
	ifstream input;
	input.open("TEMPOUT");
        root = parser(input);
	input.close();

	//End Program if no words found
	if (root == NULL) { 
		cout << "\nNo input was read, ending program...\n";
		return 0; 
	}
}

//Find Position of "fs18" in filename and remove it
string fs18 = "fs18";
size_t pos = file_name.find(fs18);
if (pos != std::string::npos){
        file_name.erase(pos, fs18.length());
}

outfile_name = file_name.append("asm");


ofstream target;
target.open(outfile_name);

//Traverse and Print the Tree
PreorderTraversal(root, target);
target.close();

//UNUSED FROM OLD PROGRAM
/*
for (vector<struct token>::iterator it = words.begin() ; it != words.end(); ++it){
    cout << ' ' << (*it).tokenId;
    cout << ' ' << (*it).tokenInstance;
    cout << ' ' << (*it).lineNumber;
    cout << '\n';
}
*/

return 0;
}
