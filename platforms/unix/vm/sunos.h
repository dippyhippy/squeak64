/* It's a mystery to me why they even bothered with /usr/include on SunOS
 * 
 * @copyright@
 */

/* Last edited: Wed Aug 16 06:21:25 2000 by piumarta (Ian Piumarta) on emilia
 */

#ifndef __squeak__sunos_h
#define __squeak__sunos_h

/* stdio.h */

extern int printf();

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

extern int fread();
extern int fclose();
extern int fseek();
extern int fprintf();

extern int sscanf();

extern int perror();

/* stdlib.h */

extern int strtol();

/* unistd.h */

extern int gethostname();
extern int gettimeofday();
extern int lstat();
extern int realpath();

/* string.h */

extern int bzero();
#include <memory.h>

/* netdb.h */

extern int h_errno;

/* dlfcn.h */

#define RTLD_NOW	1

/* time.h */

#include <sys/param.h>

#define CLK_TCK		HZ

extern int clock();
extern int time();

/* sys/types.h */

typedef int ssize_t;

/* sys/time.h */

extern int setitimer();

/* sys/socket.h */

extern int accept();
extern int bind();
extern int connect();
extern int getsockname();
extern int getpeername();
extern int listen();
extern int recvfrom();
extern int select();
extern int sendto();
extern int setsockopt();
extern int socket();

/* sys/ioctl.h */

extern int ioctl();

#endif /* !__squeak__sunos_h */
