#ifndef __HT_IC_QCX212_H__
#define __HT_IC_QCX212_H__

#include "qcx212.h"
#include "ic_qcx212.h"

/**
  \fn        void HT_XIC_SetVector(IRQn_Type IRQn, ISRFunc_T vector)
  \brief     Sets an XIC interrupt vector in SRAM based interrupt vector table.
             Use this function to bind the XIC interrupt and application ISR.
  \param[in] IRQn    Interrupt number
  \param[in] vector  Address of interrupt handler function
  \note      The interrupt number must be positive
 */
void HT_XIC_SetVector(IRQn_Type IRQn, ISRFunc_T vector);

/**
  \fn        void HT_XIC_EnableIRQ(IRQn_Type IRQn)
  \brief     Enables a device specific interrupt in the XIC interrupt controller.
  \param[in] IRQn    Interrupt number
  \note      The interrupt number must be positive
 */
void HT_XIC_EnableIRQ(IRQn_Type IRQn);

#endif /*__HT_IC_QCX212_H__ */