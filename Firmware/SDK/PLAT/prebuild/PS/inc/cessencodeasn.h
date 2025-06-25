#ifndef _CESS_ENCODE_ASN_H_
#define _CESS_ENCODE_ASN_H_
/*******************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    cessencodeasn.h
 * Description:  Function external declaration
 * History:      12/17/2018, Originated by flxing
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
*******************************************************************************/

#include "cesscomm.h"

/******************************************************************************
* Function Declaration
*******************************************************************************/


INT8 EncodeInvokeComponentHeader(INT8   parametersLength, INT8  invokeId,
          BOOL  linkedIdPresent, INT8    linkedId,
          OperationCode     operationCode, UINT8     *pDest);

INT8 EncodeReturnResultComponentHeader(INT8 parmLen, INT8 invokeId,
        ReturnResultOperationCode operationCode, UINT8 *pDest);


#endif

