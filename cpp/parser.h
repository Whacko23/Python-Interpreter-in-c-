
#ifndef PARSER_H
#define PARSER_H

#include <string>
using namespace std;

typedef enum
{
    n_statements,
    n_statement,
    n_assignment_list,
    n_assignment_int,
    n_simple_stmt,
    n_compount_stmt,
    n_booleanexp,
    n_print,
    n_prints,
    n_newline,
    // Unary operator
    n_uminus,
    // Arithmetic operator
    n_plus,
    n_minus,
    n_mul,
    n_div,
    // Relational operator
    n_eq,
    n_ne,
    n_lt,
    n_le,
    n_gt,
    n_ge,
    // Integer
    n_integer,
    n_string,
    n_list,
    // Variable
    n_id,
    // Function call,
    n_fcall,
    // Argument list
    n_args,
    // Return statement
    n_return,
    // While
    n_while,
    // If
    n_if,
    n_ifelse,
    // Error
    n_error,
    n_empty,
    n_def,
    n_block_stmt,
    n_block_stmts,

} nodetype;

typedef struct tnode *astptr;

typedef struct tnode
{
    nodetype asttype;
    string astdata;
    astptr p1, p2, p3;
} astnode;

extern astptr newnode(nodetype n, int s, astptr first, astptr second, astptr third);

extern astptr generate_ast();
extern astptr statements();
extern astptr statement();
extern astptr simple_stmt();
extern astptr compound_stmt();

extern astptr combinedexpression();
extern astptr assignment();
extern astptr ifstatement();
extern astptr whilestatement();
extern astptr blockstatement();
extern astptr blockstatements();
extern astptr printstatement();
extern astptr returnstatement();
extern astptr expressiont();
extern astptr term();
extern astptr factor();
extern astptr booleanexpression();
extern astptr funct();
extern astptr functionbody();
extern astptr argumentlist();
extern astptr list();
extern astptr booleanexpression();
extern astptr booleanoperation();
extern astptr parser();

extern void printParserTree(astptr head);
extern void freeMemory(astptr head);

#endif