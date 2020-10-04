#include <stdio.h>
#include <sys/sem.h>
#define PROJ_ID 77581  

//512K
#define MY_SHM_SIZE 524288
size_t streamread(FILE * stream, char** dest);

char* concat(const char *s1, const char *s2);

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};


const struct sembuf wait_for_ctl[1] = {{0,-1,0}};
const struct sembuf give_resourses_to_server[1] = {{0,1,0}};

const struct sembuf wait_for_client[1] = {{1,-1,0}};
const struct sembuf client_request[2] = {{2,1,0}, {1,1,0}};

const struct sembuf give_to_read[1] = {{2,-1,0}};
const struct sembuf wait_for_read[1] = {{2,0,0}};



