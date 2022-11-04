#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "log.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"



// #define LEXERTEST
#define ASTTEST

using namespace std;


int main(int argc, const char *argv[]) {
    if (argc==1){
        log(1);
        return 0;
    }

    /* Opening the file */
    string filename = argv[1];
    
    ifstream file (filename);

    
    bool firstline = true;

    linenumber = 0;

    if (file){
        while(file.good()){
            
            //Taking each line of the file as a string input
            getline(file, lineInput);

            // DEEBUG
            cout << "     Current line = " << lineInput << endl;
            
            tracker = -1;
            ch = getch();

            //Pushing tokens to vector
            if (firstline == false){
                vec.push_back(newtoken(newlinesym,""));
            }
            while( tracker < (int)lineInput.length()){
                currenttoken = lext();
                switch(currenttoken){
                    case intsym: vec.push_back(newtoken(intsym, to_string(intvalue))); break;
                    case whitespacesym: vec.push_back(newtoken(whitespacesym, " ")); break;
                    case printsym: vec.push_back(newtoken(printsym, "print")); break;
                    case blocksym: vec.push_back(newtoken(blocksym, "  "));
                    case identifiersym: vec.push_back(newtoken(identifiersym, identifier)); break;
                    case whilesym: vec.push_back(newtoken(whilesym, "while")); break;
                    case eofsym: cout << "EOF token "  << endl; break;
                    case ifsym: vec.push_back(newtoken(ifsym, "if")); break;
                    case elsesym: vec.push_back(newtoken(elsesym, "else")); break;
                    case elseifsym: vec.push_back(newtoken(elseifsym, "else if")); break;
                    case defsym: vec.push_back(newtoken(defsym, "def")); break;
                    case returnsym: vec.push_back(newtoken(returnsym, "return")); break;
                    case semicolonsym: vec.push_back(newtoken(semicolonsym, ";")); break;
                    case commasym: vec.push_back(newtoken(commasym, ",")); break;
                    case assignsym: vec.push_back(newtoken(assignsym, "=")); break;
                    case errorsym: cout << "Error "  << identifier << " is unrecognized on line " << linenumber << " at character " << tracker << endl; break;
                    case dividesym: vec.push_back(newtoken(dividesym, "/")); break;
                    case openbracketsym: vec.push_back(newtoken(openbracketsym, "(")); break;
                    case closebracketsym: vec.push_back(newtoken(closebracketsym, ")")); break;
                    case plussym: vec.push_back(newtoken(plussym, "+")); break;
                    case minussym: vec.push_back(newtoken(minussym, "-")); break;
                    case multiplysym: vec.push_back(newtoken(multiplysym, "*")); break;
                    case equalsym: vec.push_back(newtoken(equalsym, "==")); break;
                    case leftanklesym: vec.push_back(newtoken(leftanklesym, "<")); break;
                    case rightanklesym: vec.push_back(newtoken(rightanklesym, ">")); break;
                    case colonsym: vec.push_back(newtoken(colonsym, ":")); break;
                    case commentsym: vec.push_back(newtoken(commentsym, "#")); break;
                    case singlequotesym: vec.push_back(newtoken(singlequotesym, identifier)); break;
                    case doublequotesym: vec.push_back(newtoken(doublequotesym, identifier)); break;
                    case opensquaresym: vec.push_back(newtoken(opensquaresym, "[")); break;
                    case closesquaresym: vec.push_back(newtoken(closebracketsym, "]")); break;
                    case shebangsym: vec.push_back(newtoken(shebangsym, "#!")); break;
                    case notequalsym: vec.push_back(newtoken(notequalsym, "!=")); break;
                    case greaterorequalsym: vec.push_back(newtoken(greaterorequalsym, ">=")); break;
                    case lessorequalsym: vec.push_back(newtoken(lessorequalsym, "<=")); break;
                    case lessthansym: vec.push_back(newtoken(lessthansym, "<")); break;
                    case greaterthansym: vec.push_back(newtoken(greaterthansym, ">")); break;
                    case newlinesym: cout << "  New line "  << endl; break;  
                }
            }
            firstline = false;


        }
        file.close();
        currenttoken = eofsym;
        vec.push_back(newtoken(eofsym,""));

        #ifdef LEXERTEST
        cout << "0000------" << endl;

        for (vector<token>::iterator it = vec.begin() ; it != vec.end(); ++it){
            switch((*it).tokentype){
                    case intsym: cout << "Integer token = " << (*it).data << endl; break;
                    case whitespacesym: cout << "Whitespace token " << endl; break;
                    case printsym: cout << "Print token " << endl; break;
                    case blocksym: cout << "Block token "  << endl;
                    case identifiersym: cout << "Identifier token = " << (*it).data  << endl; break;
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
                    case singlequotesym: cout << "Single quote token = " << (*it).data << endl; break;
                    case doublequotesym: cout << "Double quote token = " << (*it).data  << endl; break;
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
        #endif


        #ifdef ASTTEST
        currenttoken = lexer();
        astptr parseetree = parser();
        // printParserTree(parseetree);
        // cout << " ---Parse tree done---" << endl;                


        interpret(parseetree);
        
        freeMemory(parseetree); 
        cout << " ---End of program---" << endl;                
        #endif

    } else {
        cout << "Input file not found";
    }

    /*
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
    */

   
}