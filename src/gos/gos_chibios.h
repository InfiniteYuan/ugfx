/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GOS_CHIBIOS_H
#define _GOS_CHIBIOS_H

#if GFX_USE_OS_CHIBIOS

#if GFX_COMPAT_V2
	// This shouldn't be needed but some people are complaining
	// about TRUE/FALSE redefinition so we fix it here.
	// ChibiOS will define them in its own header files.
	#undef TRUE
	#undef FALSE
#endif

#include "ch.h"
#include "hal.h"

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

#define gDelayNone		TIME_IMMEDIATE
#define gDelayForever	TIME_INFINITE

#if CH_KERNEL_MAJOR <= 4
	typedef systime_t      gDelay;
#else
	typedef sysinterval_t  gDelay;
#endif
typedef systime_t	gTicks;
typedef cnt_t		gSemcount;
typedef msg_t		gThreadreturn;
typedef tprio_t		gThreadpriority;

#define MAX_SEMAPHORE_COUNT			((gSemcount)(((unsigned long)((gSemcount)(-1))) >> 1))
#define gThreadpriorityLow				LOWPRIO
#define gThreadpriorityNormal				NORMALPRIO
#define gThreadpriorityHigh				HIGHPRIO

#define DECLARE_THREAD_STACK(name, sz)			WORKING_AREA(name, sz)
#define DECLARE_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void *param)
#define THREAD_RETURN(retval)					return retval

#if CH_KERNEL_MAJOR <= 2
	typedef struct {
		Semaphore	sem;
		gSemcount	limit;
	} gfxSem;

	typedef Mutex		gfxMutex;
	typedef Thread*		gThread;
#else
	#undef DECLARE_THREAD_STACK
	#define DECLARE_THREAD_STACK(a, b)  THD_WORKING_AREA(a, b)

	typedef struct {
		semaphore_t	sem;
		gSemcount	limit;
	} gfxSem;

	typedef mutex_t		gfxMutex;
	typedef thread_t*	gThread;
#endif


/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

// First the kernel version specific ones
#if CH_KERNEL_MAJOR <= 2
	#define gfxSystemTicks()			chTimeNow()
	#define gfxMutexInit(pmutex)		chMtxInit(pmutex)
	#define gfxMutexExit(pmutex)		chMtxUnlock()
	#define gfxExit()					chSysHalt()
	#define gfxHalt(msg)				{ chDbgPanic(msg); chSysHalt(); }
#else
	#define gfxSystemTicks()			chVTGetSystemTimeX()
	#define gfxMutexInit(pmutex)		chMtxObjectInit(pmutex)
	#define gfxMutexExit(pmutex)		chMtxUnlock(pmutex)
	#define gfxExit()					osalSysHalt("gfx_exit")
	#define gfxHalt(msg)				{ chSysHalt(msg); }
#endif

#if CH_KERNEL_MAJOR <= 4
	#define gfxMillisecondsToTicks(ms)	MS2ST(ms)
#else
	#define gfxMillisecondsToTicks(ms)	TIME_MS2I(ms)
#endif

#define gfxAlloc(sz)				chHeapAlloc(0, sz)
#define gfxFree(ptr)				chHeapFree(ptr)
#define gfxYield()					chThdYield()
#define gfxSystemLock()				chSysLock()
#define gfxSystemUnlock()			chSysUnlock()
#define gfxMutexDestroy(pmutex)		(void)pmutex
#define gfxMutexEnter(pmutex)		chMtxLock(pmutex)
void *gfxRealloc(void *ptr, size_t oldsz, size_t newsz);
void gfxSleepMilliseconds(gDelay ms);
void gfxSleepMicroseconds(gDelay ms);
void gfxSemInit(gfxSem *psem, gSemcount val, gSemcount limit);
void gfxSemDestroy(gfxSem *psem);
gBool gfxSemWait(gfxSem *psem, gDelay ms);
gBool gfxSemWaitI(gfxSem *psem);
void gfxSemSignal(gfxSem *psem);
void gfxSemSignalI(gfxSem *psem);
gThread gfxThreadCreate(void *stackarea, size_t stacksz, gThreadpriority prio, DECLARE_THREAD_FUNCTION((*fn),p), void *param);
#define gfxThreadWait(thread)		chThdWait(thread)
#define gfxThreadMe()				chThdSelf()
#define gfxThreadClose(thread)		(void)thread

#endif /* GFX_USE_OS_CHIBIOS */
#endif /* _GOS_CHIBIOS_H */
