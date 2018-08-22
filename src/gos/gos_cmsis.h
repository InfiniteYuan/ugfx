/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

/**
 * @file    src/gos/gos_cmsis.h
 * @brief   GOS - Operating System Support header file for CMSIS RTOS.
 */

#ifndef _GOS_CMSIS_H
#define _GOS_CMSIS_H

#if GFX_USE_OS_CMSIS

#include "cmsis_os.h"

#ifndef GFX_OS_HEAP_SIZE
	#define GFX_OS_HEAP_SIZE 10240
#endif

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

#define gDelayNone			0
#define gDelayForever		osWaitForever
typedef uint32_t			gDelay;
typedef uint32_t			gTicks;
typedef uint16_t			gSemcount;
typedef void				gThreadreturn;
typedef osPriority			gThreadpriority;

#define MAX_SEMAPHORE_COUNT	osFeature_Semaphore
#define gThreadpriorityLow		osPriorityLow
#define gThreadpriorityNormal		osPriorityNormal
#define gThreadpriorityHigh		osPriorityHigh

typedef struct gfxSem {
	uint32_t		semaphore[2];
	osSemaphoreId	id;
	gSemcount		available;
} gfxSem;

typedef struct gfxMutex {
	uint32_t mutex[4];
	osMutexId id;
} gfxMutex;

typedef osThreadId			gThread;

#define DECLARE_THREAD_STACK(name, sz)			uint8_t name[1];	// Some compilers don't allow zero sized arrays. Let's waste one byte
#define DECLARE_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void* param)
#define THREAD_RETURN(retval)

/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

#define gfxExit()					os_error(0)
#define gfxHalt(msg)				os_error(1)
#define gfxSystemTicks()			osKernelSysTick()
#define gfxMillisecondsToTicks(ms)	osKernelSysTickMicroSec(1000*ms)
#define gfxSystemLock()				osKernelInitialize()
#define gfxSystemUnlock()			osKernelStart()
#define gfxSleepMilliseconds(ms) 	osDelay(ms)

void gfxMutexInit(gfxMutex* pmutex);
#define gfxMutexDestroy(pmutex)		osMutexDelete((pmutex)->id)
#define gfxMutexEnter(pmutex)		osMutexWait((pmutex)->id, gDelayForever)
#define gfxMutexExit(pmutex)		osMutexRelease((pmutex)->id)

void gfxSemInit(gfxSem* psem, gSemcount val, gSemcount limit);
void gfxSemDestroy(gfxSem* psem);
gBool gfxSemWait(gfxSem* psem, gDelay ms);
gBool gfxSemWaitI(gfxSem* psem);
void gfxSemSignal(gfxSem* psem);
void gfxSemSignalI(gfxSem* psem);

gThread gfxThreadCreate(void* stackarea, size_t stacksz, gThreadpriority prio, DECLARE_THREAD_FUNCTION((*fn),p), void* param);
#define gfxYield()					osThreadYield()
#define gfxThreadMe()				osThreadGetId()
#define gfxThreadClose(thread)		{}

/*===========================================================================*/
/* Use the generic heap handling                                             */
/*===========================================================================*/

#define GOS_NEED_X_HEAP GFXON
#include "gos_x_heap.h"

#endif /* GFX_USE_OS_CMSIS */
#endif /* _GOS_CMSIS_H */
