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
	unlink(server_name);

	int sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	
	if (sock_fd == -1)
	{
		perror("[ERROR] Can't create server soket. Aborted.\n");
		close(sock_fd);
		unlink(server_name);
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

	if(bind(sock_fd, (struct sockaddr *)&server, s_name_len) == -1)
        {
                perror("[INFO] Can't bind server socket. Aborted.");
		close(sock_fd);
		unlink(server_name);
                exit(5);
        }

	//command
	
	char* req_data;
	char* command = "ps a | awk 'NR>1{print $1}' | tr '\n' ' '";
	FILE* stream = popen(command, "r");
		
	size_t req_len = streamread(stream, &req_data);
	
	pclose(stream);
	
	//sendto
	printf("[INFO] Sending request of size %ld bytes", req_len);

	ssize_t send_len = sendto(sock_fd, req_data, req_len , 0, (struct sockaddr *)&client, c_name_len );
	if(send_len == -1)
	{
		perror("\e[31m[ERROR] Can't send request. Try again later. Aborted.\n");
		close(sock_fd);
		unlink(server_name);
		exit(2);
	}


	//rcvfrom

	char rcv_data[256];
	socklen_t rcv_data_len;
	ssize_t rcv_len = recvfrom(sock_fd, &rcv_data, sizeof(rcv_data), 0, (struct sockaddr *)&client, &rcv_data_len);
	printf("[INFO] Receiving response of size %ld bytes", rcv_len);
	if(rcv_len == -1)
        {
                perror("\e[31m[ERROR] Can't receive response. Try again later. Aborted.\n");
		close(sock_fd);
		unlink(server_name);
                exit(3);
        }
	
	printf("Resulted PIDs: %s\n", req_data);
	printf("[INFO] Job's done. Aborting.\n");
	return 0;
}


