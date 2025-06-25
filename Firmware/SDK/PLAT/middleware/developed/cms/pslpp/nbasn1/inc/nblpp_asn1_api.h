#ifndef __NBLPP_ASN1_API_H__
#define __NBLPP_ASN1_API_H__



#include "nblpp_asn1_type.h"




#define __ASN1_ENC_FUNCS__

void AsnEnLPP_Message(AsnEnContext *pAsnContext, LPP_Message *pIE);


#define __ASN1_DEC_FUNCS__

void AsnDeLPP_Message(AsnDeContext *pAsnContext, LPP_Message *pIE);


#define __ASN1_CONTAINER_ENC_FUNCS__



#define __ASN1_CONTAINER_DEC_FUNCS__


#endif
