/* sqUnixFileCopyPlugin.c -- fast file copy, preserving permissions
 * 
 * @copyright@
 * 
 * Author: ian.piumarta@inria.fr
 * 
 * Last edited: 2003-03-05 05:55:27 by piumarta on emilia.inria.fr
 * 
 * NOTE:
 *   This plugin is kind of ridiculous.  Nevertheless, after seeing what
 *   somebody (and I honestly have no idea who) decided would be a good
 *   implementation of this (it might still be on SourceForge if you're
 *   perverse wough to want to look at it) I was dumbfounded into writing
 *   a version that didn't open pipes to forked processes.  (Now I bet
 *   you can't possibly resist having a peek for the original. ;^p)
 *   (Besides, the original version had BUGS -- in a one page program. 8^o)
 * 
 * CAVEATS:
 *   - we should use mmap() only if the file is "large" (define that as
 *     you will), preferring a few block-sized read()/write()s otherwise
 *   - we should fall back onto the loop if mmap fails (we might simply
 *     have a file larger than available memory)
 *
 * BUGS:
 *   - some of the system calls should handle EAGAIN and/or EINTR (this
 *     will cause problems on Solaris)
 * (the following could be fixed if we had a real "config.h":)
 *   - we assume <unistd.h> but not everyone has this
 *   - we assume alloca() but not everyone has this (ANSI does not define it)
 *   - use of stat.st_blksize is extremely non-portable
 *
 * COMPILE:
 *   gcc -Wall -W -pedantic -o copy copy.c
 */

#include "sq.h"
#include "FileCopyPlugin.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif
#ifdef HAVE_MMAP
# include <sys/mman.h>
#endif


static int copy(char *from, char *to)
{
  int status= 1;        /* exit status: assume failure */
  int in;
  struct stat stat;
  if (((in= open(from, O_RDONLY)) < 0) || (fstat(in, &stat) != 0))
    return -1;
  {
    int out;
    if ((out= open(to, O_WRONLY | O_CREAT | O_TRUNC, stat.st_mode)) < 0)
      return -1;
    {
#    ifdef HAVE_MMAP
      static const char *_dev_zero= "/dev/zero";
      int zero;
      if ((zero= open(_dev_zero, O_RDWR)) >= 0)
	{
	  void *mem;
	  if (MAP_FAILED != (mem= mmap(0, stat.st_size, PROT_READ | PROT_WRITE,
				       MAP_PRIVATE, zero, 0)))
	    {
	      if ((  (read(in, mem, stat.st_size) != stat.st_size) >= 0)
		  && (write(out, mem, stat.st_size) != stat.st_size) >= 0)
		{
		  status= 0;      /* success */
		}
	      munmap(mem, stat.st_size);
	    }
	  close(zero);
	}
#    else /* !HAVE_MMAP */
      char *buf= (char *)alloca(stat.st_blksize);
      int n;
      while ((  ((n= read(in, buf, stat.st_blksize)) > 0))
	     && (n == write(out, buf, n)))
	;
      if (n == 0)
	status= 0;    /* success */
#    endif /* !HAVE_MMAP */
      close(out);
    }
    close(in);
  }
  return status;
}


int sqCopyFilesizetosize(char *srcName, int srcNameSize, char *dstName, int dstNameSize)
{
  int status= 0;
  char *from= (char *)alloca(srcNameSize + 1);
  char *to= (char *)alloca(dstNameSize + 1);
  sqFilenameFromString(from, (int)srcName, srcNameSize);
  sqFilenameFromString(to, (int)dstName, dstNameSize);
  return copy(from, to);
}
