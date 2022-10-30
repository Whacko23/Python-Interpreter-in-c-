
#ifndef PARSER_H
#define PARSER_H

#include <string>
using namespace std;



typedef enum {
    n_assignment,
    n_print,
    //Unary operator
    n_uminus,
    //Arithmetic operator
    n_plus,
    n_minus,
    n_mul,
    n_div,
    //Relational operator
    n_eq,
    n_ne,
    n_lt,
    n_le,
    n_gt,
    n_ge,
    //Integer
    n_integer,
    //Variable
    n_id,
    //Function call,
    n_fcall,
    //Argument list
    n_args,
    //Return statement
    n_return,
    //While
    n_while,
    //If
    n_if,

} nodetype;


typedef struct tnode *astptr;

typedef struct tnode {
    nodetype asttype;
    string astdata;
    astptr p1,p2,p3;
} astnode;

extern astptr newnode(nodetype n, int s, astptr first, astptr second, astptr third);


extern void statement();
extern void assignment();
extern void ifstatement();
extern void whilestatement();
extern void printstatement();
extern void returnstatement();
extern astptr expressiont();
extern astptr term();
extern astptr factor();
extern void booleanexpression();
extern void function();
extern void functionbody();
extern void argumentlist();
extern void list();
extern void booleanexpression();
extern void booleanoperation();
extern astptr parser();


extern void printParserTree(astptr head);
extern void freeMemory(astptr head);



#endif