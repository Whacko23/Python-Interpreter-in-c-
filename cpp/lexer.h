
#ifndef LEXER_H
#define LEXER_H

//Setting max identifier length to 35 although python allows for infinite length for identifiers
#define MAXIDENTIFIERLENGTH 35

typedef enum{
    intsym,
    ptintsym,
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
} lextokens;

extern lextokens lexer();

extern char identifier[MAXIDENTIFIERLENGTH + 1];
extern char ch;

//Variable to store the last integer value encountered by the lexer
extern int intvalue;

#define TEST
#ifdef TEST
extern char getch();
#endif



#endif