
#ifndef INTERPRETER_CPP
#define INTERPRETER_CPP

#include "interpreter.h"



bool flag = false;
int previous_line = 1;
int current_line = 1;
bool assign_list_variable = false;
bool firstprint = true;
nodetype current_dataytpe=n_empty;




bool boolean_evaluate_int(double l, double r, nodetype n){
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
    double temp, bool_exp_left, bool_exp_right;
    int index;
    string save_id, bool_left_str, bool_right_str;
    vector<double> tempvec_double;

    
    // cout << "Datatype " << head->asttype << " Data " << head->astdata << endl;
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
    case n_newline:
        left = head->p1;
        interpret(left);
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
        //Hardcoded n_integer
        current_dataytpe = n_integer;
        intvalue = int_indefiers[identifier];
        break;
    case n_list_int:
        save_id = head->astdata;
        // current_vec_int.clear();
        current_vec_int = get_vector_int(save_id);
        // cout << "INside list_int save id = " << save_id<<endl;
        // print_vector_int();
        // cout << "-----" << endl;
        // notfound=false;
        break;
    case n_plus:
    
        temp = 0;
        left = head->p1;
        right = head->p2;
        //
        // cout << "inside n_plus interpreter left n_type = ";
        // print_current_parsetoken(left->asttype);
        // cout << endl;
        // //
        // //
        // cout << "inside n_plus interpreter right n_type = ";
        // print_current_parsetoken(right->asttype);
        // cout << endl;
        // //
        // current_vec_int.clear();



        if(left->asttype==n_id){
            current_vec_int=get_vector_int(left->astdata);
            if(notfound){
                interpret(left);
                temp = intvalue;
                notfound = false;
            } else {
                tempvec_double = current_vec_int;
                // cout << "first vec" << " first data = " << left->astdata;
                // print_vector_int(current_vec_int);
                // cout << endl;
            }
        } else if (left->asttype==n_integer || left->asttype==n_listindex){
            interpret(left);
            temp = intvalue;           
        } else if(left->asttype==n_list_int){

        }   


        if(right->asttype==n_id){
            current_vec_int=get_vector_int(right->astdata);
            if(notfound){
                interpret(right);
                temp = temp + intvalue;
                intvalue = temp;
                notfound = false;
            } else {
                tempvec_double.insert(tempvec_double.end(), current_vec_int.begin(), current_vec_int.end());
                assign_list_variable = true;
                current_vec_int = tempvec_double;
            }
        } else if (right->asttype==n_integer || right->asttype==n_listindex){
            interpret(right);
            temp = temp + intvalue;  
            intvalue = temp;
        } else {
            
        }   
        break;
    
   /*
        temp = 0;
        left = head->p1;
        right = head->p2;
        interpret(left);
        temp = temp + intvalue;
        interpret(right);
        temp = temp + intvalue;
        intvalue = temp;
        break;
    */
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
        left = head->p1;
        right = head->p2;
        interpret(left);
        interpret(right);
        break;
    case n_if:
        // cout << head->astdata << " ";
        left = head->p1;
        right = head->p2;
        interpret(left);
        if(flag==true){
            interpret(right);
        } 
        // cout << "n_if flag value = " << flag << endl;
        break;
    case n_block_stmts:
        left = head->p1;
        right = head->p2;
        interpret(left);
        interpret(right);
        break;
    case n_statement:
        current_line = stoi(head->astdata);
        left = head->p1;
        interpret(left);
        break;
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
        /*
        if(current_dataytpe==n_integer){
            bool_exp_left = intvalue;
            current_dataytpe = n_integer;
        } else if (current_dataytpe==n_string){
            bool_left_str = identifier;
            current_dataytpe = n_string;
        }
        */
        
        bool_exp_left = intvalue;

        interpret(right);
        bool_exp_right = intvalue;

        /*
        if(current_dataytpe==n_integer){
            bool_exp_right = intvalue;
            current_dataytpe = n_integer;
        } else if (current_dataytpe==n_string){
            current_dataytpe = n_string;
            bool_right_str = identifier;
        }
        */
        //This is a boolean operator
        interpret(mid);
        flag = boolean_evaluate_int(bool_exp_left, bool_exp_right,mid->asttype); 

        /*
        if(current_dataytpe==n_integer){
            cout << "inside boolexp left = " << bool_exp_left << "right = " << bool_exp_right << endl;
            flag = boolean_evaluate_int(bool_exp_left, bool_exp_right,mid->asttype); 
        } else if (current_dataytpe==n_string){
            flag = boolean_evaluate_string(bool_left_str, bool_right_str,mid->asttype);
        }
        */
        break;
    case n_listindex:
        save_id = head->astdata;
        left=head->p1;
        temp = stoi(left->astdata);
        // cout << "current index = " << temp << endl;
        // current_vec_int.clear();
        current_vec_int = get_vector_int(save_id);
        if(notfound){
            //TODO error
            intvalue = int_indefiers[left->astdata];
            break;
        } else {
            intvalue = current_vec_int[temp];
        }
        break;
    case n_assignment_list:
        left=head->p1;
        save_id = head->astdata;
        interpret(left);
        if(left->asttype==n_list_int){
            // current_vec_int=get_vector_int(left->astdata);
            vector_identifiers[save_id]=current_vec_int;
            // current_vec_int.clear();  
        }
        break;
    case n_assignment_int:
        left = head->p1;
        identifier = head->astdata;
        save_id = identifier;
        interpret(left);


        if(assign_list_variable==false){
            int_indefiers[identifier];
            // interpret(left);
            int_indefiers[save_id] = intvalue;
        } else {
            vector_identifiers[save_id];
            vector_identifiers[save_id] = current_vec_int;
            assign_list_variable=false;
        }
        break;
    case n_prints:
        left = head->p1->p1;
        current_dataytpe = left->asttype;
        if (current_dataytpe == n_integer || current_dataytpe == n_plus || current_dataytpe == n_minus || current_dataytpe == n_mul || current_dataytpe == n_div)
        {
            interpret(left);
            cout << intvalue;
        }
        else if (current_dataytpe == n_string)
        {
            interpret(left);
            cout << identifier;
        }
        else if (current_dataytpe==n_id)
        {
            // current_vec_int.clear();
            current_vec_int = get_vector_int(left->astdata);
            if(notfound){ 
                cout << int_indefiers[left->astdata];
            } else{
                print_vector_int();
            }
        } else if (current_dataytpe==n_listindex){
            interpret(left);
            cout << intvalue;
        }


        right = head->p2;
        if (right->asttype == n_integer || right->asttype == n_plus || right->asttype == n_minus || right->asttype == n_mul || right->asttype == n_div)
        {   
            cout << " " << intvalue;
            interpret(right);
        }
        else if (right->asttype == n_string)
        {   
            cout << " " << identifier;
            interpret(right);
        }
        else if (right->asttype == n_id)
        {

            cout << " ";
            // current_vec_int.clear();
            current_vec_int = get_vector_int(right->astdata);
            if(notfound){ 
                cout << int_indefiers[right->astdata];
                if(firstprint==true){
                    cout << endl;
                    firstprint=false;
                } else if(current_line!=previous_line){
                    cout<<endl;
                } 
                break;
            }
            print_vector_int();
        } else if (right->asttype==n_listindex){
            cout << " ";
            interpret(right);
            cout << intvalue;
        }
        if(firstprint==true){
            cout << endl;
            firstprint=false;
        } else if(current_line!=previous_line){
            cout<<endl;
        }        

        break;
    case n_print:
        left = head->p1;

        //
        cout << "___________";
        print_current_parsetoken(head->asttype);
        cout << "___________";

        //
        current_dataytpe = left->asttype;
        if (current_dataytpe == n_integer || current_dataytpe == n_plus || current_dataytpe == n_minus || current_dataytpe == n_mul || current_dataytpe == n_div)
        {
            interpret(left);
            cout << intvalue;
        }
        else if (current_dataytpe == n_string)
        {
            interpret(left);
            cout << identifier;
        }
        else if (current_dataytpe==n_id)
        {
            // current_vec_int.clear();
            current_vec_int=get_vector_int(left->astdata);
            if(notfound){ 
                cout << int_indefiers[left->astdata];
                if(firstprint==true){
                    cout << endl;
                    firstprint=false;
                } else if(current_line!=previous_line){
                    cout<<endl;
                } 
                break;
            }
            print_vector_int();
        } else if (current_dataytpe==n_listindex){
            interpret(left);
            cout << intvalue;
        }
        if(firstprint==true){
            cout << endl;
            firstprint=false;
        } else if(current_line!=previous_line){
        cout<<endl;
        }
        break;
    case n_index_assign_data:
        left = head->p1;
        mid = head->p2;
        //right is the expression
        right = head->p3;
        
        //TODO check if right asttype ==
        interpret(right);
        temp = intvalue;

        save_id = left->astdata;
        index = stod(mid->astdata);

        // current_vec_int.clear();
        // current_vec_int = get_vector_int(save_id);
        interpret(left);


        current_vec_int.at(index) = temp;
        modify_vector_int(save_id, current_vec_int);

        break;
    case n_index_assign_id:
        current_vec_int=get_vector_int(head->astdata);
        break;
    case n_error: case n_def:
    case n_empty: 
    case n_index_assign_index:
    case n_uminus: case n_listindex_data:
        break;
    }

    
}

#endif