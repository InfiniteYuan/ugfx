/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

/**
 * @file    src/gos/gos_cmsis2.h
 * @brief   GOS - Operating System Support header file for CMSIS 2.0 RTOS.
 */

#ifndef _GOS_CMSIS2_H
#define _GOS_CMSIS2_H

#if GFX_USE_OS_CMSIS2

#include "cmsis_os2.h"

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
typedef osPriority_t		gThreadpriority;

#define MAX_SEMAPHORE_COUNT	65535UL
#define gThreadpriorityLow		osPriorityLow
#define gThreadpriorityNormal		osPriorityNormal
#define gThreadpriorityHigh		osPriorityHigh

typedef osSemaphoreId_t		gfxSem;

typedef osMutexId_t 		gfxMutex;

typedef osThreadId_t		gThread;

#define DECLARE_THREAD_STACK(name, sz)			uint8_t name[1];	// Some compilers don't allow zero sized arrays. Let's waste one byte
#define DECLARE_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void* param)
#define THREAD_RETURN(retval)

/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

#define gfxExit()					os_error(0)
#define gfxHalt(msg)				os_error(1)
#define gfxSystemTicks()			osKernelGetTickCount()
#define gfxMillisecondsToTicks(ms)	(1000*(ms)/osKernelGetTickFreq())
#define gfxSystemLock()				osKernelLock()
#define gfxSystemUnlock()			osKernelUnlock()
#define gfxSleepMilliseconds(ms) 	osDelay(ms)

void gfxMutexInit(gfxMutex* pmutex);
#define gfxMutexDestroy(pmutex)		osMutexDelete(*(pmutex))
#define gfxMutexEnter(pmutex)		osMutexAcquire(*(pmutex), gDelayForever)
#define gfxMutexExit(pmutex)		osMutexRelease(*(pmutex))

void gfxSemInit(gfxSem* psem, gSemcount val, gSemcount limit);
#define gfxSemDestroy(psem)		osSemaphoreDelete(*(psem))
gBool gfxSemWait(gfxSem* psem, gDelay ms);
#define gfxSemWaitI(psem)		gfxSemWait((psem), 0)
#define gfxSemSignal(psem)		osSemaphoreRelease(*(psem))
#define gfxSemSignalI(psem)		osSemaphoreRelease(*(psem))

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
