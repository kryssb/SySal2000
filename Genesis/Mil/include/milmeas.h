/***************************************************************************/
/*

    Filename:  MILMEAS.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the defines for the MIL measurement
               module. (Mmeas...).

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILMEAS_H__
#define __MILMEAS_H__

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************/
/* CAPI defines                                                           */
/**************************************************************************/

/**************************************************************************/
/* MmeasAllocMarker                                                       */
/**************************************************************************/

#define M_POINT                           1L
#define M_EDGE                            2L
#define M_STRIPE                          3L
#define M_EDGE_LIST                       5L
#define M_STRIPE_LIST                     6L


/**************************************************************************/
/* MmeasAllocResult                                                       */
/**************************************************************************/
#define M_CALCULATE                       1L


/**************************************************************************/
/* Bitwise values that the followings cannot take                         */
/**************************************************************************/

#define M_TYPE_LONG                       0x00040000L
#define M_MULTI_MARKER_MASK               0x000003FFL
#define M_EDGE_FIRST                      0x00100000L 
#define M_EDGE_SECOND                     0x00200000L 
#define M_WEIGHT_FACTOR                   0x01000000L
#define M_MIN                             0x02000000L
#define M_MEAN                            0x03000000L
#define M_MAX                             0x04000000L
#define M_MEAS_FUTURE_USE_0               0x10000000L 
#define M_MEAS_FUTURE_USE_1               0x20000000L 
#define M_MEAS_FUTURE_USE_2               0x40000000L 
#define M_MEAS_FUTURE_USE_3               0x80000000L 


/**************************************************************************/
/* MmeasInquire(), MmeasSetMarker(), MmeasGetResult(), MmeasFindMarker(), */
/* MmeasCalculate() parameters :                                          */
/**************************************************************************/

#define M_POSITION_VARIATION              0x00008000L
#define M_ANGLE                           0x00000800L
#define M_WIDTH                           0x00010000L
#define M_WIDTH_VARIATION                 0x00020000L
#define M_POLARITY                        0x00004000L
#define M_CONTRAST                        0x00001000L
#define M_LENGTH                          0x00002000L
#define M_LINE_EQUATION                   0x00800000L
#define M_LINE_EQUATION_SLOPE             0x00801000L
#define M_LINE_EQUATION_INTERCEPT         0x00802000L
#define M_EDGE_INSIDE                     0x00400000L
#define M_POSITION                        0x00000400L
#define M_SCORE                           0x00001400L
#define M_ORIENTATION                     0x00002400L
#define M_POSITION_X                      0x00003400L
#define M_POSITION_Y                      0x00004400L
#define M_CONTRAST_VARIATION              0x00005400L
#define M_EDGE_STRENGTH                   0x00006400L
#define M_EDGE_STRENGTH_VARIATION         0x00007400L
#define M_EDGE_INSIDE_VARIATION           0x00008400L
#define M_BOX_ORIGIN                      0x00009400L
#define M_BOX_SIZE                        0x0000A400L
#define M_BOX_CENTER                      0x0000B400L
#define M_BOX_FIRST_CENTER                0x0000C400L
#define M_BOX_SECOND_CENTER               0x0000D400L
#define M_BOX_ANGLE_MODE                  0x0000E400L
#define M_BOX_ANGLE                       0x0000F400L
#define M_BOX_ANGLE_DELTA_NEG             0x00010400L
#define M_BOX_ANGLE_DELTA_POS             0x00011400L
#define M_BOX_ANGLE_TOLERANCE             0x00012400L
#define M_BOX_ANGLE_ACCURACY              0x00013400L
#define M_BOX_ANGLE_INTERPOLATION_MODE    0x00014400L
#define M_EDGE_THRESHOLD                  0x00015400L
#define M_MARKER_REFERENCE                0x00016400L
#define M_BOX_ANGLE_SIZE                  0x00017400L
#define M_MARKER_TYPE                     0x00018400L
#define M_CONTROL_FLAG                    0x00019400L
#define M_POSITION_MIN                    0x0001A400L
#define M_POSITION_MAX                    0x0001B400L
#define M_BOX_EDGES_STRENGTH              0x0001C400L
#define M_ANY_ANGLE                       0x0001D400L
#define M_VALID_FLAG                      0x0001E400L
#define M_BOX_CORNER_TOP_LEFT             0x0001F400L
#define M_BOX_CORNER_TOP_RIGHT            0x00020400L
#define M_BOX_CORNER_BOTTOM_LEFT          0x00021400L
#define M_BOX_CORNER_BOTTOM_RIGHT         0x00022400L
#define M_BOX_EDGES_STRENGTH_NUMBER       0x00023400L
#define M_POSITION_INSIDE_STRIPE          0x00024400L
#define M_BOX_ANGLE_REFERENCE             0x00025400L

#define M_CONTROL_FLAG                    0x00019400L
#define M_ZERO_OFFSET_X                            1L
#define M_ZERO_OFFSET_Y                            2L
#define M_PIXEL_ASPECT_RATIO                       5L
#define M_PIXEL_ASPECT_RATIO_INPUT                 6L
#define M_PIXEL_ASPECT_RATIO_OUTPUT                7L

#define M_RESULT_TYPE                              1L
#define M_DISTANCE                        0x00080000L
#define M_DISTANCE_X                      0x00081000L
#define M_DISTANCE_Y                      0x00082000L
#define M_ANGLE                           0x00000800L
#define M_LINE_EQUATION                   0x00800000L
#define M_LINE_EQUATION_SLOPE             0x00801000L
#define M_LINE_EQUATION_INTERCEPT         0x00802000L


/**************************************************************************/
/* MmeasInquire(), MmeasSetMarker(), MmeasGetResult(), MmeasFindMarker(), */
/* MmeasCalculate() values :                                              */
/**************************************************************************/

#define M_VERTICAL          1L
#define M_HORIZONTAL        2L
#define M_ANY               0x11000000L
#define M_POSITIVE          2L
#define M_NEGATIVE         -2L /*Must be the additive inverse of M_POSITIVE*/
#define M_OPPOSITE          3L
#define M_SAME              4L
#define M_NORMAL            1L 
#define M_CORRECTED         2L


/**************************************************************************/
/* Utility defines                                                        */
/**************************************************************************/

#define M_INFINITE_SLOPE    (1.0E+300)


/**************************************************************************/
/* Function prototypes                                                    */
/**************************************************************************/

MFTYPE32 MIL_ID MFTYPE MmeasAllocMarker  (MIL_ID SystemId,
                                          long   MarkerType,
                                          long   ControlFlag,
                                          MIL_ID *MarkerIdPtr);
MFTYPE32 MIL_ID MFTYPE MmeasAllocResult  (MIL_ID SystemId,
                                          long   ResultBufferType,
                                          MIL_ID MPTYPE *ResultIdPtr);
MFTYPE32 MIL_ID MFTYPE MmeasAllocContext (MIL_ID SystemId,
                                          long   ControlFlag,
                                          MIL_ID *ContextId);
MFTYPE32 void   MFTYPE MmeasFree         (MIL_ID MarkerOrResultIdOrContextId);
MFTYPE32 void   MFTYPE MmeasSaveMarker   (char   *FileName,
                                          MIL_ID MarkerId,
                                          long   ControlFlag);
MFTYPE32 MIL_ID MFTYPE MmeasRestoreMarker(char   *FileName,
                                          MIL_ID SystemId,
                                          long   ControlFlag,
                                          MIL_ID *MarkerIdPtr);
MFTYPE32 void   MFTYPE MmeasSetMarker    (MIL_ID MarkerId,
                                          long   Parameter,
                                          double FirstValue,
                                          double SecondValue);
MFTYPE32 void   MFTYPE MmeasFindMarker   (MIL_ID ContextId,
                                          MIL_ID ImageId,
                                          MIL_ID MarkerId,
                                          long   MeasurementList);
MFTYPE32 void   MFTYPE MmeasCalculate    (MIL_ID ContextID,
                                          MIL_ID Marker1Id,
                                          MIL_ID Marker2Id,
                                          MIL_ID ResultId,
                                          long   MeasurementList);
MFTYPE32 void   MFTYPE MmeasGetResult    (MIL_ID MarkerOrResultId,
                                          long   ResultType,
                                          void   *FirstResultPtr,
                                          void   *SecondResultPtr);
MFTYPE32 long   MFTYPE MmeasInquire      (MIL_ID MarkerIdOrResultIdOrContextId,
                                          long   ParamToInquire,
                                          void   *FirstValuePtr,
                                          void   *SecondValuePtr);
MFTYPE32 void   MFTYPE MmeasControl      (MIL_ID ContextId,
                                          long   ControlType,
                                          double Value);


/* C++ directive if needed */
#ifdef __cplusplus
}
#endif

#endif /* __MILMEAS_H__ */






