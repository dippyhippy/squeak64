/* sqUnixCharConv.h -- conversion between character encodings
 * 
 * Author: Ian.Piumarta@INRIA.Fr
 * 
 * @copyright@
 * 
 * Last edited: 2004-08-04 12:09:57 by piumarta on margaux.hpl.hp.com
 */

#ifndef __sqUnixCharConv_h
#define __sqUnixCharConv_h

extern void *sqTextEncoding;
extern void *uxTextEncoding;
extern void *uxPathEncoding;
extern void *uxUTF8Encoding;
extern void *uxXWinEncoding;

extern void setEncoding(void **encoding, char *name);

extern int convertChars(char *from, int fromLen, void *fromCode,
			char *to,   int toLen,   void *toCode,
			int norm, int term);

extern int sq2uxText(char *from, int fromLen, char *to, int toLen, int term);
extern int ux2sqText(char *from, int fromLen, char *to, int toLen, int term);
extern int sq2uxPath(char *from, int fromLen, char *to, int toLen, int term);
extern int ux2sqPath(char *from, int fromLen, char *to, int toLen, int term);
extern int sq2uxUTF8(char *from, int fromLen, char *to, int toLen, int term);
extern int ux2sqUTF8(char *from, int fromLen, char *to, int toLen, int term);

#endif /* __sqUnixCharConv_h */
