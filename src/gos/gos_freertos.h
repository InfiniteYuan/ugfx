/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

/**
 * @file    src/gos/gos_freertos.h
 * @brief   GOS - Operating System Support header file for FreeRTOS.
 */

#ifndef _GOS_FREERTOS_H
#define _GOS_FREERTOS_H

#if GFX_USE_OS_FREERTOS

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "task.h"

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

#define gDelayNone			0
#define gDelayForever		((gDelay)-1)
typedef uint32_t			gDelay;
typedef portTickType		gTicks;
typedef int32_t				gSemcount;
typedef void				gThreadreturn;
typedef portBASE_TYPE		gThreadpriority;

#define MAX_SEMAPHORE_COUNT	((gSemcount)(((unsigned long)((gSemcount)(-1))) >> 1))
#define gThreadpriorityLow		0
#define gThreadpriorityNormal		configMAX_PRIORITIES/2
#define gThreadpriorityHigh		configMAX_PRIORITIES-1

/* FreeRTOS will allocate the stack when creating the thread */
#define DECLARE_THREAD_STACK(name, sz)	uint8_t name[1]
#define DECLARE_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void *param)
#define THREAD_RETURN(retval)

typedef xSemaphoreHandle		gfxSem;
typedef xSemaphoreHandle		gfxMutex;
typedef xTaskHandle				gThread;

/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

#define gfxHalt(msg)				{while(1);}
#define gfxExit()					{while(1);}
#define gfxAlloc(sz)				pvPortMalloc(sz)
#define gfxFree(ptr)				vPortFree(ptr)
#define gfxYield()					taskYIELD()
#define gfxSystemTicks()			xTaskGetTickCount()
#define gfxMillisecondsToTicks(ms)	((gTicks)((ms) / portTICK_PERIOD_MS))
#define gfxSystemLock()				taskENTER_CRITICAL()
#define gfxSystemUnlock()			taskEXIT_CRITICAL()

void gfxMutexInit(gfxMutex* s);
#define gfxMutexDestroy(pmutex)		vSemaphoreDelete(*(pmutex))
#define gfxMutexEnter(pmutex)		xSemaphoreTake(*(pmutex),portMAX_DELAY)
#define gfxMutexExit(pmutex)		xSemaphoreGive(*(pmutex))

void *gfxRealloc(void *ptr, size_t oldsz, size_t newsz);
void gfxSleepMilliseconds(gDelay ms);
void gfxSleepMicroseconds(gDelay ms);

void gfxSemInit(gfxSem* psem, gSemcount val, gSemcount limit);
#define gfxSemDestroy(psem)			vSemaphoreDelete(*(psem))
gBool gfxSemWait(gfxSem* psem, gDelay ms);
gBool gfxSemWaitI(gfxSem* psem);
void gfxSemSignal(gfxSem* psem);
void gfxSemSignalI(gfxSem* psem);
gThread gfxThreadCreate(void *stackarea, size_t stacksz, gThreadpriority prio, DECLARE_THREAD_FUNCTION((*fn),p), void *param);

#define gfxThreadMe()				xTaskGetCurrentTaskHandle()
#if INCLUDE_eTaskGetState == 1
	gThreadreturn gfxThreadWait(gThread thread);
#endif
#define gfxThreadClose(thread)

#endif /* GFX_USE_OS_FREERTOS */
#endif /* _GOS_CHIBIOS_H */
