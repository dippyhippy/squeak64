/* sqUnixJoystickTablet.c -- support for joysticks and graphics tablets
 * 
 * @copyright@
 */

/* Author: Ian.Piumarta@INRIA.Fr
 *
 * Last edited: 2002-10-26 14:34:03 by piumarta on emilia.inria.fr
 */

#include "sq.h"
#include "JoystickTabletPlugin.h"

/* we don't have any joysticks */

void *joySticks= 0;

int joystickRead(int index)	{ return 0; }
int joystickInit(void)		{ return 0; }

/* we don't have any tablets either */

int tabletInit(void)
{
  return 0;
}

int tabletGetParameters(int cursorIndex, int result[])
{
  return 0;
}

int tabletRead(int cursorIndex, int result[])
{
  return 0;
}

int tabletResultSize(void)
{
  return 0;
}

int joystickShutdown(void)
{
  return 0;
}
