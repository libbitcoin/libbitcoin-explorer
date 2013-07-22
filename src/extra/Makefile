CXXFLAGS=$(OBELISK_INCLUDE) $(shell pkg-config --cflags libbitcoin)
LIBS=$(OBELISK_LIB_PATH) -lobelisk -lzmq -lconfig++ $(shell pkg-config --libs libbitcoin)

default: balance history

config.o: config.cpp
	g++ -c config.cpp -o config.o $(CXXFLAGS)

balance.o: balance.cpp
	g++ -c balance.cpp -o balance.o $(CXXFLAGS)
balance: balance.o config.o
	g++ -o balance balance.o config.o $(LIBS)

history.o: history.cpp
	g++ -c history.cpp -o history.o $(CXXFLAGS)
history: history.o config.o
	g++ -o history history.o config.o $(LIBS)

install:
	cp balance history /usr/local/bin
	cp sx.cfg /etc/

