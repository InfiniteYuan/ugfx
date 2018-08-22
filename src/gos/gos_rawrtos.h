#ifndef _GOS_RAWRTOS_H
#define _GOS_RAWRTOS_H

#if GFX_USE_OS_RAWRTOS

#include "raw_api.h"

#define gDelayNone			(RAW_NO_WAIT)
#define gDelayForever		(RAW_WAIT_FOREVER)
typedef uint32_t			gDelay;
typedef RAW_TICK_TYPE		gTicks;
typedef int32_t				gSemcount;
typedef uint32_t			gThreadreturn;
typedef RAW_U8				gThreadpriority;

#define MAX_SEMAPHORE_COUNT	RAW_SEMAPHORE_COUNT
#define gThreadpriorityLow		(CONFIG_RAW_PRIO_MAX-2)
#define gThreadpriorityNormal		(CONFIG_RAW_PRIO_MAX/2)
#define gThreadpriorityHigh		1

typedef RAW_SEMAPHORE		gfxSem;
typedef RAW_MUTEX			gfxMutex;
typedef RAW_TASK_OBJ*		gThread;

#define DECLARE_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void *param)
#define DECLARE_THREAD_STACK(name, sz)			PORT_STACK name[(sz) & ~3];
#define THREAD_RETURN(retval)					return retval

#define gfxHalt(msg)					for(;;)
#define gfxExit()						for(;;)
#define gfxAlloc(sz)					raw_malloc(sz)
#define gfxRealloc(p,osz,nsz)			raw_calloc(p, nsz)
#define gfxFree(ptr)					raw_free(ptr)
#define gfxYield()						raw_sleep(0)
#define gfxSystemTicks()				raw_system_time_get()
#define gfxMillisecondsToTicks(ms)		(ms*RAW_TICKS_PER_SECOND/1000)
#define gfxSystemLock()					{}
#define gfxSystemUnlock()				{}
#define gfxMutexInit(pmutex)			raw_mutex_create(pmutex, (RAW_U8 *)"", RAW_MUTEX_INHERIT_POLICY, 3)
#define gfxMutexDestroy(pmutex)			raw_mutex_delete(pmutex)
#define gfxMutexEnter(pmutex) 			raw_mutex_get(pmutex, gDelayForever)
#define gfxMutexExit(pmutex)			raw_mutex_put(pmutex)
#define gfxSemInit(psem, val, limit)	raw_semaphore_create(psem, "", val)
#define gfxSemDestroy(psem)				raw_semaphore_delete(psem)
#define gfxSemSignal(psem)				raw_semaphore_put((psem))
#define gfxSemSignalI(psem)				raw_semaphore_put_all((psem))
#define gfxThreadMe()					{(unsigned int)raw_task_identify()}
#define gfxThreadClose(thread)			{}

extern RAW_VOID *raw_malloc(RAW_U32 size);
extern RAW_VOID raw_free(void *ptr);
extern RAW_VOID *raw_calloc(RAW_U32 nmemb, RAW_U32 size);

extern RAW_U16 raw_sleep(RAW_TICK_TYPE dly);
extern RAW_TICK_TYPE  raw_system_time_get(void);

extern RAW_U16 raw_mutex_create(RAW_MUTEX *mutex_ptr, RAW_U8 *name_ptr, RAW_U8 policy, RAW_U8 ceiling_prio);
extern RAW_U16 raw_mutex_delete(RAW_MUTEX *mutex_ptr);
extern RAW_U16 raw_mutex_get(RAW_MUTEX *mutex_ptr, RAW_TICK_TYPE wait_option);
extern RAW_U16 raw_mutex_put(RAW_MUTEX *mutex_ptr);
extern RAW_U16 raw_semaphore_create(RAW_SEMAPHORE *semaphore_ptr, RAW_U8 *name_ptr, RAW_U32 initial_count);
extern RAW_U16 raw_semaphore_delete(RAW_SEMAPHORE *semaphore_ptr);
extern RAW_U16 raw_semaphore_get(RAW_SEMAPHORE *semaphore_ptr, RAW_TICK_TYPE wait_option);
extern RAW_U16 raw_semaphore_put(RAW_SEMAPHORE *semaphore_ptr);

void gfxSleepMilliseconds(gDelay ms);
void gfxSleepMicroseconds(gDelay us);
gBool gfxSemWait(gfxSem* psem, gDelay ms);
gBool gfxSemWaitI(gfxSem* psem);
gThread gfxThreadCreate(void *stackarea, size_t stacksz, gThreadpriority prio, DECLARE_THREAD_FUNCTION((*fn),p), void *param);

#endif

#endif
