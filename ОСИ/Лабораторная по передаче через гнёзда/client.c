#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "utility.h"

int main(int argc, char* argv[])
{
	unlink(client_name);

        int sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);

        if (sock_fd == -1)
        {
                perror("[ERROR] Can't create clientr soket. Aborted.\n");
		close(sock_fd);
		unlink(client_name);
                exit(1);
        }

        struct sockaddr_un server;
        server.sun_family = AF_UNIX;
	socklen_t s_name_len = strlen(server_name);
        strncpy(server.sun_path, server_name, s_name_len);
	server.sun_path[s_name_len] = '\0';


        struct sockaddr_un client;
        client.sun_family = AF_UNIX;
	socklen_t c_name_len = strlen(client_name);
        strncpy(client.sun_path, client_name, c_name_len);
	client.sun_path[c_name_len] = '\0';
	
	s_name_len += 2;
	c_name_len += 2;

	if(bind(sock_fd, (struct sockaddr *)&client, c_name_len ) == -1)
	{
		perror("[INFO] Can't bind client socket. Aborted.");
		close(sock_fd);
		unlink(client_name);
		exit(5);
	}
	
	// rcvfrom
	char data[256];
	socklen_t rcv_data_len;
	ssize_t rcv_len = recvfrom(sock_fd, data, sizeof(data), 0, (struct sockaddr *)&server, &rcv_data_len);
	
	if(rcv_len == -1)
        {
                perror("\e[31m[ERROR] Can't receive request. Try again later. Aborted.\n");
		close(sock_fd);
		unlink(client_name);
                exit(2);
        }

	data[rcv_len] = '\0';
	printf("[INFO] Recieving request of %ld bytes\n", rcv_len);
	printf("Data received: %s\n", data);
	// command
	char* command = concat(concat("ps u ", data), "| grep explorer | awk '{print $2}' | tr '\n' ' '");
	FILE* stream = popen(command, "r");

	char* resp_data;
	size_t resp_len = streamread(stream, &resp_data);
	
	pclose(stream);
	
	resp_data[resp_len] = '\0';
	
	printf("[INFO] Sending response of %ld bytes\n", resp_len);

	printf("Data sent: %s\n", resp_data);
	//sendto
	ssize_t send_len = sendto(sock_fd, resp_data, resp_len , 0, (struct sockaddr *)&server, s_name_len);
        if(send_len == -1)
        {
                perror("\e[31m[ERROR] Can't send response. Try again later. Aborted.\n");
		close(sock_fd);
		unlink(client_name);
                exit(3);
        }	
	close(sock_fd);
	unlink(client_name);
	printf("[INFO] Job's done. Aborting.\n");

	return 0;
}

