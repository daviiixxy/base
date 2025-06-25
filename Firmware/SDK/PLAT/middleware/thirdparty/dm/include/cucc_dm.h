/****************************************************************************
 *
 * Copy right:   2017-, Copyrigths of Qualcomm Ltd.
 * File name:    app.h
 * Description:  QCX212 at command demo entry header file
 * History:      Rev1.0   2018-07-12
 *
 ****************************************************************************/

#define AR_RETRY_TIME_MAX        3
#define AR_RETRY_TIME_OUT        10 /*secs*/

#define AR_REGISTER_TIME_OUT        1
#define AR_REGISTER_TIME_WAIT       0

#define AR_REGISTER_SUCC           1
#define AR_REGISTER_NO_SUCC        0

#define AR_RESEND_COUNT_MAX        5
#define CUCC_AUTO_REG_TASK_STACK_SIZE   4096 
#define CUCC_COAP_LOCAL_PORT   5188

typedef enum {
    INDEX_01  = 0,
    INDEX_02  = 1,
    INDEX_03  = 2,
    INDEX_04  = 3,
    INDEX_05  = 4,
    INDEX_06  = 5,
    INDEX_07  = 6,
    INDEX_08  = 7,

    INDEX_MAX,
} AutoRegIndex;

typedef enum {
    AR_RC_OK,
    AR_RC_FAIL,
    AR_RC_INIT_FAIL,
    AR_RC_CLIENT_FAIL,
	AR_RC_CLIENT_RECREATE,
    AR_RC_SEND_FAIL,
    AR_RC_RECV_FAIL,    
	AR_RC_WAIT_TIMER,	
    
    AR_RC_MAX
}AutoRegRet;

typedef enum {
    AR_TIMER_OUT_RETRY_MODE = 1,
	AR_TIMER_OUT_NORM_MODE = 2,
}AutoRegTimer;

typedef struct AutoRegProcSeqTbl_
{
    INT32 funcIndex;
    INT32 (* ProcFunc)(void);
    UINT32 nextFuncSeqNumb[3];
}AutoRegProcSeqTbl;

void cuccAutoRegisterInit(void);

