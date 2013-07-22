CXXFLAGS=$(OBELISK_INCLUDE) $(shell pkg-config --cflags libbitcoin)
LIBS=$(OBELISK_LIB) -lobelisk_client -lzmq $(shell pkg-config --libs libbitcoin)

default: history

main.o: main.cpp
	g++ -c main.cpp -o main.o $(CXXFLAGS)

history: main.o
	g++ -o history main.o $(LIBS)

