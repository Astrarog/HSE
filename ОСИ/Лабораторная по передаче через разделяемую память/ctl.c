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
        while( (sem_id = semget(ipckey, 0, 0)) == -1)
        {
		sleep(1);
        }
	
	printf("Semaphore set found. ID: %d\n", sem_id);
        int sh_id;
        while( (sh_id = shmget(ipckey, 0, 0)) == -1)
        {
		sleep(1);
        }
        char* sh_addr;
        sh_addr = (char *) shmat(sh_id, NULL, 0);
        if( sh_addr == (char *) -1)
        {
                perror("\e[31m[ERROR] Error while attaching shared memory. Try Again.\n");
                exit(3);
        }

	printf("Shared memory found and attached. ID: %d\n", sh_id);
		
	if(semop(sem_id, wait_for_client, 1) == -1)
        {       
                perror("\e[31m[ERROR] Error in waiting for resources. Aborted.\n");
                exit(4);
        }

	FILE* stream = popen("ls | tr '\n' ' '", "r");

	char* data;
	size_t lenght = streamread(stream, &data);
	
	pclose(stream);

	strncpy(sh_addr, data, lenght);
	sh_addr[lenght] = '\0';   	
	printf("Data was send. Waiting for the answer.\n");
	if(semop(sem_id, give_resourses_to_server, 1)==-1)
	{
		perror("\e[31m[ERROR] Error while free for resources. Aborted.\n");
                exit(5);	
	}
	if(semop(sem_id, wait_for_read, 1) == -1)
        {       
                perror("\e[31m[ERROR] Error in waiting for resources. Aborted.\n");
                exit(4);
        }

	printf("==============\n"
		"RECIEVED DATA:\n"
		"==============\n"
		"%s\n"
		"==============\n", sh_addr);
	

	struct shmid_ds stat;
        shmctl(sh_id, IPC_STAT, &stat);
        time_t last_att_time = stat.shm_atime; 

	printf("Last attached time \e[7m%ld\n", last_att_time);

	semctl(sem_id, 0, IPC_RMID);
	printf("\e[7m\e[38;5;82m[INFO] Semaphores set removed.\n");
	shmctl(sh_id, IPC_RMID, NULL);
	shmdt(sh_addr);
	printf("\e[7m\e[38;5;82m[INFO] Shared memory removed.\n");
	printf("\e[7m\e[38;5;82m[INFO] Job's done aborting...\n");
}

