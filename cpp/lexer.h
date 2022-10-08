
#ifndef LEXER_H
#define LEXER_H

#include <string>
using namespace std;

//Setting max identifier length to 35 although python allows for infinite length for identifiers
//NOTE The max identifier length can be set to unlimited
//NOTE The max length is enforced on lexer.cpp -> lexer() -> if (isalpha(ch))
#define MAXIDENTIFIERLENGTH 35

typedef enum{
    intsym,
    printsym,
    ifsym,
    elsesym,
    elseifsym,
    defsym,
    returnsym,
    whilesym,
    semicolonsym,
    commasym,
    opensquaresym,
    closesquaresym,
    openbracketsym,
    closebracketsym,
    dividesym,
    multiplysym,
    plussym,
    minussym,
    assignsym,
    equalsym,
    identifiersym,
    errorsym,
    eofsym,
} lextokens;

extern lextokens lexer();
extern int tracker;

extern string identifier;
extern char ch;

//Variable to store the last integer value encountered by the lexer
extern int intvalue;

#define TEST
#ifdef TEST
extern char getch();
extern string mycode;
#endif



#endif