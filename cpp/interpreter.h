
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include "parser.h"
#include "lexer.h"
#include "log.h"

using namespace std;

extern void interpret(astptr head);
extern bool boolean_evaluate_int(int l, int r, nodetype n);
extern bool boolean_evaluate_string(string l, string r, nodetype n);
#endif