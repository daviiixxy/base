#ifndef _CESS_COMMON_H_
#define _CESS_COMMON_H_
/*******************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    cesscomm.h
 * Description:  The common definition of SS operation and the ASN operation
 * History:      12/17/2018, Originated by flxing
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
*******************************************************************************/

#include "cenascomm.h"

/******************************************************************************
 * Macros
 ******************************************************************************/

#ifndef PARAMETER_NOT_USED
#define PARAMETER_NOT_USED(p)
#endif

#ifndef offset
#ifdef WIN32
#define offset(type, body) ((UINT32)&(((type *)0))->body)
#else


#if defined(__CC_ARM)
#define offset(type, body) ((UINT32)__INTADDR__(&(((type *)0)->body)))
#endif

#if defined(__GNUC__)
#define offset(type, body) __builtin_offsetof(type, body)
#endif

#endif
#endif

/* Coding of Component type tag */
#define     COMPONENT_TYPE_TAG_INVOKE           0xA1
#define     COMPONENT_TYPE_TAG_RETURN_RESULT    0xA2
#define     COMPONENT_TYPE_TAG_RETURN_ERROR     0xA3
#define     COMPONENT_TYPE_TAG_REJECT           0xA4

/* Coding of Component ID tag */
#define     INVOKE_ID       0x02
#define     LINKED_ID       0x80

/* Coding of Operation Code tag */
#define     OPERATION_CODE_TAG      0x02

/* Coding of Sequence and set tags */
#define     SEQUENCE_TAG    0x30
#define     SET_FLAG        0x31

typedef enum ComponentTypeTag
{
    COMPONENT_TYPE_INVOKE        = 0x01,
    COMPONENT_TYPE_RETURN_RESULT = 0x02,
    COMPONENT_TYPE_RETURN_ERROR  = 0x03,
    COMPONENT_TYPE_REJECT        = 0x04,
    COMPONENT_TYPE_INVALID       = 0xFF
}
ComponentType;

typedef struct InvokeId_Tag
{
    BOOL    present;
    INT8    id;
}
InvokeId;

typedef enum OperationCode_Tag
{
    LCS_MOLR                  = 115,
    LCS_LOCATION_NOTIFICATION = 116
}
OperationCode;

typedef enum MapErrorCode_Tag
{
    MAP_ERROR_CODE_NULL                     = 0,    
    MAP_ERROR_CODE_SUBSCRIPTION_VIOLATION   = 19,    
    MAP_ERROR_CODE_FACILITY_NOT_SUPPORTED   = 21,    
    MAP_ERROR_CODE_SYSTEM_FAILURE           = 34,
    MAP_ERROR_CODE_DATA_MISSING             = 35,
    MAP_ERROR_CODE_UNEXPECTED_DATA_VALUE    = 36,
    MAP_ERROR_CODE_POSITION_METHOD_FAILURE  = 54
}
MapErrorCode;

typedef enum MapErrorType_Tag
{
    MAP_ERROR_TYPE_NULL = 0,
    MAP_ERROR_TYPE_SUBSCRIPTION_VIOLATION,
    MAP_ERROR_TYPE_FACILITY_NOT_SUPPORTED,
    MAP_ERROR_TYPE_SYSTEM_FAILURE,
    MAP_ERROR_TYPE_DATA_MISSING,
    MAP_ERROR_TYPE_UNEXPECTED_DATA_VALUE,
    MAP_ERROR_TYPE_POSITION_METHOD_FAILURE
}
MapErrorType;

typedef struct SubscriptionViolation_Tag
{
    ExtensionContainer  extensionContainer;
}
SubscriptionViolation;

typedef struct FacilityNotSupported_Tag
{
    ExtensionContainer  extensionContainer;
    BOOL                shapeOfLocationEstimateNotSupported;
    BOOL                neededLcsCapabilityNotSupportedInServingNode;
}
FacilityNotSupported;

typedef struct UnexpectedDataValue_Tag
{
    ExtensionContainer  extensionContainer;
    BOOL                unexpectedSubscriber;
}
UnexpectedDataValue;

typedef struct DataMissing_Tag
{
    ExtensionContainer  extensionContainer;
}
DataMissing;

typedef enum NetworkResource_Tag
{
    NETWORK_RESOURCE_PLMN             = 0,
    NETWORK_RESOURCE_HLR              = 1,
    NETWORK_RESOURCE_VLR              = 2,
    NETWORK_RESOURCE_PVLR             = 3,
    NETWORK_RESOURCE_CONTROLLING_MSC  = 4,
    NETWORK_RESOURCE_VMSC             = 5,
    NETWORK_RESOURCE_EIR              = 6,
    NETWORK_RESOURCE_RSS              = 7
}
NetworkResource;

typedef union SystemFailure_Tag
{
    NetworkResource     ntworkResource;
    //extensibleSystemFailure   TBD
}
SystemFailure;

typedef enum PositionMethodFailureDiagnostic_Tag
{
    POSITION_METHOD_FAILURE_CONGESTION              = 0,
    INSUFFICIENT_RESOURCES                          = 1,
    INSUFFICIENT_MEASUREMENT_DATA                   = 2,
    INCONSISTENT_MEASUREMENT_DATA                   = 3,
    LOCATION_PROCEDURE_NOT_COMPLETED                = 4,
    LOCATION_PROCEDURE_NOT_SUPPORTED_BY_TARGET_MS   = 5,
    QOS_NOT_ATTAINABLE                              = 6,
    POSITION_METHOD_NOT_AVAILABLE_IN_NETWORK        = 7,
    POSITION_METHOD_NOT_AVAILABLE_IN_LOCATION_AREA  = 8
}
PositionMethodFailureDiagnostic;

typedef struct PositionMethodFailureDiagnosticData_Tag
{
    BOOL                                present;
    PositionMethodFailureDiagnostic     diagnostic;
}
PositionMethodFailureDiagnosticData;

typedef struct PositionMethodFailure_Tag
{
    PositionMethodFailureDiagnosticData     diagnostic;
    ExtensionContainer                      extensionContainer;
}
PositionMethodFailure;

typedef union MapErrorParameter_Tag
{
    INT8                    dummy;
    SubscriptionViolation   subscriptionViolation;
    UnexpectedDataValue     unexpectedDataValue;
    SystemFailure           systemFailure;
    PositionMethodFailure   positionMethodFailure;
}
MapErrorParameter;

typedef struct ReturnErrorCode_Tag
{
    MapErrorCode        code;
    MapErrorType        type;
    MapErrorParameter   parameter;
}
ReturnErrorCode;

typedef enum ProblemCode_Tag
{
    /* General Problem Codes */
    GENERAL_PROBLEM_CODE_UNRECOGNISED_COMPONENT         = 0x00,
    GENERAL_PROBLEM_CODE_MISTYPED_COMPONENT             = 0x01,
    GENERAL_PROBLEM_CODE_BADLY_STRUCTURED_COMPONENT     = 0x02,

    /* Invoke Problem Codes */
    INVOKE_PROBLEM_CODE_DUPLICATED_INVOKE_ID            = 0x00,
    INVOKE_PROBLEM_CODE_UNRECOGNIZED_OPERATION          = 0x01,
    INVOKE_PROBLEM_CODE_MISTYPED_PARAMETER              = 0x02,
    INVOKE_PROBLEM_CODE_RESOURCE_LIMITATION             = 0x03,
    INVOKE_PROBLEM_CODE_INITIATING_RELEASE              = 0x04,
    INVOKE_PROBLEM_CODE_UNRECOGNIZED_LINKED_ID          = 0x05,
    INVOKE_PROBLEM_CODE_LINKED_RESPONSE_UNEXPECTED      = 0x06,
    INVOKE_PROBLEM_CODE_UNEXPECTED_LINKED_OPERATION     = 0x07,

    /* Return Result Problem Codes */
    RETURN_RESULT_PROBLEM_CODE_UNRECOGNIZED_INVOKE_ID   = 0x00,
    RETURN_RESULT_PROBLEM_CODE_RETURN_RESULT_UNEXPECTED = 0x01,
    RETURN_RESULT_PROBLEM_CODE_MISTYPED_PARAMETER       = 0x02,

    /* Return Error Problem Codes */
    RETURN_ERROR_PROBLEM_CODE_UNRECOGNIZED_INVOKE_ID    = 0x00,
    RETURN_ERROR_PROBLEM_CODE_RETURN_ERROR_UNEXPECTED   = 0x01,
    RETURN_ERROR_PROBLEM_CODE_UNRECOGNIZED_ERROR        = 0x02,
    RETURN_ERROR_PROBLEM_CODE_UNEXPECTED_ERROR          = 0x03,
    RETURN_ERROR_PROBLEM_CODE_MISTYPED_PARAMETER        = 0x04
}
ProblemCode;

typedef enum ProblemTag_Tag
{
    GENERAL_PROBLEM_TAG         = 0x80,
    INVOKE_PROBLEM_TAG          = 0x81,
    RETURN_RESULT_PROBLEM_TAG   = 0x82,
    RETURN_ERROR_PROBLEM_TAG    = 0x83
}
ProblemTag;

typedef struct RejectProblemCode_Tag
{
    ProblemCode               code;
    ProblemTag                tag;
}
RejectProblemCode;

typedef struct ReturnResultOperationCode_Tag
{
    BOOL                present;
    OperationCode       operCode;
}
ReturnResultOperationCode;

typedef union ComponentData_Tag
{
    OperationCode               operationCode;
    ReturnErrorCode             error;
    RejectProblemCode           problem;
    ReturnResultOperationCode   returnResultOperCode;
}
ComponentData;

typedef struct ComponentHeader_Tag
{
    ComponentType       componentType;
    InvokeId            invokeId;
    InvokeId            linkedId;
    ComponentData       componentData;
    INT8                parametersOffset;
    INT8                componentLen;
}
ComponentHeader;


/******************************************************************************

         Universal class tag assignments
UNIVERSAL 0               Reserved for use by the encoding rules
UNIVERSAL 1               BOOL type
UNIVERSAL 2               Integer type
UNIVERSAL 3               Bitstring type
UNIVERSAL 4               Octetstring type
UNIVERSAL 5               Null type
UNIVERSAL 6               Object identifier type
UNIVERSAL 7               Object descriptor type
UNIVERSAL 8               External type and Instance-of type
UNIVERSAL 9               Real type
UNIVERSAL 10              Enumerated type
UNIVERSAL 11              Embedded-pdv type
UNIVERSAL 12              UTF8String type
UNIVERSAL 13              Relative object identifier type
UNIVERSAL 14              The time type
UNIVERSAL 15              Reserved for future editions of this Recommendation | International Standard
UNIVERSAL 16              Sequence and Sequence-of types
UNIVERSAL 17              Set and Set-of types
UNIVERSAL 18-22, 25-30    Character string types
UNIVERSAL 23-24           UTCTime and GeneralizedTime
UNIVERSAL 31-34           DATE, TIME-OF-DAY, DATE-TIME and DURATION respectively
UNIVERSAL 35              OID internationalized resource identifier type
UNIVERSAL 36              Relative OID internationalized resource identifier type
UNIVERSAL 37-...          Reserved for addenda to this Recommendation | International Standard

******************************************************************************/


#define     TIMEOUT_PERIOD_ESTABLISH    SECONDS_TO_TICKS(10)

typedef struct PendingLcsData_Tag
{
    UINT16          length;
    UINT8           *pData;
    OperationCode   opCode;
}
PendingLcsData;

typedef struct SsGlobals_Tag
{
    BOOL                    bSuspended;
    BOOL                    bWaitEstCnf;
    UINT8                   tiValue;            /* Transaction Identifier */
    CenasTimer              tLcsl;              /* T(LCSL) = 10s - 300s */
    CenasTimer              tEstablish;
    UINT8                   invokeId;
    VerificationResponse    allowance;
    PendingLcsData          pendingLcsData;    /* Pending LCS message */
    CcmCessLppUnitDataReq  *pendingLppData;    /* Pending LPP message */
}
SsGlobals;

extern void CessInitialise(void);
extern void SsStartTimer(CenasTimer    *timerEntity);
extern void CeSsProcTimerExpiry(UINT16  timerEnum);
extern void CessProcessSignal(SignalBuf *sig);

#endif



