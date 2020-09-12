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
	int mq_id = msgget(ipckey, IPC_CREAT | IPC_EXCL | 0666); // exec perm not used
	if (mq_id == -1)
	{
		printf("\e[31m[ERROR] Can't create MQ. Try another id. Aborted.\n");
		exit(1);
	}
	printf("[INFO] Message identifier is %d\n", mq_id);

	FILE* stream = popen("file * | awk -F ':' '/ASCII text/{ORS= \" \"; print $1;}'", "r");
	char* data;
       	size_t total_lenght = streamread(stream, &data);
	
	pclose(stream);
	
	struct my_msgbuf request_msg = {1, data};

	printf("[INFO] Sending request message of size=%ld\n", total_lenght);
	if(msgsnd(mq_id, &request_msg, total_lenght, 0) == -1)
	{
		printf("\e[31m[ERROR] Can't send request. Try again later. Aborted.\n");
		exit(2);
	}

	struct msqid_ds ds;
        msgctl(mq_id, IPC_STAT, &ds);
        size_t max_msg_size = ds.msg_qbytes;
        char* response_data = malloc(max_msg_size);

        struct my_msgbuf response_msg = {2, response_data};

        int response_lenght = msgrcv(mq_id, &response_msg, max_msg_size, response_msg.type, 0);
        if( response_lenght == -1)
        {
                printf("\e[31m[ERROR] Error occured while reciving response. Try again later. Aborted.\n");
                exit(3);
        }
        printf("[INFO] Reciving response message of size=%ld\n", response_lenght);
        if(response_lenght < max_msg_size){ request_msg.text[response_lenght-1] = '\0';}

	printf("[[Server answer]] More than 10 lines stored in files: %s\n", response_data);
	msgctl(mq_id, IPC_RMID, NULL);
}

