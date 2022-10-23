#include <iostream>
#include <fstream>
#include <string>
#include "log.h"
#include "lexer.h"
#include "parser.h"


#define LEXERTEST

using namespace std;



int main(int argc, const char *argv[]) {
    if (argc==1){
        log(1);
        return 0;
    }

    /* Opening the file */
    string filename = argv[1];
    
    ifstream file (filename);

    if (file){
        while(file.good()){
            
            //Taking each line of the file as a string input
            getline(file, lineInput);
            
            tracker = -1;
            ch = getch();

            #ifdef LEXERTEST
    
            while( tracker < (int)lineInput.length()){

                currenttoken = lexer();
                if(currenttoken == intsym){cout << "Integer token = " << intvalue << endl;}
                if(currenttoken == printsym) {cout << "Print token " << endl;}
                if(currenttoken == whitespacesym) {cout << "Whitespace token " << endl;}
                if(currenttoken == blocksym) {cout << "Block token "  << endl;}
                if(currenttoken == identifiersym) {cout << "Identifier token = " << identifier  << endl;}
                if(currenttoken == whilesym) {cout << "While token "  << endl;}
                if(currenttoken == eofsym) {cout << "EOF token "  << endl;}
                if(currenttoken == ifsym) {cout << "IF token "  << endl;}
                if(currenttoken == elsesym) {cout << "Else token "  << endl;}
                if(currenttoken == elseifsym) {cout << "Elseif token "  << endl;}
                if(currenttoken == defsym) {cout << "Def token "  << endl;}
                if(currenttoken == returnsym) {cout << "REturn token "  << endl;}
                if(currenttoken == semicolonsym) {cout << "semicolon token "  << endl;}
                if(currenttoken == commasym) {cout << "comma token "  << endl;}
                if(currenttoken == assignsym) {cout << "assign token "  << endl;}
                if(currenttoken == errorsym) {cout << "error token "  << endl;}
                if(currenttoken == dividesym) {cout << "divide token "  << endl;}
                if(currenttoken == openbracketsym) {cout << "OpenBracker token "  << endl;}
                if(currenttoken == closebracketsym) {cout << "CloseBracker token "  << endl;}
                if(currenttoken == plussym) {cout << "Plus token "  << endl;}
                if(currenttoken == minussym) {cout << "Minus token "  << endl;}
                if(currenttoken == multiplysym) {cout << "multiply token "  << endl;}
                if(currenttoken == equalsym) {cout << "Euqal token "  << endl;}
            }
            //std::cout << "intvalue = " << intvalue << std::endl; 
            #endif


        }
        file.close();
    } else {
        cout << "Input file not found";
    }

   
}