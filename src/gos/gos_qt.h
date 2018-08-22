/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GOS_QT_H
#define _GOS_QT_H

#if GFX_USE_OS_QT

#define DECLARE_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void *param)
#define DECLARE_THREAD_STACK(name, sz)          uint8_t name[0]
#define THREAD_RETURN(retval)					return retval

#define gDelayNone					0
#define gDelayForever				((gDelay)-1)
#define MAX_SEMAPHORE_COUNT			((gSemcount)(((unsigned long)((gSemcount)(-1))) >> 1))
#define gThreadpriorityLow				2
#define gThreadpriorityNormal				3
#define gThreadpriorityHigh				4

typedef int gTicks;
typedef int gDelay;
typedef void* gfxMutex;
typedef void* gfxSem;
typedef int gSemcount;
typedef int gThreadreturn;
typedef int gThreadpriority;
typedef void* gThread;

void _gosInit();
void _gosDeinit();

void gfxHalt(const char* msg);
void gfxExit(void);
void* gfxAlloc(size_t sz);
void* gfxRealloc(void *ptr, size_t oldsz, size_t newsz);
void gfxFree(void* ptr);
void gfxYield(void);
void gfxSleepMilliseconds(gDelay ms);
void gfxSleepMicroseconds(gDelay us);
gTicks gfxSystemTicks(void);
gTicks gfxMillisecondsToTicks(gDelay ms);
void gfxSystemLock(void);
void gfxSystemUnlock(void);
void gfxMutexInit(gfxMutex *pmutex);
void gfxMutexDestroy(gfxMutex *pmutex);
void gfxMutexEnter(gfxMutex *pmutex);
void gfxMutexExit(gfxMutex *pmutex);
void gfxSemInit(gfxSem *psem, gSemcount val, gSemcount limit);
void gfxSemDestroy(gfxSem *psem);
gBool gfxSemWait(gfxSem *psem, gDelay ms);
gBool gfxSemWaitI(gfxSem *psem);
void gfxSemSignal(gfxSem *psem);
void gfxSemSignalI(gfxSem *psem);
gThread gfxThreadCreate(void *stackarea, size_t stacksz, gThreadpriority prio, DECLARE_THREAD_FUNCTION((*fn),p), void *param);
gThreadreturn gfxThreadWait(gThread thread);
gThread gfxThreadMe(void);
void gfxThreadClose(gThread thread);

#endif /* GFX_USE_OS_QT */
#endif /* _GOS_QT_H */
