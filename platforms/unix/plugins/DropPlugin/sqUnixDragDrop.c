/* sqUnixDragDrop.c -- support for drag and drop, for those UIs that have it
 * 
 * Author: Ian Piumarta <ian.piumarta@inria.fr>
 * 
 * @copyright@
 * 
 * Last edited: 2004-04-03 22:55:04 by piumarta on cartman.inria.fr
 */

/* Why on earth does this plugin exist at all?  Brain death strikes
 * again.  And why are half the functions never called from the VM?
 * Could it be that they are only there for certain ports (we'll
 * mention no names) in which the core support needs to grub around in
 * this plugin via ioLoadFunctionFromModule (and, putting disbelief
 * aside for a moment, maybe even VICE-VERSA)?  It seems to me that
 * truth is very definitely not beauty today.  Sigh...
 */


#include "sq.h"
#include "sqVirtualMachine.h"
#include "FilePlugin.h"
#include "DropPlugin.h"

#include <assert.h>


extern struct VirtualMachine  *interpreterProxy;
extern int		       uxDropFileCount;
extern char		     **uxDropFileNames;


int dropInit(void)	{ return 1; }
int dropShutdown(void)	{ return 1; }

char *dropRequestFileName(int dropIndex)	// in st coordinates
{
  if ((dropIndex > 0) && (dropIndex <= uxDropFileCount))
    {
      assert(uxDropFileNames);
      return uxDropFileNames[dropIndex - 1];
    }
  return 0;
}

int dropRequestFileHandle(int dropIndex)
{
  char *path= dropRequestFileName(dropIndex);
  if (path)
    {
      // you cannot be serious?
      int handle= instantiateClassindexableSize(classByteArray(), fileRecordSize());
      sqFileOpen((SQFile *)fileValueOf(handle), (int)path, strlen(path), 0);
      return handle;
    }  
  return interpreterProxy->nilObject();
}

int  sqSecFileAccessCallback(void *callback)		 { return 0; }
void sqSetNumberOfDropFiles(int numberOfFiles)		 { }
void sqSetFileInformation(int dropIndex, void *dropFile) { }
