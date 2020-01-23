/* Automatically generated by
	VMPluginCodeGenerator VMMaker.oscog-eem.2672 uuid: 335f401c-b41b-48dc-b7be-2d33156978af
   from
	CameraPlugin VMMaker.oscog-eem.2672 uuid: 335f401c-b41b-48dc-b7be-2d33156978af
 */
static char __buildInfo[] = "CameraPlugin VMMaker.oscog-eem.2672 uuid: 335f401c-b41b-48dc-b7be-2d33156978af " __DATE__ ;



#include "config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
#endif

#include "CameraPlugin.h"
#include "sqMemoryAccess.h"


/*** Function Prototypes ***/
EXPORT(const char*) getModuleName(void);
EXPORT(sqInt) primCameraName(void);
EXPORT(sqInt) primCloseCamera(void);
EXPORT(sqInt) primFrameExtent(void);
EXPORT(sqInt) primGetFrame(void);
EXPORT(sqInt) primGetParam(void);
EXPORT(sqInt) primOpenCamera(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine *anInterpreter);


/*** Variables ***/

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static sqInt (*classString)(void);
static sqInt (*failed)(void);
static void * (*firstIndexableField)(sqInt oop);
static sqInt (*instantiateClassindexableSize)(sqInt classPointer, sqInt size);
static sqInt (*isWords)(sqInt oop);
static sqInt (*methodReturnInteger)(sqInt integer);
static sqInt (*pop)(sqInt nItems);
static sqInt (*popthenPush)(sqInt nItems, sqInt oop);
static sqInt (*primitiveFail)(void);
static sqInt (*stSizeOf)(sqInt oop);
static sqInt (*stackIntegerValue)(sqInt offset);
static sqInt (*stackValue)(sqInt offset);
static sqInt (*success)(sqInt aBoolean);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern sqInt classString(void);
extern sqInt failed(void);
extern void * firstIndexableField(sqInt oop);
extern sqInt instantiateClassindexableSize(sqInt classPointer, sqInt size);
extern sqInt isWords(sqInt oop);
extern sqInt methodReturnInteger(sqInt integer);
extern sqInt pop(sqInt nItems);
extern sqInt popthenPush(sqInt nItems, sqInt oop);
extern sqInt primitiveFail(void);
extern sqInt stSizeOf(sqInt oop);
extern sqInt stackIntegerValue(sqInt offset);
extern sqInt stackValue(sqInt offset);
extern sqInt success(sqInt aBoolean);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =;
#ifdef SQUEAK_BUILTIN_PLUGIN
static 	"CameraPlugin VMMaker.oscog-eem.2672 (i)";
#else
static 	"CameraPlugin VMMaker.oscog-eem.2672 (e)";
#endif



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


/*	Get the name for the camera with the given number. Fail if the camera
	number is greater than the number of available cameras.
 */

	/* CameraPlugin>>#primCameraName */
EXPORT(sqInt)
primCameraName(void)
{
    sqInt cameraNum;
    sqInt count;
    char* dst;
    sqInt i;
    char* nameStr;
    sqInt resultOop;

	cameraNum = stackIntegerValue(0);
	if (failed()) {
		return 0;
	}
	nameStr = CameraName(cameraNum);
	if (nameStr == null) {
		success(0);
		return 0;
	}
	count = (int) strlen(nameStr);
	resultOop = instantiateClassindexableSize(classString(), count);
	dst = ((char *) (firstIndexableField(resultOop)));
	for (i = 0; i < count; i += 1) {
		dst[i] = (nameStr[i]);
	}
	popthenPush(2, resultOop);
	return 0;
}


/*	Close the camera. Do nothing if it was not open. */

	/* CameraPlugin>>#primCloseCamera */
EXPORT(sqInt)
primCloseCamera(void)
{
    sqInt cameraNum;

	cameraNum = stackIntegerValue(0);
	if (failed()) {
		return 0;
	}
	CameraClose(cameraNum);
	pop(1);
	return 0;
}


/*	Answer the frame extent of the given camera, or zero if the camera is not
	open. The extent is 16 bits of width and height packed into a single
	integer. 
 */

	/* CameraPlugin>>#primFrameExtent */
EXPORT(sqInt)
primFrameExtent(void)
{
    sqInt cameraNum;

	cameraNum = stackIntegerValue(0);
	if (!(failed())) {
		methodReturnInteger(CameraExtent(cameraNum));
	}
	return 0;
}


/*	Copy a camera frame into the given Bitmap. The Bitmap should be for a Form
	of depth 32 that is the same width and height as the current camera frame.
	Fail if the camera is not open or if the bitmap is not the right size. If
	successful, answer the number of frames received from the camera since the
	last call. If this is zero, then there has been no change.
 */

	/* CameraPlugin>>#primGetFrame */
EXPORT(sqInt)
primGetFrame(void)
{
    unsigned char *bitmap;
    sqInt bitmapOop;
    sqInt cameraNum;
    sqInt pixCount;
    sqInt result;

	cameraNum = stackIntegerValue(1);
	bitmapOop = stackValue(0);
	success(isWords(bitmapOop));
	if (failed()) {
		return 0;
	}
	bitmap = ((unsigned char *) (firstIndexableField(bitmapOop)));
	pixCount = stSizeOf(bitmapOop);
	result = CameraGetFrame(cameraNum, bitmap, pixCount);
	if (result < 0) {
		return primitiveFail();
	}
	methodReturnInteger(result);
	return 0;
}


/*	Answer the given integer parameter of the given camera. */

	/* CameraPlugin>>#primGetParam */
EXPORT(sqInt)
primGetParam(void)
{
    sqInt cameraNum;
    sqInt paramNum;

	cameraNum = stackIntegerValue(1);
	paramNum = stackIntegerValue(0);
	if (!(failed())) {
		methodReturnInteger(CameraGetParam(cameraNum, paramNum));
	}
	return 0;
}


/*	Open a camera. Takes one argument, the index of the device to open. */

	/* CameraPlugin>>#primOpenCamera */
EXPORT(sqInt)
primOpenCamera(void)
{
    sqInt cameraNum;
    sqInt desiredFrameHeight;
    sqInt desiredFrameWidth;
    sqInt ok;

	cameraNum = stackIntegerValue(2);
	desiredFrameWidth = stackIntegerValue(1);
	desiredFrameHeight = stackIntegerValue(0);
	if (failed()) {
		return 0;
	}
	ok = CameraOpen(cameraNum, desiredFrameWidth, desiredFrameHeight);
	if (ok == 0) {
		success(0);
		return 0;
	}
	pop(3);
	return 0;
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
		classString = interpreterProxy->classString;
		failed = interpreterProxy->failed;
		firstIndexableField = interpreterProxy->firstIndexableField;
		instantiateClassindexableSize = interpreterProxy->instantiateClassindexableSize;
		isWords = interpreterProxy->isWords;
		methodReturnInteger = interpreterProxy->methodReturnInteger;
		pop = interpreterProxy->pop;
		popthenPush = interpreterProxy->popthenPush;
		primitiveFail = interpreterProxy->primitiveFail;
		stSizeOf = interpreterProxy->stSizeOf;
		stackIntegerValue = interpreterProxy->stackIntegerValue;
		stackValue = interpreterProxy->stackValue;
		success = interpreterProxy->success;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}


#ifdef SQUEAK_BUILTIN_PLUGIN

static char _m[] = "CameraPlugin";
void* CameraPlugin_exports[][3] = {
	{(void*)_m, "getModuleName", (void*)getModuleName},
	{(void*)_m, "primCameraName\000\000", (void*)primCameraName},
	{(void*)_m, "primCloseCamera\000\000", (void*)primCloseCamera},
	{(void*)_m, "primFrameExtent\000\000", (void*)primFrameExtent},
	{(void*)_m, "primGetFrame\000\000", (void*)primGetFrame},
	{(void*)_m, "primGetParam\000\000", (void*)primGetParam},
	{(void*)_m, "primOpenCamera\000\000", (void*)primOpenCamera},
	{(void*)_m, "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

signed char primCameraNameAccessorDepth = 0;
signed char primCloseCameraAccessorDepth = 0;
signed char primFrameExtentAccessorDepth = 0;
signed char primGetFrameAccessorDepth = 0;
signed char primGetParamAccessorDepth = 0;
signed char primOpenCameraAccessorDepth = 0;

#endif /* ifdef SQ_BUILTIN_PLUGIN */
