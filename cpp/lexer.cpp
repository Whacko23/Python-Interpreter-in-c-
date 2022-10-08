
#ifndef LEXER_CPP
#define LEXER_CPP

#include "lexer.h"

//Declaring all the global variables
char ch;
string identifier;
int intvalue;
int tracker = -1;

//For testing the lexer
#define TEST
#ifdef TEST

std::string mycode = "123print";
#include <iostream>

char getch(){
    tracker = tracker + 1;
    if (tracker < (int)mycode.length()) return mycode[tracker];
    return '\0';
}
#endif

//TODO Comprehensive testing
lextokens lexer(){
    std::string strinteger;
    lextokens currenttoken;

    if (ch == EOF) return eofsym;

    //Check integers
    if (isdigit(ch)){
        strinteger = "";
        while (isdigit(ch)){
            strinteger = strinteger + ch;
            ch = getch();
        }
        currenttoken = intsym;
        intvalue = stoi(strinteger);
        return currenttoken;
    }

    //Check identifiers, reserved keywords
    if (isalpha(ch)){
        identifier = "";
        unsigned int i = 0;
        while (isalpha(ch) || isdigit(ch)){
            if (i < MAXIDENTIFIERLENGTH) { identifier = identifier + ch; i++; } 
            else {
                //Error: The identifier name is too long
                //TODO print to the screen about the error
                //TODO write the error to the file
                return errorsym;
            }
            ch = getch();
        }

        if (identifier == "if") {currenttoken = ifsym; ch = getch();} 
        else if (identifier == "elif") {currenttoken = elseifsym; ch = getch();}
        else if (identifier == "else") {currenttoken = elsesym; ch = getch();}
        else if (identifier == "print") {currenttoken = printsym; ch = getch();}
        else if (identifier == "return") {currenttoken = returnsym; ch = getch();}
        else if (identifier == "while") {currenttoken = whilesym; ch = getch();}

        return currenttoken;
    }

    //Checking for symbols
    switch (ch) {
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
        case '#': ch = getch(); currenttoken = (ch == '!') ? shebangsym : commentsym; break;  
   }
   return currenttoken;
}
 


#endif