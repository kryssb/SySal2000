/*******************************************************************
 *
 * COPYRIGHT (c) 1994 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

/*******************************************************************
 *
 * Synopsis:      General definitions for interrupt and IO mechanisms.
 *
 * Bugs:
 *
 * Designed:      bLem for IMAGE-2
 *                10/19/94   13:12:15
 *
 * Reviewed:
 *
 * Last modified:
 *
 * Notes:
 *
 *******************************************************************/

#ifndef __IM_IRQIO_H__
#define __IM_IRQIO_H__

#if !defined(_IM_LOCAL_CODE) && defined(SHOW_INCLUDE_FILE)
#pragma message ("#include "__FILE__)
#endif

/* ---------------------------------------------------------------------- */
#if defined(_IM_COMP_MICROSOFT)

#if defined(_IM_HOST_OS_NT_KERNEL) || defined(_SLIM_GENLIB)
#define DISABLE_INTERRUPT()   ;
#define ENABLE_INTERRUPT()    ;
#elif defined(_IM_HOST_OS_NT)
#include <conio.h>
#define OUTP(adr, data)       _outp(adr, data)
#define INP(adr)              _inp(adr)
#define DISABLE_INTERRUPT()   ;
#define ENABLE_INTERRUPT()    ;
#define IRQ_STACKSIZE         512
#else
#error ERROR: __IM_IRQIO_H__ for _IM_COMP_MICROSOFT
#endif


/* ---------------------------------------------------------------------- */
#elif  defined(_IM_COMP_WATCOM)
#include <conio.h>
#include <i86.h>
#define OUTP(adr, data)       outp(adr, data)
#define INP(adr)              inp(adr)
#define DISABLE_INTERRUPT()   _disable()
#define ENABLE_INTERRUPT()    _enable()
#define IRQ_STACKSIZE         512


/* ---------------------------------------------------------------------- */
#elif  defined(_IM_COMP_BC)
#include <conio.h>
#define OUTP(adr, data)       outportb(adr, data)
#define INP(adr)              inportb(adr)
#define DISABLE_INTERRUPT()   disable()
#define ENABLE_INTERRUPT()    enable()
#define IRQ_STACKSIZE         512


/* ---------------------------------------------------------------------- */
#elif  defined(_IM_COMP_VPLUS)

#define DISABLE_INTERRUPT()   ;
#define ENABLE_INTERRUPT()    ;

/* ---------------------------------------------------------------------- */
#elif defined(_IM_COMP_GNUC) && defined(_IM_HOST_OS_LINUX_DRIVER)

#define OUTP(adr,data)        outb(adr, data)
#define INP(adr)              inb(adr)
#define DISABLE_INTERRUPT()   cli()
#define ENABLE_INTERRUPT()    sti()
#define IRQ_STACKSIZE         512

#elif defined(_IM_COMP_GNUC) && defined(_IM_HOST_OS_NTO_DRIVER)

#define OUTP(adr, data)       out8(adr, data)
#define INP(adr)              in8(adr)
#define DISABLE_INTERRUPT()   InterruptDisable()  /* use InterruptLock instead if you run on SMP hardware */
#define ENABLE_INTERRUPT()    InterruptEnable()   /* use InterruptUnlock .......*/
#define IRQ_STACKSIZE 512

#endif

/* ------------------------------------------------------------------------------ */
#define INTERRUPT_SUB_QUEUE_SIZE          128
#if defined(_IM_HOST_OS_NT) || defined(_IM_HOST_OS_QNX4) || defined(_IM_HOST_OS_LINUX) || defined(_IM_HOST_OS_NTO)
#if defined(_IM_HOST_OS_NT_KERNEL)
#define INTERRUPT_CIRCULAR_QUEUE_SIZE     64
#else
#define INTERRUPT_CIRCULAR_QUEUE_SIZE     256
#endif

typedef struct _GENESIS_ISR_QUEUE
{
   unsigned long                 Type[INTERRUPT_CIRCULAR_QUEUE_SIZE];

#if defined(_IM_HOST_OS_NT_KERNEL)
   KDPC                          Dpc[INTERRUPT_CIRCULAR_QUEUE_SIZE];
#endif

   unsigned long                 IsrIn;
   unsigned long                 IsrOut;

#if defined(_IM_HOST_OS_NT_KERNEL)
   unsigned long                 DpcIn;
   unsigned long                 DpcOut;
#endif

} GENESIS_ISR_QUEUE;

#endif



#if !defined(_IM_HOST_OS_NT_KERNEL)
/* ------------------------------------------------------------------------------ */
typedef struct _GENESIS_HOOK_FUNCTION    GENESIS_HOOK_FUNCTION;
typedef struct _GENESIS_HOOK_FUNCTION  *PGENESIS_HOOK_FUNCTION;

typedef struct _GENESIS_HOOK_LIST        GENESIS_HOOK_LIST;
typedef struct _GENESIS_HOOK_LIST      *PGENESIS_HOOK_LIST;

typedef struct _GENESIS_ISR_INFO         GENESIS_ISR_INFO;
typedef struct _GENESIS_ISR_INFO       *PGENESIS_ISR_INFO;


typedef long (IM_FTYPE IM_PTYPE *GENESISHOOKFCTPTR)(PGENESIS_HOOK_LIST pHookList) IM_LFTYPE;

#if defined(_IM_HOST_OS_QNX4) || defined(_IM_HOST_OS_NTO)
struct QNX_EVENT
{
    long autoCreate;
    sem_t     event;
};
#endif

#if defined(_IM_HOST_OS_LINUX) && !defined(_IM_HOST_OS_LINUX_DRIVER)
struct LINUX_EVENT
{
    long autoCreate;
    sem_t     event;
};
#endif

/* ------------------------------------------------------------------------------ */
struct _GENESIS_HOOK_FUNCTION
{
   PGENESIS_HOOK_LIST            pGenesisHookList;

   GENESISHOOKFCTPTR             InterruptFunctionPtr;
   void                         *UserDataPtr;
#if defined(_IM_HOST_OS_DOS) || defined(_IM_HOST_OS_QNX4) || defined(_IM_HOST_OS_LINUX) || defined(_IM_HOST_OS_NTO)
   long                          hEventUsr;
#elif defined(_IM_HOST_OS_NT)
   HANDLE                        hEventUsr;
#endif
   PGENESIS_HOOK_FUNCTION        next;
   PGENESIS_HOOK_FUNCTION        previous;
};



struct _GENESIS_HOOK_LIST
{
   PGENESIS_ISR_INFO             pGenesisIsrInfo;

   unsigned long                 InterruptType;

   PGENESIS_HOOK_FUNCTION        pGenesisHookFunction;

   PGENESIS_HOOK_LIST            next;
   PGENESIS_HOOK_LIST            previous;

};


struct _GENESIS_ISR_INFO
{
   long                          NodeId;
   PGENESIS_HOOK_LIST            pGenesisHookList;

#if defined(_IM_HOST_OS_NT) || defined(_IM_HOST_OS_QNX4) || defined(_IM_HOST_OS_LINUX) || defined(_IM_HOST_OS_NTO)
   PID_HANDLE                    hProcessThread;
#if defined(_IM_HOST_OS_NTO)
   int                           hProcessPID;
#endif
#endif

#if defined(_IM_HOST_OS_NT)
   unsigned                      ProcessThreadId;
   HANDLE                        hEventProcessThread;

   HANDLE                        hEventTerminateThread;
   HANDLE                        hEventStartedThread;

   unsigned                      InterruptThreadId;
   HANDLE                        hInterruptThread;

   /* Camera Link DLL pipe */
   unsigned                      nUartThreadId;
   HANDLE                        hUartThread;
   HANDLE                        hEventPipeServerStarted;
   HANDLE                        hPipeEvent;
   PBOOL                         pbKillUartServer;

   GENESIS_ISR_QUEUE             IsrQueue;

#elif defined(_IM_HOST_OS_QNX4) || defined(_IM_HOST_OS_LINUX) || defined(_IM_HOST_OS_NTO)
   char                         *threadStack;

#endif

   PGENESIS_ISR_INFO             next;
   PGENESIS_ISR_INFO             previous;
};


#endif



#if defined(_IM_HOST_OS_DOS)

IM_EXTC void IM_FTYPE irq_calloldhandler(int irqnr) IM_LFTYPE;
IM_EXTC void IM_FTYPE irq_disable(int irqnr) IM_LFTYPE;
IM_EXTC void IM_FTYPE irq_enable(int irqnr) IM_LFTYPE;
IM_EXTC int  IM_FTYPE irq_sethandler(int irqnr, void (*handler)(int), void IM_PTYPE *stack) IM_LFTYPE;
IM_EXTC int  IM_FTYPE irq_unsethandler(int irqnr) IM_LFTYPE;

#elif defined(_IM_HOST_OS_NT) && !defined(_IM_HOST_OS_NT_KERNEL) || (defined(_IM_HOST_OS_QNX4) && !defined(_IM_HOST_OS_QNX4_DRIVER)) || (defined(_IM_HOST_OS_LINUX) && !defined(_IM_HOST_OS_LINUX_DRIVER)) || (defined(_IM_HOST_OS_NTO) && !defined(_IM_HOST_OS_NTO_DRIVER))

IM_EXTC HANDLE IM_FTYPE GenesisGetHandleEvent(PGENESIS_HOOK_FUNCTION pGenesisHookFunction) IM_LFTYPE;

#endif


#if defined(_IM_HOST_OS_NT) && !defined(_IM_HOST_OS_NT_KERNEL)

extern void ForceInterruptEventProcess(long NodeId);

#endif

#if !defined(_IM_HOST_OS_NT_KERNEL)

IM_EXTC PGENESIS_HOOK_LIST IM_FTYPE GenesisGetHookList(long NodeId, long InterruptType) IM_LFTYPE;
IM_EXTC PGENESIS_HOOK_FUNCTION IM_FTYPE GenesisGetNextHookFunction(PGENESIS_HOOK_LIST pHookList, PGENESIS_HOOK_FUNCTION *ppGenesisHookFunction) IM_LFTYPE;
IM_EXTC GENESISHOOKFCTPTR IM_FTYPE GenesisGetFuncPtr(PGENESIS_HOOK_FUNCTION pGenesisHookFunction) IM_LFTYPE;
IM_EXTC void IM_PTYPE * IM_FTYPE GenesisGetUsrDataPtr(PGENESIS_HOOK_FUNCTION pGenesisHookFunction) IM_LFTYPE;
IM_EXTC long IM_FTYPE GenesisGetInterruptType(PGENESIS_HOOK_FUNCTION pGenesisHookFunction) IM_LFTYPE;
IM_EXTC long IM_FTYPE GenesisGetHookInterruptType(PGENESIS_HOOK_LIST pHookList) IM_LFTYPE;
IM_EXTC long IM_FTYPE GenesisHookInterruptFunction(long NodeId, GENESISHOOKFCTPTR InterruptFunctionPtr, unsigned long InterruptType, void IM_PTYPE *phEvent, void IM_PTYPE *UserDataPtr) IM_LFTYPE;

#endif

#if defined(_IM_HOST_OS_QNX4) || defined(_IM_HOST_OS_LINUX) || defined(_IM_HOST_OS_NTO)

struct MsgIrq
{
    int msgID;
    int irqNbr;
    GENESISHOOKFCTPTR InterruptFunctionPtr;
    unsigned long InterruptType;
};

#endif
#endif  /* __IM_IRQIO_H__ */

