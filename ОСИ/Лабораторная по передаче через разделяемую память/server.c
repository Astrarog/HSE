#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include "utility.h"


int main(int argc, char* argv[])
{
	int id = PROJ_ID;
        if(argc > 1)
        {
                id = strtol(argv[1], NULL, 10);
        }

	key_t ipckey = ftok("/home/explorer/lab2/lab.cfg", id);

	int  sem_id;
	if( (sem_id = semget(ipckey, 3, IPC_CREAT|IPC_EXCL|0666)) == -1)
	{
                perror("\e[31m[ERROR] Error while creating semaphore set. Try nother ID.\n");
		exit(1);
	}

	union semun arg;
	arg.val = 0;
	semctl(sem_id, 0, SETVAL, arg);
	semctl(sem_id, 1, SETVAL, arg);
	semctl(sem_id, 2, SETVAL, arg);

	printf("Semaphore set created. ID: %d\n", sem_id);


	int sh_id;
	if( (sh_id = shmget(ipckey, MY_SHM_SIZE, IPC_CREAT|IPC_EXCL|0666)) == -1)
	{
                perror("\e[31m[ERROR] Error while creating shared memory. Try nother ID.\n");
		exit(2);
	}
	char* sh_addr;
	sh_addr = (char *) shmat(sh_id, NULL, 0);
	if( sh_addr == (char *) -1)
	{
                perror("\e[31m[ERROR] Error while attaching shared memory. Aborted.\n");
		exit(3);
	}

	printf("Shared memory created and attached. ID: %d\n", sh_id);	




	if(semop(sem_id, wait_for_ctl, 1) == -1)
	{
		perror("\e[31m[ERROR] Error in waiting for resources. Aborted.\n");
		exit(4);
	}

	
	printf("==============\n"
                "RECIEVED DATA:\n"
                "==============\n"
                "%s\n"
		"==============\n"
		"Sending the answer.\n", sh_addr);

	char* command = concat(concat("ls -l ", sh_addr), " | awk '{print $9, substr($1, 2, 3)}'");
	FILE* stream = popen(command, "r");
	
	char* data;
	size_t lenght = streamread(stream, &data);
		
	pclose(stream);
	
	strncpy(sh_addr, data, lenght);
        sh_addr[lenght] = '\0';

	if(semop(sem_id, give_to_read, 1)==-1)
        {
                perror("\e[31m[ERROR] Error while free for resources. Aborted.\n");
                exit(5);
        }
	shmdt(sh_addr);
	printf("\e[7m\e[38;5;82m[INFO] Job's done aborting...\n");

}

