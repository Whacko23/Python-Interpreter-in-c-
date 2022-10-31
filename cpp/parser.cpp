
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
generate -> [statements]
*/
astptr generate_ast(){
    return statements;
}

/*
<statements> ::= <statement> | <statements>
*/
astptr statements(){
    astptr pfirst = statement();
    return newnode(n_statements, "", pfirst, statements(), NULL);
};

/*
statement: compound_stmt  | simple_stmts 
*/
astptr statement(){
    pfirst = simple_stmt();
    if (pfirst->head == n_empty){
        pfirst = compound_stmt();
    }
    return newnode(n_statement, "", pfirst , NULL, NULL)
}


/*
<statement> : := <assignment> | <printstatement> | <returnstatement> | empty
*/
astptr simple_stmt()
{
    //TODO Log("inside statement function: Parser")
    if (currenttoken == commentsym){
        int currentline = linenumber;
        while( linenumber == currentline){
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
    else if (currenttoken == defsym) return function();
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
            pwhile = newnode(n_while, "while", pbexp, blockstatement(currentline), NULL);
        } else {
            //TODO Error expected ":"
        }    
    }
    return pwhile;
};

/*
block:
    | NEWLINE INDENT statements DEDENT 
    | simple_stmts

*/
astptr blockstatement(int currentline){
    astprt pfirst;
    int current_indent;
    if (currentline != linenumber){
        if(currenttoken == blocksym){
            current_indent = 2;
            currenttoken = lexer();
            while(currenttoken == whitespacesym || currenttoken == blocksym){
                if(currenttoken == whitespace) current_indent ++; else current_indent += 2;
                currenttoken = lexer();
            }
            pfirst = newnode(n_block_stmt, to_string(current_indent), statements(), NULL, NULL);
        } else {
            //TODO IndentationError: expected an indented block
        }
    } else {
        pfirst = newnode(n_simple_stmt, "", simple_stmt, NULL,NULL)
        return pfirst;
    }

};

astprt returnstatement(){
    return newnode(n_empty, "", NULL, NULL, NULL);
};

//NOTE the previous function (assignment) has already checked for [] brackets
astptr list(){
    return newnode(n_empty, "", NULL, NULL, NULL);

};


/*
<function> -> identifier {()| (<argumentlist>))} : <functionbody>
*/
astptr function(){
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
    astptr pfirst;
    if (currenttoken != ifsym){
        //TODO Errror not an if ststaement
    } else {
        currenttoken = cleanLexer();
        booleanexpression();
        if(currenttoken != colonsym){
            //TODO Error expected ':' after if
        } else {
            //NOTE Does this need to consume another lex token?
            currenttoken = cleanLexer();
            if(currenttoken != blocksym){
                //TODO Error expected identation
            } else {
                //NOTE Does this need to consume another lex token?
                currenttoken = cleanLexer();
                statement();
                if(currenttoken == elsesym){
                    currenttoken = cleanLexer();
                    if(currenttoken != colonsym){
                        //TODO Expected ':'
                    } else {
                        if(currenttoken != blocksym){
                            //TODO expected identation
                        } else {
                            currenttoken = cleanLexer();
                            statement();
                        }                       
                    }
                }
            }  
        }
    }
}


/* assign statement
<assignment> -> identifier = {<experssion> | <list>}
*/
void assignment(){
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
                list();
                if (currenttoken != closesquaresym){
                    //TODO Expected ']'
                }
            } else {
                expression();
            }  
        }
    }
    
};

/* print statement
<print> -> print({<expression> | <list>) //TODO List
*/
void printstatement(){
    if (currenttoken != printsym){
        //TODO Expected print
    } else {
        currenttoken = cleanLexer();
        if(currenttoken != openbracketsym){
            //TODO Expected '('
        } else {
            currenttoken = cleanLexer();
            expression();
            if(currenttoken != closebracketsym){
                //TODO Expected ')'
            }
        }
    }
};

/* boolean expression
<boolean expression> -> <expresion> <boolean operation> <expression>
*/
astptr booleanexpression(){
    expression();
    booleanoperation();
    expression();
};

/* boolean operation
<boolean expression> -> { == | != | >= | <= | > | <}
*/

void booleanoperation(){
    if (currenttoken == equalsym || currenttoken == notequalsym || currenttoken == greaterorequalsym || currenttoken == lessorequalsym || currenttoken == greaterthansym || currenttoken == lessthansym){
        currenttoken = cleanLexer();
    }
}

astptr parser(){
    return expression();
};

void printParserTree(astptr head){
    string current;
    astptr left, right;

    switch(head->asttype){
        case n_id: case n_integer: 
            cout << head->astdata << " "; break;
        case n_plus: case n_minus: 
        case n_div: case n_mul:
        case n_statements: case n_while:
            cout << head->astdata << " ";
            left = head->p1;
            right = head->p2;
            printParserTree(left);
            printParserTree(right); break;
        case n_statement: case n_block_stmt:
        case n_simple_stmt:
            left = head->p1;
            printParserTree(left); break;
    }
    
}

void freeMemory(astptr head){
    astptr left, right;

     switch(head->asttype){
        case n_id: case n_integer: 
        case n_empty: 
            delete head; break;
        case n_plus: case n_minus: 
        case n_div: case n_mul:
        case statements: case n_while:
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

    }
}
#endif