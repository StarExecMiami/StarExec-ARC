/* Otter 3.3
 *
 * William McCune
 * Mathematics and Computer Science Division
 * Argonne National Laboratory
 * Argonne, IL  60439
 * U.S.A.
 *
 * E-mail: mccune@mcs.anl.gov
 * Web:    http://www.mcs.anl.gov/~mccune
 *         http://www.mcs.anl.gov/AR/otter
 */

#define OTTER_VERSION "3.3"
#define VERSION_DATE  "August 2003"

#define IN_MAIN  /* so that global vars in header.h will not be external */
#include "header.h"

/**/ int main(int argc, char **argv)
{
  struct clause *giv_cl;
  int errors, status, level, first_of_next_level;
  char *str;
  FILE *xlog_fp = NULL;
    
  non_portable_init(argc, argv);
  init();
  
  read_all_input(argc, argv);

    exit(0);

}  /* main */
