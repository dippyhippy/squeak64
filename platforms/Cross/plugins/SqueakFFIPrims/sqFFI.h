/****************************************************************************
*   PROJECT: Squeak foreign function interface
*   FILE:    sqFFI.h
*   CONTENT: Declarations for the foreign function interface
*
*   AUTHOR:  Andreas Raab (ar)
*   ADDRESS: Walt Disney Imagineering, Glendale, CA
*   EMAIL:   andreasr@wdi.disney.com
*   RCSID:   $Id: sqFFI.h,v 1.1.1.1 2001/10/24 23:12:24 rowledge Exp $
*
*   NOTES:
*
*****************************************************************************/
#ifndef SQ_FFI_H
#define SQ_FFI_H

/* Calling conventions */
#define FFICallTypeCDecl 0
#define FFICallTypeApi 1

/* Atomic types */
#define FFITypeVoid 0
#define FFITypeBool 1
#define FFITypeUnsignedByte 2
#define FFITypeSignedByte 3
#define FFITypeUnsignedShort 4
#define FFITypeSignedShort 5
#define FFITypeUnsignedInt 6
#define FFITypeSignedInt 7
#define FFITypeUnsignedLongLong 8
#define FFITypeSignedLongLong 9
#define FFITypeUnsignedChar 10
#define FFITypeSignedChar 11
#define FFITypeSingleFloat 12
#define FFITypeDoubleFloat 13

/* Shift and mask for atomic types */
#define FFIAtomicTypeShift 24
#define FFIAtomicTypeMask 251658240

/* Type flags */
#define FFIFlagPointer 131072
#define FFIFlagStructure 65536
#define FFIFlagAtomic 262144

/* Size mask */
#define FFIStructSizeMask 65535

/* error constants */
#define FFINoCalloutAvailable -1
#define FFIErrorGenericError 0
#define FFIErrorNotFunction 1
#define FFIErrorBadArgs 2
#define FFIErrorBadArg 3
#define FFIErrorIntAsPointer 4
#define FFIErrorBadAtomicType 5
#define FFIErrorCoercionFailed 6
#define FFIErrorWrongType 7
#define FFIErrorStructSize 8
#define FFIErrorCallType 9
#define FFIErrorBadReturn 10
#define FFIErrorBadAddress 11
#define FFIErrorNoModule 12
#define FFIErrorAddressNotFound 13
#define FFIErrorAttemptToPassVoid 14
#define FFIErrorModuleNotFound 15
#define FFIErrorBadExternalLibrary 16
#define FFIErrorBadExternalFunction 17
#define FFIErrorInvalidPointer 18

/* Announce a coming FFI call */
int ffiInitialize(void);

/* cleanup */
int ffiCleanup(void);

/* Allocate/free external memory */
int ffiAlloc(int byteSize);
int ffiFree(int ptr);

/* general <=32bit integer loads */
int ffiPushSignedByte(int value);
int ffiPushUnsignedByte(int value);
int ffiPushSignedShort(int value);
int ffiPushUnsignedShort(int value);
int ffiPushSignedInt(int value);
int ffiPushUnsignedInt(int value);

/* 64bit integer loads */
int ffiPushSignedLongLong(int lowWord, int highWord);
int ffiPushUnsignedLongLong(int lowWord, int highWord);
/* 64bit integer returns */
int ffiLongLongResultLow(void);
int ffiLongLongResultHigh(void);

/* special <=32bit loads */
int ffiPushSignedChar(int value);
int ffiPushUnsignedChar(int value);

/* float loads */
int ffiPushSingleFloat(double value);
int ffiPushDoubleFloat(double value);

/* structure loads */
int ffiPushStructureOfLength(int pointer, int* structSpec, int specSize);

/* pointer loads */
int ffiPushPointer(int pointer);

/* string loads */
int ffiPushStringOfLength(int srcIndex, int length);

/* return true if calling convention is supported */
int ffiSupportsCallingConvention(int callType);

/* return true if these types can be returned */
int ffiCanReturn(int* structSpec, int specSize);

/* call the appropriate function w/ the given return type */
int ffiCallAddressOfWithPointerReturn(int fn, int callType);
int ffiCallAddressOfWithStructReturn(int fn, int callType, 
				     int* structSpec, int specSize);
int ffiCallAddressOfWithReturnType(int fn, int callType, int typeSpec);

/* store the structure result of a previous call */
int ffiStoreStructure(int address, int structSize);

/* return the float value from a previous call */
double ffiReturnFloatValue(void);


#endif /* SQ_FFI_H */
