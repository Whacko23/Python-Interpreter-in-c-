
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <map>
#include <vector>
#include "parser.h"
#include "lexer.h"
#include "log.h"

using namespace std;

typedef struct function_env {
  map<string, double> integers;
  map<string, vector<double>> lists;
} environment;

//Variables
extern bool funct_found;
extern environment current_funct_env;

//Data structures
// extern map<string, environment> funct_scope;


//Functions
extern bool boolean_evaluate_int(double l, double r, nodetype n);
extern bool boolean_evaluate_string(string l, string r, nodetype n);
// extern environment get_env(string funct_name);
// extern void create_env(string funct_name);
// extern void inject_int(string funct_name, double i);
// extern void inject_list(string funct_name, vector<double> l);
extern void inject_int(string variable, double i);
extern void inject_list(string variable, vector<double> l);
extern double get_funct_int(string variable);
extern vector<double> get_funct_list(string variable);

extern void reset_env();

#endif