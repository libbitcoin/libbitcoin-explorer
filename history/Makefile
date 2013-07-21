CXXFLAGS=-I$(shell echo ~)/obelisk/include $(shell pkg-config --cflags libbitcoin)
LIBS=$(shell echo ~)/obelisk/client/libobelisk_client.a -lzmq $(shell pkg-config --libs libbitcoin)

default: history

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

history: main.o
	g++ -o history main.o $(LIBS)

