
#ifndef _HIB_TIMER_LIST_H_
#define _HIB_TIMER_LIST_H_

#include "osasys.h"
#include "cmsis_os2.h"


#define SW_TIMER_NUM 6
#define USRSW_TIMER_NUM 10


typedef struct
{
    uint8_t timerId;
    uint8_t valid;
    uint8_t swcnt_trans_flag;            // indicate timer has transfer to sc counter
    void *htimer;
	uint64_t swcnt_2048_timeout;
}TimerListHib_t;

typedef struct
{
    uint8_t valid;
    void *htimer;
}TimerHibAON_t;

typedef struct
{
    TimerListHib_t timerlist_hib[SW_TIMER_NUM];
    TimerListHib_t timerlist_hib_usr[USRSW_TIMER_NUM];
}HibTimer_Env_t;


void timerlist_deinit(void);

////////////////////deep sleep timer api////////////////
osTimerId_t timerlist_hib_gethandle(OsaHibTimerId timerId);
INT8 timerlist_hib_add(osTimerId_t htimer, OsaHibTimerId timerId);
INT8 timerlist_hib_delete(OsaHibTimerId timerId);

osTimerId_t timerlist_hib_gethandle_usr(uint8_t timerId);
INT8 timerlist_hib_add_usr(osTimerId_t htimer, uint8_t timerId);
INT8 timerlist_hib_delete_usr(uint8_t timerId);
////////////////////////////////////////////////////////

void timerlist_hib_calculate_sc_target(void);
uint32_t timerlist_hib_getremain_usr(uint8_t timerId);
void timerlist_hib_CheckFlashUpdate(uint8_t *aon_mem);
void timerlist_hib_AfterSlp(void);
void  timerlist_hib_recover_env(void *flash_addr);
uint8_t timerlist_hib_check_wakeup(void);
uint32_t timerlist_hib_getnearest(void);
uint8_t timerlist_hib_checkvalid(uint8_t timerId);
uint8_t timerlist_hib_checkvalid_usr(uint8_t timerId);
INT8 timerlist_hib_replace(osTimerId_t htimer, uint8_t timerId);
INT8 timerlist_hib_replace_usr(osTimerId_t htimer, uint8_t timerId);

///////////////////continuous timer api///////////////////
void timerlist_hib_ct_apprecover(bool first_boot);    //recover ct in app
void timerlist_hib_ct_recover(uint32_t passed_2k_cycle, uint32_t sw_cnt);
uint32_t timerlist_hib_get_8HZcounter(void);
void timerlist_hib_ct_presleep(uint32_t sw_cnt);    //excute before hib sleep: save
uint32_t timerlist_hib_getsecondcount(void);
///////////////////////////////////////////////////////////

#endif
