/***************************************************************************/
/*

    Filename:  MILPAT.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the defines for the MIL pattern
               recognition module. (Mpat...).

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILPAT_H__
#define __MILPAT_H__

/* C++ directive if needed */
#ifdef __cplusplus
extern "C"
{
#endif

/* Bit encoded model types */
#define M_TEMPLATE    1L
#define M_NORMALIZED  2L
#define M_ROTATION    4L
#define M_NOISY       0x0800L

/* Levels of speed and/or accuracy */
#define M_VERY_LOW        0L
#define M_LOW             1L
#define M_MEDIUM          2L
#define M_HIGH            3L
#define M_VERY_HIGH       4L
#define M_FULL_SEARCH  0x80L

/* Bit encoded flags for MpatPreprocModel() */
#define M_DELETE_LOW    0x10L
#define M_DELETE_MEDIUM 0x20L
#define M_DELETE_HIGH   0x40L

#define M_ALL             0L
#define M_DISABLE     -9999L
#define M_UNKNOWN     -9999L
#define M_NO_CHANGE   -9998L
#define M_ABSOLUTE        1L
#define M_OFFSET          2L

/* 'type' parameter of MpatAlloc() */
#define M_REGULAR     0x20000L
#define M_FAST        0x40000L
#define M_NO_ROTATION 0x80000L
#define M_BEST        0x100000L
#define M_PAT_DEBUG   0x200000L
#define M_MULTIPLE    0x400000L

/* 'Flag' parameter of MpatCopy() */
#define M_CLEAR_BACKGROUND 0x2000L

/* Used by MpatGetResult() */
#define M_FOUND_FLAG        1L
#define M_SCORE             0x00001400L
#define M_POSITION_X        0x00003400L
#define M_POSITION_Y        0x00004400L
#define M_SCALE             6L
#define M_ORIENTATION_SCORE 7L

/* Used by MpatInquire() */
#define M_ALLOC_TYPE              1L
#define M_ALLOC_SIZE_X            2L
#define M_ALLOC_SIZE_Y            3L
#define M_CENTER_X                4L
#define M_CENTER_Y                5L
#define M_ORIGINAL_X              6L
#define M_ORIGINAL_Y              7L
#define M_SPEED_FACTOR            8L
#define M_POSITION_START_X        9L
#define M_POSITION_START_Y       10L
#define M_POSITION_UNCERTAINTY_X 11L
#define M_POSITION_UNCERTAINTY_Y 12L
#define M_POSITION_ACCURACY      13L
#define M_PREPROCESSED           14L
#define M_ALLOC_OFFSET_X         15L
#define M_ALLOC_OFFSET_Y         16L
#define M_ACCEPTANCE_THRESHOLD   17L 
#define M_NUMBER_OF_OCCURENCES   18L
#define M_NUMBER_OF_OCCURRENCES  18L
#define M_WORKSPACE_SIZE_X       19L
#define M_WORKSPACE_SIZE_Y       20L
#define M_WORKSPACE_FAST         21L
#define M_WORKSPACE_ROTATION     22L
#define M_WORKSPACE              23L
#define M_NUMBER_OF_ENTRIES      24L
#define M_CERTAINTY_THRESHOLD    25L

/* Search parameters */
#define M_FIRST_LEVEL             31L
#define M_LAST_LEVEL              32L
#define M_MODEL_STEP              33L
#define M_FAST_FIND               34L
#define M_MIN_SPACING_X           35L
#define M_MIN_SPACING_Y           36L
#define M_SCORE_TYPE              37L
#define M_MODEL_FILE_TYPE         38L
#define M_KEEP_PYRAMID            39L
#define M_REJECTION_THRESHOLD     41L
#define M_HIGHEST_REJECTED_SCORE  42L
#define M_HIGHEST_REJECTED_LEVEL  43L
#define M_MODEL_FILE_TYPE_HOST    3L
#define M_MODEL_FILE_TYPE_GENESIS 4L

/* Parameters for find orientation */
#define M_RESULT_RANGE_180       0x00000001L
#define M_RESULT_RANGE_90        0x00000002L
#define M_RESULT_RANGE_360       0x00000004L
#define M_RESULT_RANGE_45        0x00000008L
#define M_ORIENTATION_ACCEPTANCE 200.0


/* Search parameters for search with rotation */
#define M_SEARCH_ANGLE_MODE                   0x00000080L
#define M_SEARCH_ANGLE                        0x00000100L
#define M_SEARCH_ANGLE_DELTA_NEG              0x00000200L
#define M_SEARCH_ANGLE_DELTA_POS              0x00000400L
#define M_SEARCH_ANGLE_TOLERANCE              0x00000800L
#define M_SEARCH_ANGLE_ACCURACY               0x00001000L
#define M_SEARCH_ANGLE_FINE_REGION            0x00002000L
#define M_SEARCH_ANGLE_DEBUG                  0x00004000L
#define M_SEARCH_ANGLE_INTERPOLATION_MODE     0x00008000L
#define M_SEARCH_ANGLE_DIRTY                  0x00010000L
#define M_SEARCH_ANGLE_MAGIC_V1               0x0100CAFEL
#define M_SEARCH_ANGLE_V1_FREE                0x128

#define M_DEF_SEARCH_ANGLE_MODE               M_DISABLE
#define M_DEF_SEARCH_ANGLE                    0.0
#define M_DEF_SEARCH_ANGLE_DELTA_NEG          0.0
#define M_DEF_SEARCH_ANGLE_DELTA_POS          0.0
#define M_DEF_SEARCH_ANGLE_TOLERANCE          5.0
#define M_DEF_SEARCH_ANGLE_ACCURACY           M_DISABLE
#define M_DEF_SEARCH_ANGLE_FINE_REGION        30L
#define M_DEF_SEARCH_ANGLE_DEBUG              M_DISABLE
#define M_DEF_SEARCH_ANGLE_INTERPOLATION_MODE M_NEAREST_NEIGHBOR

/* Spelling variations */
#define M_CENTRE_X     M_CENTER_X
#define M_CENTRE_Y     M_CENTER_Y

/********************************************************************
 * Error codes
 ********************************************************************/

/* Model errors */
#define M_PAT_MODEL_ID_ERROR           (1000+M_FUNC_ERROR)
#define M_PAT_MODEL_CORRUPT_ERROR      (1001+M_FUNC_ERROR)
#define M_PAT_MODEL_TYPE_ERROR         (1002+M_FUNC_ERROR)

/* Result errors */
#define M_PAT_RESULT_ID_ERROR          (1050+M_FUNC_ERROR)
#define M_PAT_RESULT_EMPTY_ERROR       (1051+M_FUNC_ERROR)

/* File errors */
#define M_PAT_FILE_OPEN_ERROR          (1100+M_FUNC_ERROR)
#define M_PAT_FILE_READ_ERROR          (1101+M_FUNC_ERROR)
#define M_PAT_FILE_WRITE_ERROR         (1102+M_FUNC_ERROR)

/* Memory errors */
#define M_PAT_MEMORY_ERROR             (1150+M_FUNC_ERROR)
#define M_PAT_NO_IDS_ERROR             (1152+M_FUNC_ERROR)

/* Processing errors */
#define M_PAT_PARAMETER_ERROR          (1204+M_FUNC_ERROR)
#define M_PAT_WORKBUF_ERROR            (1205+M_FUNC_ERROR)
#define M_PAT_NOT_IMPLEMENTED_ERROR    (1207+M_FUNC_ERROR)

/********************************************************************
 * Function prototypes
 ********************************************************************/

#ifndef __midl // MIDL compiler used by ActiveMIL


MFTYPE32 MIL_ID MFTYPE MpatAlloc(                            long SizeX,
                                                             long SizeY,
                                                             long Type,
                                                             MIL_ID MPTYPE *IdPtr);
MFTYPE32 MIL_ID MFTYPE MpatAllocModel(                       MIL_ID SystemId,
                                                             MIL_ID SrcImageId,
                                                             long OffX,
                                                             long OffY,
                                                             long SizeX,
                                                             long SizeY,
                                                             long ModelType,
                                                             MIL_ID MPTYPE *IdPtr);
MFTYPE32 MIL_ID MFTYPE MpatAllocResult(                      MIL_ID SystemId,
                                                             long NumEntries,
                                                             MIL_ID MPTYPE *IdPtr);
MFTYPE32 void MFTYPE MpatCopy(                               MIL_ID ModelId,
                                                             MIL_ID ImageId,
                                                             long Version);
MFTYPE32 void MFTYPE MpatFindModel(                          MIL_ID ImageId,
                                                             MIL_ID ModelId,
                                                             MIL_ID ResultId);
MFTYPE32 void MFTYPE MpatFindMultipleModel(                  MIL_ID ImageId,
                                                             MIL_ID MPTYPE *ModelId,
                                                             MIL_ID MPTYPE *ResultId,
                                                             long NumModels,
                                                             long Flag);
MFTYPE32 void MFTYPE MpatFindOrientation(                    MIL_ID ImageId,
                                                             MIL_ID ModelId,
                                                             MIL_ID ResultId,
                                                             long ResultRange);
MFTYPE32 void MFTYPE MpatFree(                               MIL_ID PatBufferId);
MFTYPE32 long MFTYPE MpatGetNumber(                          MIL_ID ResultId,
                                                             long MPTYPE *CountPtr);
MFTYPE32 void MFTYPE MpatGetResult(                          MIL_ID ResultId,
                                                             long Type,
                                                             double MPTYPE *ArrayPtr);
MFTYPE32 void MFTYPE MpatInquire(                            MIL_ID ModelId,
                                                             long Item,
                                                             void MPTYPE *VarPtr);
MFTYPE32 void MFTYPE MpatPreprocModel(                       MIL_ID ImageId,
                                                             MIL_ID ModelId,
                                                             long Mode);
MFTYPE32 MIL_ID MFTYPE MpatRead(                             MIL_ID SystemId,
                                                             void *FileHandle,
                                                             MIL_ID MPTYPE *IdPtr);
MFTYPE32 MIL_ID MFTYPE MpatRestore(                          MIL_ID SystemId,
                                                             char MPTYPE *FileName,
                                                             MIL_ID MPTYPE *IdPtr);
MFTYPE32 MIL_ID MFTYPE MpatAllocRotatedModel(                MIL_ID SystemId,
                                                             MIL_ID SrcModelorImageId,
                                                             double Angle,
                                                             long InterpolMode,
                                                             long ModelType,
                                                             MIL_ID MPTYPE *IdPtr);
MFTYPE32 MIL_ID MFTYPE MpatAllocRotatedModelAndSetDontCare(  MIL_ID SystemId,
                                                             MIL_ID SrcImageId,
                                                             MIL_ID SrcDontCareId,
                                                             double Angle,
                                                             long InterpolMode,
                                                             long ModelType,
                                                             MIL_ID MPTYPE *IdPtr);
MFTYPE32 void MFTYPE MpatSave(                               char MPTYPE *FileName,
                                                             MIL_ID ModelId);
MFTYPE32 void MFTYPE MpatSetAcceptance(                      MIL_ID ModelId,
                                                             double AcceptanceThreshold);
MFTYPE32 void MFTYPE MpatSetAccuracy(                        MIL_ID ModelId,
                                                             long Accuracy);
MFTYPE32 void MFTYPE MpatSetAngle(                           MIL_ID ModelId,
                                                             long ControlType,
                                                             double ControlValue);
MFTYPE32 void MFTYPE MpatSetCenter(                          MIL_ID ModelId,
                                                             double OffX,
                                                             double OffY);
MFTYPE32 void MFTYPE MpatSetCertainty(                       MIL_ID ModelId,
                                                             double CertaintyThreshold);
MFTYPE32 void MFTYPE MpatSetDontCare(                        MIL_ID ModelId,
                                                             MIL_ID ImageId,
                                                             long OffX,
                                                             long OffY,
                                                             long Value);
MFTYPE32 void MFTYPE MpatSetNumber(                          MIL_ID ModelId,
                                                             long NumMatches);
MFTYPE32 void MFTYPE MpatSetPosition(                        MIL_ID ModelId,
                                                             long StartX,
                                                             long StartY,
                                                             long SizeX,
                                                             long SizeY);
MFTYPE32 void MFTYPE MpatSetSearchParameter(                 MIL_ID ModelId,
                                                             long Parameter,
                                                             double Value);
MFTYPE32 void MFTYPE MpatSetSpeed(                           MIL_ID ModelId,
                                                             long Speed);
MFTYPE32 void MFTYPE MpatWrite(                              void *FileHandle,
                                                             MIL_ID ModelId);
MFTYPE32 MIL_ID  MFTYPE MpatAllocAutoModel(                  MIL_ID SystemId,
                                                             MIL_ID BufId,
                                                             long ModelSizeX,
                                                             long ModelSizeY,
                                                             long PosUncertaintyX,
                                                             long PosUncertaintyY,
                                                             long ModelType,
                                                             long Mode,
                                                             MIL_ID *ModelId);


#endif /* #ifdef __midl */


/* C++ directive if needed */
#ifdef __cplusplus
}
#endif

#endif /* __MILPAT_H__ */
