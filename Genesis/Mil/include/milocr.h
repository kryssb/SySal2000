/***************************************************************************/
/*

    Filename:  MILOCR.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the prototypes and #defines for the Matrox
               Imaging Library (MIL) C OCR module user's functions.

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef __MILOCR_H__
#define __MILOCR_H__


#ifndef __midl // MIDL compiler used by ActiveMIL

/* Prototypes              */
/* C++ directive if needed */

#ifdef __cplusplus
extern "C"
{
#endif


typedef MFTYPE32 long (MFTYPE MPTYPE *MOCRHOOKFCTPTR)(long HookType,
                                                      char *String,
                                                      void MPTYPE *FExpansionFlagPtr);

MFTYPE32 MIL_ID  MFTYPE MocrAllocFont(    MIL_ID SystemId,
                                          long FontType,
                                          long CharNumber,
                                          long CharBoxSizeX,
                                          long CharBoxSizeY,
                                          long CharOffsetX,
                                          long CharOffsetY,
                                          long CharSizeX,
                                          long CharSizeY,
                                          long CharThickness,
                                          long StringLength,
                                          long InitFlag,
                                          MIL_ID *FontIdPtr);

MFTYPE32 MIL_ID  MFTYPE MocrAllocResult(  MIL_ID SystemId,
                                          long InitFlag,
                                          MIL_ID *ResultIdPtr);

MFTYPE32 void    MFTYPE MocrCalibrateFont(MIL_ID CalibrationImageId,
                                          MIL_ID FontId,
                                          char *String,
                                          double TargetCharSizeXMin,
                                          double TargetCharSizeXMax,
                                          double TargetCharSizeXStep,
                                          double TargetCharSizeYMin,
                                          double TargetCharSizeYmax,
                                          double TargetCharSizeYStep,
                                          long Operation);

MFTYPE32 void    MFTYPE MocrCopyFont(     MIL_ID ImageId,
                                          MIL_ID FontId,
                                          long Operation,
                                          char *CharListString);

MFTYPE32 void    MFTYPE MocrFree(         MIL_ID FontOrResultId);

MFTYPE32 void    MFTYPE MocrGetResult(    MIL_ID ResultId,
                                          long ResultToGet,
                                          void *ResultPtr);

MFTYPE32 void    MFTYPE MocrImportFont(   char *FileName,
                                          long FileFormat,
                                          long Operation,
                                          char *CharListString,
                                          MIL_ID FontId);

MFTYPE32 void    MFTYPE MocrInquire(      MIL_ID FontId,
                                          long InquireItem,
                                          void *ResultPtr);

MFTYPE32 void    MFTYPE MocrReadString(   MIL_ID ImageId,
                                          MIL_ID FontId,
                                          MIL_ID ResultId);

MFTYPE32 void    MFTYPE MocrModifyFont(   MIL_ID FontId,
                                          long   Operation,
                                          long   ControlFlag);

MFTYPE32 MIL_ID  MFTYPE MocrRestoreFont(  char *FileName,
                                          long Operation,
                                          MIL_ID SystemId,
                                          MIL_ID *FontId);

MFTYPE32 void    MFTYPE MocrSaveFont(     char *FileName,
                                          long Operation,
                                          MIL_ID FontId);

MFTYPE32 void    MFTYPE MocrSetConstraint(MIL_ID FontId,
                                          long CharPos,
                                          long CharPosType,
                                          char *CharValidString);

MFTYPE32 void    MFTYPE MocrControl(   MIL_ID FontId,
                                       long ControlToSet,
                                       double Value);

MFTYPE32 void    MFTYPE MocrVerifyString( MIL_ID ImageId,
                                          MIL_ID FontId,
                                          char   *String,
                                          MIL_ID ResultId);

MFTYPE32 long    MFTYPE MocrValidateString(MIL_ID FontId,
                                           long Mode,
                                           char   *String);

MFTYPE32 MOCRHOOKFCTPTR MFTYPE MocrHookFunction(MIL_ID FontId,
                                                long HookType,
                                                MOCRHOOKFCTPTR FctPtr,
                                                void   *UserData);

MFTYPE32 long MFTYPE OcrSemiM1292CheckValid(long HookType,
                                            char *String,
                                            void MPTYPE *FExpansionFlagPtr);
MFTYPE32 long MFTYPE OcrSemiM1388CheckValid(long HookType,
                                            char *String,
                                            void MPTYPE *FExpansionFlagPtr);
MFTYPE32 long MFTYPE OcrSemiCheckValid(long HookType,
                                       char *String,
                                       void MPTYPE *FExpansionFlagPtr);
MFTYPE32 long MFTYPE OcrDefaultCheckValid(long HookType,
                                          char *String,
                                          void MPTYPE *FExpansionFlagPtr);

/* C++ directive if needed */
#ifdef __cplusplus
}
#endif


#endif /* #ifdef __midl */

// OCR control defaults
#define M_DEF_STRING_LOC_MAX_NB_ITER           2L
#define M_DEF_STRING_LOC_STOP_ITER           0.50
#define M_DEF_STRING_LOC_GOOD_NB_CHAR          4L
#define M_DEF_STRING_READ_BAD_SIZE_X         0.40
#define M_DEF_STRING_READ_BAD_SIZE_Y         0.40
#define M_DEF_STRING_READ_GOOD_SIZE_X        0.25
#define M_DEF_STRING_READ_GOOD_SIZE_Y        0.25
#define M_DEF_STRING_READ_BAD_ADD_CHAR         4L
#define M_DEF_STRING_LOC_MIN_CHAR_SIZE       0.66
#define M_DEF_STRING_LOC_MAX_CHAR_SIZE       1.50
#define M_DEF_STRING_LOC_MIN_CHAR_SPACE      0.66
#define M_DEF_STRING_LOC_MAX_CHAR_DISTANCE   0.50
#define M_DEF_STRING_LOC_GOOD_CHAR_SIZE      0.90
#define M_DEF_STRING_MAX_SLOPE               0.1763269
#define M_DEF_STRING_READ_SIZE_X             0.33
#define M_DEF_STRING_READ_SIZE_Y             0.25
#define M_DEF_SKIP_SEARCH               M_DISABLE
#define M_DEF_SKIP_STRING_LOCATION      M_DISABLE
#define M_DEF_SKIP_CONTRAST_ENHANCE     M_DISABLE
#define M_DEF_STRING_ACCEPTANCE              1.00
#define M_DEF_CHAR_ACCEPTANCE                1.00
#define M_DEF_CHAR_INVALID                      0
#define M_DEF_DEBUG                            0
#define M_DEF_ADD_TOP_HAT                      2L
#define M_DEF_KILL_BORDER                M_ENABLE
#define M_DEF_READ_SPEED                 M_MEDIUM
#define M_DEF_READ_ACCURACY              M_MEDIUM
#define M_DEF_READ_FIRST_LEVEL          M_DEFAULT
#define M_DEF_READ_LAST_LEVEL           M_DEFAULT
#define M_DEF_READ_MODEL_STEP           M_DEFAULT
#define M_DEF_READ_FAST_FIND            M_DEFAULT
#define M_DEF_READ_ROBUSTNESS            M_MEDIUM
#define M_DEF_STRING_LOC_NB_MODELS             2L
#define M_DEF_PAT_ON_ACCELERATED        M_DISABLE
#define M_DEF_BLOB_ON_ACCELERATED       M_DISABLE
#define M_DEF_PROC_ON_ACCELERATED        M_ENABLE

// Control associated InfoType defines
#define M_STRING_LOC_CHAR_SIZE_X               1L
#define M_STRING_LOC_CHAR_SIZE_Y               2L
#define M_STRING_LOC_MAX_NB_ITER               3L
#define M_FOREGROUND_VALUE                     4L
#define M_STRING_LOC_STOP_ITER                 5L
#define M_STRING_LOC_GOOD_NB_CHAR              6L
#define M_STRING_READ_BAD_SIZE_X               7L
#define M_STRING_READ_BAD_SIZE_Y               8L
#define M_STRING_READ_GOOD_SIZE_X              9L
#define M_STRING_READ_GOOD_SIZE_Y             10L
#define M_STRING_READ_BAD_ADD_CHAR            11L
#define M_STRING_LOC_MIN_CHAR_SIZE            12L
#define M_STRING_LOC_MAX_CHAR_SIZE            13L
#define M_STRING_LOC_MIN_CHAR_SPACE           14L
#define M_STRING_LOC_MAX_CHAR_DISTANCE        15L
#define M_STRING_LOC_GOOD_CHAR_SIZE           16L
#define M_STRING_MAX_SLOPE                    17L
#define M_STRING_READ_SIZE_X                  18L
#define M_STRING_READ_SIZE_Y                  19L
#define M_SKIP_SEARCH                         21L
#define M_SKIP_STRING_LOCATION                22L
#define M_SKIP_CONTRAST_ENHANCE               23L
#define M_STRING_ACCEPTANCE                   24L
#define M_CHAR_ACCEPTANCE                     25L
#define M_CHAR_INVALID                        26L
#define M_TARGET_CHAR_SIZE_X                  27L
#define M_TARGET_CHAR_SIZE_Y                  28L
#define M_TARGET_CHAR_SPACING                 29L
#define M_DEBUG                               30L
#define M_FONT_TYPE                           31L
#define M_CHAR_NUMBER                         32L
#define M_CHAR_BOX_SIZE_X                     33L
#define M_CHAR_BOX_SIZE_Y                     34L
#define M_CHAR_OFFSET_X                       35L
#define M_CHAR_OFFSET_Y                       36L
#define M_CHAR_SIZE_X                         37L
#define M_CHAR_SIZE_Y                         38L
#define M_CHAR_THICKNESS                      39L
#define M_STRING_LENGTH                       40L
#define M_FONT_INIT_FLAG                      41L
#define M_CHAR_IN_FONT                        42L
#define M_ADD_TOP_HAT                         43L
#define M_KILL_BORDER                         44L
#define M_CHAR_ERASE                          45L
#define M_MODEL_LIST                          46L
#define M_CHAR_NUMBER_IN_FONT                 47L
#define M_STRING_VALIDATION                   48L
#define M_STRING_VALIDATION_HANDLER_PTR       M_STRING_VALIDATION
#define M_STRING_VALIDATION_HANDLER_USER_PTR  49L
#define M_READ_SPEED                          50L
#define M_READ_ACCURACY                       51L
#define M_READ_FIRST_LEVEL                    52L
#define M_READ_LAST_LEVEL                     53L
#define M_READ_FAST_FIND                      55L
#define M_READ_ROBUSTNESS                     56L
#define M_STRING_LOC_NB_MODELS                57L
#define M_READ_MODEL_STEP                     58L
#define M_PAT_ON_ACCELERATED                  59L
#define M_BLOB_ON_ACCELERATED                 60L
#define M_PROC_ON_ACCELERATED                 61L

#define M_CONSTRAINT                   0x4000000L
#define M_CONSTRAINT_TYPE              0x8000000L

#define M_PRINT_ENABLE                         1L
#define M_DISPLAY_ENABLE                       2L
#define M_BENCHMARK_ENABLE                     4L

// MocrControl (M_SKIP_STRING_LOCATION possible values)
#define M_STRING_LOCATION_BLOB_ONLY            2L            /* YC: obsolete ? */
#define M_STRING_LOCATION_SEARCH_ONLY          3L            /* YC: obsolete ? */
#define M_STRING_LOCATION_BLOB_THAN_SEARCH     4L            /* YC: obsolete ? */
#define M_STRING_LOCATION_SEARCH_THAN_BLOB     5L            /* YC: obsolete ? */

// MocrAllocFont()
#define M_DEFAULT                     0x10000000L
#define M_SEMI_M12_92                        0x1L
#define M_SEMI_M13_88                        0x2L
#define M_SEMI                               0x3L
#define M_FOREGROUND_WHITE                  0x80L
#define M_FOREGROUND_BLACK                 0x100L

// MocrCalibrateFont()
#define M_DEFAULT                     0x10000000L
#define M_FAST                           0x40000L

// MocrImportFont(), MocrRestoreFont(), MocrSaveFont()
#define M_RESTORE                              0L
#define M_LOAD                                 1L
#define M_LOAD_CONSTRAINT                    0x2L
#define M_LOAD_CONTROL                       0x4L
#define M_LOAD_CHARACTER                     0x8L
#define M_SAVE                             0x100L
#define M_SAVE_CONSTRAINT                  0x200L
#define M_SAVE_CONTROL                     0x400L
#define M_SAVE_CHARACTER                   0x800L
#define M_REPLACE                     0x01000060L
#define M_MIL                                  0L
#define M_RAW                                  1L
#define M_TIFF                                 2L
#define M_GIF                                  3L
#define M_FONT_MIL                    0x00008000L
#define M_FONT_ASCII                  0x00004000L

// MocrGetResult()
#define M_STRING_VALID_FLAG                    1L
#define M_STRING_SCORE                         M_SCORE
#define M_STRING                               3L
#define M_CHAR_VALID_FLAG                      4L
#define M_CHAR_SCORE                           5L
#define M_CHAR_POSITION_X                      6L
#define M_CHAR_POSITION_Y                      7L
#define M_GOOD_LOCATION_QUALITY_FLAG           8L
#define M_CHAR_SIZE_SCORE                      9L
#define M_CHAR_MIN_OFFSET_X                   10L
#define M_CHAR_MAX_OFFSET_X                   11L
#define M_CHAR_MIN_OFFSET_Y                   12L
#define M_CHAR_MAX_OFFSET_Y                   13L

// MocrCopyFont()
#define M_COPY_TO_FONT                         1L
#define M_COPY_FROM_FONT                       2L
#define M_CHARACTER_PAT_MODEL            0x10000L
#define M_ALL_CHAR                        0x8000L
#define M_SKIP_SEMI_STRING_UPDATE         0x4000L

// MocrSetConstraint()
#define M_ADD                             0x0000L
#define M_CLEAR                       0x00000001L
#define M_LETTER                          0x0002L
#define M_DIGIT                           0x0003L
#define M_UPPERCASE                      0x10000L
#define M_LOWERCASE                       0x8000L
#define M_DEFAULT                     0x10000000L

// MocrModifyFont()
#define M_RESIZE                               1L
#define M_INVERT                               2L

// MocrValidateString()
#define M_TRUE                                 1L
#define M_STRING_LENGTH                       40L
#define M_ALL                                  0L
#define M_PRESENT                              2L
#define M_CHECK_VALID                          3L
#define M_CHECK_VALID_FAST                     4L


#endif // __MILOCR_H__
