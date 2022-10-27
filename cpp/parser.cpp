
#ifndef PARSER_CPP
#define PARSER_CPP

#include "parser.h"
#include "lexer.h"
#include "log.h"

astptr newnode(nodetype n, int s, astptr first, astptr second, astptr third){
    astnode* mynode = new astnode();
    mynode->asttype = n;
    mynode->astdata1 = s;
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
if (currenttoken==identifiersym) assignment();
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
    nodetype ntype;

    startingtoken = plussym;
    if ((currenttoken == plussym) || (currenttoken == minussym)) {
        startingtoken = currenttoken;
        currenttoken = lexer();
    }

    pfirst = term();

    if (startingtoken==minussym) pfirst = newnode(n_uminus, 0, pfirst, NULL, NULL);
    while ((currenttoken == plussym) || (currenttoken == minussym)) {
        if (currenttoken == plussym) ntype = n_plus; else ntype = n_minus;
            currenttoken = lexer();
            term2 = term();
            pfirst = newnode(ntype, 0, pfirst, term2, NULL);
        }

    return pfirst;
}

/* term
<term> -> <factor> {(* | /) <factor>)
*/
astptr term() {
    astptr pfirst;
    pfirst = newnode(n_assignment,3,NULL,NULL, NULL);
    factor();

    while ((currenttoken == multiplysym) || (currenttoken == dividesym)) {
        currenttoken = lexer();
        factor();
        }
    
    return pfirst;
}

/* factor
<factor> -> id | integer | ( <expr> )
*/
void factor(){

    if(currenttoken == identifiersym ){
        currenttoken = lexer();
        //TODO
        cout << "Do something" << endl;
    } else if(currenttoken == intsym) {
        currenttoken = lexer();
        //TODO
        cout << "Do something" << endl;
    } else {
        if(currenttoken ==  openbracketsym) {
            currenttoken = lexer();
            expression();
            if (currenttoken == closebracketsym){
                currenttoken = lexer();
            } else {
                //TODO - Missing ')' 
            }
        } else {
            //TODO - error not an id, integer or (expression)
        }
    }
}

/* if statement
<ifstmt> -> if <boolexpr> <statement> [else <statement>]
//TODO <ifstmt> -> if (<boolexpr>) <statement> [else <statement>] --> Add () around boolexpr
*/
void ifstatement(){
    if (currenttoken != ifsym){
        //TODO Errror not an if ststaement
    } else {
        currenttoken = lexer();
        booleanexpression();
        if(currenttoken != colonsym){
            //TODO Error expected ':' after if
        } else {
            //NOTE Does this need to consume another lex token?
            currenttoken = lexer();
            if(currenttoken != blocksym){
                //TODO Error expected identation
            } else {
                //NOTE Does this need to consume another lex token?
                currenttoken = lexer();
                statement();
                if(currenttoken == elsesym){
                    currenttoken = lexer();
                    if(currenttoken != colonsym){
                        //TODO Expected ':'
                    } else {
                        if(currenttoken != blocksym){
                            //TODO expected identation
                        } else {
                            currenttoken = lexer();
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
        currenttoken = lexer();
        if (currenttoken != assignsym){
            //TODO Expected assign symbol
        } else {
            currenttoken = lexer();
            if (currenttoken == opensquaresym){
                currenttoken = lexer();
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
        currenttoken = lexer();
        if(currenttoken != openbracketsym){
            //TODO Expected '('
        } else {
            currenttoken = lexer();
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
        currenttoken = lexer();
    }
}

#endif