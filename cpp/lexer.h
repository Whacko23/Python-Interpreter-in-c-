
#ifndef LEXER_H
#define LEXER_H

#include <string>
using namespace std;

//Setting max identifier length to 35 although python allows for infinite length for identifiers
//NOTE The max identifier length can be set to unlimited. Max length is enforced on lexer.cpp -> lexer() -> if (isalpha(ch))

#define MAXIDENTIFIERLENGTH 35

typedef enum{
    whitespacesym,
    blocksym,
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
    shebangsym,
    commentsym,
    leftanklesym,
    rightanklesym,
    colonsym,
    notequalsym,
    greaterthansym,
    lessthansym,
    greaterorequalsym,
    lessorequalsym,
} lextokens;

extern lextokens lexer();
extern int tracker;

extern string identifier;
extern char ch;
extern lextokens currenttoken;

//Variable to store the last integer value encountered by the lexer
extern int intvalue;
extern string lineInput;

extern char getch();

#define TEST
#ifdef TEST

extern string mycode;
#endif



#endif