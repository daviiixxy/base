#include "string.h"
#include "bsp.h"
#include "ostask.h"
#include "debug_log.h"
#include "FreeRTOS.h"
#include "main.h"



/**
  \fn          static void appInit(void *arg)
  \brief
  \return
*/
static void appInit(void *arg)
{
   // add user defined init code

    return;


}

/**
  \fn          int main_entry(void)
  \brief       main entry function.
  \return
*/
void main_entry(void)
{
    BSP_CommonInit();
    osKernelInitialize();
    registerAppEntry(appInit, NULL);
    if (osKernelGetState() == osKernelReady)
    {
        osKernelStart();
    }
    while(1);

}
