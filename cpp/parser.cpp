
#ifndef PARSER_CPP
#define PARSER_CPP

#include "parser.h"
#include "lexer.h"
#include "log.h"

astptr newnode(nodetype n, string s, astptr first, astptr second, astptr third){
    astnode* mynode = new astnode();
   
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
astptr statements(){
    astptr pfirst = statement();
    while(true){
        if(currenttoken == eofsym)break;
        if(currenttoken == newlinesym){
            currenttoken = cleanLexer();
            pfirst = newnode(n_statements, "", pfirst, statement(), NULL);
        }
    }
    
    return pfirst;
};

/*
statement: compound_stmt  | simple_stmts 
*/
astptr statement(){
    astptr pfirst = simple_stmt();
    if (pfirst->asttype == n_empty){
        pfirst = compound_stmt();
    }
    return newnode(n_statement, "", pfirst , NULL, NULL);
}


/*
<statement> : := <assignment> | <printstatement> | <returnstatement> | empty
*/
astptr simple_stmt()
{
    //TODO Log("inside statement function: Parser")
    if (currenttoken == commentsym){
        currenttoken = cleanLexer();
        
        while(true){
            if(currenttoken == newlinesym){
                currenttoken = cleanLexer();
                break;
            } else if(currenttoken == eofsym){
                break;
            }
            currenttoken = cleanLexer(); 
        }  
    }
    if (currenttoken==identifiersym) return assignment();
    else if (currenttoken==printsym) return printstatement();
    else if (currenttoken==returnsym) return returnstatement();
    else return newnode(n_empty, "", NULL, NULL, NULL);

}

/*
compound_stmt:
    | function_def
    | if_stmt
    | while_stmt
*/
astptr compound_stmt(){
    if (currenttoken==ifsym) return ifstatement();
    else if (currenttoken == defsym) return funct();
    else if (currenttoken == whilesym) return  whilestatement();
    else return newnode(n_empty, "", NULL, NULL, NULL);
}

/*
<while> -> "while" <binary expression> ":" <block statement> ["else" <block statement>]
*/
astptr whilestatement(){
    astptr pbexp = NULL;
    astptr pwhile = NULL;
    int currentline;

    if (currenttoken != whilesym){
        //TODO Error Expected while
    } else {
        currenttoken = cleanLexer();
        pbexp = booleanexpression();
        if (currenttoken == colonsym){
            currentline = linenumber;
            currenttoken = lexer();
            pwhile = newnode(n_while, "while", pbexp, blockstatement(), NULL);
        } else {
            //TODO Error expected ":"
        }    
    }
    return pwhile;
};

/*
block statement:
    | NEWLINE INDENT statements DEDENT 
    | simple_stmts

*/
/*
astptr blockstatement(){
    astptr pfirst;
    int current_indent;
    if (currenttoken == newlinesym){
        currenttoken = cleanLexer();
        if(currenttoken == blocksym){
            current_indent = 2;
            currenttoken = lexer();
            while(currenttoken == whitespacesym || currenttoken == blocksym){
                if(currenttoken == whitespacesym) current_indent ++; else current_indent += 2;
                currenttoken = lexer();
            }
            pfirst = newnode(n_block_stmt, to_string(current_indent), statements(), NULL, NULL);
        } else {
            //TODO IndentationError: expected an indented block
        }
    } else {
        pfirst = newnode(n_simple_stmt, "", simple_stmt(), NULL,NULL);
        return pfirst;
    }

};
*/

/*
block statement: block <statement>

*/
astptr blockstatement(){
    astptr pfirst;
    int current_indent = 0;
    while (true){
        currenttoken = lexer();
       if(currenttoken!=whitespacesym) break;
       current_indent++;
    }
    if(current_indent==0) return newnode(n_error,"No block",NULL,NULL,NULL);
    pfirst = statement();
    return newnode(n_block_stmt,to_string(current_indent), pfirst, NULL, NULL);
};

/*
<blockstatements> ::= <block statement> | <block statements>
*/
astptr blockstatements(){
    astptr pfirst = blockstatement();
    astptr psecond;
    int i = 0;
    cout << "Printed " << currenttoken << endl;
    while(true){
        if(currenttoken == eofsym)break;
        if(currenttoken == newlinesym){
            currenttoken = lexer();
            psecond = blockstatement();
            pfirst = newnode(n_block_stmts, "", pfirst, psecond, NULL);
        }
    }
    
    return pfirst;
};


astptr returnstatement(){
    return newnode(n_empty, "", NULL, NULL, NULL);
};

//NOTE the previous function (assignment) has already checked for [] brackets
astptr list(){
    return newnode(n_empty, "", NULL, NULL, NULL);

};


/*
<function> -> identifier {()| (<argumentlist>))} : <functionbody>
*/
astptr funct(){
    return newnode(n_empty, "", NULL, NULL, NULL);

};

astptr functionbody(){
    return newnode(n_empty, "", NULL, NULL, NULL);

};

astptr argumentlist(){
    return newnode(n_empty, "", NULL, NULL, NULL);

};



/*
<expr> -> [+ | -]<term> {(+ | -) <term>} 
*/
astptr expression() {

    //TODO Log("inside expression function: Parser")

    astptr pfirst; /* first pointer in the expr chain */
    astptr term2;
    int startingtoken;
    string tokendata;
    nodetype ntype;

    // cout << "Inside expression" << endl;

    startingtoken = plussym;
    if ((currenttoken == plussym) || (currenttoken == minussym)) {
        startingtoken = currenttoken;
        currenttoken = cleanLexer();
    }

    pfirst = term();

    if (startingtoken==minussym) pfirst = newnode(n_uminus, "-", pfirst, NULL, NULL);
    while ((currenttoken == plussym) || (currenttoken == minussym)) {
        if (currenttoken == plussym) {ntype = n_plus; tokendata = "+";} else {ntype = n_minus; tokendata = "-";};
        currenttoken = cleanLexer();
        term2 = term();
        pfirst = newnode(ntype, tokendata, pfirst, term2, NULL);
        }

    return pfirst;
}

/* term
<term> -> <factor> {(* | /) <factor>)
*/
astptr term() {
    
    astptr pfirst, factor2;
    nodetype ntype;
    string tokendata;
    pfirst = factor();

    // cout << "Inside term" << endl;

    while ((currenttoken == multiplysym) || (currenttoken == dividesym)) {
        if (currenttoken == multiplysym) {ntype = n_mul; tokendata = "*";} else {ntype = n_div; tokendata = "/";};
        currenttoken = cleanLexer();
        factor2 = factor();
        pfirst = newnode(ntype, tokendata, pfirst, factor2, NULL);
        }
    
    return pfirst;
}

/* factor
<factor> -> id | integer | ( <expr> )
*/
astptr factor(){
    astptr pfirst;

    // cout << "Inside factor" << endl;
    if(currenttoken == identifiersym ){      
        // cout << "Inside identifier" << identifier << endl;
        pfirst = newnode(n_id, identifier, NULL, NULL, NULL);
        currenttoken = cleanLexer();
    } else if(currenttoken == intsym) {
        // cout << "Inside intsym" << intvalue << endl;
        pfirst = newnode(n_integer, to_string(intvalue) , NULL, NULL, NULL);
        currenttoken = cleanLexer();
    } else {
        if(currenttoken ==  openbracketsym) {
            currenttoken = cleanLexer();
            pfirst = expression();
            if (currenttoken == closebracketsym){
                currenttoken = cleanLexer();
            } else {
                //TODO - Missing ')' 
            }
        } else {
            //TODO - error not an id, integer or (expression)
        }
    }
    return pfirst;
}

/* if statement
<ifstmt> -> if <boolexpr> <statement> [else <statement>]
//TODO <ifstmt> -> if (<boolexpr>) <statement> [else <statement>] --> Add () around boolexpr
*/
astptr ifstatement(){
    astptr pfirst = NULL, bexp = NULL, elsee = NULL;
    if (currenttoken != ifsym){
        //TODO Errror not an if ststaement
    } else {
        currenttoken = cleanLexer();
        bexp = booleanexpression();
        if(currenttoken != colonsym){
            //TODO Error expected ':' after if
        } else {
            //NOTE Does this need to consume another lex token?
            currenttoken = lexer();
            //TODO Make this as a block statement instead of checking for blocksym
            if(currenttoken != blocksym){
                //TODO Error expected identation
            } else {
                //NOTE Does this need to consume another lex token?
                currenttoken = cleanLexer();
                pfirst = statement();
                if(currenttoken == elsesym){
                    currenttoken = cleanLexer();
                    if(currenttoken != colonsym){
                        //TODO Expected ':'
                    } else {
                        currenttoken = lexer();
                        //TODO Make this as a block statement instead of checking for blocksym
                        if(currenttoken != blocksym){
                            //TODO expected identation
                        } else {
                            currenttoken = cleanLexer();
                            elsee = statement();
                        }                       
                    }
                }
            }  
        }
    }
    return newnode(n_if, "", bexp, pfirst, elsee);
}


/* assign statement
<assignment> -> identifier = {<experssion> | <list>}
*/
astptr assignment(){
    astptr pfirst, lis, exp;
    string id;
    if(currenttoken != identifiersym){
        //TODO Expected identifier
    } else {
        currenttoken = cleanLexer();
        if (currenttoken != assignsym){
            //TODO Expected assign symbol
        } else {
            currenttoken = cleanLexer();
            if (currenttoken == opensquaresym){
                currenttoken = cleanLexer();
                id = identifier;
                lis = list();
                pfirst = newnode(n_assignment_list, identifier, lis, NULL, NULL);
                if (currenttoken != closesquaresym){
                    //TODO Expected ']'
                }
            } else {
                id = identifier;
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
astptr printstatement(){
    astptr pfirst, expr;
    if (currenttoken != printsym){
        //TODO Expected print
    } else {
        currenttoken = cleanLexer();
        if(currenttoken != openbracketsym){
            //TODO Expected '('
        } else {
            currenttoken = cleanLexer();
            expr = expression();
            pfirst = newnode(n_print,"print",expr,NULL, NULL);
            if(currenttoken == commasym){

                currenttoken == cleanLexer();
                while(currenttoken != closebracketsym){
                    
                    if (tracker == lineInput.length() - 1 || currenttoken == closebracketsym) {
                    expr = expression();
                    printParserTree(expr);
                    pfirst = newnode(n_prints,"",pfirst,expr, NULL);
                        break;
                    }
                }
            }
            if(currenttoken != closebracketsym){
                //TODO Expected ')'
            } else {
                currenttoken = cleanLexer();
            }
        }
    }
    return pfirst;
};

/* boolean expression
<boolean expression> -> <expresion> <boolean operation> <expression>
*/
astptr booleanexpression(){
    astptr exp1, exp2, bexp;
    exp1 = expression();
    exp2 = booleanoperation();
    bexp = expression();
    return newnode(n_booleanexp, "", exp1, bexp, exp2);
};

/* boolean operation
<boolean expression> -> { == | != | >= | <= | > | <}
*/

astptr booleanoperation(){
    switch (currenttoken) {
        case equalsym: currenttoken = cleanLexer(); return newnode(n_eq, "=", NULL, NULL, NULL); break;
        case notequalsym: currenttoken = cleanLexer(); return newnode(n_ne, "!=", NULL, NULL, NULL); break;
        case greaterorequalsym: currenttoken = cleanLexer(); return newnode(n_ge, ">=", NULL, NULL, NULL); break;
        case greaterthansym: currenttoken = cleanLexer(); return newnode(n_gt, ">", NULL, NULL, NULL); break;
        case lessthansym: currenttoken = cleanLexer(); return newnode(n_lt, "<", NULL, NULL, NULL); break;
        case lessorequalsym: currenttoken = cleanLexer(); return newnode(n_le, "<=", NULL, NULL, NULL); break;
        default:
            break;
    }
}

astptr parser(){
    return blockstatements();
};

void printParserTree(astptr head){
    string current;
    astptr left, right, mid;

    switch(head->asttype){
        case n_id: case n_integer: 
            cout << head->astdata << " "; break;
        case n_plus: case n_minus: 
        case n_div: case n_mul:
        case n_statements: case n_while:
        case n_prints: case n_block_stmts:
            cout << head->astdata << " ";
            left = head->p1;
            right = head->p2;
            printParserTree(left);
            printParserTree(right); break;
        case n_statement: case n_block_stmt:
        case n_simple_stmt:
            left = head->p1;
            printParserTree(left); break;
        case n_if: 
            left = head->p1;
            mid = head->p2;
            right = head->p3;
            printParserTree(left);
            printParserTree(mid);
            printParserTree(right); break;
        case n_assignment_list: case n_assignment_int:
            cout << head->astdata << " = ";
            left = head->p1;
            printParserTree(left); break;
        case n_print:
            left = head->p1;
            cout << head->astdata << " ";
            printParserTree(left); break;
   
    }
    
}

void freeMemory(astptr head){
    astptr left, right, mid;

     switch(head->asttype){
        case n_id: case n_integer: 
        case n_empty: case n_error:
            delete head; break;
        case n_plus: case n_minus: 
        case n_div: case n_mul:
        case n_statements: case n_while:
        case n_prints: case n_block_stmts:
            left = head->p1;
            right = head->p2;
            delete head;
            freeMemory(left);
            freeMemory(right); break;
        case n_statement: case n_block_stmt:
        case n_simple_stmt:
            left = head->p1;
            delete head;
            freeMemory(left); break;
        case n_if:
            left = head->p1;
            mid = head->p2;
            right = head->p3;
            delete head;
            freeMemory(left);
            freeMemory(mid);
            freeMemory(right); break;
        case n_assignment_list: case n_assignment_int:
            left = head->p1;
            delete head;
            freeMemory(left); break;
        case n_print:
            left = head->p1;
            delete head;
            freeMemory(left); break;

    }
}
#endif