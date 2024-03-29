/*
    FreeRTOS V7.1.1 - Copyright (C) 2012 Real Time Engineers Ltd.
	

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!
    
    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    
    http://www.FreeRTOS.org - Documentation, training, latest information, 
    license and contact details.
    
    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell 
    the code with commercial support, indemnification, and middleware, under 
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under 
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

/* 

Changes from V2.6.0

	+ AVR port - Replaced the inb() and outb() functions with direct memory
	  access.  This allows the port to be built with the 20050414 build of
	  WinAVR.
*/

#include <stdlib.h>
#include <avr/interrupt.h>

#include "FreeRTOS.h"
#include "task.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the AVR port.
 *----------------------------------------------------------*/

/* Start tasks with interrupts enabled. */
#define portFLAGS_INT_ENABLED					( ( portSTACK_TYPE ) 0x80 )

/*-----------------------------------------------------------*/

/* We require the address of the pxCurrentTCB variable, but don't want to know
any details of its type. */
typedef void tskTCB;
extern volatile tskTCB * volatile pxCurrentTCB;

/*-----------------------------------------------------------*/

/* If stack tracing is active, declare a variable which will be used by the task
 * wrapper class to get the address of the top of the stack just after a task has
 * been created. The variable is static so it retains its value. */
#if (INCLUDE_uxTaskGetStackHighWaterMark == 1)
	size_t portStackTopForTask;
#endif

/*-----------------------------------------------------------*/

/* 
 * Macro to save all the general purpose registers, the save the stack pointer
 * into the TCB.  
 * 
 * The first thing we do is save the flags then disable interrupts.  This is to 
 * guard our stack against having a context switch interrupt after we have already 
 * pushed the registers onto the stack - causing the 32 registers to be on the 
 * stack twice. 
 * 
 * r1 is set to zero as the compiler expects it to be thus, however some
 * of the math routines make use of R1. 
 * 
 * The interrupts will have been disabled during the call to portSAVE_CONTEXT()
 * so we need not worry about reading/writing to the stack pointer. 
 */

/*----------------MODIFIED BY TEAM BALANCE BOT-----------------------*/	
/* Added #ifs to allow compiler to choose whether to use 3 byte PC (2560) 
 * or 2 byte PC (lesser microcontrollers) */
#if __AVR_3_BYTE_PC__
	#define portSAVE_CONTEXT()								\
	asm volatile (	"push	r0						\n\t"	\
					"in		r0, __SREG__			\n\t"	\
					"cli							\n\t"	\
					"push	r0						\n\t"	\
					"in		r0, 0x3b				\n\t"	\
					"push	r0						\n\t"	\
					"in		r0, 0x3c				\n\t"	\
					"push	r0						\n\t"	\
					"push	r1						\n\t"	\
					"clr	r1						\n\t"	\
					"push	r2						\n\t"	\
					"push	r3						\n\t"	\
					"push	r4						\n\t"	\
					"push	r5						\n\t"	\
					"push	r6						\n\t"	\
					"push	r7						\n\t"	\
					"push	r8						\n\t"	\
					"push	r9						\n\t"	\
					"push	r10						\n\t"	\
					"push	r11						\n\t"	\
					"push	r12						\n\t"	\
					"push	r13						\n\t"	\
					"push	r14						\n\t"	\
					"push	r15						\n\t"	\
					"push	r16						\n\t"	\
					"push	r17						\n\t"	\
					"push	r18						\n\t"	\
					"push	r19						\n\t"	\
					"push	r20						\n\t"	\
					"push	r21						\n\t"	\
					"push	r22						\n\t"	\
					"push	r23						\n\t"	\
					"push	r24						\n\t"	\
					"push	r25						\n\t"	\
					"push	r26						\n\t"	\
					"push	r27						\n\t"	\
					"push	r28						\n\t"	\
					"push	r29						\n\t"	\
					"push	r30						\n\t"	\
					"push	r31						\n\t"	\
					"lds	r26, pxCurrentTCB		\n\t"	\
					"lds	r27, pxCurrentTCB + 1	\n\t"	\
					"in		r0, 0x3d				\n\t"	\
					"st		x+, r0					\n\t"	\
					"in		r0, 0x3e				\n\t"	\
					"st		x+, r0					\n\t"	\
				);
#else	
	#define portSAVE_CONTEXT()							\
	asm volatile (	"push	r0					\n\t"	\
					"in		r0, __SREG__			\n\t"	\
					"cli							\n\t"	\
					"push	r0					\n\t"	\
					"push	r1					\n\t"	\
					"clr	r1						\n\t"	\
					"push	r2					\n\t"	\
					"push	r3					\n\t"	\
					"push	r4					\n\t"	\
					"push	r5					\n\t"	\
					"push	r6					\n\t"	\
					"push	r7					\n\t"	\
					"push	r8					\n\t"	\
					"push	r9					\n\t"	\
					"push	r10					\n\t"	\
					"push	r11					\n\t"	\
					"push	r12					\n\t"	\
					"push	r13					\n\t"	\
					"push	r14					\n\t"	\
					"push	r15					\n\t"	\
					"push	r16					\n\t"	\
					"push	r17					\n\t"	\
					"push	r18					\n\t"	\
					"push	r19					\n\t"	\
					"push	r20					\n\t"	\
					"push	r21					\n\t"	\
					"push	r22					\n\t"	\
					"push	r23					\n\t"	\
					"push	r24					\n\t"	\
					"push	r25					\n\t"	\
					"push	r26					\n\t"	\
					"push	r27					\n\t"	\
					"push	r28					\n\t"	\
					"push	r29					\n\t"	\
					"push	r30					\n\t"	\
					"push	r31					\n\t"	\
					"lds	r26, pxCurrentTCB		\n\t"	\
					"lds	r27, pxCurrentTCB + 1	\n\t"	\
					"in		r0, 0x3d				\n\t"	\
					"st		x+, r0				\n\t"	\
					"in		r0, 0x3e				\n\t"	\
					"st		x+, r0				\n\t"	\
				);
#endif

/* 
 * Opposite to portSAVE_CONTEXT().  Interrupts will have been disabled during
 * the context save so we can write to the stack pointer. 
 */
#if __AVR_3_BYTE_PC__	
#define portRESTORE_CONTEXT()	/* Three byte PC restore*/	\
	asm volatile (	"lds	r26, pxCurrentTCB		\n\t"	\
					"lds	r27, pxCurrentTCB + 1	\n\t"	\
					"ld		r28, x+					\n\t"	\
					"out	__SP_L__, r28			\n\t"	\
					"ld		r29, x+					\n\t"	\
					"out	__SP_H__, r29			\n\t"	\
					"pop	r31						\n\t"	\
					"pop	r30						\n\t"	\
					"pop	r29						\n\t"	\
					"pop	r28						\n\t"	\
					"pop	r27						\n\t"	\
					"pop	r26						\n\t"	\
					"pop	r25						\n\t"	\
					"pop	r24						\n\t"	\
					"pop	r23						\n\t"	\
					"pop	r22						\n\t"	\
					"pop	r21						\n\t"	\
					"pop	r20						\n\t"	\
					"pop	r19						\n\t"	\
					"pop	r18						\n\t"	\
					"pop	r17						\n\t"	\
					"pop	r16						\n\t"	\
					"pop	r15						\n\t"	\
					"pop	r14						\n\t"	\
					"pop	r13						\n\t"	\
					"pop	r12						\n\t"	\
					"pop	r11						\n\t"	\
					"pop	r10						\n\t"	\
					"pop	r9						\n\t"	\
					"pop	r8						\n\t"	\
					"pop	r7						\n\t"	\
					"pop	r6						\n\t"	\
					"pop	r5						\n\t"	\
					"pop	r4						\n\t"	\
					"pop	r3						\n\t"	\
					"pop	r2						\n\t"	\
					"pop	r1						\n\t"	\
					"pop	r0						\n\t"	\
					"out	0x3c, r0				\n\t"	\
					"pop	r0						\n\t"	\
					"out	0x3b, r0				\n\t"	\
					"pop	r0						\n\t"	\
					"out	__SREG__, r0			\n\t"	\
					"pop	r0						\n\t"	\
				);
#else		/* Two (2) byte PC restore*/
#define portRESTORE_CONTEXT()								\
	asm volatile (	"lds	r26, pxCurrentTCB		\n\t"	\
					"lds	r27, pxCurrentTCB + 1	\n\t"	\
					"ld		r28, x+				\n\t"	\
					"out	__SP_L__, r28			\n\t"	\
					"ld		r29, x+				\n\t"	\
					"out	__SP_H__, r29			\n\t"	\
					"pop	r31						\n\t"	\
					"pop	r30						\n\t"	\
					"pop	r29						\n\t"	\
					"pop	r28						\n\t"	\
					"pop	r27						\n\t"	\
					"pop	r26						\n\t"	\
					"pop	r25						\n\t"	\
					"pop	r24						\n\t"	\
					"pop	r23						\n\t"	\
					"pop	r22						\n\t"	\
					"pop	r21						\n\t"	\
					"pop	r20						\n\t"	\
					"pop	r19						\n\t"	\
					"pop	r18						\n\t"	\
					"pop	r17						\n\t"	\
					"pop	r16						\n\t"	\
					"pop	r15						\n\t"	\
					"pop	r14						\n\t"	\
					"pop	r13						\n\t"	\
					"pop	r12						\n\t"	\
					"pop	r11						\n\t"	\
					"pop	r10						\n\t"	\
					"pop	r9						\n\t"	\
					"pop	r8						\n\t"	\
					"pop	r7						\n\t"	\
					"pop	r6						\n\t"	\
					"pop	r5						\n\t"	\
					"pop	r4						\n\t"	\
					"pop	r3						\n\t"	\
					"pop	r2						\n\t"	\
					"pop	r1						\n\t"	\
					"pop	r0						\n\t"	\
					"out	__SREG__, r0				\n\t"	\
					"pop	r0						\n\t"	\
				);
#endif

/*-----------------------------------------------------------*/

/*
 * Perform hardware setup to enable ticks from timer 1 or 3, compare match A.
 */
static void prvSetupTimerInterrupt( void );
/*-----------------------------------------------------------*/

/* 
 * See header file for description. 
 */
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, 
									  pdTASK_CODE pxCode, void *pvParameters )
{
	unsigned short usAddress;

	// This is a kludge, but it should work. If stack tracing is active, keep a static
	// variable here which holds the address of the top of the stack. It will be
	// grabbed by the task's wrapper object just after xTaskCreate() is called so that
	// the task object knows where its stack is. The stack can then be dumped to a
	// serial port (as a hex printout) for debugging purposes. 
	#if (INCLUDE_uxTaskGetStackHighWaterMark == 1)
		portStackTopForTask = (size_t)pxTopOfStack;
	#endif

	/* Place a few bytes of known values on the bottom of the stack. 
	This is just useful for debugging. */

	*pxTopOfStack = 0x11;
	pxTopOfStack--;
	*pxTopOfStack = 0x22;
	pxTopOfStack--;
	*pxTopOfStack = 0x33;
	pxTopOfStack--;

	/* Simulate how the stack would look after a call to vPortYield() generated by 
	the compiler. */

	/*lint -e950 -e611 -e923 Lint doesn't like this much - but nothing I can do about it. */

/*-----------------------MODIFIED BY TEAM BALANCE BOT----------------------*/
/*keeping with the whole 3 byte program counter thing*/
#if __AVR_3_BYTE_PC__
	/* The start of the task code will be popped off the stack last, so place
	it on first. */
	usAddress = ( unsigned portSHORT ) pxCode;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned portSHORT ) 0x00ff );
	pxTopOfStack--;

	usAddress >>= 8;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned portSHORT ) 0x00ff );
	pxTopOfStack--;

	*pxTopOfStack = 0;
	pxTopOfStack--;
#else
	/* The start of the task code will be popped off the stack last, so place
	it on first. */
	usAddress = ( unsigned short ) pxCode;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned short ) 0x00ff );
	pxTopOfStack--;

	usAddress >>= 8;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned short ) 0x00ff );
	pxTopOfStack--;
#endif

	/* Next simulate the stack as if after a call to portSAVE_CONTEXT().  
	portSAVE_CONTEXT places the flags on the stack immediately after r0
	to ensure the interrupts get disabled as soon as possible, and so ensuring
	the stack use is minimal should a context switch interrupt occur. */
	*pxTopOfStack = ( portSTACK_TYPE ) 0x00;	/* R0 */
	pxTopOfStack--;
	*pxTopOfStack = portFLAGS_INT_ENABLED;
	pxTopOfStack--;

/*-----------------------MODIFIED BY TEAM BALANCE BOT----------------------*/
/* taking care of EIND and RAMPZ, which are 2560-specific */ 
#if __AVR_3_BYTE_PC__
	/* If we have an ATmega256x, we are also saving the RAMPZ and EIND registers.
	 * We should default those to 0.
	 */
	*pxTopOfStack = ( portSTACK_TYPE ) 0x00;	/* EIND */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x00;	/* RAMPZ */
	pxTopOfStack--;
#endif

	/* Now the remaining registers.   The compiler expects R1 to be 0. */
	*pxTopOfStack = ( portSTACK_TYPE ) 0x00;	/* R1 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x02;	/* R2 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x03;	/* R3 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x04;	/* R4 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x05;	/* R5 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x06;	/* R6 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x07;	/* R7 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x08;	/* R8 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x09;	/* R9 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x10;	/* R10 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x11;	/* R11 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x12;	/* R12 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x13;	/* R13 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x14;	/* R14 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x15;	/* R15 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x16;	/* R16 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x17;	/* R17 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x18;	/* R18 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x19;	/* R19 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x20;	/* R20 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x21;	/* R21 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x22;	/* R22 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x23;	/* R23 */
	pxTopOfStack--;

	/* Place the parameter on the stack in the expected location. */
	usAddress = ( unsigned short ) pvParameters;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned short ) 0x00ff );
	pxTopOfStack--;

	usAddress >>= 8;
	*pxTopOfStack = ( portSTACK_TYPE ) ( usAddress & ( unsigned short ) 0x00ff );
	pxTopOfStack--;

	*pxTopOfStack = ( portSTACK_TYPE ) 0x26;	/* R26 X */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x27;	/* R27 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x28;	/* R28 Y */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x29;	/* R29 */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x30;	/* R30 Z */
	pxTopOfStack--;
	*pxTopOfStack = ( portSTACK_TYPE ) 0x031;	/* R31 */
	pxTopOfStack--;

	/*lint +e950 +e611 +e923 */

	return pxTopOfStack;
}

/*-----------------------------------------------------------*/

portBASE_TYPE xPortStartScheduler( void )
{
	/* Setup the hardware to generate the tick. */
	prvSetupTimerInterrupt();

	/* Restore the context of the first task that is going to run. */
	portRESTORE_CONTEXT();

	/* Simulate a function call end as generated by the compiler.  We will now
	jump to the start of the task the context of which we have just restored. */
	asm volatile ( "ret" );

	/* Should not get here. */
	return pdTRUE;
}

/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
	/* It is unlikely that the AVR port will get stopped.  If required simply
	disable the tick interrupt here. */
}

/*-----------------------------------------------------------*/

/*
 * Manual context switch.  The first thing we do is save the registers so we
 * can use a naked attribute.
 */
void vPortYield( void ) __attribute__ ( ( naked ) );
void vPortYield( void )
{
	portSAVE_CONTEXT();
	vTaskSwitchContext();
	portRESTORE_CONTEXT();

	asm volatile ( "ret" );
}

/*-----------------------------------------------------------*/

/*
 * Context switch function used by the tick.  This must be identical to 
 * vPortYield() from the call to vTaskSwitchContext() onwards.  The only
 * difference from vPortYield() is the tick count is incremented as the
 * call comes from the tick ISR.
 */
void vPortYieldFromTick( void ) __attribute__ ( ( naked ) );
void vPortYieldFromTick( void )
{
	portSAVE_CONTEXT();
	vTaskIncrementTick();
	vTaskSwitchContext();
	portRESTORE_CONTEXT();

	asm volatile ( "ret" );
}

//-------------------------------------------------------------------------------------
/** This function sets up a Timer compare match to generate a tick interrupt. 
 *  This interrupt will be the one that transfers control to the RTOS scheduler. 
 *  
 *  We prefer to use Timer 5 if it exists, as on the ATmega1281 and ATmega128RFa1. If
 *  it doesn't, we try Timer 3, which the ATmega128 has (and according to rumor, newer
 *  ATmega1284's). If those aren't there, we're stuck with Timer 1 so we use that. 
 *
 * If the device is an xmega then first attempt is at Timer E1 and second attempt is at
 * Timer D0.
 */

static void prvSetupTimerInterrupt( void )
{
	union                                   // This union is used to assemble a 16-bit
	{                                       // divisor for the compare match register,
		uint16_t word;                      // then pull out the bytes one at a time
		uint8_t byte[2];                    // to put into the special function regi-
	}                                       // sters which hold the value to which the
	compare_match;                          // timer/counter counts before it's reset

	// This calculation calculates a value to put in the output compare register
	compare_match.word = (uint16_t)(configCPU_CLOCK_HZ / (configTICK_RATE_HZ 
						 * portCLOCK_PRESCALER)) - 1;

	// Use the highest numbered timer available on a given AVR processor, because the
	// lower numbered timers are hooked up to useful things such as PWM's
	#if (defined TIMER5_COMPA_vect)             // Use Timer 5 on ATmega1280/1281
		#define RT_VECT TIMER5_COMPA_vect
		OCR5AH = compare_match.byte[1];         // Set high byte of compare match
		OCR5AL = compare_match.byte[0];         // register, then low byte
		TCCR5B = (1 << CS51) | (1 << WGM52);    // Prescale F_CPU / 8, clear on match
		TIMSK5 |= (1 << OCIE5A);                // Enable the timer interrupt
	#elif (defined TIMER3_COMPA_vect)           // Use Timer 3 on ATmega128/1284
		#define RT_VECT TIMER3_COMPA_vect
		OCR3AH = compare_match.byte[1];         // Set high byte of compare match
		OCR3AL = compare_match.byte[0];         // register, then low byte
		TCCR3B = (1 << CS31) | (1 << WGM32);    // Prescale F_CPU / 8, clear on match
		#ifdef TIMSK3                           // Exists on 640/1280/1281/2560/2561
			TIMSK3 |= (1 << OCIE3A);            // but not on most others
		#elif defined ETIMSK
			ETIMSK |= (1 << OCIE3A);
		#endif
	#elif (defined TIMER1_COMPA_vect)           // We're stuck with Timer 1           // Lesser chips only have 16-bit Timer 1
		#define RT_VECT TIMER1_COMPA_vect
		OCR1AH = compare_match.byte[1];         // Set high byte of compare match
		OCR1AL = compare_match.byte[0];         // register, then low byte
		TCCR1B = (1 << CS11) | (1 << WGM12);    // Prescale F_CPU / 8, clear on match
		#ifdef TIMSK1                           // Exists on 640/1280/1281/2560/2561
			TIMSK1 |= (1 << OCIE1A);            // but not on most others
		#elif defined ETIMSK
			ETIMSK |= (1 << OCIE1A);
		#endif
	#elif (defined TCE1_CCA_vect)  // Xmega Board Timer E1
		 #define RT_VECT TCE1_CCA_vect
		 TCE1_CCAH = compare_match.byte[1];     // Set high byte of compare match
		 TCE1_CCAL = compare_match.byte[0];     // register, then low byte
		 TCE1_CTRLA = (1 << TC1_CLKSEL0_bp);	// Prescale F_CPU / 1,
		 TCE1_CTRLB = (1 << TC1_CCAEN_bp);		// Enable Compare Capture A
		 TCE1_INTCTRLB = (TC_CCAINTLVL_LO_gc);
	#elif (defined TCD0_CCA_vect)  // Xmega Board Timer D0
		#define RT_VECT TCD0_CCA_vect
		TCD0_CCAH = compare_match.byte[1];      // Set high byte of compare match
		TCD0_CCAL = compare_match.byte[0];      // register, then low byte
		TCD0_CTRLA = (1 << TC0_CLKSEL0_bp);		// Prescale F_CPU / 1,
		TCD0_CTRLB = (1 << TC0_CCAEN_bp);		// Enable Compare Capture A
		TCD0_INTCTRLB = (TC_CCAINTLVL_LO_gc);
	#else
		#error No available timer
	#endif
}


//-------------------------------------------------------------------------------------
/*  This is the ISR which runs when the tick timer hits a compare match. It comes in 
 *  two flavors, one for a preemptive scheduler and one for a cooperative scheduler. 
 *  We can use the "naked" attribute, as the context is saved at the start of 
 *  vPortYieldFromTick().  The tick count is incremented after the context is saved. 
 */

void RT_VECT (void) __attribute__ ((signal, naked));
void RT_VECT (void)
{
	#if (RT_VECT == TCD0_CCA_vect)
		static uint16_t compare_interval = (uint16_t)(configCPU_CLOCK_HZ / (configTICK_RATE_HZ 
						 * portCLOCK_PRESCALER)) - 1;
		TCD0.CCA += compare_interval;
	#elif (RT_VECT = TCE1_CCA_vect))
		static uint16_t compare_interval = (uint16_t)(configCPU_CLOCK_HZ / (configTICK_RATE_HZ 
						 * portCLOCK_PRESCALER)) - 1;
		TCE1.CCA += compare_interval;
	#endif
	
	
	// For the preemptive scheduler, enable a context switch
	#if configUSE_PREEMPTION == 1
		vPortYieldFromTick ();
		asm volatile ( "reti" );
	#else
	// For the cooperative scheduler, all this does is increment the tick count.  
	// We don't need to switch context; that's done by manual calls to taskYIELD()
		vTaskIncrementTick ();
	#endif
}
