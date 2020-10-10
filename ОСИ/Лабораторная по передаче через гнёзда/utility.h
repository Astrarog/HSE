#include <stdio.h>

#define UNIX_PATH_MAX 108 
#define PROJ_ID 4926

size_t streamread(FILE * stream, char** dest);

char* concat(const char *s1, const char *s2);

struct my_msgbuf
{
        long type;
        char text[];
};

const char server_name[UNIX_PATH_MAX] = "./sock_lab_server";
const char client_name[UNIX_PATH_MAX] = "./sock_lab_client";
