/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GOS_OSX_H
#define _GOS_OSX_H

#if GFX_USE_OS_OSX

#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>

typedef unsigned long		gTicks;
typedef void *				gThreadreturn;
typedef unsigned long		gDelay;
typedef pthread_t 			gThread;
typedef int					gThreadpriority;
typedef uint32_t			gSemcount;
typedef pthread_mutex_t		gfxMutex;

#define DECLARE_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void *param)
#define DECLARE_THREAD_STACK(name, sz)			uint8_t name[0];
#define THREAD_RETURN(retval)					return retval

#define gfxExit()						exit(0)
#define gfxAlloc(sz)					malloc(sz)
#define gfxRealloc(p,osz,nsz)			realloc(p, nsz)
#define gfxFree(ptr)					free(ptr)
#define gfxMillisecondsToTicks(ms)		(ms)
#define gfxYield()						sched_yield()
#define gfxThreadMe()					pthread_self()
#define gfxThreadClose(th)				(void)th
#define gfxMutexInit(pmtx)				pthread_mutex_init(pmtx, 0)
#define gfxMutexDestroy(pmtx)			pthread_mutex_destroy(pmtx)
#define gfxMutexEnter(pmtx)				pthread_mutex_lock(pmtx)
#define gfxMutexExit(pmtx)				pthread_mutex_unlock(pmtx)
#define gfxSemWaitI(psem)				gfxSemWait(psem, gDelayNone)
#define gfxSemSignalI(psem)				gfxSemSignal(psem)

#define gDelayNone					0
#define gDelayForever				((gDelay)-1)
#define MAX_SEMAPHORE_COUNT			((gSemcount)-1)
#define gThreadpriorityLow				10
#define gThreadpriorityNormal				0
#define gThreadpriorityHigh				-10

typedef struct gfxSem {
	pthread_mutex_t	mtx;
	pthread_cond_t	cond;
	gSemcount		cnt;
	gSemcount		max;
} gfxSem;

/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

void gfxHalt(const char *msg);
void gfxSleepMilliseconds(gDelay ms);
void gfxSleepMicroseconds(gDelay ms);
gTicks gfxSystemTicks(void);
void gfxSystemLock(void);
void gfxSystemUnlock(void);
void gfxSemInit(gfxSem *psem, gSemcount val, gSemcount limit);
void gfxSemDestroy(gfxSem *psem);
gBool gfxSemWait(gfxSem *psem, gDelay ms);
void gfxSemSignal(gfxSem *psem);
gThread gfxThreadCreate(void *stackarea, size_t stacksz, gThreadpriority prio, DECLARE_THREAD_FUNCTION((*fn),p), void *param);
gThreadreturn gfxThreadWait(gThread thread);

#endif /* GFX_USE_OS_OSX */
#endif /* _GOS_OSX_H */
