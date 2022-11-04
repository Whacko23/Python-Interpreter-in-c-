
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include "parser.h"
#include "lexer.h"
#include "log.h"

using namespace std;

extern void interpret(astptr head);

#endif