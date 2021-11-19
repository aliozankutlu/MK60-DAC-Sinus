/* ###################################################################
**     Filename    : Events.c
**     Project     : ProcessorExpert
**     Processor   : MK60FN1M0VLQ15
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-08-09, 13:45, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

extern void setDACBuffer();
extern void resetDACBuffer();

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MK60FN1M0LQ15]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

PE_ISR(PDB_ISR)
{
// NOTE: The routine should include actions to clear the appropriate
//       interrupt flags.
//
}
/*
** ===================================================================
**     Event       :  DAC_OnComplete (module Events)
**
**     Component   :  DAC [DAC_LDD]
*/
/*!
**     @brief
**         Called at the end of a DMA transfer. If the Half complete
**         property in initialization section is enabled, this event is
**         also called when current major iteration count reaches the
**         halfway point. See SetEventMask() and GetEventMask() methods.
**         This event is enabled only if Interrupt service property and
**         DMA property are enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void DAC_OnComplete(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

uint8 state=0;
PE_ISR(delayInterrupt)
{
	PIT_TFLG0 = PIT_TFLG_TIF_MASK;
	PIT_TCTRL0 &= ~PIT_TCTRL_TEN_MASK;
	switch(state)
	{
	case 0:
		setDACBuffer();
		state = 1;
		PIT_LDVAL0 = PIT_LDVAL_TSV(0x30D3*3);  
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
	    break;
	case 1: 
		resetDACBuffer();
		state = 0;
		PIT_LDVAL0 = PIT_LDVAL_TSV(0x30D3*1); 
		PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;
		break;
	default:
		break;
	}
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
