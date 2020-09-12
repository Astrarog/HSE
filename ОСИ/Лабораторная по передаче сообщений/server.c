#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "utility.h"

#define PROJ_ID 7945

struct my_msgbuf
{
	long type;
	char* text;
};


int main(int argc, char* argv[])
{
	int id = PROJ_ID;
        if(argc > 1)
        {
                id = strtol(argv[1], NULL, 10);
        }

	key_t ipckey = ftok("/home/explorer/lab1/lab.cfg", id);
	int mq_id;
        while((mq_id = msgget(ipckey, 0666)) == -1)
	{
		sleep(1);
	}
	printf("[INFO] Message identifier is %d\n", mq_id);

	struct msqid_ds ds;
        msgctl(mq_id, IPC_STAT, &ds);
        size_t max_msg_size = ds.msg_qbytes;
        char* request_data = malloc(max_msg_size);

        struct my_msgbuf request_msg = {1, request_data};

        int request_lenght = msgrcv(mq_id, &request_msg, max_msg_size, 0, 0);
        if( request_lenght == -1)
        {
                printf("\e[31m[ERROR] Error occured while reciving request. Try again later. Aborted.\n");
                exit(2);
        }
	struct
    {
        long type;
        char text[ds.msg_qbytes];
    } message;
	printf("%d ?= %d", max_msg_size, sizeof(message.text));
        printf("[INFO] Reciving request message of size=%d\n", request_lenght);
	request_msg.text[request_lenght-1] = '\0';
	printf("Message: %s with len=%d\n", request_msg.text, strlen(request_msg.text));
        if(request_lenght < max_msg_size){ request_msg.text[request_lenght-1] = '\0';}

	char* command = "wc *";
	//char* command = concat(concat("wc -c ", request_data), "| head -n -1 | tr -s ' ' | awk '$1 > 10 {ORS= \" \"; print $2;}'");
	FILE* stream = popen(command, "r");
	char* response_data;
       	size_t response_lenght = streamread(stream, &response_data);
	
	pclose(stream);
	
	struct my_msgbuf response_msg = {2, response_data};

	printf("[INFO] Sending response message of size=%ld\n", response_lenght);
	if(msgsnd(mq_id, &response_msg, response_lenght, 0) == -1)
	{
		printf("\e[31m[ERROR] Can't send response. Try again later. Aborted.\n");
		exit(3);
	}
}

