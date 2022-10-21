
#ifndef PARSER_CPP
#define PARSER_CPP

#include "parser.h"
#include "lexer.h"
#include "log.h"

void assignment(){};
void ifstatement(){};
void whilestatement(){};
void printstatement(){};
void returnstatement(){};



/*
<statement> : := <assignment> | <ifstatement> | <whilestatement> | <printstatement> | <readstatement> | <returnstatement>
*/

void statement()
{
//TODO Log("inside statement function: Parser")
if (currenttoken==identifiersym) assignment();
else if (currenttoken==ifsym) ifstatement();
else if (currenttoken==whilesym) whilestatement();
else if (currenttoken==printsym) printstatement();
else if (currenttoken==returnsym) returnstatement();
/* else empty */
}




#endif