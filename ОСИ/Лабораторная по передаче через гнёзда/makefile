all: client server

client: client.o utility.o
	gcc client.o utility.o -o client

server: server.o utility.o
	gcc server.o utility.o -o server

server.o: server.c 
	gcc -c server.c

client.o: client.c
	gcc -c client.c

utility.o: utility.c
	gcc -c utility.c

clean:
	rm -rf *.o

