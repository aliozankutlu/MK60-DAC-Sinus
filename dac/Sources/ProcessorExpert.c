/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MK60FN1M0VLQ15
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-08-09, 13:45, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "DMA1.h"
#include "DAC.h"
#include "Inhr1.h"
#include "PDB.h"
#include "modulePIT0.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#define SINUS_LENGTH 256

int16_t Sinus[SINUS_LENGTH] = {
		2048,2248,2447,2642,2831,3013,3185,3346,
		3495,3630,3750,3853,3939,4007,4056,4085,
		4095,4085,4056,4007,3939,3853,3750,3630,
		3495,3346,3185,3013,2831,2642,2447,2248,
		2048,1847,1648,1453,1264,1082,910,749,
		600,465,345,242,156,88,39,10,
		0,10,39,88,156,242,345,465,
		600,749,910,1082,1264,1453,1648,1847,
		2048,2248,2447,2642,2831,3013,3185,3346,
		3495,3630,3750,3853,3939,4007,4056,4085,
		4095,4085,4056,4007,3939,3853,3750,3630,
		3495,3346,3185,3013,2831,2642,2447,2248,
		2048,1847,1648,1453,1264,1082,910,749,
		600,465,345,242,156,88,39,10,
		0,10,39,88,156,242,345,465,
		600,749,910,1082,1264,1453,1648,1847,
		2048,2248,2447,2642,2831,3013,3185,3346,
		3495,3630,3750,3853,3939,4007,4056,4085,
		4095,4085,4056,4007,3939,3853,3750,3630,
		3495,3346,3185,3013,2831,2642,2447,2248,
		2048,1847,1648,1453,1264,1082,910,749,
		600,465,345,242,156,88,39,10,
		0,10,39,88,156,242,345,465,
		600,749,910,1082,1264,1453,1648,1847,
		2048,2248,2447,2642,2831,3013,3185,3346,
		3495,3630,3750,3853,3939,4007,4056,4085,
		4095,4085,4056,4007,3939,3853,3750,3630,
		3495,3346,3185,3013,2831,2642,2447,2248,
		2048,1847,1648,1453,1264,1082,910,749,
		600,465,345,242,156,88,39,10,
		0,10,39,88,156,242,345,465,
		600,749,910,1082,1264,1453,1648,1847,
		
};

/* User includes (#include below this line is not maintained by Processor Expert) */

LDD_TDeviceData *DacPtr;


void setDACBuffer()
{
	 SIM_SCGC2 |= SIM_SCGC2_DAC0_MASK;                                   
	 DAC_PDD_EnableDevice(DAC0_BASE_PTR,PDD_DISABLE); /* Disable device */
	  
	 DAC0_DAT0H = DAC_DATH_DATA(0x08);                                   
	  /* DAC0_DAT0L: DATA=0 */
	  DAC0_DAT0L = DAC_DATL_DATA(0x00);                                   
	  /* DAC0_DAT1H: ??=0,??=0,??=0,??=0,DATA=0 */
	  DAC0_DAT1H = DAC_DATH_DATA(0x08);                                   
	  /* DAC0_DAT1L: DATA=0 */
	  DAC0_DAT1L = DAC_DATL_DATA(0x00);                                   
	  /* DAC0_DAT2H: ??=0,??=0,??=0,??=0,DATA=0 */
	  DAC0_DAT2H = DAC_DATH_DATA(0x08);                                   
	  /* DAC0_DAT2L: DATA=0 */
	  DAC0_DAT2L = DAC_DATL_DATA(0x00);                                   
	  /* DAC0_DAT3H: ??=0,??=0,??=0,??=0,DATA=0 */
	  DAC0_DAT3H = DAC_DATH_DATA(0x08);                                   
	  /* DAC0_DAT3L: DATA=0 */
	  DAC0_DAT3L = DAC_DATL_DATA(0x00);                                   
	  /* DAC0_C2: DACBFRP=0,DACBFUP=3 */
	  DAC0_C2 = (DAC_C2_DACBFRP(0x00) | DAC_C2_DACBFUP(0x03));                                   
	  /* DAC0_C1: DMAEN=1,??=0,??=0,DACBFWM=3,DACBFMD=0,DACBFEN=1 */
	  DAC0_C1 = DAC_C1_DMAEN_MASK |
	            DAC_C1_DACBFWM(0x03) |
	            DAC_C1_DACBFMD(0x00) |
	            DAC_C1_DACBFEN_MASK;       
	  /* DAC0_SR: ??=0,??=0,??=0,??=0,??=0,DACBFWMF=0,DACBFRPTF=0,DACBFRPBF=0 */
	  DAC0_SR = 0x00U;                                   
	  /* DAC0_C0: DACEN=1,DACRFS=1,DACTRGSEL=0,DACSWTRG=0,LPEN=0,DACBWIEN=1,DACBTIEN=1,DACBBIEN=0 */
	  DAC0_C0 = DAC_C0_DACEN_MASK |
	            DAC_C0_DACRFS_MASK |
	            DAC_C0_DACBWIEN_MASK |
	            DAC_C0_DACBTIEN_MASK;       
	  DAC_PDD_EnableDevice(DAC0_BASE_PTR,PDD_ENABLE); /* Disable device */
}

void resetDACBuffer()
{
	
	 SIM_SCGC2 |= SIM_SCGC2_DAC0_MASK;                                   
	 DAC_PDD_EnableDevice(DAC0_BASE_PTR,PDD_DISABLE); /* Disable device */
		 
	 DAC0_DAT0H = DAC_DATH_DATA(0x08);                                   
	  /* DAC0_DAT0L: DATA=0 */
	  DAC0_DAT0L = DAC_DATL_DATA(0x00);                                   
	  /* DAC0_C2: DACBFRP=0,DACBFUP=0x0F */
	  DAC0_C2 = (DAC_C2_DACBFRP(0x00) | DAC_C2_DACBFUP(0x0F));                                   
	  /* DAC0_C1: DMAEN=1,??=0,??=0,DACBFWM=0,DACBFMD=0,DACBFEN=0 */
	  DAC0_C1 = (DAC_C1_DMAEN_MASK | DAC_C1_DACBFWM(0x00) | DAC_C1_DACBFMD(0x00));                                   
	  /* DAC0_SR: ??=0,??=0,??=0,??=0,??=0,DACBFWMF=0,DACBFRPTF=0,DACBFRPBF=0 */
	  DAC0_SR = 0x00U;                                   
	  /* DAC0_C0: DACEN=1,DACRFS=1,DACTRGSEL=0,DACSWTRG=0,LPEN=0,DACBWIEN=1,DACBTIEN=1,DACBBIEN=0 */
	  DAC0_C0 = DAC_C0_DACEN_MASK |
	            DAC_C0_DACRFS_MASK |
	            DAC_C0_DACBWIEN_MASK |
	            DAC_C0_DACBTIEN_MASK;     
	  DAC_PDD_EnableDevice(DAC0_BASE_PTR,PDD_ENABLE); /* Disable device */
	  DAC0_DAT0H = DAC_DATH_DATA(0x08);                                   
	  /* DAC0_DAT0L: DATA=0 */
	  DAC0_DAT0L = DAC_DATL_DATA(0x00);  
	  
}
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  PDB_Init();  
  DacPtr = DAC_Init(NULL); 
  modulePIT0_Init();
  
  PDB0_SC |= PDB_SC_SWTRIG_MASK;  /* Now, trigger PDB module */
  /* Write your code here */
  for(;;) { }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
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
