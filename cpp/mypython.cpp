#include <iostream>
#include <fstream>
#include <string>
#include "log.h"
#include "lexer.h"
// #include "parser.h"


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

    linenumber = 0;

    if (file){
        while(file.good()){
            
            //Taking each line of the file as a string input
            getline(file, lineInput);
            linenumber++;

            // DEEBUG
            cout << "     Current line = " << lineInput << endl;
            
            tracker = -1;

            currenttoken = lexer();
            // astptr parseetree = parser();
            // printParserTree(parseetree);
            // freeMemory(parseetree);


            #ifdef LEXERTEST
            while( tracker < (int)lineInput.length()){
                currenttoken = lexer();
                switch(currenttoken){
                    case intsym: cout << "Integer token = " << intvalue << endl; break;
                    case whitespacesym: cout << "Whitespace token " << endl; break;
                    case printsym: cout << "Print token " << endl; break;
                    case blocksym: cout << "Block token "  << endl;
                    case identifiersym: cout << "Identifier token = " << identifier  << endl; break;
                    case whilesym: cout << "While token "  << endl; break;
                    case eofsym: cout << "EOF token "  << endl; break;
                    case ifsym: cout << "IF token "  << endl; break;
                    case elsesym: cout << "Else token "  << endl; break;
                    case elseifsym: cout << "Elseif token "  << endl; break;
                    case defsym: cout << "Def token "  << endl; break;
                    case returnsym: cout << "REturn token "  << endl; break;
                    case semicolonsym: cout << "semicolon token "  << endl; break;
                    case commasym: cout << "comma token "  << endl; break;
                    case assignsym: cout << "assign token "  << endl; break;
                    case errorsym: cout << "Error "  << identifier << " is unrecognized on line " << linenumber << " at character " << tracker << endl; break;
                    case dividesym: cout << "divide token "  << endl; break;
                    case openbracketsym: cout << "OpenBracker token "  << endl; break;
                    case closebracketsym: cout << "CloseBracker token "  << endl; break;
                    case plussym: cout << "Plus token "  << endl; break;
                    case minussym: cout << "Minus token "  << endl; break;
                    case multiplysym: cout << "multiply token "  << endl; break;
                    case equalsym: cout << "Euqal token "  << endl; break;
                    case leftanklesym: cout << "Left ankle token "  << endl; break;
                    case rightanklesym: cout << "Right ankle token "  << endl; break;
                    case colonsym: cout << "Colon token "  << endl; break;
                    case commentsym: cout << "Comment token "  << endl; break;
                    case singlequotesym: cout << "Single quote token = " << identifier << endl; break;
                    case doublequotesym: cout << "Double quote token = " << identifier  << endl; break;
                    case opensquaresym: cout << "Open sq bracket token "  << endl; break;
                    case closesquaresym: cout << "Close sq bracket token "  << endl; break;
                    case shebangsym: cout << "Shebang token "  << endl; break;
                    case notequalsym: cout << "Not equal token "  << endl; break;
                    case greaterorequalsym: cout << "Greater than or equal token "  << endl; break;
                    case lessorequalsym: cout << "Less than or equal token "  << endl; break;
                    case lessthansym: cout << "Less than token "  << endl; break;
                    case greaterthansym: cout << "Greater than token "  << endl; break;
                    case newlinesym: cout << "  New line "  << endl; break;
                    
                }


            }
            //std::cout << "intvalue = " << intvalue << std::endl; 
            #endif


        }
        file.close();
        currenttoken = eofsym;
    } else {
        cout << "Input file not found";
    }

   
}