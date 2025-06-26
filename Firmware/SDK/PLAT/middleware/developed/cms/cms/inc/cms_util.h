/******************************************************************************
 * (C) Copyright 2018 Qualcomm International Ltd.
 * All Rights Reserved
*******************************************************************************
 *  Filename: cms_util.h
 *
 *  Description: CMS (Communication Modem Service) utility header file
 *
 *  History:
 *
 *  Notes:
 *
******************************************************************************/
#ifndef __CMS_UTIL_H__
#define __CMS_UTIL_H__

#include "CommonTypedef.h"
#include "debug_log.h"
#include "cms_def.h"
#include "cms_api.h"
#include "cmsis_os2.h"
#include "mw_config.h"
#include "mw_aon_info.h"


/******************************************************************************
 *****************************************************************************
 * MARCO
 *****************************************************************************
******************************************************************************/

/*
 * 4 bytes MAGIC words
*/
#define CMS_MAGIC_WORDS         0xA4B6C9D2
#define CMS_MAGIC_WORDS_SIZE    4
#define CMS_SYN_API_BODY_MAX    1024

typedef CmsRetId (*CmsSynCallback)(UINT16 inputSize, void *pInput, UINT16 outputSize, void *pOutput);

//typedef void (*CmsBlockCallback)(CmsBlockApiInfo *pApiInfo);
typedef void (*CmsBlockCallback)(void *pArg);

typedef void (*CmsNonBlockCallback)(UINT16 paramSize, void *pParam);


/******************************************************************************
 *****************************************************************************
 * ENUM
 *****************************************************************************
******************************************************************************/



/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

/*
 * SIG: SIG_CMS_SYN_API_REQ
 * API called in CMS task, and without timeout
*/
typedef struct CmsSynApiInfo_Tag
{
    osSemaphoreId_t sem;
    CmsRetId        retCode;        //CmsRetId
    CmsSynCallback  cmsSynFunc;
    UINT16          inputSize;
    UINT16          outputSize;
    UINT32          hdrMagic;

    /*
     * +----------------------+--------------+---------+--------------+-------+
     * | CmsSynApiInfo        | input PARAM  | MAGIC   | output PARAM | MAGIC |
     * +----------------------+--------------+---------+--------------+-------+
     * ^                      ^              ^         ^              ^
     * pApiInfo               param          pInMagic  pOutAddr       pOutMagic
    */

    UINT8           param[];     /*input + output parameters, and should 4 bytes aligned*/
}CmsSynApiInfo;  //20 bytes

typedef struct CmsSynApiReq_Tag
{
    CmsSynApiInfo   *pApiInfo;
}CmsSynApiReq;


/*
 * SIG: SIG_CMS_BLOCK_API_REQ
 * API called in CMS task, and timeout setting
*/
typedef struct CmsBlockApiInfo_Tag
{
    osSemaphoreId_t     sem;
    CmsRetId            retCode;        //CmsRetId
    CmsBlockCallback    cmsBlockFunc;
    UINT32              timeOutMs;      //timeOut in MILLISECONDS
    UINT16              inputSize;
    UINT16              outputSize;

    void                *pInput;
    void                *pOutput;
}CmsBlockApiInfo;  //28 bytes

typedef struct CmsBlockApiReq_Tag
{
    CmsBlockApiInfo   *pApiInfo;
}CmsBlockApiReq;

/*
 * SIG: SIG_CMS_NON_BLOCK_API_REQ
 * API called in CMS task
*/
typedef struct CmsNonBlockApiReq_Tag
{
    CmsNonBlockCallback cmsNonBlockFunc;

    UINT16      paramSize;
    UINT16      rsvd;

    UINT8       param[];
}CmsNonBlockApiReq;

/******************************************************************************
 *****************************************************************************
 * API
 *****************************************************************************
******************************************************************************/
INT8 cmsDigitCharToNum(UINT8 ch);
BOOL cmsHexStrToUInt(UINT32 *pOutput, const UINT8 *pHexStr, UINT32 strMaxLen);
BOOL cmsDecStrToUInt(UINT32 *pOutput, const UINT8 *pDecStr, UINT32 strMaxLen);
BOOL cmsBinStrToUInt(UINT32 *pOutput, const UINT8 *pBinStr, UINT32 strMaxLen);
void cmsByteToBitString(UINT8 *outString, UINT8 byte, UINT8 outStrLen);


BOOL cmsBePureIntStr(CHAR * str);

/*
 * "1234" -> {0x12, 0x34}
*/
INT32 cmsHexStrToHex(UINT8 *pOutput, UINT32 outBufSize, const CHAR *pHexStr, UINT32 strMaxLen);

/*
 * {0x12, 0x34} -> "1234"
*/
INT32 cmsHexToHexStr(CHAR *pOutStr, UINT32 outBufSize, const UINT8 *pHexData, UINT32 hexLen);

/*
 * 3 -> '3'
*/
INT8 cmsNumToChar(UINT8 num);

/*
 * CMS API CALL, API called in CMS task
*/
CmsRetId cmsSynApiCall(CmsSynCallback synFunc, UINT16 inputSize, void *pInput, UINT16 outputSize, void *pOutPut);
CmsRetId cmsHighPriSynApiCall(CmsSynCallback synFunc, UINT16 inputSize, void *pInput, UINT16 outputSize, void *pOutPut);
CmsRetId cmsBlockApiCall(CmsBlockCallback blockFunc, UINT16 inputSize, void *pInput, UINT16 outputSize, void *pOutPut, UINT32 timeOutMs);
CmsRetId cmsNonBlockApiCall(CmsNonBlockCallback nonBlockFunc, UINT16 inputSize, void *pInput);


#endif

