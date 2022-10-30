
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


void whilestatement(){};
void returnstatement(){};

//NOTE the previous function (assignment) has already checked for [] brackets
void list(){};


/*
<function> -> identifier {()| (<argumentlist>))} : <functionbody>
*/
void function(){};

void functionbody(){};

void argumentlist(){};


/*
<statement> : := <assignment> | <ifstatement> | <whilestatement> | <printstatement> | <returnstatement>
*/

void statement()
{
//TODO Log("inside statement function: Parser")
if (currenttoken == commentsym){
    int currentline = linenumber;
    while( linenumber == currentline){
        currenttoken = cleanLexer(); 
    }  
}
else if (currenttoken==identifiersym) assignment();
else if (currenttoken==ifsym) ifstatement();
else if (currenttoken==whilesym) whilestatement();
else if (currenttoken==printsym) printstatement();
else if (currenttoken==returnsym) returnstatement();
/* else empty */
}

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
void ifstatement(){
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
void booleanexpression(){
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
            cout << head->astdata << " ";
            left = head->p1;
            right = head->p2;
            printParserTree(left);
            printParserTree(right); break;
    }
    
}

void freeMemory(astptr head){
    astptr left, right;

     switch(head->asttype){
        case n_id: case n_integer: 
            delete head; break;
        case n_plus: case n_minus: 
        case n_div: case n_mul:
            left = head->p1;
            right = head->p2;
            delete head;
            freeMemory(left);
            freeMemory(right); break;
    }
}
#endif