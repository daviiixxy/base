/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    ps_phy_if.h
 * Description:  API interface implementation header file for PHY service
 * History:      Rev1.0   2018-10-12
 *
 ****************************************************************************/
#ifndef __PS_PHY_IF_H__
#define __PS_PHY_IF_H__
#include "cms_util.h"

CmsRetId phyGetPhyInfo(UINT32 atHandle);
CmsRetId phySetPhyInfo(UINT32 atHandle, UINT32 module, INT32 *cfgParams, UINT8 valueParamNum);
CmsRetId phyGetPhyModuleInfo(UINT32 atHandle, UINT32 module);

#endif

