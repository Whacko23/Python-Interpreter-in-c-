
#ifndef LEXER_CPP
#define LEXER_CPP

#include "lexer.h"

//For testing the lexer
#define TEST
#ifdef TEST

std::string mycode = "123,564";
#include <iostream>

int tracker = -1;
char getch(){
    tracker = tracker + 1;
    if (tracker < (int)mycode.length()){
        return mycode[tracker];
    }
    return '\0';
}

#endif

char ch;
char identifier[MAXIDENTIFIERLENGTH + 1];
int intvalue;
lextokens lexer(){
    std::string strinteger;
    lextokens currenttoken;
    switch (ch) {
        //TODO address EOF case
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': {
            while (isdigit(ch)){
                strinteger = strinteger + ch;
                ch = getch();
            }
            currenttoken = intsym;
            intvalue = stoi(strinteger);
           // std::cout << "intvalue = " << intvalue << std::endl; 
            break;
        }
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
   }
   return currenttoken;
}
 


#endif