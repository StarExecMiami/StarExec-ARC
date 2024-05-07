#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data_structures.h"
//-----------------------------------------------------------------------------
// RETURNS -1 if file fails vreification.
int verify_file (char *file, char *path)
{
        FILE *dvdv;
        String unix_cmd;
        String unix_buff;
        int failed;
        printf("--- Verifying file: %s ---\n", file);
        failed = 0;
        memset(unix_cmd, '\0', KBYTE);
        sprintf(unix_cmd, "dvdv -p %s -i -v -k -t 5", path);
        if ((dvdv = popen(unix_cmd, "r")) == NULL) {
                perror("popen");
                exit(EXIT_FAILURE);
        }
        while (fgets(unix_buff, KBYTE, dvdv) != NULL) {
                printf("%s \n", unix_buff);
                if (strstr(unix_buff, "RESULT: Failure") != NULL) 
                        failed = -1;
        }
        pclose(dvdv);
        printf("--- File Verification Complete. ---\n");
        return failed;
}
//-----------------------------------------------------------------------------
// RETURNS 1 if file exists, 0 otherwise.
int file_exists (char *file, char *path)
{
        FILE *dvdv;
        String unix_cmd;
        sprintf(unix_cmd, "find %s", path);
        if ((dvdv = popen(unix_cmd, "r")) == NULL) {
                perror("popen");
                exit(EXIT_FAILURE);
        }
        if (fgets(unix_cmd, KBYTE, dvdv) == NULL) {
                pclose(dvdv);
                printf("File %s doesn't exist, moving on to next"
                       " verification. \n", file);
                return 0;
        }
        pclose(dvdv);
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
        FILE *results;
        String data;
        String path;
        String file_path;
        if (argc != 2) {
                printf("Please enter result file path. \n");
                exit(EXIT_FAILURE);
        }
        if ((results = fopen(argv[1], "w+")) == NULL) {
                perror("fopen");
                exit(EXIT_FAILURE);
        }
        if (signal(SIGINT, sig_handler)  ||
            signal(SIGQUIT, sig_handler) ||
            signal(SIGTERM, sig_handler) ||
            signal(SIGABRT, sig_handler)) {           
                fprintf(results,
                        "ALERT: Terminating signal has been received. \n");
                fclose(results);
                exit(EXIT_SUCCESS);
        }            
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
                        continue;
                if (verify_file(data, file_path) == -1)
                        fprintf(results, "%s: FAILED \n", data);
                else
                        fprintf(results, "%s: PASSED \n", data);
        }
        printf("\n%% VERIFICATION COMPLETED SUCCESSFULLY. \n");
        fprintf(results, "\n%% VERIFICATION COMPLETED SUCCESSFULLY. \n");
        fclose(results);
        return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------
