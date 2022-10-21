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
    string lineInput;
    ifstream file (filename);

    if (file){
        while(file.good()){
            
            //Taking each line of the file as a string input
            getline(file, lineInput);
            cout << lineInput;

        }
        file.close();
    } else {
        std::cout << "Input file not found";
    }

    #ifdef LEXERTEST
    
   ch = getch();
    while( tracker < (int)mycode.length()){

        currenttoken = lexer();
        if(currenttoken == intsym){
            cout << intvalue << endl;
        }

        if(currenttoken == printsym) {cout << "Print token =" << identifier << endl;}
        if(currenttoken == identifiersym) {cout << "Identifier token =" << identifier << endl;}
        
    }
    //std::cout << "intvalue = " << intvalue << std::endl; 
    #endif
}