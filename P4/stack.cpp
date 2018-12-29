#include "stack.h" 
#include <string>

vector<struct token>StackVector;


void StackError(string error){
cout << endl;
cout << error << " Error: Too many vars in stack" << endl;
exit(1);
}

///////////////////////////////////////////////////////////////////////////////////
void push(struct token stackToken){
StackVector.push_back(stackToken);

if(StackVector.size() > 100){
StackError("Overflow");
}

}

/////////////////////////////////////////////////////////////////////////////////// 
void pop(){
StackVector.pop_back();
}
/////////////////////////////////////////////////////////////////////////////////// 
int find(string tokenInstance){
int loc = 0;

if(StackVector.size() == 1){
if(tokenInstance == StackVector[0].tokenInstance)
	return loc;
}

for (auto it = StackVector.rbegin() ; it != StackVector.rend(); ++it){
 
   if(tokenInstance == (*it).tokenInstance)
	return loc;
    loc++;
}

return -1;
}
/////////////////////////////////////////////////////////////////////////////////// 
