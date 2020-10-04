all: client server ctl

client: client.o utility.o
	gcc client.o utility.o -o client

server: server.o utility.o
	gcc server.o utility.o -o server

ctl: ctl.o utility.o
	gcc ctl.o utility.o -o ctl

server.o: server.c 
	gcc -c server.c

client.o: client.c
	gcc -c client.c

utility.o: utility.c
	gcc -c utility.c

ctl.o: ctl.c
	gcc -c ctl.c

clean:
	rm -rf *.o
