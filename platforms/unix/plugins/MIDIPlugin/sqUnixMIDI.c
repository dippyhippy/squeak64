/* sqUnixMIDI.c -- Unix MIDI support
 * 
 * @copyright@
 */

/* Author: Ian.Piumarta@INRIA.FR
 * 
 * Last edited: 2002-10-26 14:34:46 by piumarta on emilia.inria.fr
 */

#include "sq.h"
#include "MIDIPlugin.h"

/* Put the given port into MIDI mode, which uses a clock supplied
   by an external MIDI interface adaptor to determine the data rate.
   Possible external clock rates: 31.25 KHz, 0.5 MHz, 1 MHz, or 2 MHz. */
int serialPortMidiClockRate(int portNum, int interfaceClockRate)
{
	success(false);
	return 0;
}

/* Close the given MIDI port. Do nothing if the port is not open.
   Fail if there is no port of the given number.*/
int sqMIDIClosePort(int portNum)
{
	success(false);
	return 0;
}

/* Return the current value of the clock used to schedule MIDI events.
   The MIDI clock is assumed to wrap at or before half the maximum
   positive SmallInteger value. This allows events to be scheduled
   into the future without overflowing into LargePositiveIntegers. 
   This implementation does not support event scheduling, so it
   just returns the value of the Squeak millisecond clock. */
int sqMIDIGetClock(void)
{
	success(false);
	return 0;
}

/* Return the number of available MIDI interfaces, including both
   hardware ports and software entities that act like ports. Ports
   are numbered from 0 to N-1, where N is the number returned by this
   primitive. */
int sqMIDIGetPortCount(void)
{
	success(false);
	return 0;
}

/* Return an integer indicating the directionality of the given
   port where: 1 = input, 2 = output, 3 = bidirectional. Fail if
   there is no port of the given number. */
int sqMIDIGetPortDirectionality(int portNum)
{
	success(false);
	return 0;
}

/* Copy the name of the given MIDI port into the string at the given
   address. Copy at most length characters, and return the number of
   characters copied. Fail if there is no port of the given number.*/
int sqMIDIGetPortName(int portNum, int namePtr, int length)
{
	success(false);
	return 0;
}

/* Open the given port, if possible. If non-zero, readSemaphoreIndex
   specifies the index in the external objects array of a semaphore
   to be signalled when incoming MIDI data is available. Note that
   not all implementations support read semaphores (this one does
   not); see sqMIDICanUseSemaphore. The interfaceClockRate parameter
   specifies the clock speed for an external MIDI interface
   adaptor on platforms that use such adaptors (e.g., Macintosh).
   Fail if there is no port of the given number.*/
int sqMIDIOpenPort(int portNum, int readSemaIndex, int interfaceClockRate)
{
	success(false);
	return 0;
}

/* Read or write the given MIDI driver parameter. If modify is 0,
   then newValue is ignored and the current value of the specified
   parameter is returned. If modify is non-zero, then the specified
   parameter is set to newValue. Note that many MIDI driver parameters
   are read-only; attempting to set one of these parameters fails.
   For boolean parameters, true = 1, false = 0. */
int sqMIDIParameter(int whichParameter, int modify, int newValue)
{
	success(false);
	return 0;
}

/* bufferPtr is the address of the first byte of a Smalltalk
   ByteArray of the given length. Copy up to (length - 4) bytes
   of incoming MIDI data into that buffer, preceded by a 4-byte
   timestamp in the units of the MIDI clock, most significant byte
   first. Implementations that do not support timestamping of
   incoming data as it arrives (see sqMIDIHasInputClock) simply
   set the timestamp to the value of the MIDI clock when this
   function is called. Return the total number of bytes read,
   including the timestamp bytes. Return zero if no data is
   available. Fail if the buffer is shorter than five bytes,
   since there must be enough room for the timestamp plus at
   least one data byte. */
int sqMIDIPortReadInto(int portNum, int count, int bufferPtr)
{
	success(false);
	return 0;
}

/* bufferPtr is the address of the first byte of a Smalltalk
   ByteArray of the given length. Send its contents to the given
   port when the MIDI clock reaches the given time. If time equals
   zero, then send the data immediately. Implementations that do
   not support a timestamped output queue, such as this one, always
   send the data immediately; see sqMIDIHasBuffer. */
int sqMIDIPortWriteFromAt(int portNum, int count, int bufferPtr, int time)
{
	success(false);
	return 0;
}


int midiInit(void)
{
	success(false);
	return 0;
}

int sqMIDIParameterGet(int which)
{
	success(false);
	return 0;
}

int sqMIDIParameterSet(int which, int value)
{
	success(false);
	return 0;
}

int midiShutdown(void)
{
	success(false);
	return 0;
}
