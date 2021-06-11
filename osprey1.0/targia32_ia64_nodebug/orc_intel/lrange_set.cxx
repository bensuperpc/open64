/* Generated by gen_s_set $Revision: 1.1 $  */
#include "defs.h"
#include "gra_bb.h"
#include "gra_lrange.h"
#include "gra_lrange_subuniverse.h"
#include "mempool.h"
/* Generated from ../../common/util/x_set_macro.c Rev 1.1.1.1 */

#include "bitset.h"
#include "lrange_set.h"

LRANGE* LRANGE_SET_Choose_NextS(
  LRANGE_SET     *set,
  LRANGE* x,
  LRANGE_SET_SUBUNIVERSE *sub
)
{
  BS_ELT elt = BS_Choose_Next((BS*) set, LRANGE_Universe_ID_S(x,sub));
  if ( elt != BS_CHOOSE_FAILURE )
    return INT_LRANGE_Sub(elt,sub);
  else
    return LRANGE_SET_CHOOSE_FAILURE;
}

LRANGE* LRANGE_SET_Intersection_Choose_NextS(
  LRANGE_SET     *set1,
  LRANGE_SET     *set2,
  LRANGE* x,
  LRANGE_SET_SUBUNIVERSE *sub
)
{
  BS_ELT elt = BS_Intersection_Choose_Next((BS*) set1, (BS*) set2,
                                                      LRANGE_Universe_ID_S(x,sub));
  if ( elt != BS_CHOOSE_FAILURE )
    return INT_LRANGE_Sub(elt,sub);
  else
    return LRANGE_SET_CHOOSE_FAILURE;
}


