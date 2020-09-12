#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "utility.h"

int main(int argc, char* argv[])
{
	int id = PROJ_ID;
        if(argc > 1)
        {
                id = strtol(argv[1], NULL, 10);
        }

	key_t ipckey = ftok("/home/explorer/lab1/lab.cfg", id);
	int mq_id = msgget(ipckey, IPC_CREAT | IPC_EXCL | 0777); // exec perm not used
	if (mq_id == -1)
	{
		printf("\e[31m[ERROR] Can't create MQ. Try another id. Aborted.\n");
		exit(1);
	}
	printf("[INFO] Message identifier is %d\n", mq_id);

	FILE* stream = popen("file * | awk -F ':' '/ASCII text/{ORS= \" \"; print $1;}'", "r");

	char* data;
	size_t request_lenght = streamread(stream, &data);
	
	pclose(stream);
	
	printf("[INFO] Sending request message of size=%ld\n", request_lenght);
	        
        struct my_msgbuf* request_msg = malloc(sizeof(struct my_msgbuf) + request_lenght);
        request_msg->type = 1;
        strncpy(request_msg->text, data, request_lenght);
        
	if(msgsnd(mq_id, request_msg, request_lenght, 0) == -1)
	{
		printf("\e[31m[ERROR] Can't send request. Try again later. Aborted.\n");
		exit(2);
	}


	struct msqid_ds ds;
        msgctl(mq_id, IPC_STAT, &ds);
        size_t max_msg_size = ds.msg_qbytes;
        
        struct my_msgbuf* response_msg = malloc(sizeof(struct my_msgbuf) + max_msg_size);
	response_msg->type = 2;
	
        int response_lenght = msgrcv(mq_id, response_msg, max_msg_size, response_msg->type, 0);
        if( response_lenght == -1)
        {
                printf("\e[31m[ERROR] Error occured while reciving response. Try again later. Aborted.\n");
                exit(3);
        }
        printf("[INFO] Reciving response message of size=%ld\n", response_lenght);
        if(response_lenght < max_msg_size){ response_msg->text[response_lenght-1] = '\0';}

	printf("[[Server answer]] More than 10 lines stored in files: \e[7m%s\n", response_msg->text);
	msgctl(mq_id, IPC_RMID, NULL);
}

