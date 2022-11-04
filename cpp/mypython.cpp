#include <iostream>
#include <fstream>
#include <string>
#include "log.h"
#include "lexer.h"
#include "parser.h"
#include <map>

// #define LEXERTEST
#define ASTTEST

map<string, double> ints_map;
map<string, string> string_map;

using namespace std;
class Number
{
public:
    double value;

    Number()
    {
        value = 0;
    }
    Number added(Number other)
    {
        Number tmp;
        tmp.value = value + other.value;
        return tmp;
    }
    Number subtracted(Number other)
    {
        Number tmp;
        tmp.value = value - other.value;
        return tmp;
    }
    Number multiplied(Number other)
    {
        Number tmp;
        tmp.value = value * other.value;
        return tmp;
    }
    Number divided(Number other)
    {
        if (value != 0)
        {
            Number tmp;
            // cout << "value on divide" << value << endl;
            tmp.value = (other.value) / value;

            return tmp;
        }
        else
        {
            cout << "CANNOT DIVIDE BY 0" << endl;
            exit(0);
        }
    }
    Number unary_m(double other)
    {
        Number tmp;
        tmp.value = (-1) * other;
        return tmp;
    }
};
class Interpreter
{
public:
    Interpreter(){};

    Number visit(astptr node)
    {
        switch (node->asttype)
        {
        case n_integer:
            return visit_number(*node);
            break;
        case n_id:
            return visit_id(*node);
            break;
        case n_plus:
            return visit_plus(*node);
            break;
        case n_minus:
            return visit_minus(*node);
            break;
        case n_uminus:
            return visit_unarym(*node);
            break;
        case n_mul:
            return visit_mult(*node);
            break;
        case n_div:
            return visit_divide(*node);
            break;
        default:
            break;
        }
    }
    Number visit_number(astnode node)
    {
        Number tmp;
        tmp.value = stod(node.astdata);
        // cout << stod(node.astdata) << endl;
        return tmp;

        cout << "found number node data : " << node.astdata << endl;
    }
    Number visit_id(astnode node)
    {
        cout << "found id node data : " << node.astdata << endl;
    }

    Number visit_plus(astnode node)
    {
        cout << "found plus node" << endl;
        Number l = visit(node.p1);
        Number r = visit(node.p2);
        Number tmp;
        tmp.value = l.added(r).value;
        cout << tmp.value << endl;
        return tmp;
    }
    Number visit_minus(astnode node)
    {
        cout << "found minus node" << endl;
        Number l = visit(node.p1);
        Number r = visit(node.p2);
        Number tmp;
        tmp.value = l.subtracted(r).value;
        cout << tmp.value << endl;
        return tmp;
    }
    Number visit_unarym(astnode node)
    {
        /* cout << "found unary node" << endl;
        Number tmp;
        double tmp1 = stod(node.astdata);
        tmp.value = tmp.unary_m(tmp1);*/
    }
    Number visit_mult(astnode node)
    {
        cout << "found multiply node" << endl;
        Number l = visit(node.p2);
        Number r = visit(node.p1);

        Number tmp;
        tmp.value = l.multiplied(r).value;
        cout << tmp.value << endl;
        return tmp;
    }
    Number visit_divide(astnode node)
    {
        cout << "found divide node" << endl;
        Number l = visit(node.p2);
        Number r = visit(node.p1);

        Number tmp;
        tmp.value = l.divided(r).value;
        cout << tmp.value << endl;
        return tmp;
    }
};

int main(int argc, const char *argv[])
{
    if (argc == 1)
    {
        log(1);
        return 0;
    }

    /* Opening the file */
    string filename = argv[1];

    ifstream file(filename);

    linenumber = 0;

    if (file)
    {
        while (file.good())
        {

            // Taking each line of the file as a string input
            getline(file, lineInput);
            linenumber++;

            // DEEBUG
            cout << "     Current line = " << lineInput << endl;

            tracker = -1;

#ifdef ASTTEST
            currenttoken = cleanLexer();
            currenttoken = cleanLexer();
            astptr parseetree = parser();
            printParserTree(parseetree);

            Interpreter tmp;
            tmp.visit(parseetree);

            freeMemory(parseetree);
            cout << " ---Endl" << endl;

#endif

#ifdef LEXERTEST
            while (tracker < (int)lineInput.length())
            {
                currenttoken = lexer();
                switch (currenttoken)
                {
                case intsym:
                    cout << "Integer token = " << intvalue << endl;
                    break;
                case whitespacesym:
                    cout << "Whitespace token " << endl;
                    break;
                case printsym:
                    cout << "Print token " << endl;
                    break;
                case blocksym:
                    cout << "Block token " << endl;
                case identifiersym:
                    cout << "Identifier token = " << identifier << endl;
                    break;
                case whilesym:
                    cout << "While token " << endl;
                    break;
                case eofsym:
                    cout << "EOF token " << endl;
                    break;
                case ifsym:
                    cout << "IF token " << endl;
                    break;
                case elsesym:
                    cout << "Else token " << endl;
                    break;
                case elseifsym:
                    cout << "Elseif token " << endl;
                    break;
                case defsym:
                    cout << "Def token " << endl;
                    break;
                case returnsym:
                    cout << "REturn token " << endl;
                    break;
                case semicolonsym:
                    cout << "semicolon token " << endl;
                    break;
                case commasym:
                    cout << "comma token " << endl;
                    break;
                case assignsym:
                    cout << "assign token " << endl;
                    break;
                case errorsym:
                    cout << "Error " << identifier << " is unrecognized on line " << linenumber << " at character " << tracker << endl;
                    break;
                case dividesym:
                    cout << "divide token " << endl;
                    break;
                case openbracketsym:
                    cout << "OpenBracker token " << endl;
                    break;
                case closebracketsym:
                    cout << "CloseBracker token " << endl;
                    break;
                case plussym:
                    cout << "Plus token " << endl;
                    break;
                case minussym:
                    cout << "Minus token " << endl;
                    break;
                case multiplysym:
                    cout << "multiply token " << endl;
                    break;
                case equalsym:
                    cout << "Euqal token " << endl;
                    break;
                case leftanklesym:
                    cout << "Left ankle token " << endl;
                    break;
                case rightanklesym:
                    cout << "Right ankle token " << endl;
                    break;
                case colonsym:
                    cout << "Colon token " << endl;
                    break;
                case commentsym:
                    cout << "Comment token " << endl;
                    break;
                case singlequotesym:
                    cout << "Single quote token = " << identifier << endl;
                    break;
                case doublequotesym:
                    cout << "Double quote token = " << identifier << endl;
                    break;
                case opensquaresym:
                    cout << "Open sq bracket token " << endl;
                    break;
                case closesquaresym:
                    cout << "Close sq bracket token " << endl;
                    break;
                case shebangsym:
                    cout << "Shebang token " << endl;
                    break;
                case notequalsym:
                    cout << "Not equal token " << endl;
                    break;
                case greaterorequalsym:
                    cout << "Greater than or equal token " << endl;
                    break;
                case lessorequalsym:
                    cout << "Less than or equal token " << endl;
                    break;
                case lessthansym:
                    cout << "Less than token " << endl;
                    break;
                case greaterthansym:
                    cout << "Greater than token " << endl;
                    break;
                case newlinesym:
                    cout << "  New line " << endl;
                    break;
                }
            }
// std::cout << "intvalue = " << intvalue << std::endl;
#endif
        }
        file.close();
        currenttoken = eofsym;
    }
    else
    {
        cout << "Input file not found";
    }
}