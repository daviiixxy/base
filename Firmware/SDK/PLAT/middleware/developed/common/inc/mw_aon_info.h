#ifndef __MW_AON_INFO_H__
#define __MW_AON_INFO_H__
/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    mw_aon_info.h
 * Description:
 * History:      Rev1.0
 *
 ****************************************************************************/
#include "commontypedef.h"
#include "cms_sock_mgr.h"
#include "mw_config.h"

#include "ecpm_qcx212_external.h"
#include "slpman_qcx212.h"

/******************************************************************************
 *****************************************************************************
 * MARCO/ENUM
 *****************************************************************************
******************************************************************************/
#define MID_WARE_AON_MAGIC_WORDS    0xA3B5C7D9



/******************************************************************************
 *****************************************************************************
 * STRUCT
 *****************************************************************************
******************************************************************************/


typedef struct MidWareSockAonInfo_Tag
{
    CmsSockMgrHibContext sockContext;
}MidWareSockAonInfo;    //92 bytes

typedef struct MidWareDefaultAonDnsCfg_Tag
{
    UINT8   ipv4Dns[MID_WARE_DEFAULT_DNS_NUM][MID_WARE_IPV4_ADDR_LEN];
    UINT8   ipv6Dns[MID_WARE_DEFAULT_DNS_NUM][MID_WARE_IPV6_ADDR_LEN];
}MidWareDefaultAonDnsCfg;     //40 bytes


/******************************************************************************
 *
 * Middleware info stored in AON memory, limited size: PMU_AON_MID_WARE_MEM_SIZE
 *
******************************************************************************/
typedef struct MidWareAonInfo_Tag
{
    /*
     * AT channel config
     *  As some configuration should not be maintained after reboot, then these settings should be store in AON memory
    */
    MidWareAtChanConfig     atChanConfig[MID_WARE_USED_AT_CHAN_NUM];    //12*4 = 48 bytes


    UINT32          boolBitInfo;        //all bitvalue reserved to 0

    /*
     * used for EC socket public setting
    */
    MidWareAtSocketConfig   ecSocPubCfg;    //4 bytes

    /*
     * socket aon info
    */
    MidWareSockAonInfo      mwSockAonInfo;  //92 bytes

    /*
    * mw aon dns server
    */
    MidWareDefaultAonDnsCfg mwDefaultAonDns; //40 bytes
}MidWareAonInfo;



/******************************************************************************
 *****************************************************************************
 * API
 *****************************************************************************
******************************************************************************/

/*
 * INIT
*/
void mwAonInfoInit(void);

/*
 * AON memory changed, meed to save
*/
void mwAonSaveConfig(void);

/*
 * get one AT channel config item value
*/
UINT32 mwAonGetAtChanConfigItemValue(UINT8 chanId, MidWareATChanCfgEnum cfgEnum);

/*
 * set and save one AT channel config item value
*/
void mwAonSetAndSaveAtChanConfigItemValue(UINT8 chanId, MidWareATChanCfgEnum cfgEnum, UINT32 value);

/*
 * set one AT channel config item value, need call API: mwAonSaveConfig()
*/
void mwAonSetAtChanConfigItemValue(UINT8 chanId, MidWareATChanCfgEnum cfgEnum, UINT32 value, BOOL *bChanged);


BOOL mwAonGetDefaultAonDnsCfg(MidWareDefaultAonDnsCfg *mwDefaultAonDnsCfg);

void mwAonSetDefaultAonDnsCfgAndSave(MidWareDefaultAonDnsCfg *mwDefaultAonDnsCfg);

void mwGetAonEcSocPublicConfig(UINT8 *mode, UINT8 *publicDlPkgNumMax, UINT16 *publicDlBufferToalSize);

void mwSetAonEcSocPublicConfig(UINT8 mode, UINT8 publicDlPkgNumMax, UINT16 publicDlBufferToalSize);


/*
 * used for SOCK task
*/
MidWareSockAonInfo* mwGetSockAonInfo(void);
void mwSetSockAonInfo(MidWareSockAonInfo *pSockAonInfo);
void mwSockAonInfoChanged(void);

void mwAonTaskRecovery(void);

#endif


