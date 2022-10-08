#include <iostream>
#include "log.h"
#include "lexer.h"

#define LEXERTEST

using namespace std;

int main(int argc, const char *argv[]) {
    if (argc==1){
        log(1);
        return 0;
    }

    #ifdef LEXERTEST
    ch = getch();
    lextokens mytoken =lexer();
    #endif
}