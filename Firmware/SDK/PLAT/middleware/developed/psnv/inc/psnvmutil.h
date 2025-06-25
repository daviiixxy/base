#ifndef __PS_NVM_UTIL_H__
#define __PS_NVM_UTIL_H__
/******************************************************************************
 ******************************************************************************
 Copyright:      - 2017- Copyrights of Qualcomm Ltd.
 File name:      - psnvmutil.h
 Description:    - Protocol Stack NVM basic utility
 History:        - 13/09/2017, Originated by jcweng
 ******************************************************************************
******************************************************************************/
#include "pssys.h"

/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/

/******************************************************************************
 * PS NVM filer header structure
 * by now: 36 bytes
******************************************************************************/
#define PS_NVM_FILE_NAME_SIZE 32
typedef struct PsNvmFileHeader_Tag
{
    UINT8  fName[PS_NVM_FILE_NAME_SIZE];
    UINT16 fileBodySize; //file body size, not include size of header;
    UINT8  version;
    UINT8  checkSum;
}PsNvmFileHeader;

/*
 * if no NVM file found, use the default value.
*/
typedef void (*PsNvmSetDefaultValueFunc)(void *ctxBuf, UINT16 bufSize);
/*
 * adjust NVM file, from OLD VERSION -> CUR/Latest verion
*/
typedef BOOL (*PsNvmAdjustVersionFunc)(UINT8 oldVer, void *oldCtx, UINT16 oldCtxSize, void *curCtx, UINT16 curCtxSize);
/*
 * 44 bytes
*/
typedef struct PsNvmFileOper_Tag
{
    UINT8 fileId;   //PsNvmFileIdEnum
    UINT8 curVersion;
    UINT16 fileSize;

    UINT8 fileName[PS_NVM_FILE_NAME_SIZE];

    PsNvmSetDefaultValueFunc setDefaultFunc;
    PsNvmAdjustVersionFunc   adjustVerFunc;
}PsNvmFileOper;


/******************************************************************************
 *****************************************************************************
 * Functions
 *****************************************************************************
******************************************************************************/


#endif

