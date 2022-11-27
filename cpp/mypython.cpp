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
// #define DEBUG

using namespace std;

int main(int argc, const char *argv[])
{
    if (argc == 1)
    {
        log(1);
        return 0;
    }

    /* Opening the file */
    string filename = argv[1];

    ifstream file(filename);

    bool firstline = true;

    linenumber = 1;

    if (file)
    {
        while (file.good())
        {

            // Taking each line of the file as a string input
            getline(file, lineInput);

            #ifdef DEBUG
            cout << "     Current line = " << lineInput << endl;
            #endif

            tracker = -1;
            ch = getch();

            // Pushing tokens to vector
            if (firstline == false)
            {
                vec.push_back(newtoken(newlinesym, ""));
            }
            while (tracker < (int)lineInput.length())
            {
                currenttoken = lext();
                switch (currenttoken)
                {
                case intsym:
                    vec.push_back(newtoken(intsym, to_string(intvalue)));
                    break;
                case whitespacesym:
                    vec.push_back(newtoken(whitespacesym, " "));
                    break;
                case printsym:
                    vec.push_back(newtoken(printsym, "print"));
                    break;
                case blocksym:
                    vec.push_back(newtoken(blocksym, "  "));
                case identifiersym:
                    vec.push_back(newtoken(identifiersym, identifier));
                    break;
                case whilesym:
                    vec.push_back(newtoken(whilesym, "while"));
                    break;
                case eofsym:
                    cout << "EOF token " << endl;
                    break;
                case ifsym:
                    vec.push_back(newtoken(ifsym, "if"));
                    break;
                case elsesym:
                    vec.push_back(newtoken(elsesym, "else"));
                    break;
                case elseifsym:
                    vec.push_back(newtoken(elseifsym, "else if"));
                    break;
                case defsym:
                    vec.push_back(newtoken(defsym, "def"));
                    break;
                case returnsym:
                    vec.push_back(newtoken(returnsym, "return"));
                    break;
                case semicolonsym:
                    vec.push_back(newtoken(semicolonsym, ";"));
                    break;
                case commasym:
                    vec.push_back(newtoken(commasym, ","));
                    break;
                case assignsym:
                    vec.push_back(newtoken(assignsym, "="));
                    break;
                case errorsym:
                    cout << "Error " << identifier << " is unrecognized on line " << linenumber << " at character " << tracker << endl;
                    break;
                case dividesym:
                    vec.push_back(newtoken(dividesym, "/"));
                    break;
                case openbracketsym:
                    vec.push_back(newtoken(openbracketsym, "("));
                    break;
                case closebracketsym:
                    vec.push_back(newtoken(closebracketsym, ")"));
                    break;
                case plussym:
                    vec.push_back(newtoken(plussym, "+"));
                    break;
                case minussym:
                    vec.push_back(newtoken(minussym, "-"));
                    break;
                case multiplysym:
                    vec.push_back(newtoken(multiplysym, "*"));
                    break;
                case equalsym:
                    vec.push_back(newtoken(equalsym, "=="));
                    break;
                case leftanklesym:
                    vec.push_back(newtoken(leftanklesym, "<"));
                    break;
                case rightanklesym:
                    vec.push_back(newtoken(rightanklesym, ">"));
                    break;
                case colonsym:
                    vec.push_back(newtoken(colonsym, ":"));
                    break;
                case commentsym:
                    vec.push_back(newtoken(commentsym, "#"));
                    break;
                case singlequotesym:
                    vec.push_back(newtoken(singlequotesym, identifier));
                    break;
                case doublequotesym:
                    vec.push_back(newtoken(doublequotesym, identifier));
                    break;
                case opensquaresym:
                    vec.push_back(newtoken(opensquaresym, "["));
                    break;
                case closesquaresym:
                    vec.push_back(newtoken(closesquaresym, "]"));
                    break;
                case shebangsym:
                    vec.push_back(newtoken(shebangsym, "#!"));
                    break;
                case notequalsym:
                    vec.push_back(newtoken(notequalsym, "!="));
                    break;
                case greaterorequalsym:
                    vec.push_back(newtoken(greaterorequalsym, ">="));
                    break;
                case lessorequalsym:
                    vec.push_back(newtoken(lessorequalsym, "<="));
                    break;
                case lessthansym:
                    vec.push_back(newtoken(lessthansym, "<"));
                    break;
                case greaterthansym:
                    vec.push_back(newtoken(greaterthansym, ">"));
                    break;
                case newlinesym:
                    cout << "  New line " << endl;
                    break;
                }
            }
            firstline = false;
        }
        file.close();
        currenttoken = eofsym;
        vec.push_back(newtoken(eofsym, ""));

#ifdef LEXERTEST
        cout << "0000------" << endl;

        for (vector<token>::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            print_current_lextoken((*it).tokentype);
        }
#endif

#ifdef ASTTEST
        currenttoken = lexer();
        #ifdef DEBUG
        cout << " -------behind lexer-------" << endl;
        #endif
        astptr parseetree = parser();
        #ifdef DEBUG
        cout << " -------behind parser-------" << endl;
        printParserTree(parseetree);
        cout << " -------Parse tree done-------" << endl;
        #endif
        // printParserTree(parseetree);

        interpret(parseetree);

        freeMemory(parseetree);
        // cout << " ---End of program---" << endl;
#endif
    }
    else
    {
        cout << "Input file not found";
    }
}