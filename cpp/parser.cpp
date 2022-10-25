
#ifndef PARSER_CPP
#define PARSER_CPP

#include "parser.h"
#include "lexer.h"
#include "log.h"


void whilestatement(){};
void returnstatement(){};
void booleanexpression(){};



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
<expr> -> <term> {(+ | -) <term>}
*/
void expression() {
    //TODO Log("inside expression function: Parser")
    term();

    while ((currenttoken == plussym) || (currenttoken == minussym)) {
        currenttoken = lexer();
        term();
        }
}

/* term
<term> -> <factor> {(* | /) <factor>)
*/
void term() {
    factor();

    while ((currenttoken == multiplysym) || (currenttoken == dividesym)) {
        currenttoken = lexer();
        factor();
        }
}

/* factor
<factor> -> id | integer | ( <expr> )
*/
void factor(){

    if(currenttoken == identifiersym ){
        //TODO
        cout << "Do something" << endl;
    } else if(currenttoken == intsym) {
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
<ifstmt> -> if (<boolexpr>) <statement>
[else <statement>]
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
<assignment> -> identifier = <experssion>
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
            expression();
        }
    }
    
};

/* print statement
<print> -> print(expression)
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


#endif