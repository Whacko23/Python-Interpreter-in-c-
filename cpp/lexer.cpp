
#ifndef LEXER_CPP
#define LEXER_CPP

#include "lexer.h"
#include <iostream>
//Declaring all the global variables
char ch;
string identifier;
int intvalue;
int tracker;
lextokens currenttoken;
string lineInput;

char getch(){
    tracker ++;
    // cout << "Tracker " << tracker << endl;
    // cout << "Requested character --> " << lineInput[tracker] << endl;
    return lineInput[tracker];
}


//TODO Comprehensive testing
lextokens lexer(){
    std::string strinteger;
    

    if (ch == EOF) return eofsym;

    //Check integers
    if (isdigit(ch)){
        strinteger = "";
        while (isdigit(ch)){
            strinteger = strinteger + ch;
            ch = getch();
        }
        intvalue = stoi(strinteger);
        return intsym;
    }

    //Check identifiers, reserved keywords
    if (isalpha(ch)){
        identifier = "";
        unsigned int i = 0;
        //NOTE Does not handle identifier that starts with '_' eg __main__
        while (isalpha(ch) || isdigit(ch) || ch == '_'){
            //Check for max identifier length 
            if (i < MAXIDENTIFIERLENGTH) { identifier = identifier + ch; i++; } 
            else {
                //Error: The identifier name is too long
                //TODO print to the screen about the error
                //TODO write the error to the file
                return errorsym;
            }
            ch = getch();
        }

        if (identifier == "if") {currenttoken = ifsym;} 
        else if (identifier == "elif") {currenttoken = elseifsym;}
        else if (identifier == "else") {currenttoken = elsesym;}
        else if (identifier == "print") {currenttoken = printsym;}
        else if (identifier == "return") {currenttoken = returnsym;}
        else if (identifier == "while") {currenttoken = whilesym;}
        else if (identifier == "def") {currenttoken = defsym;}
        else {currenttoken = identifiersym;}

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
        case '=': ch = getch(); if(ch == '='){currenttoken = equalsym; ch = getch();} else {currenttoken = assignsym;}; break;
        case '#': ch = getch(); if(ch == '!'){currenttoken = shebangsym; ch = getch();} else {currenttoken = commentsym;};  break;  
        case ' ': ch = getch(); if(ch == ' '){currenttoken = blocksym; ch = getch();} else {currenttoken = whitespacesym;}; break;
        
   }
   return currenttoken;
   
}
 


#endif