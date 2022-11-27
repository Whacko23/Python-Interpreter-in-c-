
#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <map>
#include "lexer.h"
#include "log.h"


using namespace std;

typedef enum
{
    n_statements,
    n_statement,
    n_assignment_list,
    n_assignment_int,
    n_simple_stmt,
    // n_compount_stmt,
    n_booleanexp,
    n_print,
    n_prints,
    n_newline,
    n_uminus,
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
    n_integer,
    n_string,
    n_list_int,
    n_listindex,
    n_listindex_data,
    n_index_assign_id,
    n_index_assign_index,
    n_index_assign_data,
    // Variable
    n_id,
    n_funct_definiton,
    n_funct,
    n_funct_arg,
    n_fcall,
    // n_args,
    n_return,
    n_while,
    n_if,
    n_ifelse,
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

extern astptr parseetree;


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
extern astptr expression();
extern astptr term();
extern astptr factor();
extern astptr booleanexpression();
extern astptr funct();
extern astptr funct_call();
extern astptr returnstatement();
// extern astptr argumentlist();
extern astptr list();
extern astptr booleanexpression();
extern astptr booleanoperation();
extern astptr parser();

extern void printParserTree(astptr head);
extern void freeMemory(astptr head);
extern void print_current_lextoken(lextokens t);
extern void print_current_parsetoken(nodetype n);

/*_______Interpreter_______________*/
//Data structures & variables
extern map<string, double> int_indefiers;
extern map<string, string> string_identifiers;
extern map<string, vector<double>> vector_identifiers;
extern bool notfound;
extern vector<double> current_vec_int;
extern map<string, vector<string>> funct_args;
extern vector<string> current_vec_str;
extern map<string, astptr> funct_definitions;
extern bool inside_funct;
extern string curr_fname;
extern int lineInsideFunction;
extern int function_def_line_start;


//Functions
extern string add_vector(vector<double> v);
extern void modify_vector(int i, string s);
extern vector<double> get_vector_int(string s);
extern void modify_vector_int(string s, vector<double> v);
extern void interpret(astptr head);
extern void print_vector_int();
extern void add_funct_args(string fname, vector<string> v);
extern vector<string> get_funct_args(string fname);
extern void print_vector_int(vector<double> v);
extern void add_function_def(string n, astptr p);
extern astptr get_funct_head(string s);

extern void exitProgram();
#endif