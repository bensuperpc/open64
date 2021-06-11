/* Generated by gen_s_set  */
/* Generated from ../../common/util/x_set_interface Rev 1.1.1.1 */


/* ====================================================================
 * ====================================================================
 *
 *  This package implements sets of TN*'s.  These can be
 *  manipulated with a fairly complete repertoire of set functions.
 *  The sets are represented with bit strings for efficiency of both
 *  space and run time.  The vector that represents these sets is
 *  grown as necessary to accommodate the results of the various
 *  operations.  In spite of this, the client of the package retains
 *  control over storage allocation by providing memory allocation
 *  pools (MEM_POOLs).  The representations are never automatically
 *  trimmed, so that the representation of any given bit set will be
 *  large enough to hold the element with the greatest number that it
 *  ever held.
 *
 *
 *  Destructive Operations Conventions
 *  ==================================
 *
 *  This package contains a number of functions that implement
 *  destructive operations.  The purpose of these operations is
 *  efficiency both of the operations themselves and of memory usage.
 *  Some of the destructive operations may still need to expand the
 *  storage allocated to the set.  When this happens, the set may need
 *  to be copied.  Thus you can not count on the side effects of these
 *  operations, only on the correctness of their returned values.
 *  Functions in this package that can have a destructive effect on a
 *  one of their arguments always have a name that ends with the
 *  letter D.  Only the first argument of such functions is ever
 *  destructively modified.  All destructive operations return a
 *  pointer to the set.  In the normal case this will be the same as
 *  their first argument, but sometimes the set will have to be copied
 *  in order to perform the operation.  So the client should not rely
 *  on the side effects of destructive operations.  Instead, one
 *  should use their returned values.  For now, destructive operations
 *  only expand storage, and never shrink it.
 *
 *
 *  Storage Allocation
 *  ==================
 *
 *  The client of this package has full control over storage
 *  allocation for GTN_SET's.  This is achieved by passing storage
 *  allocation pools (MEM_POOLs) to the functions that may need to use
 *  them.  All storage allocated for a set is "flat", which is to say
 *  that from the point of view of storage allocation, each BS may be
 *  seen as a single array containing no pointers to additional
 *  storage.  This allows the client to free this storage directly if
 *  its allocation pool supports freeing (See the discussion under
 *  BS_Create below).
 *
 *
 *  Types
 *  =====
 *
 *
 *  TYPE struct gtn_set GTN_SET
 *
 *      This is the client visible type of a set of TN* objects.
 *      It has no client visible fields.
 *
 *
 *  TYPE TN*
 *
 *      This is the type of an element of a GTN_SET.  It can be mapped
 *      to a numeric type with the range 0..BS_ELT_MAX by the function
 *      GTN_UNIVERSE_TN_int.  Numbers can be mapped to TN*'s with the
 *      function GTN_UNIVERSE_INT_tn.  It is a requirement of this mapping that
 *      GTN_UNIVERSE_INT_tn(-1) == GTN_SET_CHOOSE_FAILURE.
 *
 *
 *  Creation, Clearing, and Freeing
 *  ===============================
 *
 *
 *  GTN_SET *GTN_SET_Create(
 *    size_t    size,
 *    MEM_POOL *pool
 *  )
 *
 *      Creates and returns a new GTN_SET capable of holding (without
 *      expansion) any set of TN*'s with GTN_UNIVERSE_TN_int values in
 *      the range 0 through size - 1.  'Size' must be nonnegative or
 *      an error is caused.  The newly created GTN_SET is
 *      uninitialized, and may contain any of the possible sets.
 *      'Pool' is used to allocate the space for the set.  Storage for
 *      the space is "flat", that is the set is allocated as a single
 *      array and contains no pointers to any additionally allocated
 *      memory.  The client is thus free to free the GTN_SET directly
 *      (if 'pool' supports this.)  (the allocated size may be
 *      obtained from GTN_SET_AllocSize).
 *
 *
 *  size_t GTN_SET_Size_Alloc_Size(
 *    size_t    size
 *  )
 *
 *      Returns the number of bytes which would be required to
 *      allocate a set of 'size' size, i.e., the minimum number of
 *      bytes required to hold a set containing the elements that map
 *      to 0 through size - 1.
 *
 *
 *  size_t GTN_SET_Alloc_Size(
 *    GTN_SET *set
 *  )
 *
 *      Returns the number of bytes used to allocate the 'set'.
 *
 *
 *  GTN_SET *GTN_SET_ClearD(
 *    GTN_SET *set
 *  )
 *
 *      Destructive clear operation.  After this 'set' will be empty.
 *      However, this does not change the allocated size of the set
 *      (it will still be able to contain the same members that it
 *      could before it was cleared without expansion.)
 *
 *
 *  GTN_SET *GTN_SET_Create_Empty(
 *    size_t    size,
 *    MEM_POOL *pool
 *  )
 *
 *      Create an empty set large enough to hold the TN* whose
 *      GTN_UNIVERSE_TN_int value is 'size' - 1 without expansion.  Equivalent
 *      to GTN_SET_ClearD( GTN_SET_Create( size ), pool )
 *
 *
 *  GTN_SET *GTN_SET_Range(
 *    BS_ELT      low,
 *    BS_ELT      high,
 *    MEM_POOL   *pool
 *  )
 *  GTN_SET *GTN_SET_RangeD(
 *    GTN_SET     *set,
 *    BS_ELT      low,
 *    BS_ELT      high,
 *    MEM_POOL   *pool
 *  )
 *
 *      Returns a set whose members are the GTN_UNIVERSE_INT_tn values of the
 *      numbers 'low' ... 'high'.  Both 'low' and the size of the
 *      range must be nonnegative or an error is caused.  I.e., 'low'
 *      >= 0 and ('high' - 'low' + 1) >= 0.  Note that 'high' may be
 *      -1 if 'low' is 0.
 *
 *
 *  GTN_SET *GTN_SET_Singleton(
 *    TN* element,
 *    MEM_POOL   *pool
 *  )
 *  GTN_SET *GTN_SET_SingletonD(
 *    GTN_SET     *set,
 *    TN* element,
 *    MEM_POOL   *pool
 *  )
 *
 *      Returns a set with 'element' as its sole member.
 *
 *
 *  GTN_SET *GTN_SET_Universe(
 *    size_t    size,
 *    MEM_POOL *pool
 *  )
 *  GTN_SET *GTN_SET_UniverseD(
 *    GTN_SET   *set,
 *    size_t    size,
 *    MEM_POOL *pool
 *  )
 *
 *      Returns a set containing the GTN_UNIVERSE_INT_tn values of the numbers
 *      0...'size' - 1.  'Size' must be nonnegative or an error is
 *      caused.
 *
 *
 *
 *  Copying
 *  =======
 *
 *
 *  GTN_SET *GTN_SET_Copy(
 *    GTN_SET   *set,
 *    MEM_POOL *pool
 *  )
 *  GTN_SET *GTN_SET_CopyD(
 *    GTN_SET   *set1,
 *    GTN_SET   *set2,
 *    MEM_POOL *pool
 *  )
 *
 *      Returns an exact copy of set.  Note that for BS_CopyD, if
 *      storage is allocated it will be the same as the storage
 *      actually allocated to set2, regardless of the current size of
 *      set2.  Thus the following sequence:
 *
 *          GTN_SET *set1, set2;
 *          set1 = GTN_SET_Create( 32, pool );
 *          set2 = GTN_SET_Create( 1024, pool );
 *          set2 = GTN_SET_ClearD( set2 );
 *          set1 = GTN_SET_CopyD( set1, set2, pool );
 *
 *      will result in set1 being grown to be large enough to contain
 *      the TN* whose GTN_UNIVERSE_TN_int value is 1023, even though it
 *      will be empty.
 *
 *
 *  Set Operations
 *  ==============
 *
 *
 *  TN* GTN_SET_Choose(
 *    GTN_SET *set
 *  )
 *
 *      Returns some element of 'set', if 'set' is nonempty.  Else
 *      returns GTN_SET_CHOOSE_FAILURE.  In fact, this is defined so
 *      that it always returns the least element of the set.
 *
 *
 *  TN* GTN_SET_Choose_Next(
 *    GTN_SET     *set,
 *    TN* x
 *  )
 *
 *      Returns the "next" element of 'set', starting after 'x', if
 *	'set' is nonempty.  Else returns GTN_SET_CHOOSE_FAILURE.
 *	This is used for looping over the elements of a set.
 *
 *
 *  TN* GTN_SET_Choose_Range(
 *    GTN_SET   *set,
 *    BS_ELT    low,
 *    BS_ELT    high
 *  )
 *
 *      Returns some element of 'set' whose GTN_UNIVERSE_TN_int value is in the
 *      range low..high if there is one.  Else returns
 *      GTN_SET_CHOOSE_FAILURE.  Both 'low' and the size of the range
 *	must be nonnegative or an error is caused.  I.e., 'low' >= 0 and
 *      ('high' - 'low' + 1) >= 0.  Note that 'high' may be -1 if
 *      'low' is 0.  As with the _Choose function, always returns the
 *      last element of the set that's in range.
 *
 *
 *  CONST TN* GTN_SET_CHOOSE_FAILURE
 *
 *      A special value that GTN_SET_Choose and GTN_SET_ChooseRange
 *      return when they are unable to choose an element.
 *
 *
 *  GTN_SET *GTN_SET_Difference(
 *    GTN_SET   *set1,
 *    GTN_SET   *set2,
 *    MEM_POOL *pool
 *  )
 *  GTN_SET *GTN_SET_DifferenceD(
 *    GTN_SET *set1,
 *    GTN_SET *set2
 *  )
 *
 *      Returns { x : member( x, 'set1' ) & ~ member( x, 'set2' ) }.
 *
 *
 *  GTN_SET *GTN_SET_Difference1(
 *    GTN_SET     *set,
 *    TN* x,
 *    MEM_POOL   *pool
 *  )
 *  GTN_SET *GTN_SET_Difference1D(
 *    GTN_SET     *set,
 *    TN* x
 *  )
 *
 *      Returns { y : member( y , set ) & ~ ( y = x ) }.  X must be
 *      nonnegative or an error is caused.
 *
 *
 *  GTN_SET *GTN_SET_Intersection(
 *    GTN_SET   *set1,
 *    GTN_SET   *set2,
 *    MEM_POOL *pool
 *  )
 *  GTN_SET *GTN_SET_IntersectionD(
 *    GTN_SET *set1,
 *    GTN_SET *set2
 *  )
 *
 *      Returns the intersection of 'set1' and 'set2'.
 *
 *
 *  size_t GTN_SET_Size(
 *    GTN_SET *set
 *  )
 *
 *
 *  GTN_SET *GTN_SET_Union(
 *    GTN_SET   *set1,
 *    GTN_SET   *set2,
 *    MEM_POOL *pool
 *  )
 *  GTN_SET *GTN_SET_UnionD(
 *    GTN_SET   *set1,
 *    GTN_SET   *set2,
 *    MEM_POOL *pool
 *  )
 *
 *      Returns the union of set1 and set2.
 *
 *
 *  GTN_SET *GTN_SET_Union1(
 *    GTN_SET     *set,
 *    TN* x,
 *    MEM_POOL   *pool
 *  )
 *  GTN_SET *GTN_SET_Union1D(
 *    GTN_SET     *set,
 *    TN* x,
 *    MEM_POOL   *pool
 *  )
 *
 *      Returns set union { x }.  X must be nonnegative or an error is
 *      caused.
 *
 *
 *  GTN_SET *GTN_SET_UnionD_Intersection(
 *      GTN_SET    *set1,
 *      GTN_SET    *set2,
 *      GTN_SET    *set3,
 *      MEM_POOL   *pool
 *  )
 *
 *      Returns set1 | (set2 & set3).
 *      
 *
 *  Testing Sets
 *  ============
 *
 *
 *  BOOL GTN_SET_ContainsP(
 *    GTN_SET *set1,
 *    GTN_SET *set2
 *  )
 *
 *      Returns TRUE iff every element of 'set2' is in 'set1'.  Else
 *      FALSE.
 *
 *
 *  BOOL GTN_SET_EmptyP(
 *    GTN_SET *set
 *  )
 *
 *      Returns TRUE iff 'set' is empty.  Else FALSE.
 *
 *
 *  BOOL GTN_SET_EqualP(
 *    GTN_SET *set1,
 *    GTN_SET *set2
 *  )
 *
 *      Returns TRUE iff 'set1' has exactly the same members as
 *      'set2'.  Else FALSE.
 *
 *
 *  BOOL GTN_SET_IntersectsP(
 *    GTN_SET *set1,
 *    GTN_SET *set2
 *  )
 *
 *      Returns TRUE iff 'set1' and 'set2' have at least one member in
 *      common.  Else FALSE.
 *
 *
 *  BOOL GTN_SET_MemberP(
 *    GTN_SET     *set,
 *    TN* x
 *  )
 * 
 *      Returns TRUE iff 'x' is a member of 'set'.  Else FALSE.  'X'
 *      must be nonnegative or an error is caused.
 *
 *
 *
 *  Looping Over Members
 *  ====================
 *
 *
 *  This is done using GTN_SET_Choose and GTN_SET_Choose_Next.  Here is an
 *  example:
 *
 *	TN* x;
 *
 *	for ( x = GTN_SET_Choose( set );
 *	      x != GTN_SET_CHOOSE_FAILURE;
 *            x = GTN_SET_Choose_Next( set, x )
 *      ) {
 *        x is a member of the set
 *      }
 *
 *
 *  FOR_ALL_GTN_SET_members(set,x)
 *
 *      This macro can be used instead of the above 'for' loop. It expands
 *      into the same code.
 *
 *  Handling Intersections Effeciently
 *  ===================================
 *
 *
 *  Often, once wants to perform operations on the intersection of two
 *  sets without having to create the intersection.  This can be thought
 *  of as an "operation with a mask".  Anyway, a set of functions is
 *  provided to support this:
 *
 *
 *  BOOL GTN_SET_Intersection_MemberP(
 *    GTN_SET     *set1,
 *    GTN_SET     *set2,
 *    TN* x
 *  )
 *
 *      Returns TRUE iff 'x' is a member of the intersection of 'set1' and
 *      'set2' .  Else FALSE.  'X' must be nonnegative or an error is
 *      caused.
 *
 *
 *  TN* GTN_SET_Intersection_Choose(
 *    GTN_SET *set1,
 *    GTN_SET *set2
 *  )
 *
 *      Returns some element of of the intersection of 'set1' and 'set2',
 *      if the intersection is nonempty.  Else returns
 *      GTN_SET_CHOOSE_FAILURE.  In fact, this is defined so that it always
 *      returns the least element of the set.
 *
 *
 *  TN* GTN_SET_Intersection_Choose_Next(
 *    GTN_SET     *set1,
 *    GTN_SET     *set2,
 *    TN* x
 *  )
 *
 *      Returns the "next" element of the intersection of 'set1' and
 *      'set2', starting after 'x', if there is such a member.  Else
 *      returns GTN_SET_CHOOSE_FAILURE.  This is very useful for looping
 *	over the elements of a set.
 *
 *
 *  Printing Sets
 *  =============
 *
 *
 *  void GTN_SET_Print(
 *    GTN_SET *set,
 *    FILE   *f
 *  )
 *
 *      Prints 'set' on 'f'.  The type FILE is as defined in stdio.h.
 *
 * ====================================================================
 * ====================================================================
 */
/* Generated from ../../common/util/x_set_macro.h Rev 1.1.1.1 */

#ifndef GTN_SET_INCLUDED
#define GTN_SET_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif


#include "bitset.h"	/* our clients do not need to know about it */

typedef BS GTN_SET;


#define GTN_SET_CHOOSE_FAILURE ((TN*)BS_CHOOSE_FAILURE)

/* This macro will maps BS_ELTs to their corresponding base_type elements,
 * allowing for the possibility that GTN_UNIVERSE_INT_tn may not be defined on
 * BS_CHOOSE_FAILURE and maintaining the mapping from BS_CHOOSE_FAILURE to
 * GTN_SET_CHOOSE_FAILURE.   In other words:
 *
 *      GTN_SET_bs_elt_bas_type(x) ==>
 *              GTN_SET_CHOOSE_FAILURE if x == BS_CHOOSE_FAILURE
 *              GTN_UNIVERSE_INT_tn(x)          otherwise
 *
 * The complexity arises from the possibility that x may be an expression,
 * instead of a simple variable.  In that case we can't evaluate it twice,
 * since it may have side effects or be expensive to evaluate.  So we'll
 * assign it to a file scoped static and select the result depending on
 * whether it's a choose failure.  Not so great, huh?
 *
 * TODO: Allow an optional straightforward implementation for mappings that
 * map BS_CHOOSE_FAILURE to GTN_SET_CHOOSE_FAILURE.
 */
inline TN*
GTN_SET_bs_elt_base_type( BS_ELT x )
{
  if ( x == BS_CHOOSE_FAILURE )
    return GTN_SET_CHOOSE_FAILURE;
  else
    return GTN_UNIVERSE_INT_tn(x);
}


/* A subuniverse version as well. */

#define GTN_SET_Create BS_Create
#define GTN_SET_Size_Alloc_Size BS_Size_Alloc_Size
#define GTN_SET_Alloc_Size BS_Alloc_Size
#define GTN_SET_ClearD BS_ClearD
#define GTN_SET_Create_Empty BS_Create_Empty
#define GTN_SET_Range BS_Range
#define GTN_SET_RangeD BS_RangeD

#define GTN_SET_Singleton(e,p)                                           \
    BS_Singleton(GTN_UNIVERSE_TN_int(e),(p))


#define GTN_SET_SingletonD(s,e,p)                                        \
    BS_SingletonD((s),GTN_UNIVERSE_TN_int(e),(p))


#define GTN_SET_Universe BS_Universe
#define GTN_SET_UniverseD BS_UniverseD
#define GTN_SET_Copy BS_Copy
#define GTN_SET_CopyD BS_CopyD

#define GTN_SET_Choose(x)                                                \
  GTN_SET_bs_elt_base_type(BS_Choose(x))

#define GTN_SET_ChooseS(x,s)                                             \
  GTN_SET_bs_elt_base_type_sub(BS_Choose(x),s)

#define GTN_SET_Intersection_Choose(x1,x2)                               \
  GTN_SET_bs_elt_base_type(BS_Intersection_Choose((x1),(x2)))

#define GTN_SET_Intersection_ChooseS(x1,x2,s)                            \
  GTN_SET_bs_elt_base_type_sub(BS_Intersection_Choose((x1),(x2)),(s))

#define GTN_SET_Choose_Next(x,e)                                         \
  GTN_SET_bs_elt_base_type(BS_Choose_Next((x),GTN_UNIVERSE_TN_int(e)))


#define GTN_SET_Intersection_Choose_Next(x1,x2,e)                        \
  GTN_SET_bs_elt_base_type(BS_Intersection_Choose_Next((x1),(x2),GTN_UNIVERSE_TN_int(e)))


#define GTN_SET_Choose_Range(x,l,h)                                      \
  GTN_SET_bs_elt_base_type(BS_Choose_Range((x),(l),(h)))

#define GTN_SET_Choose_RangeS(x,l,h,s)                                   \
  GTN_SET_bs_elt_base_type_sub(BS_Choose_Range((x),(l),(h)),(s))

#define GTN_SET_Difference BS_Difference
#define GTN_SET_DifferenceD BS_DifferenceD

#define GTN_SET_Difference1(s,e,p)                                       \
    BS_Difference1(s,GTN_UNIVERSE_TN_int(e),(p))


#define GTN_SET_Difference1D(s,e)                                        \
    BS_Difference1D(s,GTN_UNIVERSE_TN_int(e))


#define GTN_SET_Intersection BS_Intersection
#define GTN_SET_IntersectionD BS_IntersectionD
#define GTN_SET_Size BS_Size
#define GTN_SET_Union BS_Union
#define GTN_SET_UnionD BS_UnionD

#define GTN_SET_Union1(s,x,p)                                            \
    BS_Union1((s),GTN_UNIVERSE_TN_int(x),(p))

#define GTN_SET_UnionD_Intersection(s1,s2,s3,p)                          \
    BS_UnionD_Intersection((s1),(s2),(s3),(p))


#define GTN_SET_Union1D(s,x,p)                                           \
    BS_Union1D((s),GTN_UNIVERSE_TN_int(x),(p))


#define GTN_SET_ContainsP BS_ContainsP
#define GTN_SET_EmptyP BS_EmptyP
#define GTN_SET_EqualP BS_EqualP
#define GTN_SET_IntersectsP BS_IntersectsP

#define GTN_SET_MemberP(set,x) BS_MemberP((set),GTN_UNIVERSE_TN_int(x))


#define GTN_SET_Intersection_MemberP(set1,set2,x)                        \
    BS_Intersection_MemberP((set1),(set2),GTN_UNIVERSE_TN_int(x))


#define GTN_SET_Print BS_Print

#define FOR_ALL_GTN_SET_members(set,x)	\
    for (x = GTN_SET_Choose(set);	\
	 x != GTN_SET_CHOOSE_FAILURE;	\
	 x = GTN_SET_Choose_Next(set,x))

#ifdef __cplusplus
}
#endif
#endif /* GTN_SET_INCLUDED */
