
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <map>
#include <vector>
#include "parser.h"
#include "lexer.h"
#include "log.h"

using namespace std;

extern bool boolean_evaluate_int(double l, double r, nodetype n);
extern bool boolean_evaluate_string(string l, string r, nodetype n);
#endif