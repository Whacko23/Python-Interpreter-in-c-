g++ -std=c++17 -c -Wall cpp/log.cpp cpp/lexer.cpp cpp/parser.cpp
mv *.o ~/bin
g++ -std=c++17 -Wall ~/bin/log.o ~/bin/lexer.o ~/bin/parser.o cpp/mypython.cpp -o ~/bin/mypython
