#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data_structures.h"
//-----------------------------------------------------------------------------
// RETURNS -1 if file fails vreification.
 
//-----------------------------------------------------------------------------
// RETURNS 1 if file exists, 0 otherwise.
int file_exists (char *file, char *path)
{
        struct stat *stat_buff;
        if (existat(file, stat_buff) == -1)
                return 0;
        else
                return 1;
}
//-----------------------------------------------------------------------------
void sig_handler (int sig)
{
     printf("ALERT: Terminating signal %d has been received. \n", sig);
}
//-----------------------------------------------------------------------------
// Input piped from STDIN
int main (int argc, char *argv[])
{ 
        String data;
        String path;
        String file_path;
        while (fgets(data, KBYTE, stdin) != NULL) {
                data[strlen(data) - 1] = '\0';
                if (strncmp(data, "dir::", 5) == 0) {
                        strcpy(path, &(data[5]));
                        printf("\n%% Verifying files in directory: %s \n", 
                               path);
                        continue;
                }
                sprintf(file_path, "%s/%s/SPASS---2.1.s", path, data);
                if (file_exists(file_path, path) == 0) 
                        printf("ERROR: FILE %s doesn't exist. \n", file_path);
                else
                        printf ("exists \n");
        }
        return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------
