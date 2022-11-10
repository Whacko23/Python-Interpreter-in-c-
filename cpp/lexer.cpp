
#ifndef LEXER_CPP
#define LEXER_CPP

#include "lexer.h"
#include <iostream>
//Declaring all the global variables
char ch;
string identifier;
int intvalue;
int tracker;
int linenumber = 1;
int vectorindex = 0;
lextokens currenttoken;
string lineInput;
bool firstline = true;
double currdouble;
vector<token> vec;

char getch(){
    tracker ++;
    // cout << "Tracker " << tracker << endl;
    // cout << "Requested character --> " << lineInput[tracker] << endl;
    return lineInput[tracker];
}

token newtoken(lextokens type, string data){
    token l;
    l.data=data;
    l.tokentype=type;
    return l;
}

lextokens lext(){
    string strinteger;

    if (ch == '"'){
        identifier = "";
        ch = getch();
        while(tracker < (int)lineInput.length()){
            identifier = identifier + ch;
            ch = getch();
            if(ch == '"') break;
            if(tracker == (int)lineInput.length() - 1){
                //TODO SyntaxError: EOL while scanning string literal
                cout << "SyntaxError: EOL while scanning string literal" << endl;
                break;
            } 
        }
        ch = getch();
        return doublequotesym;
    }

    if (ch == '\''){
        identifier = "";
        ch = getch();
        while(tracker < (int)lineInput.length()){
            identifier = identifier + ch;
            ch = getch();
            if(ch == '\'') break;
            if(tracker == (int)lineInput.length() - 1){
                //TODO SyntaxError: EOL while scanning string literal
                cout << "SyntaxError: EOL while scanning string literal" << endl;
                break;
            } 
        }
        ch = getch();
        return singlequotesym;
    }


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
    //TODO Fix "  '2+3 " as a token s.t. block, identifier and double quote
    switch (ch) {
        case ';': currenttoken = semicolonsym; ch = getch(); break;
        case ':': currenttoken = colonsym; ch = getch(); break;
        case ',': currenttoken = commasym; ch = getch(); break;
        case '+': currenttoken = plussym; ch = getch(); break;
        case '/': currenttoken = dividesym; ch = getch(); break;
        case '-': currenttoken = minussym; ch = getch(); break;
        case '*': currenttoken = multiplysym; ch = getch(); break;
        case '(': currenttoken = openbracketsym; ch = getch(); break;
        case ')': currenttoken = closebracketsym; ch = getch(); break;
        case '[': currenttoken = opensquaresym; ch = getch(); break;
        case ']': currenttoken = closesquaresym; ch = getch(); break;
        case ' ': currenttoken = whitespacesym; ch = getch(); break;
        case '!': ch = getch(); if(ch == '='){currenttoken = notequalsym; ch = getch();}; break;
        case '>': ch = getch(); if(ch == '='){currenttoken = greaterorequalsym; ch = getch();} else {currenttoken = greaterthansym;}; break;
        case '<': ch = getch(); if(ch == '='){currenttoken = lessorequalsym; ch = getch();} else {currenttoken = lessthansym;}; break;
        case '=': ch = getch(); if(ch == '='){currenttoken = equalsym; ch = getch();} else {currenttoken = assignsym;}; break;
        case '#': ch = getch(); if(ch == '!'){currenttoken = shebangsym; ch = getch();} else {currenttoken = commentsym;};  break;
        default: currenttoken = errorsym; cout << "Im the culprit " << ch  << " tracker " << tracker<< endl; identifier = ""; identifier = identifier + ch; ch = getch(); break;
   }

   return currenttoken;
   
}

lextokens lexer(){
    token current = vec[vectorindex];
    lextokens tok = current.tokentype;
    string dat = current.data;

    if(tok==newlinesym) linenumber++;
    if(tok==intsym) intvalue = stoi(dat);
    if(tok==identifiersym || tok==singlequotesym || tok==doublequotesym) identifier = dat;

    vectorindex++;
    return tok;
}
lextokens cleanLexer(){
    currenttoken = lexer();
    while(currenttoken == whitespacesym){
        currenttoken = lexer();
    }
    return currenttoken;
}

#endif