#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "data_structures.h"
//-----------------------------------------------------------------------------
int
main (void)
{ /* Input taken from STDIN. */
  FILE *chk_pr;
  String data;
  String path;
  String filename;
  String chk_cmd;
  String chk_str;
  String unix_command;

  while (fgets (data, KBYTE, stdin) != NULL) {
    data[strlen(data) - 1] = '\0';
    if (strncmp (data, "dir::", 5) == 0) {
      strcpy (path, &(data[5]));
      printf ("\n%% Verifying files in directory: %s \n", path);
    }
    else {
      sprintf (filename, "%s/%s/SPASS---2.1.s", path, data);
      sprintf (chk_cmd, "find %s", filename);
      if ((chk_pr = popen(chk_cmd, "r")) == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
      }
      if (fgets (chk_str, KBYTE, chk_pr) == NULL) {
        pclose (chk_pr);
        printf ("File doesn't exist, moving on to next verification. \n");
        continue;
      } 
      pclose (chk_pr);     
      printf ("%% Verifying file: %s \n", data);
      sprintf (unix_command, 
               "dvdv -p %s -i -v -t 5 > results/%s.res", 
	       filename, data);
      printf (unix_command);
      printf("\n");
      if (system (unix_command) == -1)
	printf ("DV ERROR: Unspecified system error occurred. \n");
      else {
	sprintf (unix_command, "grep Result: %s", filename);
	system (unix_command);
      }
    }
  }
  printf ("\n%% VERIFICATION COMPLETED SUCCESSFULLY. \n");
  return EXIT_SUCCESS;
}
//-----------------------------------------------------------------------------
