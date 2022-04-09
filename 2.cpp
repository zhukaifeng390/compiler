#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;

string str;
string str_1;
int index = 0;
int flag = 0;
char c='#';
void E();       //E->TE'
void Ep();      //E'->+TE'|-TE'|ε
void T();       //T->FT'
void Tp();      //T'->*FT'|/FT'|ε
void F();       //F->(E)|i
int pre_process();

void error(string str){
    cout<<"ERROR AT "<<str<<endl;
    exit(0);
}

int pre_process(){
    int i=0;
    while(str_1[i]!='#'){
        if((str_1[i]>='0' && str_1[i]<='9') || str_1[i] == '.'){
            for(int dot=1;(str_1[i]>='0' && str_1[i]<='9') || str_1[i] == '.';i++){
                if(str_1[i] == '.'){
                    if(dot == 1){
                        dot--;
                    }
                    else{
                        cout<<"浮点数识别出错"<<endl;
                        return 0;
                    }
                }
            }
            str+='i';
        }
        else{
            str += str_1[i];
            i++;
        }
    }
    str += c;
    return 1;
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
    if(str[index]=='i'){
        index++;
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
            cout<<flag<<endl;
            error("F");
        }
        }
        else{
            flag = 2;
            cout<<flag<<endl;
            error("F");
        }
    }
}

int main(){
    int i=0;
    cout<<"Plese input arithmetic expressions:"<<endl;
    cin>>str_1;
    str_1 += c;
    i=pre_process();
    if(i==1){
    E();
    if(str[index] == '#' && flag == 0)
        cout<<"SUCCESS"<<endl;
    }
    return 0;
}