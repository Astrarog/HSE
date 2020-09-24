#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

size_t streamread(FILE * stream, char** dest)
{
	const size_t buf_size = 256;
	char buf[buf_size];
	size_t read_count;

	size_t data_size = buf_size;
	char* data = malloc(data_size);

	size_t total_lenght = 0;
    	while ((read_count = fread(buf, sizeof(char), sizeof(buf), stream)) != 0) 
    	{
		total_lenght += read_count;
	        if (total_lenght > data_size) 
		{   // double data capacity
	            data_size *= 2;
        	    data = realloc(data, data_size);
	        }
	        memmove( &(data[total_lenght - read_count]), buf, read_count);
   	 }
	*dest = data;
	return total_lenght;
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
