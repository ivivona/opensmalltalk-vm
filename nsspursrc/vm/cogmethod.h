/* Automatically generated by
	CCodeGenerator VMMaker.oscog-eem.735 uuid: ee13367a-8346-4ce8-a124-276cba680fc1
 */

typedef struct {
	unsigned short	homeOffset;
	unsigned short	startpc;
	unsigned int	padToWord;
	unsigned		cmNumArgs : 8;
	unsigned		cmType : 3;
	unsigned		cmRefersToYoung : 1;
	unsigned		cpicHasMNUCase : 1;
	unsigned		cmUsageCount : 3;
	unsigned		cmUsesPenultimateLit : 1;
	unsigned		cmUsesMethodClass : 1;
	unsigned		cmUnusedFlags : 2;
	unsigned		stackCheckOffset : 12;
 } CogBlockMethod;

typedef struct _CogMethod {
	sqLong	objectHeader;
	unsigned		cmNumArgs : 8;
	unsigned		cmType : 3;
	unsigned		cmRefersToYoung : 1;
	unsigned		cpicHasMNUCase : 1;
	unsigned		cmUsageCount : 3;
	unsigned		cmUsesPenultimateLit : 1;
	unsigned		cmUsesMethodClass : 1;
	unsigned		cmUnusedFlags : 2;
	unsigned		stackCheckOffset : 12;
	unsigned short	blockSize;
	unsigned short	blockEntryOffset;
	sqInt	methodObject;
	sqInt	methodHeader;
	sqInt	selector;
	struct _CogMethod *nextMethod;
 } CogMethod;

#define NewspeakCogMethod CogMethod
