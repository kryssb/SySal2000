/*******************************************************************
 *
 * COPYRIGHT (c) 2000 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

/*******************************************************************
 *
 * Synopsis:      General definitions for interrupt and IO mechanisms.
 *
 * Notes:
 *
 *******************************************************************/

#ifndef __IM_IRQIO_H__
#define __IM_IRQIO_H__

#if !defined(_IM_HOST_OS_LINUX) || defined(__IMAGE2_H__)

#if defined(SHOW_INCLUDE_FILE)
#pragma message ("#include "__FILE__)
#endif


/* ------------------------------------------------------------------------------ */

#if defined(_IM_COMP_GNUC)
#pragma pack(1)
#else
#pragma pack(push,1)
#endif


#if !defined(_IM_DRIVER_CODE)
/* ------------------------------------------------------------------------------ */

typedef struct _ODYSSEY_HOOK_LIST        ODYSSEY_HOOK_LIST;
typedef struct _ODYSSEY_HOOK_LIST      *PODYSSEY_HOOK_LIST;

typedef struct _ODYSSEY_ISR_INFO         ODYSSEY_ISR_INFO;
typedef struct _ODYSSEY_ISR_INFO       *PODYSSEY_ISR_INFO;


typedef long (IM_FTYPE  *ODYSSEYHOOKFCTPTR)(PODYSSEY_HOOK_LIST pHookList) IM_LFTYPE;

#if defined(_IM_HOST_OS_LINUX)
struct LINUX_EVENT
{
    long autoCreate;
    sem_t     event;
};
#endif

/* ------------------------------------------------------------------------------ */

struct _ODYSSEY_HOOK_LIST
{
   PODYSSEY_ISR_INFO             pOdysseyIsrInfo;

   IM_UINT32                     InterruptType;

   ODYSSEYHOOKFCTPTR             InterruptFunctionPtr;
   void                         *UserDataPtr;
   HANDLE                        hSema;
   void                         *IntrHook;

#if defined(_IM_HOST_OS_NEUTRINO) || defined(_IM_HOST_OS_LINUX)
   PID_HANDLE                    hProcessPid;
#endif

   PODYSSEY_HOOK_LIST            next;
   PODYSSEY_HOOK_LIST            previous;

   //HANDLE                        hEventTerminateThread;
   HANDLE                        hEventStartedThread;

   IM_UINT32                     InterruptThreadId;
   HANDLE                        hInterruptThread;
   HANDLE                        hEventInterruptThreadCompleted;
};


struct _ODYSSEY_ISR_INFO
{
   IM_INT32                      NodeId;
   PODYSSEY_HOOK_LIST            pOdysseyHookList;

#if defined(_IM_HOST_OS_LINUX)
   PID_HANDLE                    hProcessThread;
   char                         *threadStack;
#endif

   PODYSSEY_ISR_INFO             next;
   PODYSSEY_ISR_INFO             previous;
};

IM_EXTC HANDLE                   IM_FTYPE OdysseyGetHandleEvent(PODYSSEY_HOOK_LIST pOdysseyHookFunction) IM_LFTYPE;
IM_EXTC PODYSSEY_HOOK_LIST       IM_FTYPE OdysseyGetHookList(long NodeId, long InterruptType) IM_LFTYPE;
IM_EXTC ODYSSEYHOOKFCTPTR        IM_FTYPE OdysseyGetFuncPtr(PODYSSEY_HOOK_LIST pOdysseyHookFunction) IM_LFTYPE;
IM_EXTC void  *                  IM_FTYPE OdysseyGetUsrDataPtr(PODYSSEY_HOOK_LIST pOdysseyHookFunction) IM_LFTYPE;
IM_EXTC long                     IM_FTYPE OdysseyGetInterruptType(PODYSSEY_HOOK_LIST pOdysseyHookFunction) IM_LFTYPE;
IM_EXTC long                     IM_FTYPE OdysseyHookInterruptFunction(long NodeId, ODYSSEYHOOKFCTPTR InterruptFunctionPtr, unsigned long InterruptType, HANDLE hSema, void  *UserDataPtr) IM_LFTYPE;
#endif

#if defined(_IM_HOST_OS_LINUX)

struct MsgIrq
{
    int msgID;
    int irqNbr;
    ODYSSEYHOOKFCTPTR InterruptFunctionPtr;
    unsigned long InterruptType;
};

#endif

#if defined(_IM_COMP_GNUC)
#pragma pack()
#else
#pragma pack(pop)
#endif

#endif /* !defined(_IM_HOST_OS_LINUX) || defined(__IMAGE2_H__)*/

#endif  /* __IM_IRQIO_H__ */
