#include <stdio.h>      //for printf, scanf
#include <stdlib.h>     //for malloc, exit
#include <string.h>     //for memset, stings in c
#include <math.h>       //for ceil, log10
#include <sys/types.h>  //for any Uxnix-like system
#include <unistd.h>     //for fork, pipe
#include <sys/wait.h>   //for wait
#include <signal.h>     //for signals
#include <setjmp.h>     //for jumps

#define FILENAME_SIZE 256
#define SAVE_MASK 1

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void get_file_name(char* filename){
    while (1){
        memset(filename, 0, FILENAME_SIZE+1);   // empty filename
        printf("Enter filename: ");
        read(0, filename, FILENAME_SIZE);
        if ((strlen(filename) > 0) && (filename[strlen (filename) - 1] == '\n'))
        {
            filename[strlen (filename) - 1] = '\0';
        }

        if (access(filename, F_OK)!=0) // checks that file filename exists
        {
            printf("File \"%s\" not found\n", filename);
            return;
        } else {
            return;
        }
    }
}



int count_signals_taken = 0;
char user_input[FILENAME_SIZE+1];
sigjmp_buf buf;

void process_signal ()
{
    ++count_signals_taken;
    if (count_signals_taken % 5 == 0)
    {
        if (access(user_input, F_OK)!=0) // checks that file filename exists
        {
            printf("File \"%s\" not found\n", user_input);

        } else {
            system(concat(concat(concat("echo There are `wc -c ", user_input), " | cut -d ' ' -f 1` symbols in file "), user_input));
        }

    }
    siglongjmp(buf, 1);
    return;
}

int main()
{
    sigset_t my_set;
    sigemptyset(&my_set);
    sigaddset(&my_set, SIGINT);

    struct sigaction my_sig;
    my_sig.sa_handler = process_signal;
    my_sig.sa_mask = my_set;
    my_sig.sa_flags = 0 ;

    sigaction(SIGINT, &my_sig, NULL);

    int p[2];
    pipe(p);

    if(fork()==0)
    {
        close(1);
        dup(p[1]);
        close(p[1]);
        system("wc -c *| tr -s ' ' ");
        exit(0);
    }
    else
    {
        wait(NULL);

        if(sigsetjmp(buf, SAVE_MASK))
        {
            printf("\nThere was an interruption, please repeat the filename.\n");
        }
        get_file_name(user_input);

        dup(0);
        close(0);
        dup2(p[0], 0);

        system(concat(concat("echo File consists of `grep ", user_input), " | cut -d ' ' -f 2` blocks"));
        system("echo Total directory size: `grep total | cut -d ' ' -f 1` blocks");

        close(0);
        dup(5);
        close(5);

    }
    return 0;
}
