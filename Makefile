CC = gcc
CFLAGS = -Wall -Werror
DBFLAGS = -ggdb -DDEBUG
LDFLAGS = -lpthread
DEBUG-TARGETS = server-debug client-debug
RELEASE-TARGETS = server client
HEADERS = mesg.h

build-debug = $(CC) $(CFLAGS) $(DBFLAGS) $(LDFLAGS)
build-release = $(CC) $(CFLAGS) $(LDFLAGS) -O3

.PHONY: all debug release default clean

# Rules for a debug build of the project
debug: $(DEBUG-TARGETS)

server-debug: server_main-debug.o server-debug.o wrappers-debug.o 
	$(build-debug) -o $@ $^

server_main-debug.o: server_main.c
	$(build-debug) -c -o $@ $^

server-debug.o: server.c
	$(build-debug) -c -o $@ $^

wrappers-debug.o: wrappers.c
	$(build-debug) -c -o $@ $^


client-debug: client_main-debug.o client-debug.o wrappers-debug.o
	$(build-debug) -o $@ $^

client_main-debug.o: client_main.c
	$(build-debug) -c -o $@ $^

client-debug.o: client.c
	$(build-debug) -c -o $@ $^


# Rules for a release build
release: $(RELEASE-TARGETS)

server: server_main.o server.o wrappers.o
	$(build-release) -o $@ $^

server_main.o: server_main.c
	$(build-release) -c -o $@ $^

server.o: server.c
	$(build-release) -c -o $@ $^

client: client_main.o client.o wrappers.o
	$(build-release) -o $@ $^

client_main.o: client_main.c
	$(build-release) -c -o $@ $^

client.o: client.c 
	$(build-release) -c -o $@ $^

wrappers.o: wrappers.c
	$(build-release) -c -o $@ $^



clean:
	rm -rf $(DEBUG-TARGETS) $(RELEASE-TARGETS) *.o

