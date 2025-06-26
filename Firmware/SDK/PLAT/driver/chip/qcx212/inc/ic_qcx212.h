/****************************************************************************
 *
 * Copy right:   2018-, Copyrigths of Qualcomm Ltd.
 * File name:    ic_qcx212.h
 * Description:  QCX212 interrupt controller header file
 * History:      Rev1.0   2018-11-15
 *
 ****************************************************************************/

#ifndef _IC_QCX212_H
#define _IC_QCX212_H

#include "qcx212.h"
#include "Driver_Common.h"

/**
  \addtogroup xic_interface_gr
  \{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define NUM_XIC_MODULE                      (2U)      /**< number of XIC module */
#define NUM_XIC0_INT                        (32U)     /**< number of interrupts in XIC0 */
#define NUM_XIC1_INT                        (32U)     /**< number of interrupts in XIC1 */
#define MAX_NUM_XIC_INT                     (32U)     /**< maximum number of interrupts in XIC */

/** ISR function type define */
typedef void ( *ISRFunc_T )(void);

/*******************************************************************************
 * API
 ******************************************************************************/

#ifdef __cplusplus
 extern "C" {
#endif

/**
  \fn        void IC_PowupInit(void)
  \brief     Initialize the interrupt controller, including HW configuration and ISR initialization,
             called when POR or wakeup from Hibernate, in which the SRAM contents have been lost.
 */
void IC_PowupInit(void);
/**
  \fn        void IC_Powoff(void)
  \brief     DeInitialize the interrupt controller, including HW configuration and ISR initialization.
 */
void IC_Powoff(void);
/**
  \fn        void XIC_SetVector(IRQn_Type IRQn, ISRFunc_T vector)
  \brief     Sets an XIC interrupt vector in SRAM based interrupt vector table.
             Use this function to bind the XIC interrupt and application ISR.
  \param[in] IRQn    Interrupt number
  \param[in] vector  Address of interrupt handler function
  \note      The interrupt number must be positive
 */
void XIC_SetVector(IRQn_Type IRQn, ISRFunc_T vector);

/**
  \fn        void XIC_EnableIRQ(IRQn_Type IRQn)
  \brief     Enables a device specific interrupt in the XIC interrupt controller.
  \param[in] IRQn    Interrupt number
  \note      The interrupt number must be positive
 */
void XIC_EnableIRQ(IRQn_Type IRQn);

/**
  \fn        void XIC_DisableIRQ(IRQn_Type IRQn)
  \brief     Disables a device specific interrupt in the XIC interrupt controller.
  \param[in] IRQn    Interrupt number
  \note      The interrupt number must be positive
 */
void XIC_DisableIRQ(IRQn_Type IRQn);

/**
  \fn        void XIC_BackupIRQSetting(uint32_t *mask0, uint32_t *mask1, uint32_t *clrovf0)
  \brief     backup the interrupt mask and ovf setting before sleep
  \param[out] mask0, mask1, clrovf0 to store the irq mask and ovf setting
  \note
 */
void XIC_BackupIRQSetting(uint32_t *mask0, uint32_t *mask1, uint32_t *clrovf0);

/**
  \fn        void XIC_RestoreIRQSetting(uint32_t mask0, uint32_t mask1, uint32_t clrovf0)
  \brief     restore the interrupt mask and ovf setting after sleep
  \param[in] mask0, mask1, clrovf0 is the stored value before sleep
  \note
 */
void XIC_RestoreIRQSetting(uint32_t mask0, uint32_t mask1, uint32_t clrovf0);

/**
  \fn        void XIC_SetPendingIRQ(IRQn_Type IRQn)
  \brief     Sets the pending bit of a device specific interrupt in the XIC pending register,
             mainly used for SW generating interrupt.
  \param[in] IRQn    Interrupt number
  \note      The interrupt number must be positive
 */
void XIC_SetPendingIRQ(IRQn_Type IRQn);

/**
  \fn        void XIC_ClearPendingIRQ(IRQn_Type IRQn)
  \brief     Clears the pending bit of a device specific interrupt in the XIC pending register.
  \param[in] IRQn    Interrupt number
  \note      The interrupt number must be positive
 */
void XIC_ClearPendingIRQ(IRQn_Type IRQn);

/**
  \fn        uint32_t XIC_LatchIRQ(XIC_TypeDef* xic)
  \brief     Latch the pending interrupt status to the latch register and read out.
  \param[in] xic     Pointer to XIC instance
  \return    Interrupt status
 */
uint32_t XIC_LatchIRQ(XIC_TypeDef* xic);

/**
  \fn        void XIC_SuppressOvfIRQ(IRQn_Type IRQn)
  \brief     Suppress overflow IRQ
  \param[in] IRQn    Interrupt number
  \note      The interrupt number must be positive
 */
void XIC_SuppressOvfIRQ(IRQn_Type IRQn);

/**
  \fn        void XIC_ClearAllPendingIRQ(XIC_TypeDef* xic)
  \brief     Clears all pending bits of a XIC interrupt controller.
  \param[in] xic     Pointer to XIC instance
 */
void XIC_ClearAllPendingIRQ(XIC_TypeDef* xic);

/** \} */

#ifdef __cplusplus
}
#endif

#endif

