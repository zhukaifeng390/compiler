#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;

string str;
int index = 0;
int flag = 0;
char c='#';
void E();       //E->TE'
void Ep();      //E'->+TE'|-TE'|ε
void T();       //T->FT'
void Tp();      //T'->*FT'|/FT'|ε
void F();       //F->(E)|i
void error(string str);

void error(string str){
    cout<<"ERROR AT "<<str<<endl;
    exit(0);
}

void E(){
    T();
    Ep();
}

void Ep(){
    if(str[index] == '+' || str[index] == '-'){
        index++;
        T();
        Ep();
    }
    else if(str[index] == ')' || str[index] == '#');
    else error("Ep");
}

void T(){
    F();
    Tp();
}

void Tp(){
    if(str[index] == '*' || str[index] == '/'){
        index++;
        F();
        Tp();
    }
    else if(str[index] == '+' || str[index] == '-' || str[index] == '#' || str[index] == ')');
    else error("Tp");
}

void F(){
    if((str[index]>='0' && str[index]<='9') || str[index] == '.'){
            for(int dot=1;(str[index] >= '0' && str[index] <= '9') || str[index] == '.';index++){
                if(str[index] == '.'){
                    if(dot == 1){
                        dot--;
                    }
                    else{
                        cout<<"浮点数识别出错"<<endl;
                        exit(0);
                    }
                }
            }
        }
    else{
        if(str[index] == '('){
            index++;
            E();
            if(str[index] == ')'){
                index++;
        }
        else{
            flag = 1;
            error("F");
        }
        }
        else{
            flag = 2;
            error("F");
        }
    }
}

int main(){
    int i=0;
    cout<<"Plese input arithmetic expressions:"<<endl;
    cin>>str;
    str += c;
    E();
    if(str[index] == '#'&flag == 0)
        cout<<"SUCCESS"<<endl;
    return 0;
}