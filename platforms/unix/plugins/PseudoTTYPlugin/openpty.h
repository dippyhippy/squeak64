/* openpty.h -- provides openpty() and login_tty()
 * 
 * @copyright@
 * 
 * Author: Ian.Piumarta@inria.fr
 * 
 * Last edited: 2003-09-03 17:42:22 by piumarta on emilia.inria.fr
 */

#if defined(HAVE_OPENPTY)

# include <utmp.h>		/* login_tty() */
# if defined(HAVE_PTY_H)
#   include <pty.h>		/* openpty() */
# elif defined(HAVE_UTIL_H)
#   include <util.h>		/* openpty() */
# elif defined(HAVE_LIBUTIL_H)
#   include <libutil.h>		/* openpty() on FreeBSD */
# else
#   error: cannot find headers for openpty()
# endif

#else /* !HAVE_OPENPTY */

# if defined(HAVE_UNIX98_PTYS)

    /* we'll just roll our own, it ain't hard */

#   include <stdlib.h>	/* ptsname(), grantpt(), unlockpt() */
#   include <unistd.h>
#   include <string.h>
#   include <fcntl.h>
#   if defined(HAVE_STROPTS_H)
#     include <stropts.h>
#     include <sys/ioctl.h>
#   endif

static int openpty(int *ptmp, int *ptsp, char *ttyp, void *termiosp, void *winp)
{
  int   ptm= -1, pts= -1;
  char *tty= 0;
  if ((ptm= open("/dev/ptmx", O_RDWR, 0)) == -1) return -1;
  tty= ptsname(ptm);
  if (grantpt(ptm)  == -1) return -1;
  if (unlockpt(ptm) == -1) return -1;
  if ((pts= open(tty, O_RDWR, 0)) == -1) return -1;
  *ptmp= ptm;
  *ptsp= pts;
  strcpy(ttyp, tty);
  return 0;
}

static int login_tty(int pts)
{
#if defined(HAVE_STROPTS_H)
  /* push a terminal onto stream head */
  if (ioctl(pts, I_PUSH, "ptem")   == -1) return -1;
  if (ioctl(pts, I_PUSH, "ldterm") == -1) return -1;
#endif
  setsid();
#if defined(TIOCSCTTY)
  ioctl(pts, TIOCSCTTY, 0);
#endif
  dup2(pts, 0);
  dup2(pts, 1);
  dup2(pts, 2);
  if (pts > 2) close(pts);
  return 0;
}

# else /* !HAVE_UNIX98_PTYS */
#   error: cannot open a pty -- this plugin will not work
# endif
#endif /* !HAVE_OPENPTY */
