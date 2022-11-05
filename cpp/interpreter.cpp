
#ifndef INTERPRETER_CPP
#define INTERPRETER_CPP

#include "interpreter.h"
#include <map>
#include <vector>
map<string, double> int_indefiers;
map<string, string> string_identifiers;
map<string, vector<double>> vector_identifiers;

void interpret(astptr head)
{
    string current;
    astptr left, right, mid;
    int temp;
    string save_id;
    int bleft;
    int bright;
    nodetype boolean_expression;
    bool flag = false;

    switch (head->asttype)
    {
    case n_integer:
        intvalue = stoi(head->astdata);
        break;
    case n_string:

    case n_id:
        identifier = head->astdata;
        cout << "identofier in switch: " << identifier << endl;
        intvalue = int_indefiers[identifier];
        cout << "int  in switch: " << intvalue << endl;
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
        cout << head->astdata << " ";
        left = head->p1;
        right = head->p2;
        interpret(left);
        boolean_expression = left->p3->asttype;
        cout << "boolean exp" << boolean_expression << endl;
        switch (boolean_expression)
        {
        case n_eq:
            if (left->p1->astdata == left->p2->astdata)
            {
                flag = true;
            }
        case n_gt:
            if (left->p1->asttype == n_integer)
            {
                bleft = stoi(left->p1->astdata);
            }
            if (left->p2->asttype == n_integer)
            {
                bright = stoi(left->p2->astdata);
            }
            if (bleft > bright)
            {
                flag = true;
            }
        case n_lt:
            if (left->p1->asttype == n_integer)
            {
                bleft = stoi(left->p1->astdata);
            }
            if (left->p2->asttype == n_integer)
            {
                bright = stoi(left->p2->astdata);
            }
            if (bleft < bright)
            {
                flag = true;
            }
        default:
            break;
        }
        if (flag == true)
        {
            interpret(right);
            flag = false;
        }
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
        cout << head->astdata << " ";

    case n_booleanexp:
        left = head->p1;
        mid = head->p2;
        right = head->p3;
        interpret(left);
        interpret(mid);
        interpret(right);
        break;
    case n_assignment_list:
    case n_assignment_int:
        left = head->p1;
        identifier = head->astdata;
        int_indefiers[identifier];
        save_id = identifier;
        interpret(left);
        int_indefiers[save_id] = intvalue;
        cout << save_id << " = " << int_indefiers[save_id] << endl;
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
            cout << " " << identifier;
        }
        else if (n_id)
        {
            cout << int_indefiers[left->astdata] << endl;
        }
        break;
    }
}

#endif