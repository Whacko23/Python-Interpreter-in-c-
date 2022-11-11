
#ifndef PARSER_CPP
#define PARSER_CPP

#include "parser.h"

#define DEEBUG


int grammar_tracker = 1;


vector<double> int_vector;
vector<string> string_vector;

astptr newnode(nodetype n, string s, astptr first, astptr second, astptr third)
{
    astnode *mynode = new astnode();

    mynode->asttype = n;
    mynode->astdata = s;
    mynode->p1 = first;
    mynode->p2 = second;
    mynode->p3 = third;
    return mynode;
}

/*
<statements> ::= <statement> | <statements>
*/
astptr statements()
{
    #ifdef DEEBUG
    cout << grammar_tracker << " ---inside  stmts ---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst = statement();
    int i=1;
    while (true)
    {
        if(i==10)break;
        i++;
        cout << "currenttoken";
        print_current_lextoken(currenttoken);
        cout << endl;
        if (currenttoken == eofsym){
            #ifdef DEEBUG
            cout << grammar_tracker << " ---exit  stmts loop---" << endl;
            grammar_tracker++;
            #endif

            break;
        }
        if (currenttoken == newlinesym)
        {
            linenumber++;
            pfirst = newnode(n_newline, "", pfirst, NULL, NULL);
            currenttoken = cleanLexer();
        }

        pfirst = newnode(n_statements, "", pfirst, statement(), NULL);

        #ifdef DEEBUG
        cout << grammar_tracker << " ---inside  stmts loop---" << endl;
        grammar_tracker++;
        #endif
    }

    return pfirst;
};

/*
statement: compound_stmt  | simple_stmts
*/
astptr statement()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  stmt---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst = simple_stmt();
    if (pfirst->asttype == n_empty)
    {
        pfirst = compound_stmt();
    }
    return newnode(n_statement, to_string(linenumber), pfirst, NULL, NULL);
}

/*
<statement> : := <assignment> | <printstatement> | <returnstatement> | empty
*/
astptr simple_stmt()
{
    // TODO Log("inside statement function: Parser")
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  simple stmts---" << endl;
    grammar_tracker++;
    #endif
    astptr pfirst = NULL;
    if (currenttoken == commentsym)
    {
        currenttoken = cleanLexer();

        while (true)
        {   
            #ifdef DEEBUG
            cout << grammar_tracker<< " ---inside  simple stmts loop---" << endl;
            grammar_tracker++;
            #endif

            if (currenttoken == newlinesym)
            {
                linenumber++;
                pfirst = newnode(n_newline, "", pfirst, NULL, NULL);
                currenttoken = cleanLexer();

                #ifdef DEEBUG
                cout << grammar_tracker << " ---exit simple stmts loop by newline ----" << endl;
                grammar_tracker++;
                #endif

                break;
            }
            else if (currenttoken == eofsym)
            {
                #ifdef DEEBUG
                cout << grammar_tracker << " ---exit simple stmts loop by eof ----" << endl;
                grammar_tracker++;
                #endif                  
                break;
            }
            currenttoken = cleanLexer();
        }
    }
    if (currenttoken == identifiersym)
        return assignment();
    else if (currenttoken == printsym)
        return printstatement();
    else if (currenttoken == returnsym)
        return returnstatement();
    else {
        pfirst = newnode(n_empty, "", NULL, NULL, NULL);

    }
    return pfirst;
}

/*
compound_stmt:
    | function_def
    | if_stmt
    | while_stmt
*/
astptr compound_stmt()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  compound stmts ---" << endl;
    grammar_tracker++;
    #endif

    if (currenttoken == ifsym)
        return ifstatement();
    else if (currenttoken == defsym)
        return funct();
    else if (currenttoken == whilesym)
        return whilestatement();
    else
        return newnode(n_empty, "", NULL, NULL, NULL);
}

/*
<while> -> "while" <binary expression> ":" <block statement> ["else" <block statement>]
*/
astptr whilestatement()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  while stmt ---" << endl;
    grammar_tracker++;
    #endif

    astptr pbexp = NULL;
    astptr pwhile = NULL;
    // int currentline;

    if (currenttoken != whilesym)
    {
        // TODO Error Expected while
    }
    else
    {
        currenttoken = cleanLexer();
        pbexp = booleanexpression();
        if (currenttoken == colonsym)
        {
            // currentline = linenumber;
            currenttoken = lexer();
            pwhile = newnode(n_while, "while", pbexp, blockstatement(), NULL);
        }
        else
        {
            // TODO Error expected ":"
        }
    }
    return pwhile;
};

/*
block statement: block <statement>
*/
astptr blockstatement()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  block stmt ---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst;
    int current_indent = 0;

    if (currenttoken != whitespacesym)
    {

        return newnode(n_empty, "", NULL, NULL, NULL);
    }

    while (true)
    {
        #ifdef DEEBUG
        cout << grammar_tracker<< " ---inside  block stmt loop---" << endl;
        grammar_tracker++;
        #endif

        if (currenttoken != whitespacesym){
            #ifdef DEEBUG
            cout << grammar_tracker<< " ---exit  block stmt loop not whitespace---" << endl;
            grammar_tracker++;
            #endif

            break;
        }
        currenttoken = lexer();
        current_indent++;
    }

    pfirst = statement();

    return newnode(n_block_stmt, to_string(current_indent), pfirst, NULL, NULL);
};

/*
<blockstatements> ::= <block statement> | <block statements>
*/
astptr blockstatements()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  block stmts ---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst = blockstatement();

    if (pfirst->asttype == n_empty)
        return newnode(n_empty, "", NULL, NULL, NULL);

    string firstdata = pfirst->astdata;
    string seconddata = "";
    // int findent = stoi(firstdata);
    // int sindent = 0;
    astptr psecond;
    
    while (true)
    {
        #ifdef DEEBUG
        cout << grammar_tracker<< " ---inside  block stmts loop---" << endl;
        cout << currenttoken << " cuttnet " << endl;
        grammar_tracker++;
        #endif
        
        if (currenttoken == eofsym){
                #ifdef DEEBUG
                cout << grammar_tracker << " ---exit block stmt loop by eof ----" << endl;
                grammar_tracker++;
                #endif
            break;
        }
        if (currenttoken == elsesym){
                #ifdef DEEBUG
                cout << grammar_tracker << " ---exit block stmt loop by else ----" << endl;
                grammar_tracker++;
                #endif
            break;
        }
        if (currenttoken == newlinesym)
        {
            linenumber++;
            pfirst = newnode(n_newline, "", pfirst, NULL, NULL);
            currenttoken = lexer();
            if (currenttoken != whitespacesym){

                #ifdef DEEBUG
                cout << grammar_tracker << " ---exit block stmts loop by newline & not whitespace----" << endl;
                grammar_tracker++;
                #endif

                break;
            }
            psecond = blockstatement();

            seconddata = psecond->astdata;
            if (psecond->asttype == n_block_stmt || psecond->asttype == n_block_stmts)
            {
                // sindent = stoi(seconddata);
            }
            pfirst = newnode(n_block_stmts, seconddata, pfirst, psecond, NULL);
        }
    }
    return pfirst;
};

astptr returnstatement()
{
    return newnode(n_empty, "", NULL, NULL, NULL);
};

// NOTE the previous function (assignment) has already checked for [] brackets
astptr list()
{
    astptr pfirst=NULL;
    string tempid;
    if (currenttoken == opensquaresym)
    {
        currenttoken = cleanLexer();
        if (currenttoken == intsym)
        {
            /*
            int tempvalue = intvalue;
            currenttoken = cleanLexer();
            if(currenttoken==closesquaresym){
                pfirst = newnode(n_listindex,to_string(tempvalue), NULL, NULL, NULL);
                currenttoken = cleanLexer();
                return pfirst;
            }
            */

            while (true)
            {
                if(currenttoken!=intsym){
                    //TODO error type mismatch
                }
                int_vector.push_back(intvalue);
                currenttoken = cleanLexer();

                if (currenttoken == eofsym)
                {
                    #ifdef DEEBUG
                    cout << grammar_tracker << " ---exit list  loop by eof ----" << endl;
                    grammar_tracker++;
                    #endif

                    break;
                }
                if (currenttoken == newlinesym)
                {
                    #ifdef DEEBUG
                    cout << grammar_tracker << " ---exit list  loop by newline ----" << endl;
                    grammar_tracker++;
                    #endif
                    //TODO error
                    linenumber++;
                    pfirst = newnode(n_newline, "", pfirst, NULL, NULL);
                    currenttoken = cleanLexer();
                    break;
                }

                if (currenttoken == closesquaresym)
                {
                    #ifdef DEEBUG
                    cout << grammar_tracker << " ---exit list  loop by closebracker ----" << endl;
                    grammar_tracker++;
                    #endif
                    currenttoken = cleanLexer();
                    break;
                }
                if (currenttoken == commasym){
                    currenttoken = cleanLexer();
                } else {
                    cout << "Error in list function checking for comma or closed bracket" << endl;
                    // Display error
                    break;
                }
            }//: Exit while
            tempid = add_vector(int_vector);
            pfirst = newnode(n_list_int,tempid, NULL, NULL, NULL);
        }
        else if (currenttoken == doublequotesym || currenttoken == singlequotesym)
        {
        }
    }
    return pfirst;
};

/*
<function> -> identifier {()| (<argumentlist>))} : <functionbody>
*/
astptr funct()
{
    return newnode(n_empty, "", NULL, NULL, NULL);
};

astptr functionbody()
{
    return newnode(n_empty, "", NULL, NULL, NULL);
};

astptr argumentlist()
{
    return newnode(n_empty, "", NULL, NULL, NULL);
};


/*
<expr> -> [+ | -]<term> {(+ | -) <term>}
*/
astptr expression()
{

    // TODO Log("inside expression function: Parser")
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  expression---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst=NULL; /* first pointer in the expr chain */
    astptr term2=NULL;
    int startingtoken;
    string tokendata;
    nodetype ntype;

    // cout << "Inside expression" << endl;

    startingtoken = plussym;
    if ((currenttoken == plussym) || (currenttoken == minussym))
    {
        startingtoken = currenttoken;
        currenttoken = cleanLexer();
    }

    pfirst = term();

    if (startingtoken == minussym)
        pfirst = newnode(n_uminus, "-", pfirst, NULL, NULL);
    while ((currenttoken == plussym) || (currenttoken == minussym))
    {
        #ifdef DEEBUG
        cout << grammar_tracker<< " ---inside  expression loop ---" << endl;
        grammar_tracker++;
        #endif

        if (currenttoken == plussym)
        {
            ntype = n_plus;
            tokendata = "+";
        }
        else
        {
            ntype = n_minus;
            tokendata = "-";
        };
        currenttoken = cleanLexer();
        term2 = term();
        pfirst = newnode(ntype, tokendata, pfirst, term2, NULL);
    }

    return pfirst;
}

/* term
<term> -> <factor> {(* | /) <factor>)
*/
astptr term()
{

    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  term---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst, factor2;
    nodetype ntype;
    string tokendata;
    pfirst = factor();

    // cout << "Inside term" << endl;

    while ((currenttoken == multiplysym) || (currenttoken == dividesym))
    {
        #ifdef DEEBUG
        cout << grammar_tracker<< " ---inside  term loop---" << endl;
        grammar_tracker++;
        #endif

        if (currenttoken == multiplysym)
        {
            ntype = n_mul;
            tokendata = "*";
        }
        else
        {
            ntype = n_div;
            tokendata = "/";
        };
        currenttoken = cleanLexer();
        factor2 = factor();
        pfirst = newnode(ntype, tokendata, pfirst, factor2, NULL);
    }

    return pfirst;
}

/* factor
<factor> -> id | arrayindex | integer | string | ( <expr> )
*/
astptr factor()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  factor ---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst=NULL;
    string temp;

    // cout << "Inside factor" << endl;
    if (currenttoken == identifiersym)
    {
        temp = identifier;
        currenttoken = lexer();
        if(currenttoken==opensquaresym){
            currenttoken = cleanLexer();
            if(currenttoken!=intsym){
                //TODO TypeError: list indices must be integers or slices, not str
            }else{
                pfirst = newnode(n_listindex_data,to_string(intvalue),NULL,NULL,NULL);
                pfirst = newnode(n_listindex,temp, pfirst,NULL,NULL);
                currenttoken = cleanLexer();
                if(currenttoken!=closesquaresym){
                    //TODO SyntaxError: invalid syntax missing ']'
                } else {
                    currenttoken=cleanLexer();
                }
            }
        } else {
            //No need to call for new token since it has already been called before if statement
            pfirst = newnode(n_id, identifier, NULL, NULL, NULL);
        }
    }
    else if (currenttoken == intsym)
    {
        pfirst = newnode(n_integer, to_string(intvalue), NULL, NULL, NULL);
        currenttoken = cleanLexer();
    }
    else if (currenttoken == doublequotesym || currenttoken == singlequotesym)
    {
        pfirst = newnode(n_string, identifier, NULL, NULL, NULL);
        currenttoken = cleanLexer();
    }
    else
    {
        if (currenttoken == openbracketsym)
        {
            currenttoken = cleanLexer();
            pfirst = expression();
            if (currenttoken == closebracketsym)
            {
                currenttoken = cleanLexer();
            }
            else
            {
                // TODO - Missing ')'
            }
        }
        else
        {
            // TODO - error not an id, integer or (expression)
        }
    }
    return pfirst;
}


/* if statement
<ifstmt> -> if <boolexpr> colon <block statement> [else <statement>]
*/
astptr ifstatement()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  if stmt ---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst = NULL, bexp = NULL, elsee = NULL;
    // int currentindent = 0;
    if (currenttoken != ifsym)
    {
        // TODO Errror not an if ststaement
    }
    else
    {
        currenttoken = cleanLexer();
        bexp = booleanexpression();
        if (currenttoken != colonsym)
        {
            // TODO Error expected ':' after if
        }
        else
        {
            currenttoken = lexer();
            if (currenttoken == newlinesym){
                linenumber++;
                pfirst = newnode(n_newline, "", pfirst, NULL, NULL);
                currenttoken = lexer();
            }
            pfirst = blockstatements();

            if (currenttoken == elsesym)
            {
                currenttoken = cleanLexer();
                if (currenttoken == colonsym)
                {
                    currenttoken = lexer();
                    if (currenttoken == newlinesym){
                        linenumber++;
                        pfirst = newnode(n_newline, "", pfirst, NULL, NULL);
                        currenttoken = lexer();
                    }
                    elsee = blockstatements();
                    pfirst = newnode(n_ifelse, "", bexp, pfirst, elsee);
                }
                else
                {
                    // TODO Missing colon
                }
            }
            else
            {
                pfirst = newnode(n_if, "", bexp, pfirst, NULL);
            }
        }
    }
    return pfirst;
}
/* assign statement
<assignment> -> identifier = {<experssion> | <list>}
*/
astptr assignment()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  assignment ---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst=NULL, lis=NULL, exp=NULL,index_id=NULL, index_num=NULL;
    string id;
    if (currenttoken != identifiersym)
    {
        // TODO Expected identifier
    }
    else
    {
        id = identifier;
        currenttoken = cleanLexer();
        if(currenttoken==opensquaresym){
            currenttoken = cleanLexer();
            if(currenttoken!=intsym){
                //TODO TypeError: list indices must be integers or slices, not str
            }else{
                index_num = newnode(n_index_assign_index,to_string(intvalue),NULL,NULL,NULL);
                index_id = newnode(n_index_assign_id,id, NULL,NULL,NULL);
                currenttoken = cleanLexer();
                if(currenttoken!=closesquaresym){
                    //TODO SyntaxError: invalid syntax missing ']'
                } else {
                    currenttoken=cleanLexer();
                }
            }

            if (currenttoken != assignsym) {
                // TODO Expected assign symbol
            } else {
                currenttoken = cleanLexer();
                exp = expression();
                pfirst = newnode(n_index_assign_data, "", index_id, index_num , exp);
            }
        }
        /*
        id = identifier;
        currenttoken = cleanLexer();
        */
        if (currenttoken != assignsym)
        {
            // TODO Expected assign symbol
        }
        else
        {
            currenttoken = cleanLexer();
            if (currenttoken == opensquaresym)
            {
                //TODO check for list indexes as well
                lis = list();
                pfirst = newnode(n_assignment_list, id, lis, NULL, NULL);
                if (currenttoken != closesquaresym)
                {
                    // TODO Expected ']'
                } else{
                    currenttoken = cleanLexer();
                }
            }
            else
            {

                exp = expression();

                pfirst = newnode(n_assignment_int, id, exp, NULL, NULL);
            }
        }
    }
    return pfirst;
};

/* print statement
<print> -> print({<expression> | <list>) //TODO List
*/
astptr printstatement()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  print stmt ---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst=NULL, expr=NULL;
    if (currenttoken != printsym)
    {
        // TODO Expected print
    }
    else
    {
        currenttoken = cleanLexer();
        if (currenttoken != openbracketsym)
        {
            // TODO Expected '('
        }
        else
        {
            currenttoken = cleanLexer();
            expr = expression();
            if (currenttoken == doublequotesym || currenttoken == singlequotesym)
                currenttoken = cleanLexer();
            pfirst = newnode(n_print, "print", expr, NULL, NULL);

            while (currenttoken == commasym)
            {

                #ifdef DEEBUG
                cout << " ---inside  print stmt loop ---" << endl;
                #endif


                currenttoken = cleanLexer();
                expr = expression();
                if (currenttoken == doublequotesym || currenttoken == singlequotesym)
                    currenttoken = cleanLexer();
                pfirst = newnode(n_prints, "", pfirst, expr, NULL);
            }

            if (currenttoken != closebracketsym)
            {
                // TODO Expected ')'
            }
            else
            {
                currenttoken = cleanLexer();
            }
        }
    }
    return pfirst;
};

/* boolean expression
<boolean expression> -> <expresion> <boolean operation> <expression>
*/
astptr booleanexpression()
{
    bool brackettracker=false;
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  bool exp ---" << endl;
    grammar_tracker++;
    #endif

    astptr exp1=NULL, exp2=NULL, bexp=NULL;
    if(currenttoken==openbracketsym){
        brackettracker=true;
        currenttoken=cleanLexer();
    } 
    exp1 = expression();
    exp2 = booleanoperation();
    bexp = expression();
    if(brackettracker){
        if(currenttoken==closebracketsym){
            currenttoken=cleanLexer();
        } else{
            //TODO "missing )"
        }
    }
    return newnode(n_booleanexp, "", exp1, bexp, exp2);
};

/* boolean operation
<boolean expression> -> { == | != | >= | <= | > | <}
*/

astptr booleanoperation()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  bool op ---" << endl;
    grammar_tracker++;
    #endif

    switch (currenttoken)
    {
    case equalsym:
        currenttoken = cleanLexer();
        return newnode(n_eq, "==", NULL, NULL, NULL);
        break;
    case notequalsym:
        currenttoken = cleanLexer();
        return newnode(n_ne, "!=", NULL, NULL, NULL);
        break;
    case greaterorequalsym:
        currenttoken = cleanLexer();
        return newnode(n_ge, ">=", NULL, NULL, NULL);
        break;
    case greaterthansym:
        currenttoken = cleanLexer();
        return newnode(n_gt, ">", NULL, NULL, NULL);
        break;
    case lessthansym:
        currenttoken = cleanLexer();
        return newnode(n_lt, "<", NULL, NULL, NULL);
        break;
    case lessorequalsym:
        currenttoken = cleanLexer();
        return newnode(n_le, "<=", NULL, NULL, NULL);
        break;
    default:
        return newnode(n_error, " ", NULL, NULL, NULL);
        break;
    }
}

astptr parser()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  parser() ---" << endl;
    grammar_tracker++;
    #endif

    return statements();
};

void printParserTree(astptr head)
{
    string current;
    astptr left, right, mid;

    switch (head->asttype)
    {
    case n_id:
    case n_integer:
    case n_string:
    case n_eq:
    case n_ne:
    case n_gt:
    case n_lt:
    case n_le:
    case n_ge:
    case n_list_int:
    case n_listindex_data:
    case n_index_assign_index:
    case n_index_assign_id:
    case n_error:
    case n_empty:
    case n_def:
        cout << head->astdata << " ";
        cout << "*leaf* " << endl;
        break;
    case n_plus:
    case n_minus:
    case n_div:
    case n_mul:
    case n_statements:
    case n_while:
    case n_prints:
    case n_if:
        cout << head->astdata << " ";
        left = head->p1;
        right = head->p2;
        cout << "left " << endl;
        printParserTree(left);
        cout << "right " << endl;
        printParserTree(right);
        break;
    case n_block_stmts:
        left = head->p1;
        right = head->p2;
        cout << "left " << endl;
        printParserTree(left);
        cout << "right " << endl;
        printParserTree(right);
        break;
    case n_statement:
    case n_block_stmt:
    case n_simple_stmt:
    case n_newline:
        left = head->p1;
        cout << "down " << endl;
        printParserTree(left);
        break;
    case n_ifelse: case n_booleanexp:
    case n_index_assign_data:
        left = head->p1;
        mid = head->p2;
        right = head->p3;
        cout << "left " << endl;
        printParserTree(left);
        cout << "mid " << endl;
        printParserTree(mid);
        cout << "right " << endl;
        printParserTree(right);
        break;
    case n_assignment_list:
    case n_assignment_int:
        cout << head->astdata << " = ";
        left = head->p1;
        cout << "down " << endl;
        printParserTree(left);
        break;
    case n_print:
    case n_listindex:
    case n_uminus:
        left = head->p1;
        cout << head->astdata << " ";
        cout << "down" << endl;
        printParserTree(left);
        break;
    }
}

void freeMemory(astptr head)
{
    astptr left, right, mid;

    switch (head->asttype)
    {
    case n_def:
    case n_id:
    case n_integer:
    case n_empty:
    case n_error:
    case n_string:
    case n_eq:
    case n_ne:
    case n_gt:
    case n_lt:
    case n_le:
    case n_ge:
    case n_list_int:
    case n_listindex_data:
    case n_index_assign_index:
    case n_index_assign_id:
        delete head;
        break;
    case n_plus:
    case n_minus:
    case n_div:
    case n_mul:
    case n_statements:
    case n_while:
    case n_prints:
    case n_block_stmts:
    case n_if:
        left = head->p1;
        right = head->p2;
        delete head;
        freeMemory(left);
        freeMemory(right);
        break;
    case n_statement:
    case n_block_stmt:
    case n_simple_stmt:
    case n_newline:
    case n_listindex:
    case n_assignment_list:
    case n_assignment_int:
    case n_print:
    case n_uminus:
        left = head->p1;
        delete head;
        freeMemory(left);
        break;
    case n_ifelse: case n_booleanexp:
    case n_index_assign_data:
        left = head->p1;
        mid = head->p2;
        right = head->p3;
        delete head;
        freeMemory(left);
        freeMemory(mid);
        freeMemory(right);
        break;
    }
}

void print_current_lextoken(lextokens t){
                switch(t){
                    case intsym: cout << "Integer token = " << intvalue << endl; break;
                    case whitespacesym: cout << "Whitespace token " << endl; break;
                    case printsym: cout << "Print token " << endl; break;
                    case blocksym: cout << "Block token "  << endl;
                    case identifiersym: cout << "Identifier token = " << identifier  << endl; break;
                    case whilesym: cout << "While token "  << endl; break;
                    case eofsym: cout << "EOF token "  << endl; break;
                    case ifsym: cout << "IF token "  << endl; break;
                    case elsesym: cout << "Else token "  << endl; break;
                    case elseifsym: cout << "Elseif token "  << endl; break;
                    case defsym: cout << "Def token "  << endl; break;
                    case returnsym: cout << "REturn token "  << endl; break;
                    case semicolonsym: cout << "semicolon token "  << endl; break;
                    case commasym: cout << "comma token "  << endl; break;
                    case assignsym: cout << "assign token "  << endl; break;
                    case errorsym: cout << "Error "  << identifier << " is unrecognized on line " << linenumber << " at character " << tracker << endl; break;
                    case dividesym: cout << "divide token "  << endl; break;
                    case openbracketsym: cout << "OpenBracker token "  << endl; break;
                    case closebracketsym: cout << "CloseBracker token "  << endl; break;
                    case plussym: cout << "Plus token "  << endl; break;
                    case minussym: cout << "Minus token "  << endl; break;
                    case multiplysym: cout << "multiply token "  << endl; break;
                    case equalsym: cout << "Euqal token "  << endl; break;
                    case leftanklesym: cout << "Left ankle token "  << endl; break;
                    case rightanklesym: cout << "Right ankle token "  << endl; break;
                    case colonsym: cout << "Colon token "  << endl; break;
                    case commentsym: cout << "Comment token "  << endl; break;
                    case singlequotesym: cout << "Single quote token = " << identifier << endl; break;
                    case doublequotesym: cout << "Double quote token = " << identifier  << endl; break;
                    case opensquaresym: cout << "Open sq bracket token "  << endl; break;
                    case closesquaresym: cout << "Close sq bracket token "  << endl; break;
                    case shebangsym: cout << "Shebang token "  << endl; break;
                    case notequalsym: cout << "Not equal token "  << endl; break;
                    case greaterorequalsym: cout << "Greater than or equal token "  << endl; break;
                    case lessorequalsym: cout << "Less than or equal token "  << endl; break;
                    case lessthansym: cout << "Less than token "  << endl; break;
                    case greaterthansym: cout << "Greater than token "  << endl; break;
                    case newlinesym: cout << "  New line "  << endl; break;
                }
};

void print_current_parsetoken(nodetype n){
    switch (n)
    {
        case n_statements:
            cout << "n_statements" << endl;
             break;
        case n_statement:
            cout << "n_statement" << endl;
             break;
        case n_assignment_list:
            cout << "n_assignment_list" << endl;
             break;
        case n_assignment_int:
            cout << "n_assignment_int" << endl;
             break;
        case n_simple_stmt:
            cout << "n_simple_stmt" << endl;
             break;
        case n_booleanexp:
            cout << "n_booleanexp" << endl;
             break;
        case n_print:
            cout << "n_print" << endl;
             break;
        case n_prints:
            cout << "n_prints" << endl;
             break;
        case n_newline:
            cout << "n_newline" << endl;
             break;
        case n_uminus:
            cout << "n_uminus" << endl;
             break;
        case n_plus:
            cout << "n_plus" << endl;
             break;
        case n_minus:
            cout << "n_minus" << endl;
             break;
        case n_mul:
            cout << "n_mul" << endl;
             break;
        case n_div:
            cout << "n_div" << endl;
             break;
        case n_eq:
            cout << "n_eq" << endl;
             break;
        case n_ne:
            cout << "n_ne" << endl;
             break;
        case n_lt:
            cout << "n_lt" << endl;
             break;
        case n_le:
            cout << "n_le" << endl;
             break;
        case n_gt:
            cout << "n_gt" << endl;
             break;
        case n_ge:
            cout << "n_ge" << endl;
             break;
        case n_integer:
            cout << "n_integer" << endl;
             break;
        case n_string:
            cout << "n_string" << endl;
             break;
        case n_list_int:
            cout << "n_list_int" << endl;
             break;
        case n_listindex:
            cout << "n_listindex" << endl;
             break;
        case n_id:
            cout << "n_id" << endl;
             break;
        case n_while:
            cout << "n_while" << endl;
             break;
        case n_if:
            cout << "n_if" << endl;
             break;
        case n_ifelse:
            cout << "n_ifelse" << endl;
             break;
        case n_error:
            cout << "n_error" << endl;
             break;
        case n_empty:
            cout << "n_empty" << endl;
             break;
        case n_def:
            cout << "n_def" << endl;
             break;
        case n_block_stmt:
            cout << "n_block_stmt" << endl;
             break;
        case n_block_stmts:
            cout << "n_block_stmts" << endl;
             break;
    default:
        break;
    }
};


/*_________Interpreter______*/

int vector_index = 0;
map<string, double> int_indefiers;
map<string, string> string_identifiers;
map<string, vector<double>> vector_identifiers;
bool notfound = false;
vector<double> current_vec_int;
vector<string> current_vec_str;

string add_vector(vector<double> v){
    vector_index++;
    vector_identifiers.insert({to_string(vector_index),v});
    return to_string(vector_index);
}

vector<double> get_vector_int(string s){
    map<string, vector<double>>::iterator search = vector_identifiers.find(s);
    vector<double> v;
    if(search==vector_identifiers.end()){
        //TODO not found
        notfound=true;
    } else {
        v = search->second;
    }

    return v;
}

void print_vector_int(){
    cout << "[";
    for(int i=0; i<current_vec_int.size(); i++){
        cout << current_vec_int[i];
        if(i!=current_vec_int.size()-1){
            cout << ",";
        }
        else{
            cout << "]";
        }
    }
};
void print_vector_int(vector<double> v){
    cout << "[";
    for(auto itr : v)
        cout << itr << " ";
};
#endif