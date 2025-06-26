#ifndef _LCS_ENCODE_ASN_H_
#define _LCS_ENCODE_ASN_H_
/*******************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    lcsencodeasn.h
 * Description:  Function external declaration
 * History:      12/17/2018, Originated by flxing
 *
 ******************************************************************************/

/*******************************************************************************
* Includes
*******************************************************************************/

/******************************************************************************
* Function Declaration
*******************************************************************************/

extern void ConstructLcsMolr(MolrRequest    *pMolr, FacilityIe     *pFacility);
extern void ConstructLcsNotificationResult(LcsLocationNotificationResult   *pNotificationResullt,
                       FacilityIe     *pFacility);

#endif

