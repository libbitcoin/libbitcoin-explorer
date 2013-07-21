CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: genpriv

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

genpriv: main.o
	g++ -o genpriv main.o $(LIBS)

