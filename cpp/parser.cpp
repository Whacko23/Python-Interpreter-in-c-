
#ifndef PARSER_CPP
#define PARSER_CPP

#include "parser.h"
#include "lexer.h"
#include "log.h"
#include <vector>
#include <string>

#define DEEBUG


int grammar_tracker = 1;


vector<int> int_vector;
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
    while (true)
    {

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
    astptr pfirst;
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
    astptr pfirst;
    if (currenttoken == opensquaresym)
    {
        currenttoken = cleanLexer();
        if (currenttoken == intsym)
        {
            while (true)
            {

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
                    linenumber++;
                    pfirst = newnode(n_newline, "", pfirst, NULL, NULL);
                    currenttoken = cleanLexer();
                    break;
                }
                int_vector.push_back(intvalue);
                currenttoken = cleanLexer();

                if (currenttoken == closesquaresym)
                {
                    currenttoken = cleanLexer();
                    break;
                }
                if (currenttoken != commasym || currenttoken != closesquaresym)
                {
                    cout << "Error in list function checking for comma or closed bracket" << endl;
                    // Display error
                    break;
                }
                currenttoken = cleanLexer();
            }
        }
        else if (currenttoken == doublequotesym || currenttoken == singlequotesym)
        {
        }
    }
    return newnode(n_list, "", NULL, NULL, NULL);
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

    astptr pfirst; /* first pointer in the expr chain */
    astptr term2;
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
<factor> -> id | integer | string | ( <expr> )
*/
astptr factor()
{
    #ifdef DEEBUG
    cout << grammar_tracker<< " ---inside  factor ---" << endl;
    grammar_tracker++;
    #endif

    astptr pfirst;

    // cout << "Inside factor" << endl;
    if (currenttoken == identifiersym)
    {
        pfirst = newnode(n_id, identifier, NULL, NULL, NULL);
        currenttoken = cleanLexer();
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
        if (currenttoken == opensquaresym)
        {
            currenttoken = cleanLexer();
            pfirst = expression();
            if (currenttoken == closesquaresym)
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

    astptr pfirst, lis, exp;
    string id;
    if (currenttoken != identifiersym)
    {
        // TODO Expected identifier
    }
    else
    {
        id = identifier;
        currenttoken = cleanLexer();
        if (currenttoken != assignsym)
        {
            // TODO Expected assign symbol
        }
        else
        {
            currenttoken = cleanLexer();
            if (currenttoken == opensquaresym)
            {
                currenttoken = cleanLexer();
                lis = list();
                pfirst = newnode(n_assignment_list, identifier, lis, NULL, NULL);
                if (currenttoken != closesquaresym)
                {
                    // TODO Expected ']'
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

    astptr pfirst, expr;
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

    astptr exp1, exp2, bexp;
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
        left = head->p1;
        delete head;
        freeMemory(left);
        break;
    case n_ifelse: case n_booleanexp:
        left = head->p1;
        mid = head->p2;
        right = head->p3;
        delete head;
        freeMemory(left);
        freeMemory(mid);
        freeMemory(right);
        break;
    case n_assignment_list:
    case n_assignment_int:
        left = head->p1;
        delete head;
        freeMemory(left);
        break;
    case n_print:
        left = head->p1;
        delete head;
        freeMemory(left);
        break;
    }
}
#endif