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

#if defined(SHOW_INCLUDE_FILE)
#pragma message ("#include "__FILE__)
#endif

/* ---------------------------------------------------------------------- */
#if defined(_IM_COMP_MICROSOFT)

#if defined(_IM_HOST_OS_NT_KERNEL)
#define DISABLE_INTERRUPT()               ;
#define ENABLE_INTERRUPT()                ;
#elif defined(_IM_HOST_OS_NT)
#include <conio.h>
#define OUTP(adr, data)                   _outp(adr, data)
#define INP(adr)                          _inp(adr)
#define DISABLE_INTERRUPT()               ;
#define ENABLE_INTERRUPT()                ;
#define IRQ_STACKSIZE                     512
#else
#error ERROR: __IM_IRQIO_H__ for _IM_COMP_MICROSOFT
#endif


/* ---------------------------------------------------------------------- */
#elif  defined(_IM_COMP_WATCOM)
#include <conio.h>
#include <i86.h>
#define OUTP(adr, data)                   outp(adr, data)
#define INP(adr)                          inp(adr)
#define DISABLE_INTERRUPT()               _disable()
#define ENABLE_INTERRUPT()                _enable()
#define IRQ_STACKSIZE                     512


/* ---------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- */
#elif defined(_IM_COMP_GNUC) && defined(_IM_HOST_OS_LINUX_DRIVER)

#define OUTP(adr,data)                    outb(adr, data)
#define INP(adr)                          inb(adr)
#define DISABLE_INTERRUPT()               cli()
#define ENABLE_INTERRUPT()                sti()
#define IRQ_STACKSIZE                     512

#endif

/* ------------------------------------------------------------------------------ */
#define INTERRUPT_SUB_QUEUE_SIZE          256

#if defined(_IM_HOST_OS_NT_KERNEL)
#define INTERRUPT_CIRCULAR_QUEUE_SIZE     256
#else
#define INTERRUPT_CIRCULAR_QUEUE_SIZE     512
#endif

#if defined(_IM_COMP_GNUC)
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

typedef struct _ODYSSEY_INT_TYPE
{
   ULONGLONG  Type;
   ULONG      Flags;
} ODYSSEY_INT_TYPE;

typedef struct _ODYSSEY_ISR_QUEUE
{
   ODYSSEY_INT_TYPE              Type[INTERRUPT_CIRCULAR_QUEUE_SIZE];

#if defined(_IM_HOST_OS_NT_KERNEL)
   KDPC                          Dpc[INTERRUPT_CIRCULAR_QUEUE_SIZE];
#endif

   unsigned long                 IsrIn;
   unsigned long                 IsrOut;

#if defined(_IM_HOST_OS_NT_KERNEL)
   unsigned long                 DpcIn;
   unsigned long                 DpcOut;
#endif

} ODYSSEY_ISR_QUEUE;


#if !defined(_IM_HOST_OS_NT_KERNEL)
/* ------------------------------------------------------------------------------ */
typedef struct _ODYSSEY_HOOK_FUNCTION    ODYSSEY_HOOK_FUNCTION;
typedef struct _ODYSSEY_HOOK_FUNCTION  *PODYSSEY_HOOK_FUNCTION;

typedef struct _ODYSSEY_HOOK_LIST        ODYSSEY_HOOK_LIST;
typedef struct _ODYSSEY_HOOK_LIST      *PODYSSEY_HOOK_LIST;

typedef struct _ODYSSEY_ISR_INFO         ODYSSEY_ISR_INFO;
typedef struct _ODYSSEY_ISR_INFO       *PODYSSEY_ISR_INFO;


typedef long (IM_FTYPE  *ODYSSEYHOOKFCTPTR)(PODYSSEY_HOOK_LIST pHookList) IM_LFTYPE;

#if defined(_IM_HOST_OS_LINUX) && !defined(_IM_HOST_OS_LINUX_DRIVER)
struct LINUX_EVENT
{
    long autoCreate;
    sem_t     event;
};
#endif

/* ------------------------------------------------------------------------------ */
struct _ODYSSEY_HOOK_FUNCTION
{
   PODYSSEY_HOOK_LIST            pOdysseyHookList;

   ODYSSEYHOOKFCTPTR             InterruptFunctionPtr;
   void                         *UserDataPtr;
#if defined(_IM_HOST_OS_NT)
   HANDLE                        hEventUsr;
#elif defined(_IM_HOST_OS_NTO) || defined(_IM_HOST_OS_LINUX)
   sem_t*                        hEventUsr;
#endif
   PODYSSEY_HOOK_FUNCTION        next;
   PODYSSEY_HOOK_FUNCTION        previous;
};



struct _ODYSSEY_HOOK_LIST
{
   PODYSSEY_ISR_INFO             pOdysseyIsrInfo;

   unsigned long                 InterruptType;

   PODYSSEY_HOOK_FUNCTION        pOdysseyHookFunction;

   PODYSSEY_HOOK_LIST            next;
   PODYSSEY_HOOK_LIST            previous;

};


struct _ODYSSEY_ISR_INFO
{
   long                          NodeId;
   PODYSSEY_HOOK_LIST            pOdysseyHookList;

   PID_HANDLE                    hProcessThread;

#if defined(_IM_HOST_OS_NT)
   unsigned                      ProcessThreadId;
   HANDLE                        hEventProcessThread;
   HANDLE                        hEventProcessThreadCompleted;

   HANDLE                        hEventTerminateThread;
   HANDLE                        hEventStartedThread;

   unsigned                      InterruptThreadId;
   HANDLE                        hInterruptThread;
   HANDLE                        hEventInterruptThreadCompleted;

   ODYSSEY_ISR_QUEUE             IsrQueue;

#elif defined(_IM_HOST_OS_NTO)
   int                           hProcessPID;
#elif defined(_IM_HOST_OS_LINUX)
   char                         *threadStack;

#endif

   PODYSSEY_ISR_INFO             next;
   PODYSSEY_ISR_INFO             previous;
};


#endif



#if !defined(_IM_DRIVER_CODE)

#if defined(_IM_HOST_OS_NT)
IM_EXTC HANDLE                   IM_FTYPE OdysseyGetHandleEvent(PODYSSEY_HOOK_FUNCTION pOdysseyHookFunction) IM_LFTYPE;
#elif defined(_IM_HOST_OS_NTO) || defined(_IM_HOST_OS_LINUX)
IM_EXTC sem_t*                   IM_FTYPE OdysseyGetHandleEvent(PODYSSEY_HOOK_FUNCTION pOdysseyHookFunction) IM_LFTYPE;
#endif

#endif

#if !defined(_IM_HOST_OS_NT_KERNEL)

IM_EXTC PODYSSEY_HOOK_LIST       IM_FTYPE OdysseyGetHookList(long NodeId, long InterruptType) IM_LFTYPE;
IM_EXTC PODYSSEY_HOOK_FUNCTION   IM_FTYPE OdysseyGetNextHookFunction(PODYSSEY_HOOK_LIST pHookList, PODYSSEY_HOOK_FUNCTION *ppOdysseyHookFunction) IM_LFTYPE;
IM_EXTC ODYSSEYHOOKFCTPTR        IM_FTYPE OdysseyGetFuncPtr(PODYSSEY_HOOK_FUNCTION pOdysseyHookFunction) IM_LFTYPE;
IM_EXTC void  *                  IM_FTYPE OdysseyGetUsrDataPtr(PODYSSEY_HOOK_FUNCTION pOdysseyHookFunction) IM_LFTYPE;
IM_EXTC long                     IM_FTYPE OdysseyGetInterruptType(PODYSSEY_HOOK_FUNCTION pOdysseyHookFunction) IM_LFTYPE;
IM_EXTC long                     IM_FTYPE OdysseyGetHookInterruptType(PODYSSEY_HOOK_LIST pHookList) IM_LFTYPE;
IM_EXTC long                     IM_FTYPE OdysseyHookInterruptFunction(long NodeId, ODYSSEYHOOKFCTPTR InterruptFunctionPtr, unsigned long InterruptType, void  *phEvent, void  *UserDataPtr) IM_LFTYPE;

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

#endif  /* __IM_IRQIO_H__ */
