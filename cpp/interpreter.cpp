
#ifndef INTERPRETER_CPP
#define INTERPRETER_CPP


#include "interpreter.h"


void interpret(astptr head){
    string current;
    astptr left, right, mid;
    int temp;

    switch(head->asttype){
        case n_integer: 
            intvalue = stoi(head->astdata); break;
        case n_string: case n_id:
            identifier = head->astdata; break;
        case n_plus: 
            temp = 0;
            left = head->p1;
            right = head->p2;
            interpret(left);
            temp = temp + intvalue;
            interpret(right);
            temp = temp + intvalue; 
            intvalue = temp; break;
        case n_minus: 
        case n_div: case n_mul:

            cout << head->astdata << " ";
            left = head->p1;
            right = head->p2;
            interpret(left);
            interpret(right); break;
        case n_statements: case n_while:
        case n_if:
            cout << head->astdata << " ";
            left = head->p1;
            right = head->p2;
            interpret(left);
            interpret(right); break;
        case n_block_stmts:
            left = head->p1;
            right = head->p2;
            interpret(left);
            interpret(right); break;
        case n_statement: case n_block_stmt:
        case n_simple_stmt:
            left = head->p1;
            interpret(left); break;
        case n_ifelse: 
            left = head->p1;
            mid = head->p2;
            right = head->p3;
            interpret(left);
            interpret(mid);
            interpret(right); break;
        case n_assignment_list: case n_assignment_int:
            cout << head->astdata << " = ";
            left = head->p1;
            interpret(left); break;
        case n_prints:
            left = head->p1;
            right = head->p2;
            interpret(left);
            if(right->asttype == n_integer){
                interpret(right);
                cout << " " << intvalue;
            } else if (right->asttype == n_string){
                interpret(right);
                cout << " " << identifier;
            }
            break;
        case n_print:
            left = head->p1;
            if(left->asttype == n_integer || left->asttype == n_plus ||left->asttype == n_minus ||left->asttype == n_mul ||left->asttype == n_div){
                interpret(left);
                cout << intvalue;
            } else if (left->asttype == n_string){
                interpret(left);
                cout << " " << identifier;
            }
             break;
   
    }
    
}

#endif