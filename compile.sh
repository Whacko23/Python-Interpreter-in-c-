g++ -std=c++17 -c -Wall log.cpp
mv *.o ~/bin
g++ -std=c++17 -Wall ~/bin/log.o mypython.cpp -o ~/bin/mypython
