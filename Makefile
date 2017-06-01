CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
DEBUG = $(CFLAGS) += -ggdb

all: main RShellBase Command Connector RShellContainer
	mkdir -p bin
	$(CC) $(CFLAGS) main.o RShellBase.o Command.o Connector.o RShellContainer.o -o ./bin/rshell
main:
	$(CC) $(CFLAGS) -c ./src/main.cpp
RShellBase:
	$(CC) $(CFLAGS) -c ./src/RShellBase.cc
Command:
	$(CC) $(CFLAGS) -c ./src/Command.cc
Connector:
	$(CC) $(CFLAGS) -c ./src/Connector.cc
RShellContainer:
	$(CC) $(CFLAGS) -c ./src/RShellContainer.cc
clean:
	rm -r *.o
