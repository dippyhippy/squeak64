/* sqUnixSoundNull.c -- sound module for no sound
 *
 * Author: Ian.Piumarta@inria.fr
 * 
 * Last edited: 2004-06-13 23:42:48 by piumarta on emilia.local
 *
 * @copyright@
 */

#include "sq.h"

#define FAIL(X) { success(false); return X; }

/* output */
static sqInt  sound_AvailableSpace(void)									FAIL(8192)
static sqInt  sound_InsertSamplesFromLeadTime(sqInt frameCount, sqInt srcBufPtr, sqInt samplesOfLeadTime)	FAIL(frameCount)
static sqInt  sound_PlaySamplesFromAtLength(sqInt frameCount, sqInt arrayIndex, sqInt startIndex)		FAIL(8192)
static sqInt  sound_PlaySilence(void)										FAIL(8192)
static sqInt  sound_Start(sqInt frameCount, sqInt samplesPerSec, sqInt stereo, sqInt semaIndex)			FAIL(1)
static sqInt  sound_Stop(void)											FAIL(0)
/* input */
static sqInt  sound_StartRecording(sqInt desiredSamplesPerSec, sqInt stereo, sqInt semaIndex)			FAIL(0)
static sqInt  sound_StopRecording(void)										FAIL(0)
static double sound_GetRecordingSampleRate(void)								FAIL(0)
static sqInt  sound_RecordSamplesIntoAtLength(sqInt buf, sqInt startSliceIndex, sqInt bufferSizeInBytes)	FAIL(0)
/* mixer */
static void   sound_Volume(double *left, double *right)								{ return; }
static void   sound_SetVolume(double left, double right)							{ return; }
static sqInt  sound_SetRecordLevel(sqInt level)									{ return level; }

#include "SqSound.h"

SqSoundDefine(null);

#include "SqModule.h"

static void sound_parseEnvironment(void) {}

static int  sound_parseArgument(int argc, char **argv)
{
  if (!strcmp(argv[0], "-nosound")) return 1;
  return 0;
}

static void  sound_printUsage(void) {}
static void  sound_printUsageNotes(void) {}
static void *sound_makeInterface(void) { return &sound_null_itf; }

SqModuleDefine(sound, null);
