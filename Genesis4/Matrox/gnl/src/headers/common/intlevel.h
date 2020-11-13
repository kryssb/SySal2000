/*******************************************************************
 *
 * COPYRIGHT (c) 1994,1995 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

/*******************************************************************
 *
 * Synopsis:      Prototypes for interrupt sources.
 *
 * Bugs:
 *
 * Designed:      bLem for IMAGE-2
 *                12/22/94   10:57:26
 *
 * Reviewed:
 *
 * Last modified: rBec for IMAGE-2
 *                01/04/95   15:30:00
 *                Removed _MP_CPU_INTFLG_PKT_DONE from the interrupts
 *                serviced by _MP_CPU_INTFLGS_GENERAL.
 *
 * Notes:
 *
 *******************************************************************/

#ifndef __INTLEVEL_H__
#define __INTLEVEL_H__

#if !defined(_IM_LOCAL_CODE) && defined(SHOW_INCLUDE_FILE)
#pragma message ("#include "__FILE__)
#endif

/* Each section use 32 semaphores */
#define _MP_MAX_SEMA_BY_SECTION                 (32L)
#define _MP_CPU_SEMA_OFFSET                     (0L)
#define _MP_PRIMARY_VIA_SEMA_OFFSET             (_MP_CPU_SEMA_OFFSET+_MP_MAX_SEMA_BY_SECTION)
#define _MP_DISPLAY_VIA_SEMA_OFFSET             (_MP_PRIMARY_VIA_SEMA_OFFSET+_MP_MAX_SEMA_BY_SECTION)
#define _MP_GRAB_MODULE_SEMA_OFFSET             (_MP_DISPLAY_VIA_SEMA_OFFSET+_MP_MAX_SEMA_BY_SECTION)
#define _MP_NOA_SEMA_OFFSET                     (_MP_GRAB_MODULE_SEMA_OFFSET+_MP_MAX_SEMA_BY_SECTION)

#define _MP_INTLVL_MASK                         0x1f              /* Bit 0 to 31 */

#if defined(_IM_COMP_MVP)
/*
 * Levels assigned to MP's hardware interrupts
 */
#define MP_CPU_INTLVL_FP_INVALID                (_MP_CPU_SEMA_OFFSET + 2L)       /* floating point invalid */
#define MP_CPU_INTLVL_FP_DIV0                   (_MP_CPU_SEMA_OFFSET + 3L)       /* floating point divide by 0 */
#define MP_CPU_INTLVL_INT_OVERFLOW              (_MP_CPU_SEMA_OFFSET + 4L)       /* integer overflow */
#define MP_CPU_INTLVL_FP_OVERFLOW               (_MP_CPU_SEMA_OFFSET + 5L)       /* floating point overflow */
#define MP_CPU_INTLVL_FP_UNDERFLOW              (_MP_CPU_SEMA_OFFSET + 6L)       /* floating point underflow */
#define MP_CPU_INTLVL_FP_INEXACT                (_MP_CPU_SEMA_OFFSET + 7L)       /* floating point inexact */
#define MP_CPU_INTLVL_FRAME_TIMER0              (_MP_CPU_SEMA_OFFSET + 8L)       /* frame timer 0 interrupt */
#define MP_CPU_INTLVL_FRAME_TIMER1              (_MP_CPU_SEMA_OFFSET + 9L)       /* frame timer 1 interrupt */
#define MP_CPU_INTLVL_CLOCK_TIMER               (_MP_CPU_SEMA_OFFSET + 10L)      /* clock timer interrupt */
#define MP_CPU_INTLVL_EXTERNAL1                 (_MP_CPU_SEMA_OFFSET + 11L)      /* external interrupt 1 */
#define MP_CPU_INTLVL_EXTERNAL2                 (_MP_CPU_SEMA_OFFSET + 12L)      /* external interrupt 2 */
#define MP_CPU_INTLVL_MEM_FAULT                 (_MP_CPU_SEMA_OFFSET + 14L)      /* memory fault */
#define MP_CPU_INTLVL_MSGINT_PP0                (_MP_CPU_SEMA_OFFSET + 16L)      /* message interrupt from PP0 */
#define MP_CPU_INTLVL_MSGINT_PP1                (_MP_CPU_SEMA_OFFSET + 17L)      /* message interrupt from PP1 */
#define MP_CPU_INTLVL_MSGINT_PP2                (_MP_CPU_SEMA_OFFSET + 18L)      /* message interrupt from PP2 */
#define MP_CPU_INTLVL_MSGINT_PP3                (_MP_CPU_SEMA_OFFSET + 19L)      /* message interrupt from PP3 */
#define MP_CPU_INTLVL_MSGINT_PP4                (_MP_CPU_SEMA_OFFSET + 20L)      /* message interrupt from PP4 */
#define MP_CPU_INTLVL_MSGINT_PP5                (_MP_CPU_SEMA_OFFSET + 21L)      /* message interrupt from PP5 */
#define MP_CPU_INTLVL_MSGINT_PP6                (_MP_CPU_SEMA_OFFSET + 22L)      /* message interrupt from PP6 */
#define MP_CPU_INTLVL_MSGINT_PP7                (_MP_CPU_SEMA_OFFSET + 23L)      /* message interrupt from PP7 */
#define MP_CPU_INTLVL_MSGINT_MP                 (_MP_CPU_SEMA_OFFSET + 25L)      /* message interrupt from MP */
#define MP_CPU_INTLVL_PKT_DONE                  (_MP_CPU_SEMA_OFFSET + 26L)      /* packet transfer completed */
#define MP_CPU_INTLVL_PKT_BUSY                  (_MP_CPU_SEMA_OFFSET + 27L)      /* packet transfer completed */
#define MP_CPU_INTLVL_PKT_BAD                   (_MP_CPU_SEMA_OFFSET + 28L)      /* bad packet transfer request */
#define MP_CPU_INTLVL_EXTERNAL3                 (_MP_CPU_SEMA_OFFSET + 29L)      /* external interrupt 3 */
#define MP_CPU_INTLVL_EXTERNAL4                 (_MP_CPU_SEMA_OFFSET + 30L)      /* external interrupt 4 */
#define MP_CPU_INTLVL_PPERROR                   (_MP_CPU_SEMA_OFFSET + 31L)      /* PP error interrupt */


/*
 * MP's INTPEN and IE registers -- bit masks for interrupt flags
 */
#define _MP_CPU_INTFLG_FP_INVALID               (1L<<(MP_CPU_INTLVL_FP_INVALID   - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_FP_DIV0                  (1L<<(MP_CPU_INTLVL_FP_DIV0      - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_INT_OVERFLOW             (1L<<(MP_CPU_INTLVL_INT_OVERFLOW - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_FP_OVERFLOW              (1L<<(MP_CPU_INTLVL_FP_OVERFLOW  - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_FP_UNDERFLOW             (1L<<(MP_CPU_INTLVL_FP_UNDERFLOW - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_FP_INEXACT               (1L<<(MP_CPU_INTLVL_FP_INEXACT   - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_FRAME_TIMER0             (1L<<(MP_CPU_INTLVL_FRAME_TIMER0 - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_FRAME_TIMER1             (1L<<(MP_CPU_INTLVL_FRAME_TIMER1 - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_CLOCK_TIMER              (1L<<(MP_CPU_INTLVL_CLOCK_TIMER  - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_EXTERNAL1                (1L<<(MP_CPU_INTLVL_EXTERNAL1    - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_EXTERNAL2                (1L<<(MP_CPU_INTLVL_EXTERNAL2    - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_MEM_FAULT                (1L<<(MP_CPU_INTLVL_MEM_FAULT    - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_MSGINT_PP0               (1L<<(MP_CPU_INTLVL_MSGINT_PP0   - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_MSGINT_PP1               (1L<<(MP_CPU_INTLVL_MSGINT_PP1   - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_MSGINT_PP2               (1L<<(MP_CPU_INTLVL_MSGINT_PP2   - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_MSGINT_PP3               (1L<<(MP_CPU_INTLVL_MSGINT_PP3   - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_MSGINT_PP4               (1L<<(MP_CPU_INTLVL_MSGINT_PP4   - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_MSGINT_PP5               (1L<<(MP_CPU_INTLVL_MSGINT_PP5   - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_MSGINT_PP6               (1L<<(MP_CPU_INTLVL_MSGINT_PP6   - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_MSGINT_PP7               (1L<<(MP_CPU_INTLVL_MSGINT_PP7   - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_MSGINT_MP                (1L<<(MP_CPU_INTLVL_MSGINT_MP    - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_PKT_DONE                 (1L<<(MP_CPU_INTLVL_PKT_DONE     - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_PKT_BUSY                 (1L<<(MP_CPU_INTLVL_PKT_BUSY     - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_PKT_BAD                  (1L<<(MP_CPU_INTLVL_PKT_BAD      - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_EXTERNAL3                (1L<<(MP_CPU_INTLVL_EXTERNAL3    - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_EXTERNAL4                (1L<<(MP_CPU_INTLVL_EXTERNAL4    - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_PPERROR                  (1L<<(MP_CPU_INTLVL_PPERROR      - _MP_CPU_SEMA_OFFSET))

#define _MP_CPU_INTFLGS_MSGINT_PPS              (_MP_CPU_INTFLG_MSGINT_PP0 | \
                                                 _MP_CPU_INTFLG_MSGINT_PP1 | \
                                                 _MP_CPU_INTFLG_MSGINT_PP2 | \
                                                 _MP_CPU_INTFLG_MSGINT_PP3 | \
                                                 _MP_CPU_INTFLG_MSGINT_PP4 | \
                                                 _MP_CPU_INTFLG_MSGINT_PP5 | \
                                                 _MP_CPU_INTFLG_MSGINT_PP6 | \
                                                 _MP_CPU_INTFLG_MSGINT_PP7)

#define _MP_CPU_INTFLGS_GENERAL                 (_MP_CPU_INTFLG_PPERROR     | \
                                                 _MP_CPU_INTFLG_PKT_BAD     | \
                                                 _MP_CPU_INTFLG_PKT_BUSY    | \
                                                 _MP_CPU_INTFLG_MSGINT_MP   | \
                                                 _MP_CPU_INTFLG_CLOCK_TIMER)

#define _MP_CPU_INTFLGS_EXTERNAL                (_MP_CPU_INTFLG_EXTERNAL4)     /* never use _MP_CPU_INTFLG_EXTERNAL3 */

#define _MP_CPU_INTFLGS_FPU                     (_MP_CPU_INTFLG_FP_INVALID   | \
                                                 _MP_CPU_INTFLG_FP_DIV0      | \
                                                 _MP_CPU_INTFLG_FP_OVERFLOW  | \
                                                 _MP_CPU_INTFLG_FP_UNDERFLOW)

#elif defined(_IM_COMP_PPC)

#define MP_CPU_INTLVL_EXTERNAL3                 (_MP_CPU_SEMA_OFFSET + 5L)      /* external interrupt    0x0500 */
#define MP_CPU_INTLVL_EXTERNAL4                 (_MP_CPU_SEMA_OFFSET + 5L)      /* external interrupt    0x0500 */
#define MP_CPU_INTLVL_ALIGNMENT                 (_MP_CPU_SEMA_OFFSET + 6L)      /* alignment interrupt   0x0600 */
#define MP_CPU_INTLVL_CLOCK_TIMER               (_MP_CPU_SEMA_OFFSET + 9L)      /* decrementer interrupt 0x0900 */
#define MP_CPU_INTLVL_SYSTEM_CALL               (_MP_CPU_SEMA_OFFSET + 12L)     /* system call           0x0c00 */

#define _MP_CPU_INTFLG_EXTERNAL3                (1L<<(MP_CPU_INTLVL_EXTERNAL3    - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_EXTERNAL4                (1L<<(MP_CPU_INTLVL_EXTERNAL4    - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_ALIGNMENT                (1L<<(MP_CPU_INTLVL_ALIGNMENT    - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_CLOCK_TIMER              (1L<<(MP_CPU_INTLVL_CLOCK_TIMER  - _MP_CPU_SEMA_OFFSET))
#define _MP_CPU_INTFLG_SYSTEM_CALL              (1L<<(MP_CPU_INTLVL_SYSTEM_CALL  - _MP_CPU_SEMA_OFFSET))

#endif



/*
 * Levels assigned to primary VIA's hardware interrupts
 */
#define MP_PVIA_INTLVL_INTHST_MVP_COMM             (_MP_PRIMARY_VIA_SEMA_OFFSET + 1L)
#define MP_PVIA_INTLVL_INTHST_SELF                 (_MP_PRIMARY_VIA_SEMA_OFFSET + 2L)
#define MP_PVIA_INTLVL_INTHST_PASSUP_IRQ           (_MP_PRIMARY_VIA_SEMA_OFFSET + 3L)
#define MP_PVIA_INTLVL_INTHST_SNOOPER              (_MP_PRIMARY_VIA_SEMA_OFFSET + 4L)
#define MP_PVIA_INTLVL_INTHST_HST_COMM             (_MP_PRIMARY_VIA_SEMA_OFFSET + 5L)
#define MP_PVIA_INTLVL_INTHST_OSB_UPDATE           (_MP_PRIMARY_VIA_SEMA_OFFSET + 6L)
#define MP_PVIA_INTLVL_INTHST_ARP                  (_MP_PRIMARY_VIA_SEMA_OFFSET + 7L)
#define MP_PVIA_INTLVL_PEINT                       (_MP_PRIMARY_VIA_SEMA_OFFSET + 8L)
#define MP_PVIA_INTLVL_SEINT                       (_MP_PRIMARY_VIA_SEMA_OFFSET + 9L)
#define MP_PVIA_INTLVL_TMRINT                      (_MP_PRIMARY_VIA_SEMA_OFFSET + 10L)
#define MP_PVIA_INTLVL_GLINEINT                    (_MP_PRIMARY_VIA_SEMA_OFFSET + 11L)
#define MP_PVIA_INTLVL_SOGINT                      (_MP_PRIMARY_VIA_SEMA_OFFSET + 12L)
#define MP_PVIA_INTLVL_EOGINT                      (_MP_PRIMARY_VIA_SEMA_OFFSET + 13L)
#define MP_PVIA_INTLVL_VLINEINT                    (_MP_PRIMARY_VIA_SEMA_OFFSET + 14L)
#define MP_PVIA_INTLVL_SOTINT                      (_MP_PRIMARY_VIA_SEMA_OFFSET + 15L)
#define MP_PVIA_INTLVL_EOTINT                      (_MP_PRIMARY_VIA_SEMA_OFFSET + 16L)
#define MP_PVIA_INTLVL_VMINT                       (_MP_PRIMARY_VIA_SEMA_OFFSET + 17L)
#define MP_PVIA_INTLVL_CMDRINT                     (_MP_PRIMARY_VIA_SEMA_OFFSET + 18L)
#define MP_PVIA_INTLVL_CMDSINT                     (_MP_PRIMARY_VIA_SEMA_OFFSET + 19L)
#define MP_PVIA_INTLVL_DLINEINT                    (_MP_PRIMARY_VIA_SEMA_OFFSET + 20L)
#define MP_PVIA_INTLVL_EXTINT                      (_MP_PRIMARY_VIA_SEMA_OFFSET + 21L)
#define MP_PVIA_INTLVL_INTMVP_HST_COMM             (_MP_PRIMARY_VIA_SEMA_OFFSET + 22L)
#define MP_PVIA_INTLVL_INTMVP_SELF                 (_MP_PRIMARY_VIA_SEMA_OFFSET + 23L)
#define MP_PVIA_INTLVL_INTMVP_MVPREPLY_COMM        (_MP_PRIMARY_VIA_SEMA_OFFSET + 24L)
#define MP_PVIA_INTLVL_INTMVP_UNDEF_4              (_MP_PRIMARY_VIA_SEMA_OFFSET + 25L)
#define MP_PVIA_INTLVL_INTMVP_UNDEF_5              (_MP_PRIMARY_VIA_SEMA_OFFSET + 26L)
#define MP_PVIA_INTLVL_INTMVP_OSB_UPDATE           (_MP_PRIMARY_VIA_SEMA_OFFSET + 27L)
#define MP_PVIA_INTLVL_INTMVP_ARP                  (_MP_PRIMARY_VIA_SEMA_OFFSET + 28L)
#define MP_PVIA_INTLVL_INTMVP_UNDEF_8              (_MP_PRIMARY_VIA_SEMA_OFFSET + 29L)
#define MP_PVIA_INTLVL_INTMVP_FLUSH_CACHE          (_MP_PRIMARY_VIA_SEMA_OFFSET + 30L)

/*
 * VIA's INTPEN and IE registers -- bit masks for interrupt flags
 */
#define _MP_PVIA_INTFLG_INTHST_MVP_COMM            (1L<<(MP_PVIA_INTLVL_INTHST_MVP_COMM            - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTHST_SELF                (1L<<(MP_PVIA_INTLVL_INTHST_SELF                - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTHST_PASSUP_IRQ          (1L<<(MP_PVIA_INTLVL_INTHST_PASSUP_IRQ          - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTHST_SNOOPER             (1L<<(MP_PVIA_INTLVL_INTHST_SNOOPER             - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTHST_HST_COMM            (1L<<(MP_PVIA_INTLVL_INTHST_HST_COMM            - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTHST_OSB_UPDATE          (1L<<(MP_PVIA_INTLVL_INTHST_OSB_UPDATE          - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTHST_ARP                 (1L<<(MP_PVIA_INTLVL_INTHST_ARP                 - _MP_PRIMARY_VIA_SEMA_OFFSET))

#define _MP_PVIA_INTFLG_INTMVP_HST_COMM            (1L<<(MP_PVIA_INTLVL_INTMVP_HST_COMM            - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTMVP_SELF                (1L<<(MP_PVIA_INTLVL_INTMVP_SELF                - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTMVP_MVPREPLY_COMM       (1L<<(MP_PVIA_INTLVL_INTMVP_MVPREPLY_COMM       - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTMVP_FLUSH_CACHE         (1L<<(MP_PVIA_INTLVL_INTMVP_FLUSH_CACHE         - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTMVP_OSB_UPDATE          (1L<<(MP_PVIA_INTLVL_INTMVP_OSB_UPDATE          - _MP_PRIMARY_VIA_SEMA_OFFSET))
#define _MP_PVIA_INTFLG_INTMVP_ARP                 (1L<<(MP_PVIA_INTLVL_INTMVP_ARP                 - _MP_PRIMARY_VIA_SEMA_OFFSET))

#define _MP_PVIA_INTFLG_EOGINT                     (1L<<(MP_PVIA_INTLVL_EOGINT                     - _MP_PRIMARY_VIA_SEMA_OFFSET))

/*
 * Levels assigned to display VIA's hardware interrupts
 */
#define MP_DVIA_INTLVL_INTHST_MVP_COMM             (_MP_DISPLAY_VIA_SEMA_OFFSET + 1L)
#define MP_DVIA_INTLVL_INTHST_UNDEF_2              (_MP_DISPLAY_VIA_SEMA_OFFSET + 2L)
#define MP_DVIA_INTLVL_INTHST_PASSUP_IRQ           (_MP_DISPLAY_VIA_SEMA_OFFSET + 3L)
#define MP_DVIA_INTLVL_INTHST_UNDEF_4              (_MP_DISPLAY_VIA_SEMA_OFFSET + 4L)
#define MP_DVIA_INTLVL_INTHST_HST_COMM             (_MP_DISPLAY_VIA_SEMA_OFFSET + 5L)
#define MP_DVIA_INTLVL_INTHST_OSB_UPDATE           (_MP_DISPLAY_VIA_SEMA_OFFSET + 6L)
#define MP_DVIA_INTLVL_INTHST_ARP                  (_MP_DISPLAY_VIA_SEMA_OFFSET + 7L)
#define MP_DVIA_INTLVL_PEINT                       (_MP_DISPLAY_VIA_SEMA_OFFSET + 8L)
#define MP_DVIA_INTLVL_SEINT                       (_MP_DISPLAY_VIA_SEMA_OFFSET + 9L)
#define MP_DVIA_INTLVL_TMRINT                      (_MP_DISPLAY_VIA_SEMA_OFFSET + 10L)
#define MP_DVIA_INTLVL_GLINEINT                    (_MP_DISPLAY_VIA_SEMA_OFFSET + 11L)
#define MP_DVIA_INTLVL_SOGINT                      (_MP_DISPLAY_VIA_SEMA_OFFSET + 12L)
#define MP_DVIA_INTLVL_EOGINT                      (_MP_DISPLAY_VIA_SEMA_OFFSET + 13L)
#define MP_DVIA_INTLVL_VLINEINT                    (_MP_DISPLAY_VIA_SEMA_OFFSET + 14L)
#define MP_DVIA_INTLVL_SOTINT                      (_MP_DISPLAY_VIA_SEMA_OFFSET + 15L)
#define MP_DVIA_INTLVL_EOTINT                      (_MP_DISPLAY_VIA_SEMA_OFFSET + 16L)
#define MP_DVIA_INTLVL_VMINT                       (_MP_DISPLAY_VIA_SEMA_OFFSET + 17L)
#define MP_DVIA_INTLVL_CMDRINT                     (_MP_DISPLAY_VIA_SEMA_OFFSET + 18L)
#define MP_DVIA_INTLVL_CMDSINT                     (_MP_DISPLAY_VIA_SEMA_OFFSET + 19L)
#define MP_DVIA_INTLVL_DLINEINT                    (_MP_DISPLAY_VIA_SEMA_OFFSET + 20L)
#define MP_DVIA_INTLVL_EXTINT                      (_MP_DISPLAY_VIA_SEMA_OFFSET + 21L)
#define MP_DVIA_INTLVL_INTMVP_UNDEF_1              (_MP_DISPLAY_VIA_SEMA_OFFSET + 22L)
#define MP_DVIA_INTLVL_INTMVP_UNDEF_2              (_MP_DISPLAY_VIA_SEMA_OFFSET + 23L)
#define MP_DVIA_INTLVL_INTMVP_UNDEF_3              (_MP_DISPLAY_VIA_SEMA_OFFSET + 24L)
#define MP_DVIA_INTLVL_INTMVP_UNDEF_4              (_MP_DISPLAY_VIA_SEMA_OFFSET + 25L)
#define MP_DVIA_INTLVL_INTMVP_UNDEF_5              (_MP_DISPLAY_VIA_SEMA_OFFSET + 26L)
#define MP_DVIA_INTLVL_INTMVP_UNDEF_6              (_MP_DISPLAY_VIA_SEMA_OFFSET + 27L)
#define MP_DVIA_INTLVL_INTMVP_ARP                  (_MP_DISPLAY_VIA_SEMA_OFFSET + 28L)
#define MP_DVIA_INTLVL_INTMVP_UNDEF_8              (_MP_DISPLAY_VIA_SEMA_OFFSET + 29L)
#define MP_DVIA_INTLVL_INTMVP_UNDEF_9              (_MP_DISPLAY_VIA_SEMA_OFFSET + 30L)

/*
 * VIA's INTPEN and IE registers -- bit masks for interrupt flags
 */
#define _MP_DVIA_INTFLG_INTHST_MVP_COMM            (1L<<(MP_DVIA_INTLVL_INTHST_MVP_COMM   - _MP_DISPLAY_VIA_SEMA_OFFSET))
#define _MP_DVIA_INTFLG_INTHST_PASSUP_IRQ          (1L<<(MP_DVIA_INTLVL_INTHST_PASSUP_IRQ - _MP_DISPLAY_VIA_SEMA_OFFSET))
#define _MP_DVIA_INTFLG_INTHST_HST_COMM            (1L<<(MP_DVIA_INTLVL_INTHST_HST_COMM   - _MP_DISPLAY_VIA_SEMA_OFFSET))

#define _MP_DVIA_INTFLG_INTHST_OSB_UPDATE          (1L<<(MP_DVIA_INTLVL_INTHST_OSB_UPDATE - _MP_DISPLAY_VIA_SEMA_OFFSET))
#define _MP_DVIA_INTFLG_INTHST_ARP                 (1L<<(MP_DVIA_INTLVL_INTHST_ARP        - _MP_DISPLAY_VIA_SEMA_OFFSET))
#define _MP_DVIA_INTFLG_INTMVP_ARP                 (1L<<(MP_DVIA_INTLVL_INTMVP_ARP        - _MP_DISPLAY_VIA_SEMA_OFFSET))


/*
 * Levels assigned to Meteor II/Dig hardware interrupts
 */
#define MP_GRABMODULE_INTLVL_UART                  (_MP_GRAB_MODULE_SEMA_OFFSET + 9L)
#define MP_GRABMODULE_INTLVL_MJPEG                 (_MP_GRAB_MODULE_SEMA_OFFSET + 10L)
#define MP_GRABMODULE_INTLVL_PSG                   (_MP_GRAB_MODULE_SEMA_OFFSET + 11L)    /* Same as MP_GRABMODULE_INTLVL_USERIN */

/*
 * Levels assigned to standard grab module hardware interrupts
 */
#define MP_GRABMODULE_INTLVL_USERIN                (_MP_GRAB_MODULE_SEMA_OFFSET + 11L)

/*
 * Levels assigned to DAC module hardware interrupts
 */
#define MP_GRABMODULE_INTLVL_MACCH0_SOG            (_MP_GRAB_MODULE_SEMA_OFFSET + 12L)
#define MP_GRABMODULE_INTLVL_MACCH0_GLINE          (_MP_GRAB_MODULE_SEMA_OFFSET + 13L)
#define MP_GRABMODULE_INTLVL_MACCH0_EOG            (_MP_GRAB_MODULE_SEMA_OFFSET + 14L)
#define MP_GRABMODULE_INTLVL_MACCH0_DMA_OVR        (_MP_GRAB_MODULE_SEMA_OFFSET + 15L)
#define MP_GRABMODULE_INTLVL_MACCH0_GRB_OVR        (_MP_GRAB_MODULE_SEMA_OFFSET + 16L)
#define MP_GRABMODULE_INTLVL_MACCH0_FRM_DROP       (_MP_GRAB_MODULE_SEMA_OFFSET + 17L)
#define MP_GRABMODULE_INTLVL_MACCH1_SOG            (_MP_GRAB_MODULE_SEMA_OFFSET + 18L)
#define MP_GRABMODULE_INTLVL_MACCH1_GLINE          (_MP_GRAB_MODULE_SEMA_OFFSET + 19L)
#define MP_GRABMODULE_INTLVL_MACCH1_EOG            (_MP_GRAB_MODULE_SEMA_OFFSET + 20L)
#define MP_GRABMODULE_INTLVL_MACCH1_DMA_OVR        (_MP_GRAB_MODULE_SEMA_OFFSET + 21L)
#define MP_GRABMODULE_INTLVL_MACCH1_GRB_OVR        (_MP_GRAB_MODULE_SEMA_OFFSET + 22L)
#define MP_GRABMODULE_INTLVL_MACCH1_FRM_DROP       (_MP_GRAB_MODULE_SEMA_OFFSET + 23L)

/*
 * Levels assigned to NOA's hardware interrupts
 */
#define MP_NOA_INTLVL_EOPINT                       (_MP_NOA_SEMA_OFFSET + 0L)
#define MP_NOA_INTLVL_ACCINT                       (_MP_NOA_SEMA_OFFSET + 1L)
#define MP_NOA_INTLVL_MINT                         (_MP_NOA_SEMA_OFFSET + 2L)


#endif /* __INTLEVEL_H__ */
