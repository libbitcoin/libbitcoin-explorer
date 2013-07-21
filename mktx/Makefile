CXXFLAGS=$(shell pkg-config --cflags libbitcoin)
LIBS=$(shell pkg-config --libs libbitcoin)

default: mktx

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

mktx: main.o
	g++ -o mktx main.o $(LIBS)

