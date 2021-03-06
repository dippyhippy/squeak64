/****************************************************************************
*   PROJECT: Common include
*   FILE:    sq.h
*   CONTENT: 
*
*   AUTHOR:  
*   ADDRESS: 
*   EMAIL:   
*   RCSID:   $Id: sq.h,v 1.11 2003/11/13 16:18:54 nedkonz Exp $
*
*	11/12/03	nedkonz - float bug fix for gcc 3.3 optimization
*	05/20/03	tim - move browser related macros in front of
*			include of sqPlatformSpecific.h
*	02/26/03	tim change browser plugin support code
*	01/28/02	Tim add macro default for sqFilenameFromStringOpen
*		and sqFTruncate
*	01/22/2002 JMM change off_t to squeakOffsetFileType
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sqConfig.h"
#include "sqMemoryAccess.h"
#include "sqVirtualMachine.h"

#define true 1
#define false 0
#define null 0  /* using "null" because nil is predefined in Think C */

/* pluggable primitives macros */
/* Note: All pluggable primitives are defined as
	EXPORT(int) somePrimitive(void)
   If the platform requires special declaration modifiers
   the EXPORT macro can be redefined
*/
#define EXPORT(returnType) returnType

/* image save/restore macros */
/* Note: The image file save and restore code uses these macros; they
   can be redefined in sqPlatformSpecific.h if desired. These default
   versions are defined in terms of the ANSI Standard C libraries.
*/
#define sqImageFile FILE *
#define sqImageFileClose(f)                  fclose(f)
#define sqImageFileOpen(fileName, mode)      fopen(fileName, mode)
#define sqImageFilePosition(f)               ftell(f)
#define sqImageFileRead(ptr, sz, count, f)   fread(ptr, sz, count, f)
#define sqImageFileSeek(f, pos)              fseek(f, pos, SEEK_SET)
#define sqImageFileWrite(ptr, sz, count, f)  fwrite(ptr, sz, count, f)
#define sqImageFileStartLocation(fileRef, fileName, size)  0

/* platform-dependent macros for handling object memory */
/* Note: The grow/shrink macros assume that the object memory can be extended
   continuously at its prior end. The garbage collector cannot deal with 'holes'
   in the object memory so the support code needs to reserve the virtual maximum
   of pages that can be allocated beforehand. The amount of 'extra' memory should
   describe the amount of memory that can be allocated from the OS (including swap
   space if the flag is set to true) and must not exceed the prior reserved memory.
   (in other words: don't you dare to report more free space then you can actually allocate).
   The default implementation assumes a fixed size memory allocated at startup.
*/
#define sqAllocateMemory(minHeapSize, desiredHeapSize)   malloc(desiredHeapSize)
#define sqGrowMemoryBy(oldLimit, delta) oldLimit
#define sqShrinkMemoryBy(oldLimit, delta) oldLimit
#define sqMemoryExtraBytesLeft(includingSwap) 0

/* platform-dependent memory size adjustment macro */
/* Note: This macro can be redefined to allows platforms with a
   fixed application memory partition (notably, the Macintosh)
   to reserve extra C heap memory for special applications that need
   it (e.g., for a 3D graphics library). Since most platforms can
   extend their application memory partition at run time if needed,
   this macro is defined as a noop here and redefined if necessary
   in sqPlatformSpecific.h.
*/

#define reserveExtraCHeapBytes(origHeapSize, bytesToReserve) origHeapSize

/* platform-dependent millisecond clock macros */
/* Note: The Squeak VM uses three different clocks functions for
   timing. The primary one, ioMSecs(), is used to implement Delay
   and Time millisecondClockValue. The resolution of this clock
   determines the resolution of these basic timing functions. For
   doing real-time control of music and MIDI, a clock with resolution
   down to one millisecond is preferred, but a coarser clock (say,
   1/60th second) can be used in a pinch. The VM calls a different
   clock function, ioLowResMSecs(), in order to detect long-running
   primitives. This function must be inexpensive to call because when
   a Delay is active it is polled twice per primitive call. On several
   platforms (Mac, Win32), the high-resolution system clock used in
   ioMSecs() would incur enough overhead in this case to slow down the
   the VM significantly. Thus, a cheaper clock with low resolution is
   used to implement ioLowResMSecs() on these platforms. Finally, the
   function ioMicroMSecs() is used only to collect timing statistics
   for the garbage collector and other VM facilities. (The function
   name is meant to suggest that the function is based on a clock
   with microsecond accuracy, even though the times it returns are
   in units of milliseconds.) This clock must have enough precision to
   provide accurate timings, and normally isn't called frequently
   enough to slow down the VM. Thus, it can use a more expensive clock
   that ioMSecs(). By default, all three clock functions are defined
   here as macros based on the standard C library function clock().
   Any of these macros can be overridden in sqPlatformSpecific.h.
*/

sqInt ioMSecs(void);
sqInt ioLowResMSecs(void);
sqInt ioMicroMSecs(void);

#define ioMSecs()		((1000 * clock()) / CLOCKS_PER_SEC)
#define ioLowResMSecs()	((1000 * clock()) / CLOCKS_PER_SEC)
#define ioMicroMSecs()	((1000 * clock()) / CLOCKS_PER_SEC)

/* filename copy/transform macro. An opportunity to transform the filenames for
   platforms with strange needs, anda simple encapsulation for everyone else
*/
#define sqFilenameFromString(dst, src, num)	\
  do {						\
    int i;					\
    for (i= 0;  i < num;  ++i)			\
      (dst)[i]= (src)[i];			\
    dst[num]= '\0';				\
  } while(0)

/* macro needed to support MacOS-X file opening problems */
#define sqFilenameFromStringOpen(d,s,n) sqFilenameFromString(d,s,n)

/* macro to provide default null behaviour for ftruncate - a non-ansi call used
   in FilePlugin.
   Over ride in sqPlatformSpecific.h for each platform that implements a file
   truncate. 
*/
#define sqFTruncate(filenum, fileoffset) true

/* old browser plug-in support, maintained for a little while */
#if 1
void plugInForceTimeToReturn(void);
sqInt plugInInit(char *imageName);
sqInt plugInNotifyUser(char *msg);
void plugInSetStartTime(void);
sqInt plugInShutdown(void);
sqInt plugInTimeToReturn(void);
#endif
/* macros to support Mac browser plugin needs without ugly
 * code in Interpreter
 */
#define insufficientMemorySpecifiedError() error("Insufficient memory for this image")
#define insufficientMemoryAvailableError() error("Failed to allocate memory for the heap")
#define unableToReadImageError() error("Read failed or premature end of image file")
#define browserPluginReturnIfNeeded()
#define browserPluginInitialiseIfNeeded()

/* this include file may redefine earlier definitions and macros: */
#include "sqPlatformSpecific.h"

/* interpreter entry points */
void error(char *s);
sqInt checkedByteAt(sqInt byteAddress);
sqInt checkedByteAtput(sqInt byteAddress, sqInt byte);
sqInt checkedLongAt(sqInt byteAddress);
sqInt checkedLongAtput(sqInt byteAddress, sqInt a32BitInteger);
sqInt fullDisplayUpdate(void);
sqInt initializeInterpreter(sqInt bytesToShift);
sqInt interpret(void);
sqInt primitiveFail(void);
sqInt signalSemaphoreWithIndex(sqInt semaIndex);
sqInt success(sqInt);

/* display, mouse, keyboard, time i/o */
sqInt ioBeep(void);
sqInt ioExit(void);
sqInt ioForceDisplayUpdate(void);
sqInt ioFormPrint(sqInt bitsAddr, sqInt width, sqInt height, sqInt depth,
		 double hScale, double vScale, sqInt landscapeFlag);
sqInt ioSetFullScreen(sqInt fullScreen);
sqInt ioRelinquishProcessorForMicroseconds(sqInt microSeconds);
sqInt ioScreenSize(void);
sqInt ioScreenDepth(void);
sqInt ioSeconds(void);
sqInt ioSetCursor(sqInt cursorBitsIndex, sqInt offsetX, sqInt offsetY);
sqInt ioSetCursorWithMask(sqInt cursorBitsIndex, sqInt cursorMaskIndex, sqInt offsetX, sqInt offsetY);
sqInt ioShowDisplay(sqInt dispBitsIndex, sqInt width, sqInt height, sqInt depth,
		   sqInt affectedL, sqInt affectedR, sqInt affectedT, sqInt affectedB);
sqInt ioHasDisplayDepth(sqInt depth);
sqInt ioSetDisplayMode(sqInt width, sqInt height, sqInt depth, sqInt fullscreenFlag);

/* Power Management */

sqInt ioDisablePowerManager(sqInt disableIfNonZero);

/* User input recording I:
   In general, either set of input function can be supported,
   depending on the platform. This (first) set is state based
   and should be supported even on platforms that make use
   of the newer event driven API to support older images 
   without event support.
*/
sqInt ioGetButtonState(void);
sqInt ioGetKeystroke(void);
sqInt ioMousePoint(void);
sqInt ioPeekKeystroke(void);
/* Note: In an event driven architecture, ioProcessEvents is obsolete.
   It can be implemented as a no-op since the image will check for
   events in regular intervals. */
sqInt ioProcessEvents(void);


/* User input recording II:
   The following functions and definition can be used on
   platform supporting events directly.
*/
/* types of events */
#define EventTypeNone 0
#define EventTypeMouse 1
#define EventTypeKeyboard 2
#define EventTypeDragDropFiles 3

/* keypress state for keyboard events */
#define EventKeyChar 0
#define EventKeyDown 1
#define EventKeyUp 2

/* button definitions */
#define RedButtonBit 4
#define YellowButtonBit 2
#define BlueButtonBit 1

/* modifier definitions */
#define ShiftKeyBit 1
#define CtrlKeyBit 2
#define OptionKeyBit 4
#define CommandKeyBit 8

/* generic input event definition */
typedef struct sqInputEvent {
	int type; /* type of event; either one of EventTypeXXX */
	unsigned int timeStamp; /* time stamp */
     /* the interpretation of the following fields depend on the type of the event */
	int unused1;
	int unused2;
	int unused3;
	int unused4;
	int unused5;
	int unused6;
} sqInputEvent;

/* mouse input event definition */
typedef struct sqMouseEvent {
	int type; /* EventTypeMouse */
	unsigned int timeStamp; /* time stamp */
	int x; /* mouse position x */
	int y; /* mouse position y */
	int buttons; /* combination of xxxButtonBit */
	int modifiers; /* combination of xxxKeyBit */
	int reserved1; /* reserved for future use */
	int reserved2; /* reserved for future use */
} sqMouseEvent;

/* keyboard input event definition */
typedef struct sqKeyboardEvent {
	int type; /* EventTypeKeyboard */
	unsigned int timeStamp; /* time stamp */
	int charCode; /* character code in Mac Roman encoding */
	int pressCode; /* press code; any of EventKeyXXX */
	int modifiers; /* combination of xxxKeyBit */
	int reserved1; /* reserved for future use */
	int reserved2; /* reserved for future use */
	int reserved3; /* reserved for future use */
} sqKeyboardEvent;

/* drop files event definition:
   DragEnter - drag operation from OS entered Squeak window
   DragMove  - drag operation from OS moved within Squeak window
   DragLeave - drag operation from OS left Squeak window
   DragDrop  - drag operation dropped contents onto Squeak.
*/
#define DragEnter 1
#define DragMove  2
#define DragLeave 3
#define DragDrop  4
typedef struct sqDragDropFilesEvent {
	int type; /* EventTypeDropFiles */
	unsigned int timeStamp; /* time stamp */
	int dragType; /* one of the DragXXX constants */
	int x; /* mouse position x */
	int y; /* mouse position y */
	int modifiers; /* combination of xxxKeyBit */
	int numFiles; /* number of files in transaction */
	int reserved1; /* reserved for future use */
} sqDragDropFilesEvent;


/* set an asynchronous input semaphore index for events */
sqInt ioSetInputSemaphore(sqInt semaIndex);
/* retrieve the next input event from the OS */
sqInt ioGetNextEvent(sqInputEvent *evt);

/* image file and VM path names */
extern char imageName[];
sqInt imageNameGetLength(sqInt sqImageNameIndex, sqInt length);
sqInt imageNamePutLength(sqInt sqImageNameIndex, sqInt length);
sqInt imageNameSize(void);
sqInt vmPathSize(void);
sqInt vmPathGetLength(sqInt sqVMPathIndex, sqInt length);

/* image security traps */
sqInt ioCanRenameImage(void);
sqInt ioCanWriteImage(void);
sqInt ioDisableImageWrite(void);
#ifdef DISABLE_SECURITY
# define ioCanRenameImage() 1
# define ioCanWriteImage() 1
# define ioDisableImageWrite() 1
#endif

/* save/restore */
/* Read the image from the given file starting at the given image offset */
sqInt readImageFromFileHeapSizeStartingAt(sqImageFile f, sqInt desiredHeapSize, squeakFileOffsetType imageOffset);
/* NOTE: The following is obsolete - it is only provided for compatibility */
#define readImageFromFileHeapSize(f, s) readImageFromFileHeapSizeStartingAt(f,s,0)

/* clipboard (cut/copy/paste) */
sqInt clipboardSize(void);
sqInt clipboardReadIntoAt(sqInt count, sqInt byteArrayIndex, sqInt startIndex);
sqInt clipboardWriteFromAt(sqInt count, sqInt byteArrayIndex, sqInt startIndex);



/* interpreter entry points needed by compiled primitives */
void *arrayValueOf(sqInt arrayOop);
sqInt checkedIntegerValueOf(sqInt intOop);
void *fetchArrayofObject(sqInt fieldIndex, sqInt objectPointer);
double fetchFloatofObject(sqInt fieldIndex, sqInt objectPointer);
sqInt fetchIntegerofObject(sqInt fieldIndex, sqInt objectPointer);
double floatValueOf(sqInt floatOop);
sqInt pop(sqInt nItems);
sqInt pushInteger(sqInt integerValue);
sqInt sizeOfSTArrayFromCPrimitive(void *cPtr);
sqInt storeIntegerofObjectwithValue(sqInt fieldIndex, sqInt objectPointer, sqInt integerValue);

/* profiling */
sqInt clearProfile(void);
sqInt dumpProfile(void);
sqInt startProfiling(void);
sqInt stopProfiling(void);

/* system attributes */
sqInt attributeSize(sqInt id);
sqInt getAttributeIntoLength(sqInt id, sqInt byteArrayIndex, sqInt length);

/*** pluggable primitive support ***/
/* NOTE: The following functions are those implemented by sqNamedPrims.c */
void *ioLoadExternalFunctionOfLengthFromModuleOfLength(sqInt functionNameIndex, sqInt functionNameLength,
						       sqInt moduleNameIndex, sqInt moduleNameLength);
sqInt  ioUnloadModuleOfLength(sqInt moduleNameIndex, sqInt moduleNameLength);
void *ioLoadFunctionFrom(char *functionName, char *pluginName);
sqInt  ioShutdownAllModules(void);
sqInt  ioUnloadModule(char *moduleName);
sqInt  ioUnloadModuleOfLength(sqInt moduleNameIndex, sqInt moduleNameLength);
char *ioListBuiltinModule(sqInt moduleIndex);
char *ioListLoadedModule(sqInt moduleIndex);
/* The next two are FFI entries! (implemented in sqNamedPrims.c as well) */
void *ioLoadModuleOfLength(sqInt moduleNameIndex, sqInt moduleNameLength);
void *ioLoadSymbolOfLengthFromModule(sqInt functionNameIndex, sqInt functionNameLength, void *moduleHandle);

/* The next three functions must be implemented by sqXYZExternalPrims.c */
/* ioLoadModule:
	Load a module from disk.
	WARNING: this always loads a *new* module. Don't even attempt to find a loaded one.
	WARNING: never primitiveFail() within, just return 0
*/
void *ioLoadModule(char *pluginName);

/* ioFindExternalFunctionIn:
	Find the function with the given name in the moduleHandle.
	WARNING: never primitiveFail() within, just return 0.
*/
void *ioFindExternalFunctionIn(char *lookupName, void *moduleHandle);

/* ioFreeModule:
	Free the module with the associated handle.
	WARNING: never primitiveFail() within, just return 0.
*/
sqInt  ioFreeModule(void *moduleHandle);

/* The Squeak version this interpreter was generated from */
extern const char *interpreterVersion;
