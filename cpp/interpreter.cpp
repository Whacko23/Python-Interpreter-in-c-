
#ifndef INTERPRETER_CPP
#define INTERPRETER_CPP

#include "interpreter.h"

// #define TREE

//variables
int previous_line = 1,
    current_line = 1;
bool firstprint = true, 
     function_return = false,
     assign_list_variable = false,
     flag = false,
     inside_funct = false,
     funct_found = false;

nodetype current_dataytpe=n_empty;

environment current_funct_env;


/*
    The funct_scope is useful for nested function or recursive function
    So for a single function, a global variable for environment will suffice
    
    Hence, it is commented down below 


// map<string, environment> funct_scope;


environment get_env(string funct_name){
    map<string, environment>::iterator search = funct_scope.find(funct_name);
    environment env;
    if(search==funct_scope.end()){
        funct_found=false;
    } else {
        funct_found=true;
        env = search->second;
    }

    return env;
};

void create_env(string funct_name){

};

void inject_int(string funct_name, double i){
};

void inject_list(string funct_name, vector<double> l){

};
*/

void reset_env(){
    current_funct_env.integers.clear();
    current_funct_env.lists.clear();
}


void inject_int(string variable, double i){
    current_funct_env.integers.insert({variable, i});
};

void inject_list(string variable, vector<double> l){
    current_funct_env.lists.insert({variable, l});
};

extern double get_funct_int(string variable){
    double d=0;
    map<string, double>::iterator search = current_funct_env.integers.find(variable);
    if(search==current_funct_env.integers.end()){
        notfound=true;
    } else {
        notfound=false;
        d = search->second;
    }
    return d;
};

extern vector<double> get_funct_list(string variable){
    vector<double> d;
    map<string, vector<double>>::iterator search = current_funct_env.lists.find(variable);
    if(search==current_funct_env.lists.end()){
        notfound=true;
    } else {
        notfound=false;
        d = search->second;
    }
    return d;
};


//evaluation helper
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

//evaluation helper
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
    double temp =0,
           bool_exp_left=0, 
           bool_exp_right=0;
    int index;
    string save_id, bool_left_str, bool_right_str, temp_str;
    vector<double> tempvec_double;
    nodetype bool_left_type = n_empty,
             bool_right_type = n_empty;

    
    // cout << "Datatype " << head->asttype << " Data " << head->astdata << endl;
    switch (head->asttype)
    {
    case n_eq:
    case n_ne:
    case n_gt:
    case n_lt:
    case n_le:
    case n_ge:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        current_dataytpe = head->asttype;
        break;
    case n_newline:
        left = head->p1;
        interpret(left);
        current_dataytpe = head->asttype;    
        break;
    case n_integer:
        intvalue = stod(head->astdata);
        current_dataytpe= n_integer;

        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        cout << " = " << intvalue << " *leaf* ";
        #endif

        break;
    case n_string:
        identifier = head->astdata;
        current_dataytpe = n_string;

        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        cout << " = " << identifier << " *leaf* ";
        #endif

        break;
    case n_id:
        identifier = head->astdata;
        
        if(inside_funct){
            current_vec_int = get_funct_list(identifier);
            if(notfound){
                current_dataytpe = n_integer;
                intvalue = get_funct_int(identifier);
                if(notfound){
                    //TODO ERROR
                }
            } else {
                current_dataytpe = n_list_int;
            }
        } else {
            current_vec_int=get_vector_int(identifier);
            if(notfound){
                current_dataytpe = n_integer;
                intvalue = int_indefiers[identifier];
            } else {
                current_dataytpe = n_list_int;
            }
        }

        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        cout << " = " << identifier << " *leaf* ";
        #endif

        break;
    case n_list_int:
        save_id = head->astdata;
        // current_vec_int.clear();
        current_vec_int = get_vector_int(save_id);
        // cout << "INside list_int save id = " << save_id<<endl;
        // print_vector_int();
        // cout << "-----" << endl;
        // notfound=false;
        current_dataytpe = head->asttype;

        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        cout <<" *leaf* ";
        #endif

        break;
    case n_plus:
    
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
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
        //
        // current_vec_int.clear();



        if(left->asttype==n_id){
            current_vec_int=get_vector_int(left->astdata);
            if(notfound){
                #ifdef TREE
                cout << " left " << endl;
                #endif                
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
            #ifdef TREE
            cout << " left " << endl;
            #endif 
            interpret(left);
            temp = intvalue;           
        } else if(left->asttype==n_list_int){

        } else if(left->asttype==n_plus){
            #ifdef TREE
            cout << " left " << endl;
            #endif 
            interpret(left);
            temp = temp + intvalue;
            tempvec_double.insert(tempvec_double.end(), current_vec_int.begin(), current_vec_int.end());
        } else {
            #ifdef TREE
            cout << " left " << endl;
            #endif 
            interpret(left);
            temp = intvalue;
            notfound = false;
        }


        if(right->asttype==n_id){
            current_vec_int=get_vector_int(right->astdata);
            if(notfound){
                #ifdef TREE
                cout << " right " << endl;
                #endif 
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
                #ifdef TREE
                cout << " right " << endl;
                #endif 
            interpret(right);
            temp = temp + intvalue;  
            intvalue = temp;
        } else if(right->asttype==n_list_int){
           //This is for a = [1,2] + [3,4] 
        } else if(right->asttype==n_plus){
                #ifdef TREE
                cout << " right " << endl;
                #endif 
            interpret(right);
            temp = temp + intvalue;  
            intvalue = temp;
            tempvec_double.insert(tempvec_double.end(), current_vec_int.begin(), current_vec_int.end());
            current_vec_int = tempvec_double;

        } else {
                #ifdef TREE
                cout << " right " << endl;
                #endif 
            interpret(right);
            temp = temp + intvalue;
            intvalue = temp;
            notfound = false;

        }
        current_dataytpe = head->asttype;
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
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif

        temp = 0;
        left = head->p1;
        right = head->p2;
                #ifdef TREE
                cout << " left " << endl;
                #endif 
        interpret(left);
        temp = temp + intvalue;
                #ifdef TREE
                cout << " right " << endl;
                #endif 
        interpret(right);
        temp = temp - intvalue;
        intvalue = temp;
        current_dataytpe = head->asttype;
        break;
    case n_div:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        temp = 0;
        left = head->p1;
        right = head->p2;
                #ifdef TREE
                cout << " left " << endl;
                #endif 
        interpret(left);
        temp = temp + intvalue;
                #ifdef TREE
                cout << " right " << endl;
                #endif 
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
        current_dataytpe = head->asttype;
        break;
    case n_mul:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        temp = 0;
        left = head->p1;
        right = head->p2;
                #ifdef TREE
                cout << " left " << endl;
                #endif 
        interpret(left);
        temp = temp + intvalue;
                #ifdef TREE
                cout << " right " << endl;
                #endif 
        interpret(right);
        temp = temp * intvalue;
        intvalue = temp;
        current_dataytpe = head->asttype;
        break;
    case n_statements:
    case n_while:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        left = head->p1;
        right = head->p2;
                #ifdef TREE
                cout << " left " << endl;
                #endif 
        interpret(left);
                #ifdef TREE
                cout << " right " << endl;
                #endif 
        interpret(right);
        current_dataytpe = head->asttype;
        break;
    case n_if:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        // cout << head->astdata << " ";
        left = head->p1;
        right = head->p2;
                #ifdef TREE
                cout << " left " << endl;
                #endif  
        interpret(left);
        if(flag==true){
                #ifdef TREE
                cout << " right " << endl;
                #endif 
            interpret(right);
        } 
        // cout << "n_if flag value = " << flag << endl;
        current_dataytpe = head->asttype;
        break;
    case n_block_stmts:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        left = head->p1;
        right = head->p2;
                #ifdef TREE
                cout << " left " << endl;
                #endif 
        interpret(left);
                #ifdef TREE
                cout << " right " << endl;
                #endif 
        interpret(right);
        current_dataytpe = head->asttype;
        break;
    case n_statement:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        current_line = stoi(head->astdata);
        left = head->p1;
                #ifdef TREE
                cout << " down " << endl;
                #endif 
        interpret(left);
        current_dataytpe = head->asttype;
        break;
    case n_block_stmt:
    case n_simple_stmt:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        left = head->p1;
                #ifdef TREE
                cout << " down " << endl;
                #endif 
        interpret(left);
        current_dataytpe = head->asttype;
        break;
    case n_ifelse: 
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        left = head->p1;
        mid = head->p2;
        right = head->p3;
                #ifdef TREE
                cout << " left " << endl;
                #endif 
        interpret(left);
        if(flag==true){
                #ifdef TREE
                cout << " mid " << endl;
                #endif 
            interpret(mid);
        } else {
                #ifdef TREE
                cout << " right " << endl;
                #endif 
            interpret(right);
        }
        current_dataytpe = head->asttype;
        break;
    case n_booleanexp:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        left = head->p1;
        mid = head->p3;
        right = head->p2;

        //This takes into account of the order that n_booleaexp has booleanexpression, booleanexpression, boolean operator
                #ifdef TREE
                cout << " left " << endl;
                #endif 
        interpret(left);

        bool_left_type = current_dataytpe;

        //NOTE this might cause problem for if string * int or string + int
        
        if(bool_left_type==n_integer){
            bool_exp_left = intvalue;
        } else if (bool_left_type==n_string){
            bool_left_str = identifier;
        }
        
                #ifdef TREE
                cout << " right " << endl;
                #endif 
        interpret(right);
        
        bool_right_type = current_dataytpe;


        if(bool_right_type==n_integer){
            bool_exp_right = intvalue;
        } else if (bool_right_type==n_string){
            bool_right_str = identifier;
        }
        
        //This is a boolean operator
                #ifdef TREE
                cout << " mid " << endl;
                #endif 
        interpret(mid);
        flag = boolean_evaluate_int(bool_exp_left, bool_exp_right,mid->asttype); 
        //
            cout << " . current flag == " << flag;

        //
        

        //comaprison between string and int not supported
        //will add support later
        if(bool_right_type==n_integer){
            cout << "inside boolexp left = " << bool_exp_left << "right = " << bool_exp_right << endl;
            flag = boolean_evaluate_int(bool_exp_left, bool_exp_right,mid->asttype); 
        } else if (bool_right_type==n_string){
            flag = boolean_evaluate_string(bool_left_str, bool_right_str,mid->asttype);
        }
        
        current_dataytpe = head->asttype;
        break;
    case n_listindex:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        save_id = head->astdata;
        left=head->p1;

        if(left->p1==NULL){
            temp = stoi(left->astdata);
        } else {
            /*
            this is an identifier
                    *id* in "a = fe[id]"
            */
            temp_str = left->astdata;
            temp = int_indefiers[temp_str];
        }

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
        current_dataytpe = head->asttype;
        break;
    case n_assignment_list:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        left=head->p1;
        save_id = head->astdata;
                #ifdef TREE
                cout << " down " << endl;
                #endif 
        interpret(left);
        if(left->asttype==n_list_int){
            if(inside_funct){
                inject_list(save_id,current_vec_int);
            } else {
                vector_identifiers[save_id]=current_vec_int;
            }
        }
        current_dataytpe = head->asttype;
        break;
    case n_assignment_int:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        left = head->p1;
        identifier = head->astdata;
        save_id = identifier;
                #ifdef TREE
                cout << " down " << endl;
                #endif 
        interpret(left);


        if(assign_list_variable==false){
            if(inside_funct){
                inject_int(save_id,intvalue);
            } else {
                int_indefiers[save_id] = intvalue;
            }
        } else {
            if(inside_funct){
                inject_list(save_id, current_vec_int);
            } else {
                vector_identifiers[save_id] = current_vec_int;
                assign_list_variable=false;
            }

        }
        current_dataytpe = head->asttype;
        break;
    case n_prints:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        left = head->p1->p1;
        current_dataytpe = left->asttype;
        if (current_dataytpe == n_integer || current_dataytpe == n_plus || current_dataytpe == n_minus || current_dataytpe == n_mul || current_dataytpe == n_div)
        {
            #ifdef TREE
            cout << " left " << endl;
            #endif
            interpret(left);
            cout << intvalue;
        }
        else if (current_dataytpe == n_string)
        {
            #ifdef TREE
            cout << " left " << endl;
            #endif
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
            #ifdef TREE
            cout << " left " << endl;
            #endif
            interpret(left);
            cout << intvalue;
        }


        right = head->p2;
        if (right->asttype == n_integer || right->asttype == n_plus || right->asttype == n_minus || right->asttype == n_mul || right->asttype == n_div)
        {   
            cout << " " << intvalue;
                #ifdef TREE
                cout << " right " << endl;
                #endif 
            interpret(right);
        }
        else if (right->asttype == n_string)
        {   
            cout << " " << identifier;
                #ifdef TREE
                cout << " right " << endl;
                #endif 
            interpret(right);
        }
        else if (right->asttype == n_id)
        {

            cout << " ";
            if(inside_funct){
                current_vec_int = get_funct_list(right->astdata);
                if(notfound){ 
                    cout << get_funct_int(right->astdata);
                    if(firstprint==true){
                        cout << endl;
                        firstprint=false;
                    } else if(current_line!=previous_line){
                        cout<<endl;
                    } 
                    break;
                }
                print_vector_int();
            } else {
                current_vec_int=get_vector_int(right->astdata);
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
            }           
        } else if (right->asttype==n_listindex){
            cout << " ";
                #ifdef TREE
                cout << " right " << endl;
                #endif 
            interpret(right);
            cout << intvalue;
        }
        if(firstprint==true){
            cout << endl;
            firstprint=false;
        } else if(current_line!=previous_line){
            cout<<endl;
        }        
        current_dataytpe = head->asttype;
        break;
    case n_print:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        left = head->p1;

        //
        // cout << "___________";
        // print_current_parsetoken(left->asttype);
        // cout << "___________" << endl;

        //
        current_dataytpe = left->asttype;
        if (current_dataytpe == n_integer || current_dataytpe == n_plus || current_dataytpe == n_minus || current_dataytpe == n_mul || current_dataytpe == n_div)
        {
                #ifdef TREE
                cout << " down " << endl;
                #endif 
            interpret(left);
            cout << intvalue;
        }
        else if (current_dataytpe == n_string)
        {
                #ifdef TREE
                cout << " down " << endl;
                #endif 
            interpret(left);
            cout << identifier;
        }
        else if (current_dataytpe==n_id)
        {
            if(inside_funct){
                current_vec_int = get_funct_list(identifier);
                if(notfound){ 
                    cout << get_funct_int(identifier);
                    if(firstprint==true){
                        cout << endl;
                        firstprint=false;
                    } else if(current_line!=previous_line){
                        cout<<endl;
                    } 
                    break;
                }
                print_vector_int();
            } else {
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
            }           

        } else if (current_dataytpe==n_listindex){
            #ifdef TREE
            cout << " down " << endl;
            #endif 
            interpret(left);
            cout << intvalue;
        }
        if(firstprint==true){
            cout << endl;
            firstprint=false;
        } else if(current_line!=previous_line){
            cout<<endl;
        }
        current_dataytpe = head->asttype;
        break;
    case n_index_assign_data:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        left = head->p1;
        mid = head->p2;
        //right is the expression
        right = head->p3;
        
        //TODO check if right asttype ==
                #ifdef TREE
                cout << " right " << endl;
                #endif 
        interpret(right);
        temp = intvalue;

        save_id = left->astdata;
        index = stod(mid->astdata);

        // current_vec_int.clear();
        // current_vec_int = get_vector_int(save_id);
                #ifdef TREE
                cout << " left " << endl;
                #endif 
        interpret(left);


        current_vec_int.at(index) = temp;
        modify_vector_int(save_id, current_vec_int);
        current_dataytpe = head->asttype;
        break;
    case n_index_assign_id:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        current_vec_int=get_vector_int(head->astdata);
        current_dataytpe = head->asttype;
        break;
    case n_funct_definiton:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        /*
        Do nothing bc parser has already handled it 
        on astptr funct()

        The parser has saved the head of the function
        pointer in a map with its name as the key
        */ 
        current_dataytpe = head->asttype;
        break;
    case n_fcall:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        save_id = head->astdata;
        left = head->p1;
        right = head->p2;
        if(left==NULL){
            /*This is an function without argument*/

            //getting funciton parse tree
            mid = get_funct_head(save_id);
            // printParserTree(mid);

            if(mid->asttype!=n_funct){
                //TODO error. takes 0 positional arguments but 1 was given
                //EXIT here
            }
                #ifdef TREE
                cout << " down " << endl;
                #endif 
            interpret(mid);

        }
        current_dataytpe = head->asttype;
        break;
    case n_funct:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif 

        mid = head->p1;
        // printParserTree(mid);

                #ifdef TREE
                cout << " down " << endl;
                #endif 
        inside_funct=true;
        reset_env();
        interpret(mid);
        inside_funct=false;
        break;  
    case n_error: case n_def:
    case n_empty: 
    case n_index_assign_index:
    case n_uminus: case n_listindex_data:
        #ifdef TREE
        cout << "token type = ";
        print_current_parsetoken(head->asttype);
        #endif
        break;
    }

    
}

#endif