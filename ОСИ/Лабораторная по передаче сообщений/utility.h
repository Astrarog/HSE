#include <stdio.h>
#define PROJ_ID 7945

size_t streamread(FILE * stream, char** dest);

char* concat(const char *s1, const char *s2);

struct my_msgbuf
{
        long type;
        char text[];
};

