/* sqPlatformSpecific.h -- platform-specific modifications to sq.h
 * 
 * @copyright@
 * 
 * Author: ian.piumarta@inria.fr
 * 
 * Last edited: 2004-08-04 12:10:53 by piumarta on margaux.hpl.hp.com
 */

/* undefine clock macros (these are implemented as functions) */

#undef ioMSecs
#undef ioMicroMSecs
#undef ioLowResMSecs

#undef sqAllocateMemory
#undef sqGrowMemoryBy
#undef sqShrinkMemoryBy
#undef sqMemoryExtraBytesLeft

#include "sqMemoryAccess.h"

extern void *sqAllocateMemory(sqInt minHeapSize, sqInt desiredHeapSize);
extern sqInt sqGrowMemoryBy(sqInt oldLimit, sqInt delta);
extern sqInt sqShrinkMemoryBy(sqInt oldLimit, sqInt delta);
extern sqInt sqMemoryExtraBytesLeft(sqInt includingSwap);

#include <sys/types.h>

typedef off_t squeakFileOffsetType;

#undef	sqFilenameFromString
#undef	sqFilenameFromStringOpen
#define sqFilenameFromStringOpen sqFilenameFromString

extern void sqFilenameFromString(char *uxName, sqInt stNameIndex, int sqNameLength);

#include <unistd.h>

#undef	sqFTruncate
#define	sqFTruncate(f,o) ftruncate(fileno(f), o)
