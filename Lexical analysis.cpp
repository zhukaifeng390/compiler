#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

//keyword list
struct{
	string symbol;
	int classID;
}keywordtable[33];

//initialize keyword table
void initial_keyword(){
	int i=0;
	ifstream file;
	file.open("symbol.txt");
	string str;
	int j;
	while(i<33){
		file>>str;
		file>>j;
		keywordtable[i].symbol=str;
		keywordtable[i].classID=j;
		i++;
	}
	file.close();
}

//symbol table
struct{
	string name;
	int type;	
}symtable[100];

//Binary formula
struct{
	string sign;
	int classID;
}binary_formula[100];

int key_count=33;					//the number of key word
int sym_count=0;					//current count of symbol table
int binary_formula_count=0;			//current count of binary formula

//judge whether p is keyword
int p_is_keyword(string p){
	int i=0;
	for(int j=0;j<key_count;j++){
		if(p==keywordtable[j].symbol){	
			i=keywordtable[j].classID;
			break;
		}
	}
	return i;
}

//judge whether p is symbol
int p_is_symbol(string p){
	int i=0;
	for(int j=0;j<sym_count;j++){
		if(p==symtable[j].name){	
			i=symtable[j].type;
			break;
		}
	}
	return i;
}

//judge whether p is integer
bool p_is_integer(string p){
	int i;
	for(i=0;i<p.length();i++){
	if (p[i]-'0'==0||p[i]-'0'==1||p[i]-'0'==2||p[i]-'0'==3||p[i]-'0'==4||p[i]-'0'==5||p[i]-'0'==6||p[i]-'0'==7||p[i]-'0'==8||p[i]-'0'==9)
	continue;
	else
	break;	
	}
	if(i<p.length())
	return false;
	else
	return true;
}

//find what p is
void lookup(string p){
	int i=0;
	i=p_is_keyword(p);
	if(i!=0){
		binary_formula[binary_formula_count].sign=p;
		binary_formula[binary_formula_count++].classID=i;
	}
	else{
	bool flag=false;
	flag=p_is_integer(p);
	if(flag){
		binary_formula[binary_formula_count].sign=p;
		binary_formula[binary_formula_count++].classID=2;//classID of integer is 2
	}
	else{
	i=p_is_symbol(p);
	if(i!=0){
		binary_formula[binary_formula_count].sign=p;
		binary_formula[binary_formula_count++].classID=i;
	}
	else{
		symtable[sym_count].name=p;
		symtable[sym_count++].type=1;
		binary_formula[binary_formula_count].sign=p;
		binary_formula[binary_formula_count++].classID=1;//classID of customization identifier is 1
	}
	}
	}
}

//analysis source code
void wordanalysis(){
	ifstream file;//instantiate a read file object
	file.open("Test.txt");
	string str;
	while(file>>str){
		lookup(str);
	}
	file.close();
	ofstream outFile; //instantiate a write file object
	outFile.open("result.txt");
	int i=0; 
	while(i<binary_formula_count){
		outFile<<'('<<binary_formula[i].sign<<','<<binary_formula[i].classID<<')'<<endl;
		i++;
	}
	outFile.close();
	for(int i=0;i<binary_formula_count;i++){
		cout<<binary_formula[i].sign<<"  ";
		cout<<binary_formula[i].classID<<endl;
	}
}

int main(){
	initial_keyword();
    wordanalysis();
    return 0;
}

//issues: cannot identify integer (done)
//		  cannot identify code like main(){
//		  cannot initialize keywordtable after definition(done)
//		  cannot identify comment like // and /* ..... */
