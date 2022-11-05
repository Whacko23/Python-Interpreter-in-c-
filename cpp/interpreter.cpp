
#ifndef INTERPRETER_CPP
#define INTERPRETER_CPP

#include "interpreter.h"
#include <map>
#include <vector>
map<string, double> int_indefiers;
map<string, string> string_identifiers;
map<string, vector<double>> vector_identifiers;

bool flag = false;

bool boolean_evaluate_int(int l, int r, nodetype n){
    if(n == n_eq){
        if(l==r) return true;
    } else if (n == n_ne){
        if(l!=r) return true;
    } else if (n == n_gt){
        if(l>r){
            return true;
        } else {
        }
    } else if (n == n_ge){
        if(l>=r) return true;
    } else if (n == n_le){
        if(l<=r) return true;
    } else if (n == n_lt){
        if(l<r) return true;
    }
    return false;
};

bool boolean_evaluate_string(string l, string r, nodetype n){

    if(n == n_eq){
        if(l==r) return true;
    } else if (n == n_ne){
        if(l!=r) return true;
    } else if (n == n_gt){
        if(l>r) return true;
    } else if (n == n_ge){
        if(l>=r) return true;
    } else if (n == n_le){
        if(l<=r) return true;
    } else if (n == n_lt){
        if(l<r) return true;
    }
    return false;
};

void interpret(astptr head)
{
    string current;
    astptr left, right, mid;
    int temp, bool_exp_left, bool_exp_right;
    string save_id, bool_left_str, bool_right_str;

    nodetype current_dataytpe;
    

    switch (head->asttype)
    {
    case n_eq:
    case n_ne:
    case n_gt:
    case n_lt:
    case n_le:
    case n_ge:
        current_dataytpe = head->asttype;
    break;
    case n_integer:
        intvalue = stoi(head->astdata);
        current_dataytpe= n_integer;
        break;
    case n_string:
        identifier = head->astdata;
        current_dataytpe = n_string;
        break;
    case n_id:
        identifier = head->astdata;
        current_dataytpe = n_id;
        // cout << "identofier in switch: " << identifier << endl;
        intvalue = int_indefiers[identifier];
        // cout << "int  in switch: " << intvalue << endl;
        break;
    case n_plus:
        temp = 0;
        left = head->p1;
        right = head->p2;
        interpret(left);
        temp = temp + intvalue;
        interpret(right);
        temp = temp + intvalue;
        intvalue = temp;
        break;
    case n_minus:
        temp = 0;
        left = head->p1;
        right = head->p2;
        interpret(left);
        temp = temp + intvalue;
        interpret(right);
        temp = temp - intvalue;
        intvalue = temp;
        break;
    case n_div:
        temp = 0;
        left = head->p1;
        right = head->p2;
        interpret(left);
        temp = temp + intvalue;
        interpret(right);
        if (intvalue == 0)
        {
            cout << "ZeroDivisionError: division by zero" << endl;
            // TODO error.log
        }
        else
        {
            temp = temp / intvalue;
        }
        intvalue = temp;
        break;
    case n_mul:
        temp = 0;
        left = head->p1;
        right = head->p2;
        interpret(left);
        temp = temp + intvalue;
        interpret(right);
        temp = temp * intvalue;
        intvalue = temp;
        break;
    case n_statements:
    case n_while:
    case n_if:
        // cout << head->astdata << " ";
        left = head->p1;
        right = head->p2;
        interpret(left);
        if(flag==true) interpret(right);
        break;
    case n_block_stmts:
        left = head->p1;
        right = head->p2;
        interpret(left);
        interpret(right);
        break;
    case n_statement:
    case n_block_stmt:
    case n_simple_stmt:
        left = head->p1;
        interpret(left);
        break;
    case n_ifelse: 
        left = head->p1;
        mid = head->p2;
        right = head->p3;
        interpret(left);
        if(flag==true){
            interpret(mid);
        } else {
            interpret(right);
        }
        break;
    case n_booleanexp:
        left = head->p1;
        mid = head->p3;
        right = head->p2;
        //This takes into account of the order that n_booleaexp has booleanexpression, booleanexpression, boolean operator
        interpret(left);
        //NOTE this might cause problem for if string * int or string + int
        if(left->asttype==n_integer){
            bool_exp_left = intvalue;
            current_dataytpe = n_integer;
        } else if (left->asttype==n_string){
            bool_left_str = identifier;
            current_dataytpe = n_string;
        }

        interpret(right);

        if(right->asttype==n_integer){
            bool_exp_right = intvalue;
            current_dataytpe = n_integer;
        } else if (right->asttype==n_string){
            current_dataytpe = n_string;
            bool_right_str = identifier;
        }
        //This is a boolean operator
        interpret(mid);
        if(current_dataytpe==n_integer){
            flag = boolean_evaluate_int(bool_exp_left, bool_exp_right,mid->asttype); 
        } else if (current_dataytpe==n_string){
            flag = boolean_evaluate_string(bool_left_str, bool_right_str,mid->asttype);
        }
        break;
    case n_assignment_list:
    case n_assignment_int:
        left = head->p1;
        identifier = head->astdata;
        int_indefiers[identifier];
        save_id = identifier;
        interpret(left);
        int_indefiers[save_id] = intvalue;
        // cout << save_id << " = " << int_indefiers[save_id] << endl;
        break;
    case n_prints:
        left = head->p1;
        right = head->p2;
        interpret(left);
        if (right->asttype == n_integer || right->asttype == n_plus || right->asttype == n_minus || right->asttype == n_mul || right->asttype == n_div)
        {
            interpret(right);
            cout << " " << intvalue;
        }
        else if (right->asttype == n_string)
        {
            interpret(right);
            cout << " " << identifier;
        }
        else if (right->asttype == n_id)
        {

            cout << int_indefiers[right->astdata] << endl;
        }
        break;
    case n_print:
        left = head->p1;
        if (left->asttype == n_integer || left->asttype == n_plus || left->asttype == n_minus || left->asttype == n_mul || left->asttype == n_div)
        {
            interpret(left);
            cout << intvalue;
        }
        else if (left->asttype == n_string)
        {
            interpret(left);
            cout << identifier;
        }
        else if (n_id)
        {
            cout << int_indefiers[left->astdata] << endl;
        }
        break;
    }
}

#endif