/***************************************************************************/
/*

    Filename:  MILDEC.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   6.1  $
    Content :  This file contains the defines that are used by the
               mil functions to specify which type of command decoder
               will be used by the allocated system (MsysAlloc()).

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILDEC_H
#define __MILDEC_H

    #ifdef __cplusplus
    extern "C"
    {
    #endif

    MFTYPE32 void MFTYPE MDVgaCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDMeteorCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDPulsarCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDGenesisCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDCoronaCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDMeteorIICommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDMeteorIIDigCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MD1394CommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDOrionCommandDecoder(void MPTYPE *Param);
    MFTYPE32 void MFTYPE MDRemoteCommandDecoder(void MPTYPE *Param);
    #ifdef __cplusplus
    }
    #endif

    #define M_SYSTEM_HOST        ((void MPTYPE *)(((void (MFTYPE *)(void MPTYPE *Param))NULL)))
    #define M_SYSTEM_VGA         ((void MPTYPE *)(MDVgaCommandDecoder))
    #define M_SYSTEM_METEOR      ((void MPTYPE *)(MDMeteorCommandDecoder))
    #define M_SYSTEM_PULSAR      ((void MPTYPE *)(MDPulsarCommandDecoder))
    #define M_SYSTEM_GENESIS     ((void MPTYPE *)(MDGenesisCommandDecoder))
    #define M_SYSTEM_CORONA      ((void MPTYPE *)(MDCoronaCommandDecoder))
    #define M_SYSTEM_METEOR_II   ((void MPTYPE *)(MDMeteorIICommandDecoder))
    #define M_SYSTEM_METEOR_II_DIG  ((void MPTYPE *)(MDMeteorIIDigCommandDecoder))
    #define M_SYSTEM_1394        ((void MPTYPE *)(MD1394CommandDecoder))
    #define M_SYSTEM_METEOR_II_1394   M_SYSTEM_1394
    #define M_SYSTEM_ORION       ((void MPTYPE *)(MDOrionCommandDecoder))
#endif



