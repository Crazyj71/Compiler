//Author: Jamie Wyatt
//Date: 10/22/2018
//Program Translation P4

#include "node.h"
#include "token.h"
#include "static_semantics.h"
#include "stack.h"
#include <string>


int varCount[100];
int i = 0;

void SemanticError(int errorType, struct node* p){
	cout << endl;
	if(errorType == 0){
		cout << "Redefinition Error on line "<< p->token1.lineNumber << endl;
		cout << "\t\"" <<  p->token1.tokenInstance << "\"" << " was already declared." << endl;
	}
	if(errorType == 1){
		cout << "Undefined Variable Error on line " << p->token1.lineNumber << endl;
		cout << "\t\"" <<  p->token1.tokenInstance << "\"" <<  " has not been defined." << endl;
	}

	exit(1);
}

int currentTemp=0;
string newTemp (){
string temp = "T" + to_string(currentTemp++);
return temp;
}

int currentLabel=0;
string newLabel(){
string label = "L" + to_string(currentLabel++);
return label;
}


void CallChildren(struct node* p, ofstream& target){
PreorderTraversal(p->child1,target);
PreorderTraversal(p->child2,target);
PreorderTraversal(p->child3,target);
PreorderTraversal(p->child4,target);

}

//Traverse the tree given a root node in Preorder
void PreorderTraversal(struct node* p, ofstream& target){
	
	if(p==NULL) return;

	string label = p->label;
	struct token token1 = p->token1;
	struct token token2 = p->token2;

	if(label=="program"){
		CallChildren(p, target);
		target << "STOP" << endl;
		for(int i = 0; i < currentTemp; i++){
		target << "T" + to_string(i) + " 0" << endl;;
		}
	}
	else if(label == "block")
	{
		i++;
        	varCount[i] = 0;
		CallChildren(p, target);
		      for (int x = 0; x < varCount[i]; x++){
		        pop();
        		i--;
        		target << "POP" << endl;}
        }
	else if (label == "vars")
	{
		struct token Variable = p->token1;
        	if(Variable.tokenInstance!=""){ 
		       int check = 0;
			if(varCount[i] > 0){
                                check = find(Variable.tokenInstance);
                                if(check >=0 && check < varCount[i]){
                                        SemanticError(0, p);
                                }else{
                                        push(Variable);
                                        varCount[i]++;
					target << "PUSH" << endl;
					target << "LOAD " + token2.tokenInstance << endl;
                                	target << "STACKW 0" << endl; 

				}
                	}else{
                                push(Variable);
                                varCount[i]++;;
				
				target << "PUSH" << endl;
                               	target << "LOAD " + token2.tokenInstance << endl;
				target << "STACKW 0" << endl;
                	}
	
		}

		CallChildren(p, target);	
	}
	 else if (label == "expr") 
        {
		if(token1.tokenId != ""){
			PreorderTraversal(p->child2,target);
			string Temp = newTemp();
			target << "STORE " + Temp << endl;
			PreorderTraversal(p->child1,target);
			if(token1.tokenId == "DIVtk"){
				target << "DIV " + Temp << endl;
			}else if(token1.tokenId == "MULTItk"){
				target << "MULT " + Temp << endl;
			}
		}
		else{
		CallChildren(p, target);
		}
        }
	 else if (label == "A") 
        {
		PreorderTraversal(p->child2, target);
		if(token1.tokenId=="PLUStk"){
			string Temp = newTemp();
			target << "STORE " + Temp << endl;
			PreorderTraversal(p->child1, target);
			target << "ADD " + Temp << endl;
		}else if(token1.tokenId=="MINUStk"){
			string Temp = newTemp();
                        target << "STORE " + Temp << endl;
                        PreorderTraversal(p->child1, target);
                        target << "SUB " + Temp << endl;
		}else{
			PreorderTraversal(p->child1, target);
		}
		PreorderTraversal(p->child3, target);
                PreorderTraversal(p->child4, target);

        }
	 else if (label == "M") 
        {

		if(token1.tokenId == "MINUStk"){
		CallChildren(p, target);
		target << "MULT -1" << endl;
		}else
		{
		CallChildren(p, target);
        	}
	}
	 else if (label == "R") 
        {
		struct token Variable = p->token1;
                int check = 0;

		if(token1.tokenId == "IDtk")
		{
			check = find(Variable.tokenInstance);
                	if(check == -1)
			{
                                SemanticError(1, p);
                	}

			target << "STACKR " + to_string(check) << endl;
		}
		else if (token1.tokenId == "INTtk")
		{
			target << "LOAD " + Variable.tokenInstance << endl;
		}

		CallChildren(p, target);
        }
	 else if (label == "stats") 
        {
		CallChildren(p, target);
        }
	 else if (label == "mStat") 
        {
	CallChildren(p, target);
        }
	 else if (label == "stat") 
        {
	CallChildren(p, target);
        }
	 else if (label == "in") 
        {
		struct token Variable = p->token1;
                int check = 0;
		 check = find(Variable.tokenInstance);
                        if(check == -1){
                                SemanticError(1, p);
                        }
		string Temp = newTemp();
		target << "READ " + Temp << endl;
		target << "LOAD " + Temp << endl;
		target << "STACKW " + to_string(check) << endl;		

        	CallChildren(p, target);
	}
	 else if (label == "out") 
        {
		CallChildren(p, target);
                string Temp = newTemp();
                target << "STORE " + Temp << endl;
                target << "WRITE " + Temp << endl;
        }
	 else if (label == "ifSt") 
        {
		PreorderTraversal(p->child3, target);
		string Temp = newTemp();
		target << "STORE " + Temp << endl;
		PreorderTraversal(p->child1, target);
		target << "SUB " + Temp << endl;
		string Label = newLabel();			
		if(p->child2->token1.tokenId == "LESStk"){
			if(p->child2->token2.tokenId == "EQUALtk"){
			cout << p->child2->token2.tokenId;
			target << "BRPOS " + Label << endl;
                	}else{
                        target << "BRZPOS " + Label << endl;
			}
		}else if(p->child2->token1.tokenId == "GREATERtk"){
		 	if(p->child2->token2.tokenId == "EQUALtk"){
                        target << "BRNEG " + Label << endl;
                	
			}
			else{
                        target << "BRZNEG " + Label << endl;
			
			}
                }else if(p->child2->token1.tokenId == "EQUALtk"){
		 	if(p->child2->token2.tokenId == "EQUALtk"){
                        target << "BRZERO " + Label << endl;
                	
			}else{
                        target << "BRPOS " + Label << endl;
			target << "BRNEG " + Label << endl;
			}
                }
		PreorderTraversal(p->child4, target);
		target << Label + ": NOOP" << endl;
        }
	 else if (label == "loop") 
        {
		string Label2 = newLabel();
		target << Label2 + ": NOOP" << endl;
		PreorderTraversal(p->child3, target);
                string Temp = newTemp();
                target << "STORE " + Temp << endl;
                PreorderTraversal(p->child1, target);
                target << "SUB " + Temp << endl;
                string Label = newLabel();
		if(p->child2->token1.tokenId == "LESStk"){
                        if(p->child2->token2.tokenId == "EQUALtk"){
                        target << "BRPOS " + Label << endl;
                        }else{
                        target << "BRZPOS " + Label << endl;
                        }
                }else if(p->child2->token1.tokenId == "GREATERtk"){
                        if(p->child2->token2.tokenId == "EQUALtk"){
                        target << "BRNEG " + Label << endl;

                        }
                        else{
                        target << "BRZNEG " + Label << endl;

                        }
                }else if(p->child2->token1.tokenId == "EQUALtk"){
                        if(p->child2->token2.tokenId == "EQUALtk"){
                        target << "BRZERO " + Label << endl;

                        }else{
                        target << "BRPOS " + Label << endl;
                        target << "BRNEG " + Label << endl;
                        }
                }
                PreorderTraversal(p->child4, target);
		target << "BR " + Label2 << endl;
		target << Label + ": NOOP" << endl;

        }
	 else if (label == "assign") 
        {
		struct token Variable = p->token1;
                int check = 0;
		 check = find(Variable.tokenInstance);
                        if(check == -1){
                                SemanticError(1, p);
                        }

		CallChildren(p, target);
		target << "STACKW " + to_string(check) << endl;

        }
	 else if (label == "RO") 
        {
		CallChildren(p, target);
        }




/*	if(p->token1.tokenId == "IDtk"){
		struct token Variable = p->token1;
		int check = 0;
		if(p->label == "vars"){
			if(varCount[i] > 0){
				check = find(Variable.tokenInstance);
				if(check >=0 && check < varCount[i]){
					SemanticError(0, p);
				}else{
					push(Variable);
					varCount[i]++;
				}
			}else{
				push(Variable);
				varCount[i]++;;
			}
		}else{
			check = find(Variable.tokenInstance);
			if(check == -1){
				SemanticError(1, p);
			}
		}
	}

*/
}

