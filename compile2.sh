g++ -std=c++17 -c -Wall cpp/log.cpp cpp/lexer.cpp 
mv *.o ~/bin
g++ -std=c++17 -Wall ~/bin/log.o ~/bin/lexer.o  cpp/mypython.cpp -o ~/bin/mypython
