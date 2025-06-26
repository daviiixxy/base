#ifndef _CESS_DECODE_ASN_H_
#define _CESS_DECODE_ASN_H_
/*******************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    cessdecodeasn.h
 * Description:  Function external declaration
 * History:      12/17/2018, Originated by flxing
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
*******************************************************************************/

#include "cesscomm.h"
#include "nascommon.h"

/******************************************************************************
* Function Declaration
*******************************************************************************/

void DecodeInvokeComponentHeader(void);
void DecodeReturnResultComponentHeader(void);
void DecodeReturnErrorComponentHeader(void);
void DecodeRejectComponentHeader(void);


#endif


