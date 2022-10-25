
#ifndef PARSER_H
#define PARSER_H

#include <string>
using namespace std;

typedef struct tnode *astptr;
typedef struct tnode {
    int asttype;
    int astdata1,astdata2;
    astptr p1,p2,p3;
} astnode;

extern void statement();
extern void assignment();
extern void ifstatement();
extern void whilestatement();
extern void printstatement();
extern void returnstatement();
extern void expressiont();
extern void term();
extern void factor();
extern void booleanexpression();


#endif