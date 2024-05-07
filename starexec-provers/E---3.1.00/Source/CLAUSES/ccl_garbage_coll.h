/*-----------------------------------------------------------------------

  File  : ccl_garbage_coll.h

  Author: Stephan Schulz (schulz@eprover.org)

  Contents

  High-level garbage collection (which needs clause - and
  formulasets). This is complemented by cte_garbage_coll.[ch] for the
  lower-level functions.

  Copyright 2010-2022 by the author.
  This code is released under the GNU General Public Licence and
  the GNU Lesser General Public License.
  See the file COPYING in the main E directory for details..
  Run "eprover -h" for contact information.

  Created: Sat Mar 20 09:26:51 CET 2010

-----------------------------------------------------------------------*/

#ifndef CCL_GARBAGE_COLL

#define CCL_GARBAGE_COLL


#include <ccl_formulasets.h>
#include <ccl_clausesets.h>


/*---------------------------------------------------------------------*/
/*                    Data type declarations                           */
/*---------------------------------------------------------------------*/


/*---------------------------------------------------------------------*/
/*                Exported Functions and Variables                     */
/*---------------------------------------------------------------------*/

long TBGCCollect(TB_p bank);

#endif

/*---------------------------------------------------------------------*/
/*                        End of File                                  */
/*---------------------------------------------------------------------*/
