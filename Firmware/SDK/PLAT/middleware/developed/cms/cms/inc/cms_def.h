/******************************************************************************
 * (C) Copyright 2018 Qualcomm International Ltd.
 * All Rights Reserved
*******************************************************************************
 *  Filename: cms_def.h
 *
 *  Description: Communication Modem Service layer/task MARCO/COMMON definition
 *
 *  History:
 *
 *  Notes:
 *
******************************************************************************/
#ifndef __CMS_DEF_H__
#define __CMS_DEF_H__


/******************************************************************************
 *****************************************************************************
 * CMS COMMON MARCO
 *****************************************************************************
******************************************************************************/


/******************************************************************************
 * SRC HANDLER
 *  15          12  11          8   7       5   4                0
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * |       R       |  channel ID   | SUB AT ID |        TID        |
 * +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * Note:
 * 1> Channel ID:
 *  Channel ID 0, is reserved for internal.
 *  Channel ID 1, used for AT CMD from UART (default).
 * 2> SUB AT ID
 *  If several AT CMD correlated with same CMI REQ ID, this "AT ID" is used to distinguish
 *   which AT CMD when CMI CNF comes; so MAX 8 AT CMD could use one same CMI REQ ID
 * 3> TID: AT Asynchronous Timer index
 *  Used to index AT CMD guard timer
******************************************************************************/

/*
 * Internal handler, channel ID set to 0.
 * Internal valid value: 0x01 ~ 0xFF
*/
#define BROADCAST_IND_HANDLER       0x0001
#define CMS_REQ_HANDLER             0x0060
#define PS_DIAL_REQ_HANDLER         0x0061
#define PS_STK_REQ_RSP_HANDLER      0x0062
#define APP_SYNC_REQ_HANDLER        0x0063
#define PS_LPP_REQ_RSP_HANDLER      0x0064
#define GTP_MM_RSP_HANDLER          0x0065

/*
 * used in ps_syn_cnf.c, AppPsBlockReq
 * Handler from: 0x0020 ~ 0x0030
*/
#define APP_PS_BLOCK_REQ_NUM        16
#define APP_PS_BLOCK_REQ_START_HANDLER  0x0020
#define APP_PS_BLOCK_REQ_END_HANDLER    (APP_PS_BLOCK_REQ_START_HANDLER + APP_PS_BLOCK_REQ_NUM)



#define CMS_SET_SRC_HANDLER(TID, subAtId, chanId)   ((UINT16)(((TID)&0x1F) | (((subAtId)<<5)&0xE0) | (((chanId)<<8)&0xF00)))

#define CMS_GET_HANDLER_TID(srcHandler)             ((srcHandler) & 0x1F)
#define CMS_GET_HANDLER_SUB_ATID(srcHandler)        (((srcHandler) & 0xE0) >> 5)
#define CMS_GET_HANDLER_CHAN_ID(srcHandler)         (((srcHandler) & 0xF00) >> 8)
#define CMS_GET_UINT16_HANDLER(srcHandler)          ((srcHandler) & 0xFFFF)

/******************************************************************************
 * 3 bits SUB AT ID, value: 0 - 7
 * 1> 0 is default value
 * 2> 0 - 4, used for EC
 * 3> 5,6,7, used for REF
******************************************************************************/
/*
 * CMS default SUB AT ID
 *  CMS_GET_HANDLER_SUB_ATID()
*/
#define CMS_DEFAULT_SUB_AT_ID       0

#define CMS_EC_MAX_SUB_AT_ID        4

/*
 * SUB AT ID, used for REF AT CMD
*/
#define CMS_REF_SUB_AT_1_ID         5
#define CMS_REF_SUB_AT_2_ID         6
#define CMS_REF_SUB_AT_3_ID         7



/******************************************************************************
 * CMI REQ/CNF/IND ID:
 *  15          11                               0
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |   SG ID   |           PRIM ID                 |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *
 * CMI: CIOT Modem Interface
******************************************************************************/
#define CMS_GET_CMI_SG_ID(reqId)                    (((reqId)>>12)&0x000F)
#define CMS_GET_CMI_PRIM_ID(reqId)                  ((reqId)&0x0FFF)
#define CMS_SET_CMI_REQ_CNF_ID(sgId, primId)        ((UINT16)(((sgId)<<12)|((primId)&0x0FFF)))



/*
 * STR end byte: '\0'
*/
#define CMS_NULL_CHAR_LEN           1

/******************************************************************************
 *****************************************************************************
 * CMS COMMON ENUM
 *****************************************************************************
******************************************************************************/

/*
 * CMS channel ID, MAX: 15
 * 1> 1st: 0, is reserved for: AT indication, and internal using
 * 2> 2nd: 1, default AT channel, used for AT CMD send from UART.
 * 3> 3rd: 2, reserved for AT SDK API (RIL API).
*/
typedef enum
{
    CMS_CHAN_RSVD = 0,
    CMS_CHAN_IND = CMS_CHAN_RSVD,
    CMS_CHAN_1 = 1,
    CMS_CHAN_DEFAULT = CMS_CHAN_1,
    CMS_CHAN_UART = CMS_CHAN_1,     //default is used for ATCMD from UART
    AT_CHAN_DEFAULT = CMS_CHAN_1,

    CMS_CHAN_2 = 2,
    CMS_RIL_API_CHAN = 2,   //channel reserved for SDK API (RIL API)
    AT_RIL_API_CHAN = 2,

    /*
     * still/only channel 3 & 4 are used for other purposes.
    */
    CMS_CHAN_3 = 3,
    CMS_CHAN_4 = 4,

    CMS_CHAN_NUM = 5,

    CMS_CHAN_MAX = 15
}cmsChanId;



/*
 * CMS task OSA timer ID defination:
 *
 * 16 bits timerID
 * 15      12                    0
 * +-------+---------------------+
 * | modId |   timerId in modId  |
 * +-------+---------------------+
 *  MSB 4 bits: use to distinguish which sub-module in CMS task, so MAX 16 sub-modes
*/
typedef enum CmsOsaTimerSubModId_enum
{
    CMS_TIMER_AT_SUB_MOD_ID = 0,
    CMS_TIMER_PS_LPP_SUB_MOD_ID = 1,
    CMS_TIMER_APP_PS_BLOCK_REQ_SUB_MOD_ID = 2,
    //...


    CMS_TIMER_SUB_MOD_ID_MAX = 15
}CmsOsaTimerSubModId;

#define CMS_SET_OSA_TIMER_ID(subMid, subTid)    (UINT16)((((subMid)<<12)&0xF000) | ((subTid)&0xFFF))

#define CMS_GET_OSA_TIMER_SUB_MOD_ID(timerId)   (((timerId)>>12)&0x0F)


/******************************************************************************
 * cmsDeepPmuCtrlBitmap
 * Whether CMS task allow the PMU enter the hibernate/sleep2 state (only AON memory)
 * Each sub-module has a bit to indicate whether allow it:
 *  0 - allow, 1 - not allow;
 * So when all bits is set to 0 (cmsDeepPmuCtrlBitmap == 0) just means CMS task
 *  is in IDLE state, and allow to enter hibernate state
******************************************************************************/
extern UINT32 cmsDeepPmuCtrlBitmap;

/*
*/
typedef enum CmsDeepPmuVoteSubMod_Enum
{
    CMS_AT_UART_CHAN_PMU_MOD,

    //...

    CMS_PMU_MOD_MAX = 32
}CmsDeepPmuVoteSubMod;


#define CMS_SUB_MOD_ALLOW_DEEP_PMU(subMod)              \
do {                                                    \
    if ((subMod)<32 && (subMod)>=0)                     \
        (cmsDeepPmuCtrlBitmap &= (~(1<<(subMod))));     \
    else                                                \
        OsaCheck(FALSE, subMod, cmsDeepPmuCtrlBitmap, 0); \
}while(FALSE)


#define CMS_SUB_MOD_NOT_ALLOW_DEEP_PMU(subMod)          \
do {                                                    \
    if ((subMod)<32 && (subMod)>=0)                     \
        (cmsDeepPmuCtrlBitmap |= (1<<(subMod)));        \
    else                                                \
        OsaCheck(FALSE, subMod, cmsDeepPmuCtrlBitmap, 0); \
}while(FALSE)



#endif

