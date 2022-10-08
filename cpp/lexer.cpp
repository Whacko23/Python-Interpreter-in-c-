
#ifndef LEXER_CPP
#define LEXER_CPP

#include "lexer.h"

//For testing the lexer
#define TEST
#ifdef TEST

#include <cstring>
#include <iostream>
#include <string>
using namespace std;
string mycode = "print(3+5)";

int tracker = -1;
char getch(){
    tracker = tracker + 1;
    if (tracker < mycode.length()){
        cout << mycode[tracker];
        return mycode[tracker];
    }
    return '\0';
}

#endif

char ch;
char identifier[MAXIDENTIFIERLENGTH + 1];
int intvalue = 0;
lextokens lexer(){
    lextokens currenttoken;
    switch (ch) {
        //TODO address EOF case
        case ';': currenttoken = semicolonsym; ch = getch(); break;
        case ',': currenttoken = commasym; ch = getch(); break;
        case '+': currenttoken = plussym; ch = getch(); break;
        case '/': currenttoken = dividesym; ch = getch(); break;
        case '-': currenttoken = minussym; ch = getch(); break;
        case '*': currenttoken = multiplysym; ch = getch(); break;
        case '(': currenttoken = openbracketsym; ch = getch(); break;
        case ')': currenttoken = closebracketsym; ch = getch(); break;
        case '[': currenttoken = opensquaresym; ch = getch(); break;
        case ']': currenttoken = closesquaresym; ch = getch(); break;
        case '=': ch = getch(); currenttoken = (ch == '=') ? equalsym : assignsym; break;
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': {
            while (isdigit(ch)){
                
            }
        }
   }
}
 


#endif