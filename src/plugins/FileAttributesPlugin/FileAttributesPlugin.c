/* Automatically generated by
	VMPluginCodeGenerator VMMaker.oscog-eem.2736 uuid: 1dd4c38f-c0b4-4edd-9165-f4a54a988fe7
   from
	FileAttributesPlugin FileAttributesPlugin.oscog-eem.54 uuid: 4aa6e35d-11f2-49de-9e53-ac5600cf4684
 */
static char __buildInfo[] = "FileAttributesPlugin FileAttributesPlugin.oscog-eem.54 uuid: 4aa6e35d-11f2-49de-9e53-ac5600cf4684 " __DATE__ ;



#include "config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#if _WIN32 || _WIN64
# include <windows.h>
# include <winbase.h>
# if !defined(_MSC_VER) /* i.e. cygwin or mingw */
#	include <unistd.h>
#	include <dirent.h>
# endif
# define FAIL() { return -1; }
# include "sqWin32File.h"
# if !defined(PATH_MAX) /* work around bug in 64-bit cygwin; sigh :-( */
#	define PATH_MAX 4096
# endif
# define HAVE_CHMOD 0
# define HAVE_CHOWN 0
#else
# include <unistd.h>
# include <dirent.h>
# define HAVE_CHMOD 1
# define HAVE_CHOWN 1
#endif
#include <sys/stat.h>
#if !defined(HAVE_LSTAT) && !defined(_WIN32) && !defined(_WIN64)
# define HAVE_LSTAT 1
#endif

/* AKG 2018 - FileAttributesPlugin.c translated from class FileAttributesPlugin */

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
#include "sqConfig.h"			/* Configuration options */
#include "sqVirtualMachine.h"	/*  The virtual machine proxy definition */
#include "sqPlatformSpecific.h"	/* Platform specific definitions */

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
# undef EXPORT
# define EXPORT(returnType) static returnType
# define INT_EXT "(i)"
#else
# define INT_EXT "(e)"
#endif

#include "faCommon.h"
#include "sqMemoryAccess.h"


/*** Constants ***/
#define PrimErrBadArgument 3
#define PrimErrNoCMemory 10
#define PrimErrNoMemory 9


/*** Function Prototypes ***/
static sqInt addressObjectFor(void *aMachineAddress);
static sqInt attributeArrayformask(sqInt *attributeArrayPtr, fapath *faPath, sqInt attributeMask);
static sqInt badSessionId(void);
static sqInt canOpenDirectoryStreamForlength(char *aPathCString, sqInt length);
static sqInt canStatFilePathlength(char *aPathCString, sqInt length);
#if _WIN32
static sqLong convertWinToSqueakTime(SYSTEMTIME st);
#endif /* _WIN32 */
static sqInt faSuccess(void);
EXPORT(const char*) getModuleName(void);
EXPORT(sqInt) initialiseModule(void);
static sqInt objectFromStructsize(void *aMachineAddress, sqInt structSize);
static int pathOoptoBuffermaxLen(sqInt pathNameOop, char *cPathName, sqInt maxLen);
static void * pointerFrom(sqInt directoryPointerBytes);
EXPORT(sqInt) primitiveChangeMode(void);
EXPORT(sqInt) primitiveChangeOwner(void);
EXPORT(sqInt) primitiveClosedir(void);
EXPORT(sqInt) primitiveFileAttribute(void);
EXPORT(sqInt) primitiveFileAttributes(void);
EXPORT(sqInt) primitiveFileExists(void);
EXPORT(sqInt) primitiveFileMasks(void);
EXPORT(sqInt) primitiveLogicalDrives(void);
EXPORT(sqInt) primitiveOpendir(void);
EXPORT(sqInt) primitivePathMax(void);
EXPORT(sqInt) primitivePlatToStPath(void);
EXPORT(sqInt) primitiveReaddir(void);
EXPORT(sqInt) primitiveRewinddir(void);
EXPORT(sqInt) primitiveStToPlatPath(void);
EXPORT(sqInt) primitiveSymlinkChangeOwner(void);
EXPORT(sqInt) primitiveVersionString(void);
static sqInt processDirectory(fapath *faPath);
static sqInt readLinkintomaxLength(char *cPathName, char *cLinkPtr, size_t maxLength);
EXPORT(sqInt) setInterpreter(struct VirtualMachine *anInterpreter);
static sqInt sizeOfFaPath(void);
static sqInt sizeOfFaPathPtr(void);
static sqInt stringFromCString(const char *aCString);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static void * (*arrayValueOf)(sqInt oop);
static sqInt (*classArray)(void);
static sqInt (*classByteArray)(void);
static sqInt (*classString)(void);
static sqInt (*failed)(void);
static sqInt (*instantiateClassindexableSize)(sqInt classPointer, sqInt size);
static void * (*ioLoadFunctionFrom)(char *functionName, char *moduleName);
static sqInt (*isKindOf)(sqInt oop, char *aString);
static sqInt (*isBytes)(sqInt oop);
static sqInt (*methodReturnBool)(sqInt boolean);
static sqInt (*methodReturnInteger)(sqInt integer);
static sqInt (*methodReturnValue)(sqInt oop);
static sqInt (*nilObject)(void);
static sqInt (*popthenPush)(sqInt nItems, sqInt oop);
static sqInt (*popRemappableOop)(void);
static sqInt (*positive32BitIntegerFor)(unsigned int integerValue);
static sqInt (*primitiveFail)(void);
static sqInt (*primitiveFailFor)(sqInt reasonCode);
static sqInt (*primitiveFailForOSError)(sqLong osError);
static sqInt (*primitiveFailureCode)(void);
static sqInt (*pushRemappableOop)(sqInt oop);
static sqInt (*stSizeOf)(sqInt oop);
static sqInt (*stackIntegerValue)(sqInt offset);
static sqInt (*stackObjectValue)(sqInt offset);
static sqInt (*stackValue)(sqInt offset);
static sqInt (*storePointerofObjectwithValue)(sqInt index, sqInt oop, sqInt valuePointer);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern void * arrayValueOf(sqInt oop);
extern sqInt classArray(void);
extern sqInt classByteArray(void);
extern sqInt classString(void);
extern sqInt failed(void);
extern sqInt instantiateClassindexableSize(sqInt classPointer, sqInt size);
extern void * ioLoadFunctionFrom(char *functionName, char *moduleName);
extern sqInt isKindOf(sqInt oop, char *aString);
extern sqInt isBytes(sqInt oop);
extern sqInt methodReturnBool(sqInt boolean);
extern sqInt methodReturnInteger(sqInt integer);
extern sqInt methodReturnValue(sqInt oop);
extern sqInt nilObject(void);
extern sqInt popthenPush(sqInt nItems, sqInt oop);
extern sqInt popRemappableOop(void);
extern sqInt positive32BitIntegerFor(unsigned int integerValue);
extern sqInt primitiveFail(void);
extern sqInt primitiveFailFor(sqInt reasonCode);
#if VM_PROXY_MAJOR > 1 || (VM_PROXY_MAJOR == 1 && VM_PROXY_MINOR >= 14)
extern sqInt primitiveFailForOSError(sqLong osError);
#else
# define primitiveFailForOSError(osError) 0
#endif
extern sqInt primitiveFailureCode(void);
extern sqInt pushRemappableOop(sqInt oop);
extern sqInt stSizeOf(sqInt oop);
extern sqInt stackIntegerValue(sqInt offset);
extern sqInt stackObjectValue(sqInt offset);
extern sqInt stackValue(sqInt offset);
extern sqInt storePointerofObjectwithValue(sqInt index, sqInt oop, sqInt valuePointer);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName = "FileAttributesPlugin FileAttributesPlugin.oscog-eem.54 " INT_EXT;
static void * sCLPfn;
static void * sCOFfn;
static int hasSecurityPlugin = 1;



/*	Answer an ExternalAddress object which represents aMachineAddress */

	/* FileAttributesPlugin>>#addressObjectFor: */
static sqInt
addressObjectFor(void *aMachineAddress)
{
    sqInt addressOop;
    unsigned char *addressOopArrayPointer;
    union {void *address; unsigned char bytes[sizeof(void *)];} addressUnion;
    sqInt idx;

	addressOop = instantiateClassindexableSize(classByteArray(), sizeof(void *));
	if (!(addressOop)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	addressOopArrayPointer = arrayValueOf(addressOop);
	addressUnion.address = aMachineAddress;
	idx = 0;
	while (idx < (sizeof(void *))) {
		addressOopArrayPointer[idx] = addressUnion.bytes[idx];
		idx += 1;
	}
	return addressOop;
}


/*	Create the attributes array for the specified file (faPath) and set
	attributeArrayPtr. Which attributes are retrieved are specified in
	attributeMask. On error, set the error in interpreterProxy and answer the
	appropriate status (some callers check the status, others
	interpreterProxy) 
 */

	/* FileAttributesPlugin>>#attributeArray:for:mask: */
static sqInt
attributeArrayformask(sqInt *attributeArrayPtr, fapath *faPath, sqInt attributeMask)
{
    sqInt accessArray;
    sqInt attributeArray;
    int getAccess;
    int getLinkStats;
    int getStats;
    sqInt resultOop;
    sqInt status;


	/* Determine which attributes to retrieve */
	accessArray = 0;
	attributeArray = 0;
	resultOop = 0;
	getStats = attributeMask & 1;
	getAccess = attributeMask & 2;
	if (!(getStats
		 || (getAccess))) {

		/* No information has been requested, which doesn't make sense */
		primitiveFailForOSError(-6 /* invalidArguments */);
		return -6 /* invalidArguments */;
	}
	getLinkStats = attributeMask & 4;
	if (getStats) {
		attributeArray = instantiateClassindexableSize(classArray(), 13);
		if (!(attributeArray)) {
			primitiveFailFor(PrimErrNoMemory);
			return -15 /* interpreterError */;
		}
		
#if SPURVM
		status = faFileStatAttributes(faPath, getLinkStats, attributeArray);

#else /* SPURVM */
		pushRemappableOop(attributeArray);
		status = faFileStatAttributes(faPath, getLinkStats, attributeArray);
		attributeArray = popRemappableOop()
#endif /* SPURVM */
;
		if (status != 0) {
			return status;
		}
		resultOop = attributeArray;
	}
	if (getAccess) {
		
#if SPURVM
		accessArray = instantiateClassindexableSize(classArray(), 3);

#else /* SPURVM */
		pushRemappableOop(attributeArray);
		accessArray = instantiateClassindexableSize(classArray(), 3);
		attributeArray = popRemappableOop()
#endif /* SPURVM */
;
		if (!(accessArray)) {
			primitiveFailFor(PrimErrNoMemory);

			/* interpreterError */
		}
		faAccessAttributes(faPath, accessArray, 0);
		if (failed()) {
			return -15 /* interpreterError */;
		}
		resultOop = accessArray;
	}
	if (getStats
	 && (getAccess)) {
		
#if SPURVM
		resultOop = instantiateClassindexableSize(classArray(), 2);

#else /* SPURVM */
		pushRemappableOop(attributeArray);
		pushRemappableOop(accessArray);
		resultOop = instantiateClassindexableSize(classArray(), 2);
		accessArray = popRemappableOop();
		attributeArray = popRemappableOop()
#endif /* SPURVM */
;
		if (!(resultOop)) {
			primitiveFailFor(PrimErrNoMemory);

			/* interpreterError */
		}
		storePointerofObjectwithValue(0, resultOop, attributeArray);
		storePointerofObjectwithValue(1, resultOop, accessArray);
	}
	attributeArrayPtr[0] = resultOop;
	return 0 /* faSuccess */;
}


/*	The supplied session Id doesn't match the current VM session Id */

	/* FileAttributesPlugin>>#badSessionId */
static sqInt
badSessionId(void)
{
	return -17;
}


/*	Answer non-zero if security permits the directory to be listed. */
/*	FIXME: This function has not been tested. -dtl */
/*	If the security plugin can be loaded, use it to check . 
	If not, assume it's ok */
/*	The hasSecurityPlugin flag is set to 1 by default */

	/* FileAttributesPlugin>>#canOpenDirectoryStreamFor:length: */
static sqInt
canOpenDirectoryStreamForlength(char *aPathCString, sqInt length)
{
	if (hasSecurityPlugin == 0) {
		return 1;
	}
	if (sCLPfn != 0) {
		return  ((int (*) (char *, int)) sCLPfn)(aPathCString, length);
	}
	else {

		/* Reset the flag so we do not try again next time */
		hasSecurityPlugin = 0;
		return 1;
	}
}


/*	Answer non-zero if security permits the a stat() call on the file path.
	Allow a
	stat() call only on files which we are permitted to open.
 */
/*	FIXME: This function has not been tested. -dtl */
/*	If the security plugin can be loaded, use it to check . 
	If not, assume it's ok */
/*	The hasSecurityPlugin flag is set to 1 by default */

	/* FileAttributesPlugin>>#canStatFilePath:length: */
static sqInt
canStatFilePathlength(char *aPathCString, sqInt length)
{
	if (hasSecurityPlugin == 0) {
		return 1;
	}
	if (sCOFfn != 0) {
		return  ((int (*) (char *, int, int)) sCOFfn)(aPathCString, length, 0);
	}
	else {

		/* Reset the flag so we do not try again next time */
		hasSecurityPlugin = 0;
		return 1;
	}
}


/*	Convert the supplied Windows SYSTEMTIME to Squeak time */

	/* FileAttributesPlugin>>#convertWinToSqueakTime: */
#if _WIN32
static sqLong
convertWinToSqueakTime(SYSTEMTIME st)
{
    sqLong dy;
    static sqLong nDaysPerMonth[14] = { 
		0,  0,  31,  59,  90, 120, 151,
		181, 212, 243, 273, 304, 334, 365 };
    sqLong secs;

	dy = (st.wYear) - 1901;

	/* base seconds */
	/* seconds of leap years */
	/* check if month > 2 and current year is a leap year */
	secs = ((((dy * 365) * 24) * 60) * 60) + (((((((usqLong)(dy)) >> 2)) * 24) * 60) * 60);
	if (((st.wMonth) > 2)
	 && ((dy & 3) == 3)) {

		/* add one day */
		secs += 86400;
	}

	/* add the hours, minutes, and seconds */
	secs += (nDaysPerMonth[st.wMonth] + st.wDay - 1) * 24 * 60 * 60;
	secs += st.wSecond + 60*(st.wMinute + 60*st.wHour);
	return secs;
}
#endif /* _WIN32 */

	/* FileAttributesPlugin>>#faSuccess */
static sqInt
faSuccess(void)
{
	return 0;
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

	/* InterpreterPlugin>>#getModuleName */
EXPORT(const char*)
getModuleName(void)
{
	return moduleName;
}

	/* FileAttributesPlugin>>#initialiseModule */
EXPORT(sqInt)
initialiseModule(void)
{
	sCOFfn = ioLoadFunctionFrom("secCanOpenFileOfSizeWritable", "SecurityPlugin");
	sCLPfn = ioLoadFunctionFrom("secCanListPathOfSize", "SecurityPlugin");
	return 1;
}


/*	Answer a ByteArray object which copies the structure at aMachineAddress */

	/* FileAttributesPlugin>>#objectFromStruct:size: */
static sqInt
objectFromStructsize(void *aMachineAddress, sqInt structSize)
{
    sqInt addressOop;
    unsigned char *addressOopArrayPointer;

	addressOop = instantiateClassindexableSize(classByteArray(), structSize);
	if (!(addressOop)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	addressOopArrayPointer = arrayValueOf(addressOop);
	memcpy(addressOopArrayPointer, aMachineAddress, structSize);
	return addressOop;
}


/*	Copy the supplied path name string object to the supplied c string buffer */

	/* FileAttributesPlugin>>#pathOop:toBuffer:maxLen: */
static int
pathOoptoBuffermaxLen(sqInt pathNameOop, char *cPathName, sqInt maxLen)
{
    sqInt len;
    char *sPtr;

	len = stSizeOf(pathNameOop);
	if (len >= maxLen) {
		return -1 /* stringTooLong */;
	}
	sPtr = arrayValueOf(pathNameOop);
	if ((canStatFilePathlength(sPtr, len)) == 0) {
		/* begin cantStatPath */
		return ((sqInt) -3);
	}
	memcpy(cPathName, sPtr, len);
	cPathName[len] = 0;
	return 0;
}


/*	Answer the machine address contained in anExternalAddressOop. */

	/* FileAttributesPlugin>>#pointerFrom: */
static void *
pointerFrom(sqInt directoryPointerBytes)
{
    union {void *address; unsigned char bytes[sizeof(void *)];} addressUnion;
    sqInt idx;
    unsigned char *ptr;

	if (!((isKindOf(directoryPointerBytes, "ByteArray"))
		 && ((stSizeOf(directoryPointerBytes)) == (sizeof(void *))))) {
		return null;
	}
	ptr = arrayValueOf(directoryPointerBytes);
	idx = 0;
	while (idx < (sizeof(void *))) {
		addressUnion.bytes[idx] = ptr[idx];
		idx += 1;
	}
	return addressUnion.address;
}


/*	Set the mode of the supplied file using chmod(). */

	/* FileAttributesPlugin>>#primitiveChangeMode */
EXPORT(sqInt)
primitiveChangeMode(void)
{
    fapath faPath;
    sqInt fileNameOop;
    sqInt newMode;
    sqInt status;

	fileNameOop = stackObjectValue(1);
	newMode = stackIntegerValue(0);
	if ((failed())
	 || (!(isBytes(fileNameOop)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	
#  if HAVE_CHMOD
	faSetStPathOop((&faPath), fileNameOop);
	if (failed()) {
		return primitiveFailureCode();
	}
	status = chmod(faGetPlatPath((&faPath)), newMode);
	if (status != 0) {
		return primitiveFailForOSError(errno);
	}
	return methodReturnValue(nilObject());
#  endif /* HAVE_CHMOD */
	return primitiveFailForOSError(-13 /* unsupportedOperation */);
}


/*	Set the owner of the supplied file using chown(). */

	/* FileAttributesPlugin>>#primitiveChangeOwner */
EXPORT(sqInt)
primitiveChangeOwner(void)
{
    fapath faPath;
    sqInt fileNameOop;
    sqInt groupId;
    sqInt ownerId;
    sqInt status;

	fileNameOop = stackObjectValue(2);
	ownerId = stackIntegerValue(1);
	groupId = stackIntegerValue(0);
	if ((failed())
	 || (!(isBytes(fileNameOop)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	
#  if HAVE_CHOWN
	faSetStPathOop((&faPath), fileNameOop);
	if (failed()) {
		return primitiveFailureCode();
	}
	status = chown(faGetPlatPath((&faPath)), ownerId, groupId);
	if (status != 0) {
		return primitiveFailForOSError(errno);
	}
	return methodReturnValue(nilObject());
#  endif /* HAVE_CHOWN */
	return primitiveFailForOSError(-13 /* unsupportedOperation */);
}


/*	Close the directory stream for dirPointerOop. Answer dirPointerOop on
	success. Raise PrimErrBadArgument if the parameter is not a ByteArray
	length size(void *).
	If closedir() returns an error raise PrimitiveOSError.
 */

	/* FileAttributesPlugin>>#primitiveClosedir */
EXPORT(sqInt)
primitiveClosedir(void)
{
    void *buffer;
    sqInt dirPointerOop;
    fapath *faPath;
    FAPathPtr *faPathPtr;
    sqInt result;
    sqInt structSize;

	dirPointerOop = stackValue(0);
	/* begin structFromObject:size: */
	structSize = sizeof(FAPathPtr);
	if (!((stSizeOf(dirPointerOop)) == structSize)) {
		primitiveFailFor(PrimErrBadArgument);
		faPathPtr = ((void *) 0);
		goto l1;
	}
	buffer = alloca(structSize);
	if (buffer == 0) {
		primitiveFailFor(PrimErrNoCMemory);
	}
	else {
		memcpy(buffer, arrayValueOf(dirPointerOop), structSize);
	}
	faPathPtr = buffer;
	l1:	/* end structFromObject:size: */;
	if (faPathPtr == 0) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	if (!(faValidateSessionId((faPathPtr->sessionId)))) {
		return primitiveFailForOSError(-17 /* badSessionId */);
	}
	faPath = (faPathPtr->faPath);
	result = faCloseDirectory(faPath);
	faInvalidateSessionId(&faPathPtr->sessionId);
	if (!(result == 0)) {
		return primitiveFailForOSError(result);
	}
	free(faPath);
	methodReturnValue(dirPointerOop);
	return 0;
}


/*	Answer a single file attribute.
	primFileAttributes: aString attributeNumber: attributeNumber
	aString is the path to the file
	attributeNumber identifies which attribute to return:
	1 - 12: stat(): name, mode, ino, dev, nlink, uid, gid, size, accessDate,
	modifiedDate, changeDate, creationDate
	13 - 15: access(): R_OK, W_OK, X_OK
	16: isSymlink
	On error, answer a single element array containing the appropriate error
	code. 
 */

	/* FileAttributesPlugin>>#primitiveFileAttribute */
EXPORT(sqInt)
primitiveFileAttribute(void)
{
    sqInt attributeNumber;
    fapath faPath;
    sqInt fileName;
    sqInt resultOop;

	fileName = stackObjectValue(1);
	attributeNumber = stackIntegerValue(0);
	if ((failed())
	 || ((!(((attributeNumber >= 1) && (attributeNumber <= 16))))
	 || (!(isBytes(fileName))))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faSetStPathOop((&faPath), fileName);
	if (failed()) {
		return primitiveFailureCode();
	}
	resultOop = faFileAttribute((&faPath), attributeNumber);
	if (failed()) {
		return primitiveFailureCode();
	}
	if (resultOop == 0) {

		/* It shouldn't be possible to get here */
		primitiveFailForOSError(-14 /* unexpectedError */);
	}
	else {
		methodReturnValue(resultOop);
	}
	return 0;
}


/*	Answer an array of file attributes.
	primFileAttributes: aString mask: attributeMask
	aString is the path to the file
	attributeMask indicates which attributes to retrieve:
	bit 0 - get stat() attributes
	bit 1 - get access() attributes
	bit 2 - use lstat() instead of stat()
	On error answer the appropriate error code (Integer) */

	/* FileAttributesPlugin>>#primitiveFileAttributes */
EXPORT(sqInt)
primitiveFileAttributes(void)
{
    sqInt attributeMask;
    fapath faPath;
    sqInt fileName;
    sqInt resultOop;
    sqInt status;
    sqInt val;

	resultOop = 0;
	val = 0;
	fileName = stackObjectValue(1);
	attributeMask = stackIntegerValue(0);
	if ((failed())
	 || (!(isBytes(fileName)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faSetStPathOop((&faPath), fileName);
	if (failed()) {
		return primitiveFailureCode();
	}
	status = attributeArrayformask((&resultOop), (&faPath), attributeMask);
	if (status != 0) {
		return primitiveFailForOSError(status);
	}
	return methodReturnValue(resultOop);
}


/*	Check for existence of a file with a call to access(), or the appropriate
	platform function.
 */

	/* FileAttributesPlugin>>#primitiveFileExists */
EXPORT(sqInt)
primitiveFileExists(void)
{
    fapath faPath;
    sqInt fileNameOop;

	fileNameOop = stackValue(0);
	if (!(isBytes(fileNameOop))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faSetStPathOop((&faPath), fileNameOop);
	if (!(failed())) {
		return methodReturnBool(faExists((&faPath)));
	}
	return 0;
}


/*	Answer an array of well known file masks */

	/* FileAttributesPlugin>>#primitiveFileMasks */
EXPORT(sqInt)
primitiveFileMasks(void)
{
    sqInt masks;

	masks = instantiateClassindexableSize(classArray(), 8);
	if (!(masks)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	storePointerofObjectwithValue(0, masks, positive32BitIntegerFor(S_IFMT));
	
#  if !(defined(_WIN32))
	storePointerofObjectwithValue(1, masks, positive32BitIntegerFor(S_IFSOCK));
	storePointerofObjectwithValue(2, masks, positive32BitIntegerFor(S_IFLNK));
#  endif /* !(defined(_WIN32)) */
	storePointerofObjectwithValue(3, masks, positive32BitIntegerFor(S_IFREG));
	storePointerofObjectwithValue(4, masks, positive32BitIntegerFor(S_IFBLK));
	storePointerofObjectwithValue(5, masks, positive32BitIntegerFor(S_IFDIR));
	storePointerofObjectwithValue(6, masks, positive32BitIntegerFor(S_IFCHR));
	storePointerofObjectwithValue(7, masks, positive32BitIntegerFor(S_IFIFO));
	popthenPush(1, masks);
	return 0;
}


/*	Answer the logical drive mask on windows */

	/* FileAttributesPlugin>>#primitiveLogicalDrives */
EXPORT(sqInt)
primitiveLogicalDrives(void)
{
    unsigned int mask;

	
#  if defined(_WIN32)
	mask = GetLogicalDrives();
	if (mask != 0) {
		return popthenPush(1, positive32BitIntegerFor(mask));
	}
#  endif /* defined(_WIN32) */
	primitiveFail();
	return 0;
}


/*	Open the supplied directory and answer the first entry and directory
	pointer. If the directory is empty, answer nil as the first entry.
	If the directory can't be opened, answer an error (cantOpenDir) */
/*	self primOpendir: '/etc' */

	/* FileAttributesPlugin>>#primitiveOpendir */
EXPORT(sqInt)
primitiveOpendir(void)
{
    sqInt addressOop;
    unsigned char *addressOopArrayPointer;
    void *aMachineAddress;
    sqInt dirName;
    sqInt dirOop;
    fapath *faPath;
    FAPathPtr faPathPtr;
    sqInt resultOop;
    sqInt status;
    sqInt structSize;


	/* Process the parameters */
	dirName = stackObjectValue(0);
	if (!(isBytes(dirName))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faPath = (fapath *) calloc(1, sizeof(fapath));
	if (faPath == null) {
		return primitiveFailForOSError(-10 /* cantAllocateMemory */);
	}
	faSetStDirOop(faPath, dirName);
	if (failed()) {
		return primitiveFailureCode();
	}
	if (!(canOpenDirectoryStreamForlength(faGetStPath(faPath), faGetStPathLen(faPath)))) {
		free(faPath);
		return primitiveFailForOSError(-9 /* cantOpenDir */);
	}
	status = faOpenDirectory(faPath);
	if (status == 1 /* noMoreData */) {
		free(faPath);
		return methodReturnValue(nilObject());
	}
	if (status < 0) {
		free(faPath);
		return primitiveFailForOSError(status);
	}
	resultOop = processDirectory(faPath);
	if (failed()) {
		free(faPath);
		return primitiveFailureCode();
	}
	faInitSessionId(&faPathPtr.sessionId);
	(faPathPtr.faPath = faPath);
	
#if SPURVM
	/* begin objectFromStruct:size: */
	aMachineAddress = (&faPathPtr);
	structSize = sizeOfFaPathPtr();
	addressOop = instantiateClassindexableSize(classByteArray(), structSize);
	if (!(addressOop)) {
		dirOop = primitiveFailFor(PrimErrNoMemory);
		goto l1;
	}
	addressOopArrayPointer = arrayValueOf(addressOop);
	memcpy(addressOopArrayPointer, aMachineAddress, structSize);
	dirOop = addressOop;
	l1:	/* end objectFromStruct:size: */;

#else /* SPURVM */
	pushRemappableOop(resultOop);
	/* begin objectFromStruct:size: */
	aMachineAddress = (&faPathPtr);
	structSize = sizeOfFaPathPtr();
	addressOop = instantiateClassindexableSize(classByteArray(), structSize);
	if (!(addressOop)) {
		dirOop = primitiveFailFor(PrimErrNoMemory);
		goto l1;
	}
	addressOopArrayPointer = arrayValueOf(addressOop);
	memcpy(addressOopArrayPointer, aMachineAddress, structSize);
	dirOop = addressOop;
	l1:	/* end objectFromStruct:size: */;
	resultOop = popRemappableOop()
#endif /* SPURVM */
;
	return (storePointerofObjectwithValue(2, resultOop, dirOop),
		methodReturnValue(resultOop));
}


/*	Answer the value of FA_PATH_MAX (PATH_MAX) for the current VM */

	/* FileAttributesPlugin>>#primitivePathMax */
EXPORT(sqInt)
primitivePathMax(void)
{
	return methodReturnInteger(FA_PATH_MAX);
}


/*	Convert the supplied file name (platform encoded) to the St UTF8 encoded
	byte array
 */

	/* FileAttributesPlugin>>#primitivePlatToStPath */
EXPORT(sqInt)
primitivePlatToStPath(void)
{
    unsigned char *byteArrayPtr;
    fapath faPath;
    sqInt fileName;
    sqInt resultOop;

	fileName = stackObjectValue(0);
	if ((failed())
	 || (!(isBytes(fileName)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faSetPlatPathOop((&faPath), fileName);
	if (failed()) {
		return primitiveFailureCode();
	}
	resultOop = instantiateClassindexableSize(classByteArray(), faGetStPathLen((&faPath)));
	if (!(resultOop)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	byteArrayPtr = arrayValueOf(resultOop);
	memcpy(byteArrayPtr, faGetStPath((&faPath)), faGetStPathLen((&faPath)));
	return methodReturnValue(resultOop);
}


/*	Get the next entry in the directory stream. Answer the name of the entry,
	or nil for the end of the directory stream.
	Arguments:
	- directoryPointer (ByteArray) */

	/* FileAttributesPlugin>>#primitiveReaddir */
EXPORT(sqInt)
primitiveReaddir(void)
{
    void *buffer;
    sqInt dirPointerOop;
    fapath *faPath;
    FAPathPtr *faPathPtr;
    sqInt resultArray;
    sqInt status;
    sqInt structSize;

	dirPointerOop = stackValue(0);
	/* begin structFromObject:size: */
	structSize = sizeof(FAPathPtr);
	if (!((stSizeOf(dirPointerOop)) == structSize)) {
		primitiveFailFor(PrimErrBadArgument);
		faPathPtr = ((void *) 0);
		goto l1;
	}
	buffer = alloca(structSize);
	if (buffer == 0) {
		primitiveFailFor(PrimErrNoCMemory);
	}
	else {
		memcpy(buffer, arrayValueOf(dirPointerOop), structSize);
	}
	faPathPtr = buffer;
	l1:	/* end structFromObject:size: */;
	if (faPathPtr == 0) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	if (!(faValidateSessionId((faPathPtr->sessionId)))) {
		return primitiveFailForOSError(-17 /* badSessionId */);
	}
	faPath = (faPathPtr->faPath);
	status = faReadDirectory(faPath);
	if (status == 1 /* noMoreData */) {
		return methodReturnValue(nilObject());
	}
	if (status < 0) {
		return primitiveFailForOSError(status);
	}

	/* no need to check the status of #processDirectory: as it will have flagged an error with interpreterProxy */
	resultArray = processDirectory(faPath);
	return methodReturnValue(resultArray);
}


/*	Set directoryStream to first entry. Answer dirPointerOop. */

	/* FileAttributesPlugin>>#primitiveRewinddir */
EXPORT(sqInt)
primitiveRewinddir(void)
{
    void *buffer;
    sqInt dirPointerOop;
    fapath *faPath;
    FAPathPtr *faPathPtr;
    sqInt resultOop;
    sqInt status;
    sqInt structSize;

	dirPointerOop = stackValue(0);
	/* begin structFromObject:size: */
	structSize = sizeof(FAPathPtr);
	if (!((stSizeOf(dirPointerOop)) == structSize)) {
		primitiveFailFor(PrimErrBadArgument);
		faPathPtr = ((void *) 0);
		goto l1;
	}
	buffer = alloca(structSize);
	if (buffer == 0) {
		primitiveFailFor(PrimErrNoCMemory);
	}
	else {
		memcpy(buffer, arrayValueOf(dirPointerOop), structSize);
	}
	faPathPtr = buffer;
	l1:	/* end structFromObject:size: */;
	if (faPathPtr == 0) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	if (!(faValidateSessionId((faPathPtr->sessionId)))) {
		return primitiveFailForOSError(-17 /* badSessionId */);
	}
	faPath = (faPathPtr->faPath);
	status = faRewindDirectory(faPath);
	if (status < 0) {
		return primitiveFailForOSError(status);
	}

	/* no need to check the status of #processDirectory: as it will have flagged an error with interpreterProxy */
	resultOop = processDirectory(faPath);
	return methodReturnValue(resultOop);
}


/*	Convert the supplied file name (UTF8 encoded) to the platform encoded byte
	array 
 */

	/* FileAttributesPlugin>>#primitiveStToPlatPath */
EXPORT(sqInt)
primitiveStToPlatPath(void)
{
    unsigned char *byteArrayPtr;
    fapath faPath;
    sqInt fileName;
    sqInt resultOop;

	fileName = stackObjectValue(0);
	if ((failed())
	 || (!(isBytes(fileName)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	faSetStPathOop((&faPath), fileName);
	if (failed()) {
		return primitiveFailureCode();
	}
	resultOop = instantiateClassindexableSize(classByteArray(), faGetPlatPathByteCount((&faPath)));
	if (!(resultOop)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	byteArrayPtr = arrayValueOf(resultOop);
	memcpy(byteArrayPtr, faGetPlatPath((&faPath)), faGetPlatPathByteCount((&faPath)));
	return methodReturnValue(resultOop);
}


/*	Set the owner of the supplied file using chown(). */

	/* FileAttributesPlugin>>#primitiveSymlinkChangeOwner */
EXPORT(sqInt)
primitiveSymlinkChangeOwner(void)
{
    fapath faPath;
    sqInt fileNameOop;
    sqInt groupId;
    sqInt ownerId;
    sqInt status;

	fileNameOop = stackObjectValue(2);
	ownerId = stackIntegerValue(1);
	groupId = stackIntegerValue(0);
	if ((failed())
	 || (!(isBytes(fileNameOop)))) {
		return primitiveFailFor(PrimErrBadArgument);
	}
	
#  if HAVE_CHOWN
	faSetStPathOop((&faPath), fileNameOop);
	if (failed()) {
		return primitiveFailureCode();
	}
	status = lchown(faGetPlatPath((&faPath)), ownerId, groupId);
	if (status != 0) {
		return primitiveFailForOSError(errno);
	}
	return methodReturnValue(nilObject());
#  endif /* HAVE_CHOWN */
	return primitiveFailForOSError(-13 /* unsupportedOperation */);
}


/*	Answer a string containing the version string for this plugin. */

	/* FileAttributesPlugin>>#primitiveVersionString */
EXPORT(sqInt)
primitiveVersionString(void)
{
	popthenPush(1, stringFromCString("2.0.9"));
	return 0;
}


/*	The supplied faPath contains the full path to the current entry while
	iterating over a directory.
	Convert the file name to an object, get the attributes and answer the
	resulting array.
 */

	/* FileAttributesPlugin>>#processDirectory: */
static sqInt
processDirectory(fapath *faPath)
{
    sqInt attributeArray;
    sqInt entryName;
    sqInt resultArray;
    sqInt status;
    sqInt val;

	attributeArray = 0;
	entryName = 0;
	val = 0;
	status = faCharToByteArray(faGetStFile(faPath), (&entryName));
	if (status != 0) {
		return primitiveFailForOSError(status);
	}

	/* If the stat() fails, still return the filename, just no attributes */
	status = attributeArrayformask((&attributeArray), faPath, 1);
	if (status != 0) {
		if (status == -3 /* cantStatPath */) {
			attributeArray = nilObject();
		}
		else {
			return primitiveFailForOSError(status);
		}
	}
	
#if SPURVM
	resultArray = instantiateClassindexableSize(classArray(), 3);

#else /* SPURVM */
	pushRemappableOop(entryName);
	pushRemappableOop(attributeArray);
	resultArray = instantiateClassindexableSize(classArray(), 3);
	attributeArray = popRemappableOop();
	entryName = popRemappableOop()
#endif /* SPURVM */
;
	if (!(resultArray)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	storePointerofObjectwithValue(0, resultArray, entryName);
	storePointerofObjectwithValue(1, resultArray, attributeArray);
	return resultArray;
}


/*	Get the target filename of the supplied symbolic link. */

	/* FileAttributesPlugin>>#readLink:into:maxLength: */
static sqInt
readLinkintomaxLength(char *cPathName, char *cLinkPtr, size_t maxLength)
{
    sqInt len;


	/* len must be signed so that -1 can be communicated as an error. */
	len = 
#  if defined(_WIN32)
		-1
#  else /* defined(_WIN32) */
		readlink(cPathName, cLinkPtr, maxLength)
#  endif /* defined(_WIN32) */
		;
	if (len < 0) {
		
#    if defined(INDEBUG)
		fprintf(stderr, "FileAttributesPlugin: unable to readlink(): %d, errno=%d\n", len, errno);
#    endif /* defined(INDEBUG) */
		/* begin cantReadlink */
		return -8;
	}
	cLinkPtr[len] = 0;
	return len;
}


/*	Note: This is coded so that it can be run in Squeak. */

	/* InterpreterPlugin>>#setInterpreter: */
EXPORT(sqInt)
setInterpreter(struct VirtualMachine *anInterpreter)
{
    sqInt ok;


	/* This may seem tautological, but in a real plugin it checks that the VM provides
	   the version the plugin was compiled against which is the version the plugin expects. */
	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {
		
#if !defined(SQUEAK_BUILTIN_PLUGIN)
		arrayValueOf = interpreterProxy->arrayValueOf;
		classArray = interpreterProxy->classArray;
		classByteArray = interpreterProxy->classByteArray;
		classString = interpreterProxy->classString;
		failed = interpreterProxy->failed;
		instantiateClassindexableSize = interpreterProxy->instantiateClassindexableSize;
		ioLoadFunctionFrom = interpreterProxy->ioLoadFunctionFrom;
		isKindOf = interpreterProxy->isKindOf;
		isBytes = interpreterProxy->isBytes;
		methodReturnBool = interpreterProxy->methodReturnBool;
		methodReturnInteger = interpreterProxy->methodReturnInteger;
		methodReturnValue = interpreterProxy->methodReturnValue;
		nilObject = interpreterProxy->nilObject;
		popthenPush = interpreterProxy->popthenPush;
		popRemappableOop = interpreterProxy->popRemappableOop;
		positive32BitIntegerFor = interpreterProxy->positive32BitIntegerFor;
		primitiveFail = interpreterProxy->primitiveFail;
		primitiveFailFor = interpreterProxy->primitiveFailFor;
#if VM_PROXY_MAJOR > 1 || (VM_PROXY_MAJOR == 1 && VM_PROXY_MINOR >= 14)
		primitiveFailForOSError = interpreterProxy->primitiveFailForOSError;
#else
#if !defined(primitiveFailForOSError)
		primitiveFailForOSError = 0;
#endif
#endif
		primitiveFailureCode = interpreterProxy->primitiveFailureCode;
		pushRemappableOop = interpreterProxy->pushRemappableOop;
		stSizeOf = interpreterProxy->stSizeOf;
		stackIntegerValue = interpreterProxy->stackIntegerValue;
		stackObjectValue = interpreterProxy->stackObjectValue;
		stackValue = interpreterProxy->stackValue;
		storePointerofObjectwithValue = interpreterProxy->storePointerofObjectwithValue;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}


/*	Answer the size of fapath */

	/* FileAttributesPlugin>>#sizeOfFaPath */
static sqInt
sizeOfFaPath(void)
{
	return sizeof(fapath);
}


/*	Answer the size of fapathptr.
	The simulation uses a two element array. */

	/* FileAttributesPlugin>>#sizeOfFaPathPtr */
static sqInt
sizeOfFaPathPtr(void)
{
	return sizeof(FAPathPtr);
}


/*	Answer a new String copied from a null-terminated C string.
	Caution: This may invoke the garbage collector. */

	/* FileAttributesPlugin>>#stringFromCString: */
static sqInt
stringFromCString(const char *aCString)
{
    sqInt len;
    sqInt newString;

	len = strlen(aCString);
	newString = instantiateClassindexableSize(classString(), len);
	if (!(newString)) {
		return primitiveFailFor(PrimErrNoMemory);
	}
	strncpy(arrayValueOf(newString), aCString, len);
	return newString;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

static char _m[] = "FileAttributesPlugin";
void* FileAttributesPlugin_exports[][3] = {
	{(void*)_m, "getModuleName", (void*)getModuleName},
	{(void*)_m, "initialiseModule", (void*)initialiseModule},
	{(void*)_m, "primitiveChangeMode\000\000", (void*)primitiveChangeMode},
	{(void*)_m, "primitiveChangeOwner\000\000", (void*)primitiveChangeOwner},
	{(void*)_m, "primitiveClosedir\000\000", (void*)primitiveClosedir},
	{(void*)_m, "primitiveFileAttribute\000\000", (void*)primitiveFileAttribute},
	{(void*)_m, "primitiveFileAttributes\000\001", (void*)primitiveFileAttributes},
	{(void*)_m, "primitiveFileExists\000\000", (void*)primitiveFileExists},
	{(void*)_m, "primitiveFileMasks\000\377", (void*)primitiveFileMasks},
	{(void*)_m, "primitiveLogicalDrives\000\377", (void*)primitiveLogicalDrives},
	{(void*)_m, "primitiveOpendir\000\000", (void*)primitiveOpendir},
	{(void*)_m, "primitivePathMax\000\377", (void*)primitivePathMax},
	{(void*)_m, "primitivePlatToStPath\000\000", (void*)primitivePlatToStPath},
	{(void*)_m, "primitiveReaddir\000\000", (void*)primitiveReaddir},
	{(void*)_m, "primitiveRewinddir\000\000", (void*)primitiveRewinddir},
	{(void*)_m, "primitiveStToPlatPath\000\000", (void*)primitiveStToPlatPath},
	{(void*)_m, "primitiveSymlinkChangeOwner\000\000", (void*)primitiveSymlinkChangeOwner},
	{(void*)_m, "primitiveVersionString\000\377", (void*)primitiveVersionString},
	{(void*)_m, "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

signed char primitiveChangeModeAccessorDepth = 0;
signed char primitiveChangeOwnerAccessorDepth = 0;
signed char primitiveClosedirAccessorDepth = 0;
signed char primitiveFileAttributeAccessorDepth = 0;
signed char primitiveFileAttributesAccessorDepth = 1;
signed char primitiveFileExistsAccessorDepth = 0;
signed char primitiveOpendirAccessorDepth = 0;
signed char primitivePlatToStPathAccessorDepth = 0;
signed char primitiveReaddirAccessorDepth = 0;
signed char primitiveRewinddirAccessorDepth = 0;
signed char primitiveStToPlatPathAccessorDepth = 0;
signed char primitiveSymlinkChangeOwnerAccessorDepth = 0;

#endif /* ifdef SQ_BUILTIN_PLUGIN */
