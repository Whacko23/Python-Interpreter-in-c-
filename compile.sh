g++ -std=c++17 -c -Wall cpp/log.cpp
mv *.o ~/bin
g++ -std=c++17 -Wall ~/bin/log.o cpp/mypython.cpp -o ~/bin/mypython
