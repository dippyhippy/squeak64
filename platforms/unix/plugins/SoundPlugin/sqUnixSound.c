/* sqUnixSound.c -- sound support for various Unix sound systems
 *
 * Author: Ian.Piumarta@inria.fr
 * 
 * Last edited: 2003-08-14 01:34:52 by piumarta on emilia.inria.fr
 *
 * @copyright@
 *
 * NOTE: The real sound support code is in one of the following files according
 *	 to the output driver selected by `configure':
 * 
 *	   sqUnixSoundOSS.c	(Open Sound System [incl. Linux native & ALSA compat])
 *	   sqUnixSoundNAS.c	(Network Audio System)
 *	   sqUnixSoundSun.c	(SunOS/Solaris)
 *	   sqUnixSoundMacOSX.c	(Mac OS 10 CoreAudio)
 *	   sqUnixSoundNull.c	(sound disabled)
 */

#include "sq.h"
#include "SoundPlugin.h"
#include "SqModule.h"
#include "SqSound.h"

extern int snd_Stop(void);

/*** module initialisation/shutdown ***/

extern struct SqModule *soundModule;
extern struct SqModule *loadModule(char *type, char *name);

static struct SqSound *snd= 0;

int soundInit(void)
{
  if (!soundModule
#    if 0
      && !(soundModule= getenv("SQUEAK_SOUND_OSS")    ? loadModule("sound", "OSS")    : 0)
      && !(soundModule= getenv("SQUEAK_SOUND_NAS")    ? loadModule("sound", "NAS")    : 0)
      && !(soundModule= getenv("SQUEAK_SOUND_SUN")    ? loadModule("sound", "Sun")    : 0)
      && !(soundModule= getenv("SQUEAK_SOUND_MACOSX") ? loadModule("sound", "MacOSX") : 0)
      && !(soundModule= getenv("AUDIOSERVER")         ? loadModule("sound", "NAS")    : 0)
      && !(soundModule= loadModule("sound", "OSS"))
      && !(soundModule= loadModule("sound", "Sun"))
      && !(soundModule= loadModule("sound", "MacOSX"))
      && !(soundModule= loadModule("sound", "null"))
#    endif
      )
    {
      fprintf(stderr, "could not find any sound module\n");
      abort();
    }
  //printf("soundModule   %p %s\n", soundModule, soundModule->name);
  snd= (struct SqSound *)soundModule->makeInterface();
  if (SqSoundVersion != snd->version)
    {
      fprintf(stderr, "module %s interface version %x does not have required version %x\n",
	      soundModule->name, snd->version, SqSoundVersion);
      abort();
    }
  return 1;
}


int soundShutdown(void)
{
  if (snd) snd->snd_Stop();
  return 1;
}


/* output */

int snd_AvailableSpace(void)
{
  return snd->snd_AvailableSpace();
}

int snd_InsertSamplesFromLeadTime(int frameCount, int srcBufPtr, int samplesOfLeadTime)
{
  return snd->snd_InsertSamplesFromLeadTime(frameCount, srcBufPtr, samplesOfLeadTime);
}

int snd_PlaySamplesFromAtLength(int frameCount, int arrayIndex, int startIndex)
{
  return snd->snd_PlaySamplesFromAtLength(frameCount, arrayIndex, startIndex);
}

int snd_PlaySilence(void)
{
  return snd->snd_PlaySilence();
}

int snd_Start(int frameCount, int samplesPerSec, int stereo, int semaIndex)
{
  return snd->snd_Start(frameCount, samplesPerSec, stereo, semaIndex);
}

int snd_Stop(void)
{
  return snd->snd_Stop();
}

/* input */

int snd_StartRecording(int desiredSamplesPerSec, int stereo, int semaIndex)
{
  return snd->snd_StartRecording(desiredSamplesPerSec, stereo, semaIndex);
}

int snd_StopRecording(void)
{
  return snd->snd_StopRecording();
}

double snd_GetRecordingSampleRate(void)
{
  return snd->snd_GetRecordingSampleRate();
}

int snd_RecordSamplesIntoAtLength(int buf, int startSliceIndex, int bufferSizeInBytes)
{
  return snd->snd_RecordSamplesIntoAtLength(buf, startSliceIndex, bufferSizeInBytes);
}

/* mixer */

void snd_Volume(double *left, double *right)	{ snd->snd_Volume(left, right); }
void snd_SetVolume(double left, double right)	{ snd->snd_SetVolume(left, right); }
int  snd_SetRecordLevel(int level)		{ return snd->snd_SetRecordLevel(level); }
