g++ -std=c++17 -c -Wall errorlog.cpp
cp *.o ~/bin
g++ -std=c++17 -Wall ~/bin/errorlog.o mypython.cpp -o ~/bin/mypython
