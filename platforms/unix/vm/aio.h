/* aio.h -- asynchronous file i/o
 *
 * @copyright@
 */

/* author: ian.piumarta@inria.fr
 *
 * last edited: 2002-12-02 20:20:13 by piumarta on calvin.inria.fr
 */

#ifndef __aio_h
#define __aio_h


#define AIO_X	(1<<0)	/* handle for exceptions */
#define AIO_R	(1<<1)	/* handle for read */
#define AIO_W	(1<<2)	/* handle for write */
#define AIO_SEQ	(1<<3)	/* call handlers sequentially  */
#define AIO_EXT	(1<<4)	/* external fd -- don't close on aio shutdown  */

#define AIO_RW	(AIO_R | AIO_W)
#define AIO_RX	(AIO_R | AIO_X)
#define AIO_WX	(AIO_W | AIO_X)

#define AIO_RWX	(AIO_R | AIO_W | AIO_X)

extern void aioInit(void);
extern void aioFini(void);

/* Initialise `fd' for handling by AIO.  `flags' can be 0 (aio takes
 * over the descriptor entirely and the application should not assume
 * anything about its subsequent behaviour) or AIO_EXT (aio will never
 * set NBIO on `fd' or close it on behalf of the client).
 */
extern void aioEnable(int fd, void *clientData, int flags);

/* Declare an interest in one or more events on `fd'.  `mask' can be
 * any combination in AIO_[R][W][X].  `handlerFn' will be called the
 * next time any event in `mask' arrives on `fd' and will receive
 * `fd', the original `clientData' (see aioEnable) and a `flag'
 * containing ONE of AIO_{R,W,X} indicating which event occurred.  In
 * the event that the same handler is set for multiple events (either
 * by setting more than one bit in `mask', or by calling aioHandle
 * several times with different `mask's) and several events arrive
 * simultaneously for the descriptor, then `handlerFn' is called
 * multiple times -- once for each event in `mask'.  The `handlerFn'
 * will NOT be called again for the same event until the client calls
 * aioHandle with an appropriate `mask' (the handled event is removed
 * implicitly from the current mask before calling `handlerFn') .
 * (Calls to aioHandle are cumulative: successive `mask's are ORed
 * with the mask currently in effect for `fd'.)
 */
typedef void (*aioHandler)(int fd, void *clientData, int flag);
extern void aioHandle(int fd, aioHandler handlerFn, int mask);

/* Suspend handling of the events in `mask' for `fd'.
 */
extern void aioSuspend(int fd, int mask);

/* Disable further AIO handling of `fd'.  The descriptor is reset to its
 * default state (w.r.t. NBIO, etc.) but is NOT closed.
 */
extern void aioDisable(int fd);

/* Sleep for at most `microSeconds'.  Any event(s) arriving for any
 * handled fd(s) will terminate the sleep, with the appropriate
 * handler(s) being called before returning.
 */
extern int aioPoll(int microSeconds);


#endif /* __aio_h */
