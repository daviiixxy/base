#ifndef __UICC_CTRL_DRV_SIG_H__
#define __UICC_CTRL_DRV_SIG_H__
/******************************************************************************
Copyright:      - 2017, All rights reserved by Qualcomm
File name:      - uiccdrvsig.h
Description:    - define all signals received by UiccDrv module.
Function List:  -
History:        - 09/05/2017, Originated by xlhu
******************************************************************************/
/*********************************************************************************
* Includes
*********************************************************************************/
#include "uiccctrldata.h"

/*********************************************************************************
* Macros
*********************************************************************************/
#define APDU_CMD_CLASS_BYTE         0
#define APDU_CMD_INSTRUCTION        1
#define APDU_CMD_P1                 2
#define APDU_CMD_P2                 3
#define APDU_CMD_P3                 4
#define APDU_CMD_DATA               5

#define EXPECTED_RSP_APDU_LEN       0
#define APDU_SW_SIZE                2

#define     APDU_CASE_1_HEADER                4 /* CLA + INS + P1 + P2 */
#define     APDU_CASE_2_HEADER                5 /* CLA + INS + P1 + P2 + Le */
#define     APDU_CASE_3_HEADER                5 /* CLA + INS + P1 + P2 + Lc */
#define     APDU_CASE_4_HEADER                6 /* CLA + INS + P1 + P2 + Lc + Le */


/******************************************************************************
 ************************** sleep state ***********************************
 * Whether uiccctrl and uiccdrv tasks allow the PMU enter sleep1/sleep2/hibernate state
 * uiccctrl task (bit 1) and  uiccdrv task (bit 2) has a bit to indicate whether allow it:
 *  0 - allow, 1 - not allow;
 ******************************************************************************
******************************************************************************/
extern UINT8 uiccCtrlDrvSleepBitmap;
#define UICC_CTRL_DRV_ALLOW_SLEEP1(taskId)     \
do {                                            \
    if ((taskId) == UICC_CTRL_TASK_ID)             \
        (uiccCtrlDrvSleepBitmap &= (~(1<<0)));   \
    else if ((taskId) == UICC_DRV_TASK_ID)         \
        (uiccCtrlDrvSleepBitmap &= (~(1<<1))); \
}while(FALSE)

#define UICC_CTRL_DRV_NOT_ALLOW_SLEEP1(taskId) \
do {                                            \
    if ((taskId) == UICC_CTRL_TASK_ID)             \
        (uiccCtrlDrvSleepBitmap |= (1<<0));      \
    else if ((taskId) == UICC_DRV_TASK_ID)         \
        (uiccCtrlDrvSleepBitmap |= (1<<1)); \
}while(FALSE)

#define UICC_CTRL_DRV_ALLOW_DEEP_SLEEP(taskId)     \
do {                                            \
    if ((taskId) == UICC_CTRL_TASK_ID)             \
        (uiccCtrlDrvSleepBitmap &= (~(1<<2)));   \
    else if ((taskId) == UICC_DRV_TASK_ID)         \
        (uiccCtrlDrvSleepBitmap &= (~(1<<3))); \
}while(FALSE)

#define UICC_CTRL_DRV_NOT_ALLOW_DEEP_SLEEP(taskId) \
do {                                            \
    if ((taskId) == UICC_CTRL_TASK_ID)             \
        (uiccCtrlDrvSleepBitmap |= (1<<2));      \
    else if ((taskId) == UICC_DRV_TASK_ID)         \
        (uiccCtrlDrvSleepBitmap |= (1<<3)); \
}while(FALSE)

void UiccModuleVotePmuState(void);

/*********************************************************************************
* Type Definition
*********************************************************************************/


/********************************************************************************
* UiccCtrl -> UiccDrv
*********************************************************************************/

/*********************************************************************************
* Enums
*********************************************************************************/

typedef enum TerminateCardCauseTag
{
    TERMINATE_INVALID_CARD,
    TERMIANTE_POWER_DOWN
}
TerminateCardCause;




/*********************************************************************************
* STRUCTS
*********************************************************************************/

/*
 * SIGID: SIG_UICC_CTRL_DRV_INIT_CARD
*/
typedef GosEmptySignal UiccCtrlDrvInitCardReq;

/*
 * SIGID: SIG_UICC_CTRL_DRV_CMD_REQ
 * send Command APDU to card. It consists of a data block containing a C-APDU
 * coded as described in TS 102 221 section 11.
*/
typedef struct UiccCtrlDrvCmdReqTag
{
    UINT16                           reserved;
    UINT16                           cmdLength;          /* command data length */
    UINT8                            cmdData[];          /* command data contents */
}
UiccCtrlDrvCmdReq;

/*
 * SIGID: SIG_UICC_CTRL_DRV_LARGE_APDU_REQ
 *
*/
typedef UiccCtrlDrvCmdReq UiccCtrlDrvLargeApduReq;


/*
 * SIGID: SIG_UICC_CTRL_DRV_RESET_REQ
*/
typedef struct UiccCardResetReqTag
{
    BOOL                       warmReset;
    UINT8                      reserved1;
    UINT16                     reserved2;
}
UiccCardResetReq;

/*
 * SIGID: SIG_UICC_CTRL_DRV_TERMINATE_REQ
*/
typedef struct UiccCardTerminateReqTag
{
    UINT8                     TerminateCause;//TerminateCardCause
    UINT8                     reserved1;
    UINT16                    reserved2;
}
UiccCardTerminateReq;

/*
 * SIGID: SIG_UICC_CTRL_DRV_CLOCK_STOP_REQ
*/
typedef GosEmptySignal UiccCtrlDrvStopClockModeReq;

/*
 * SIGID: SIG_UICC_PMU_DEEP_SLEEP_DEACTIVATE_IND
*/
typedef GosEmptySignal UiccPmuDeepSleepDeactivateInd;


#endif

