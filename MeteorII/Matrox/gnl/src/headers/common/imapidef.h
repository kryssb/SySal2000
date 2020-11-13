/*******************************************************************
 *
 * COPYRIGHT (c) 1995-2000 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

#ifndef __IMAPIDEF_H__
#define __IMAPIDEF_H__

#if !defined(_IM_LOCAL_CODE) && defined(SHOW_INCLUDE_FILE)
#pragma message ("#include "__FILE__)
#endif


/* Internal defines identifying External Register Port devices.
 * Use IM_EXTDEV_... #defines in user mode.
 * #define must be in the range of 0 to 0xff
 */
#define _IM_EXT_PORT_DEVICE_ID_NONE                   0L
#define _IM_EXT_PORT_DEVICE_ID_GRAB(g)                (g+1L)    /* g is 0 to 30 */
#define _IM_EXT_PORT_DEVICE_ID_MJPEG                  0x20L
#define _IM_EXT_PORT_DEVICE_ID_OTHERS                 0x40L       /* Corona, Meteor II/Std, ... */
#define _IM_EXT_PORT_DEVICE_ID_RASTER_BLASTER         0x80L
#define _IM_EXT_PORT_DEVICE_ID_GENESIS_PPC            0x90L
#define _IM_EXT_PORT_DEVICE_ID_GPRO_PPC_R0            0xa0L
#define _IM_EXT_PORT_DEVICE_ID_GPRO_PPC               _IM_EXT_PORT_DEVICE_ID_GPRO_PPC_R0
#define _IM_EXT_PORT_DEVICE_ID_GPRO_PPC_R1            0xa1L
#define _IM_EXT_PORT_DEVICE_ID_GENESIS_PMC            0xb0L
#define _IM_EXT_PORT_DEVICE_ID_GENESIS_PMC_GRAB       (_IM_EXT_PORT_DEVICE_ID_GENESIS_PMC+1L)

#define _IM_EXT_PORT_DEVICE_ID_GENESIS_GRAB           _IM_EXT_PORT_DEVICE_ID_GRAB(0L)        /* 1    is Genesis & Genesis LC grab module */
#define _IM_EXT_PORT_DEVICE_ID_METEOR_II_DIG          _IM_EXT_PORT_DEVICE_ID_GRAB(1L)        /* 2    is Meteor II/Dig */
#define _IM_EXT_PORT_DEVICE_ID_METEOR_II_DIG_MJPEG    _IM_EXT_PORT_DEVICE_ID_GRAB(0x20L+1L)  /* 32+2 is Meteor II/Dig with MJPEG */
#define _IM_EXT_PORT_DEVICE_ID_DAC_R0                 _IM_EXT_PORT_DEVICE_ID_GRAB(2L)        /* 3    is 2 channels MACABre Revision 0 (fpgas) */
#define _IM_EXT_PORT_DEVICE_ID_DAC_R1                 _IM_EXT_PORT_DEVICE_ID_GRAB(3L)        /* 4    is 2 channels MACABre Revision 1 (fpgas) */
#define _IM_EXT_PORT_DEVICE_ID_DAC_R2                 _IM_EXT_PORT_DEVICE_ID_GRAB(4L)        /* 5    is 2 channels MACABre Revision 2 (fpgas) */
#define _IM_EXT_PORT_DEVICE_ID_MACH_IV                _IM_EXT_PORT_DEVICE_ID_GRAB(5L)        /* 6    is 4 channels MACABre */
#define _IM_EXT_PORT_DEVICE_ID_METEOR_II_CL           _IM_EXT_PORT_DEVICE_ID_GRAB(6L)        /* 7    is Meteor II/Camera Link */

/*******************************************************************
 *
 * Genesis Native Library #defines.
 *
 *******************************************************************/

/* Initialization */
#define IM_RESET           0L
#define IM_PARTIAL_RESET   1L
#define IM_DOWNLOAD        2L
#define IM_FULL_RESET      IM_RESET

/* Data formats */
#define IM_UNSIGNED     0x00000000L
#define IM_SIGNED       0x10000000L
#define IM_IEEE754      0x20000000L
#define IM_PACKED       0x40000000L
#define IM_ALIGN_64K    0x80000000L       /* Internal use only */

/* Buffer types */
#define IM_BINARY    (1L  | IM_PACKED)
#define IM_RGB       (24L | IM_PACKED)
#define IM_UBYTE     (8L  | IM_UNSIGNED)
#define IM_USHORT    (16L | IM_UNSIGNED)
#define IM_ULONG     (32L | IM_UNSIGNED)
#define IM_BYTE      (8L  | IM_SIGNED)
#define IM_SHORT     (16L | IM_SIGNED)
#define IM_LONG      (32L | IM_SIGNED)
#define IM_FLOAT     (32L | IM_IEEE754)
#define IM_DOUBLE    (64L | IM_IEEE754)

/* Conditional operators */
#define IM_IN_RANGE         1L
#define IM_OUT_RANGE        2L
#define IM_EQUAL            3L
#define IM_NOT_EQUAL        4L
#define IM_GREATER          5L
#define IM_LESS             6L
#define IM_GREATER_OR_EQUAL 7L
#define IM_LESS_OR_EQUAL    8L

/* Morphological operators */
#define IM_ERODE            1L
#define IM_DILATE           2L
#define IM_THIN             3L
#define IM_THICK            4L
#define IM_HIT_OR_MISS      5L
#define IM_MATCH            6L
#define IM_CLOSE           10L
#define IM_OPEN            11L

/* Arithmetic operators */
#define IM_ADD         0x0000L
#define IM_SUB         0x0001L
#define IM_SUB_NEG     0x000AL
#define IM_SUB_ABS     0x0011L
#define IM_MIN         0x0012L
#define IM_MAX         0x0013L
#define IM_OR          0x0016L
#define IM_AND         0x0017L
#define IM_XOR         0x0018L
#define IM_NOR         0x0019L
#define IM_NAND        0x001AL
#define IM_XNOR        0x001BL
#define IM_NOT         0x0014L
#define IM_NEG         0x0023L
#define IM_ABS         0x000CL
#define IM_PASS        0x0002L
#define IM_MULT        0x0100L
#define IM_DIV         0x0101L
#define IM_DIV_INTO    0x0102L

/* Additional arithmetic operators */
#define IM_LOG         0x0000L
#define IM_EXP         0x0001L
#define IM_SIN         0x0002L
#define IM_COS         0x0003L
#define IM_TAN         0x0004L
#define IM_QUAD        0x0005L

/* Yet more arithmetic operators */
#define IM_SUB_CLIP    0x0081L
#define IM_SHIFT       0x0200L
#define IM_ADD_SAT     0x0201L
#define IM_SUB_SAT     0x0202L
#define IM_MULT_SAT    0x0203L
#define IM_SQUARE      0x0300L
#define IM_SQRT        0x0301L
#define IM_ATAN        0x0302L
#define IM_CUBE        0x0303L
#define IM_CBRT        0x0304L
#define IM_SQUARE_ADD  0x0305L
#define IM_MULT_MSB    0x0306L
#define IM_DIV_FRAC    0x0307L
#define IM_ATAN2       0x0308L
#define IM_MAGNITUDE   0x0309L

/* imGen1d() */
#define IM_POLYNOMIAL  0x0400L

/* Buffer inquiries */
#define IM_BUF_SIZE_X          3L
#define IM_BUF_SIZE_Y          4L
#define IM_BUF_NUM_BANDS       6L
#define IM_BUF_TYPE            8L
#define IM_BUF_SIZE_BIT       10L
#define IM_BUF_FORMAT         11L
#define IM_BUF_PARENT_ID      30L
#define IM_BUF_OFFSET_X       32L
#define IM_BUF_OFFSET_Y       33L
#define IM_BUF_OFFSET_BAND    37L
#define IM_BUF_NUM_FIELDS     38L
#define IM_BUF_OWNER_ID      124L

/* Additional buffer inquiries */
#define IM_BUF_LOCATION             200L
#define IM_BUF_PHYSICAL_ADDRESS     201L
#define IM_BUF_PITCH                202L
#define IM_BUF_PITCH_GRANULARITY    203L
#define IM_BUF_BUF_POINTER          400L
#define IM_BUF_BUF_JPEG_POINTER     401L

/* System inquiries */
#define IM_SYS_NUM_NODES         1L
#define IM_SYS_NUM_DIGITIZERS    2L
#define IM_SYS_NUM_DISPLAYS      3L
#define IM_SYS_NUM_SYSTEMS       4L
#define IM_SYS_PRODUCT_LIST      5L
#define IM_SYS_PRODUCT_LIST_FREE 6L

/* Device inquiries & Controls */
#define IM_DEV_CPU                     1L
#define IM_DEV_MVP                     IM_DEV_CPU           /* For compatibility */
#define IM_DEV_CPU_SPEED               2L
#define IM_DEV_MVP_SPEED               IM_DEV_CPU_SPEED     /* For compatibility */
#define IM_DEV_VIA_PRIMARY             3L
#define IM_DEV_VIA_DISPLAY             4L
#define IM_DEV_ACCELERATOR             5L
#define IM_DEV_MEM_PROC                6L
#define IM_DEV_MEM_DISP                7L
#define IM_DEV_MEM_OVERLAY             8L
#define IM_DEV_OWNER_SYSTEM            9L
#define IM_DEV_OWNER_NODE              10L
#define IM_DEV_MSG_TOTAL               11L
#define IM_DEV_MSG_FREE                12L
#define IM_DEV_FREE_MEM_PROC           13L
#define IM_DEV_FREE_MEM_DISP           14L
#define IM_DEV_PRODUCT_ID              15L
#define IM_DEV_CUSTOMER_PRODUCT_ID     16L
#define IM_DEV_PRODUCT_SERIAL_NUMBER   17L
#define _IM_DEV_ACCESS_NOA_REGISTER    18L    /* Don't document this one */
#define _IM_DEV_ACCESS_MAC_REGISTER    19L    /* Don't document this one */
#define IM_DEV_MEM_HOST                20L
#define IM_DEV_FREE_MEM_HOST           21L
#define IM_DEV_CPU_TYPE                22L
#define IM_DEV_FREE_MEM_PROC_EXTENDED  23L
#define IM_DEV_PITCH_GRANULARITY       24L
#define IM_DEV_HEAP_SIZE               25L
#define IM_DEV_FREE_MEM_PROC_FAST      26L
#define IM_DEV_CPU_TEMP                27L   /* PPC only */
#define IM_DEV_CPU_LIMIT_TEMP          28L   /* PPC only */
#define IM_DEV_CPU_START_RECORD_TEMP   29L   /* PPC only */
#define IM_DEV_CPU_STOP_RECORD_TEMP    30L   /* PPC only */

#define IM_DEV_PPC                     (IM_DEV_MVP + 1L)

/* Device inquiries product id */
#define IM_DEV_GENESIS              1L
#define IM_DEV_GENESIS_PRO          2L
#define IM_DEV_GENESIS_LC           3L
#define IM_DEV_GENESIS_MEMORY       4L
#define IM_DEV_METEOR_II_DIG        5L
#define IM_DEV_DAC                  6L
#define IM_DEV_MACH_IV              7L
#define IM_DEV_GENESIS_PPC          8L
#define IM_DEV_GENESIS_PLUS         9L
#define IM_DEV_GENESIS_PRO_PPC      IM_DEV_GENESIS_PLUS
#define IM_DEV_GENESIS_PMC         10L
#define IM_DEV_METEOR_II_CL        11L
#define IM_DEV_GENESIS_UNDEF       99L

/* Externel Device inquiries board id */
#define IM_EXTDEV_NONE                 _IM_EXT_PORT_DEVICE_ID_NONE
#define IM_EXTDEV_GENESIS_GRAB         _IM_EXT_PORT_DEVICE_ID_GENESIS_GRAB
#define IM_EXTDEV_METEOR_II_DIG        _IM_EXT_PORT_DEVICE_ID_METEOR_II_DIG
#define IM_EXTDEV_METEOR_II_DIG_MJPEG  _IM_EXT_PORT_DEVICE_ID_METEOR_II_DIG_MJPEG
#define IM_EXTDEV_METEOR_II_CL         _IM_EXT_PORT_DEVICE_ID_METEOR_II_CL
#define IM_EXTDEV_DAC_R0               _IM_EXT_PORT_DEVICE_ID_DAC_R0
#define IM_EXTDEV_DAC_R1               _IM_EXT_PORT_DEVICE_ID_DAC_R1
#define IM_EXTDEV_DAC_R2               _IM_EXT_PORT_DEVICE_ID_DAC_R2
#define IM_EXTDEV_MACH_IV              _IM_EXT_PORT_DEVICE_ID_MACH_IV
#define IM_EXTDEV_RASTER_BLASTER       _IM_EXT_PORT_DEVICE_ID_RASTER_BLASTER
#define IM_EXTDEV_GENESIS_PMC_GRAB     _IM_EXT_PORT_DEVICE_ID_GENESIS_PMC_GRAB
#define IM_EXTDEV_MSB_R0               _IM_EXT_PORT_DEVICE_ID_GPRO_PPC_R0
#define IM_EXTDEV_MSB_R1               _IM_EXT_PORT_DEVICE_ID_GPRO_PPC_R1
#define IM_EXTDEV_MSB                  IM_EXTDEV_MSB_R0


/* Application inquires */
#define IM_APP_TIMEOUT        1

/* Miscellaneous defines */
#define IM_DEFAULT      0x10000000L
#define IM_NONE         0x20000000L
#define IM_DONT_CARE_32 0x00ffffffL
#define IM_NO_CHANGE         -9999L
#define IM_ALL                   0L
#define IM_ENABLE            -9997L
#define IM_FORCE             -9998L
#define IM_DISABLE           -9999L
#define IM_UNKNOWN           -9999L
#define IM_CONTINUOUS           -1L
#define IM_FORWARD               1L
#define IM_REVERSE               2L
#define IM_VERY_LOW              0L
#define IM_LOW                   1L
#define IM_MEDIUM                2L
#define IM_HIGH                  3L
#define IM_CLEAR                 1L
#define IM_NO_CLEAR              2L
#define IM_IDEMPOTENCE          -1L
#define IM_FAST            0x40000L
#define IM_VERY_FAST       0x80000L
#define IM_BEST           0x100000L
#define IM_MULTIPLE       0x400000L
#define IM_ABSOLUTE              1L
#define IM_OFFSET                2L
#define IM_CLEAR_BACKGROUND 0x2000L
#define IM_SYNCHRONOUS           1L
#define IM_ASYNCHRONOUS          2L
#define IM_FILL                 -1L
#define IM_VIA_ONLY              0L
#define IM_ADDRESS_ONLY          1L
#define IM_SAVE                  2L
#define IM_FASTEST               3L
#define IM_SAME_KERNEL           4L
#define IM_CACHE_BUF_SIZE   0x1000L
#define IM_PARENT       0x40000000L

/* More miscellaneous stuff */
#define IM_NOW                         1L
#define IM_FRAME                       2L
#define IM_FIELD                       3L
#define IM_LINE                        4L
#define IM_PATCH                       5L
#define IM_PACK_0                      1L
#define IM_UNPACK_0                    2L
#define IM_PACK_1                     17L
#define IM_UNPACK_1                   18L
#define IM_DONT_CARE              0x8000L
#define IM_EXACT                 0x20000L
#define IM_URGENT                      5L
#define IM_SYNCHRONIZED                1L
#define IM_CLIP_SQUARE                10L
#define IM_FIRST_FIELD                -1L
#define IM_FIRST                       0L
#define IM_SECOND                      1L
#define IM_BOTH                        2L
#define IM_MODE_2              0x8000000L
#define IM_THRESH_CONSTANT         0x100L
#define IM_THRESH_PIXEL            0x200L
#define IM_PASS_CONSTANT           0x400L
#define IM_PASS_PIXEL              0x800L
#define IM_PIXEL                       1L
#define IM_LINE_INTERLACED    0x10000000L
#define IM_LINE_PSEUDO        0x20000000L
#define IM_REGEDIT_MACALLOC           99L    /* Internal use only */

/* VIA-related values not defined elsewhere */
#define IM_24_TO_32        1L
#define IM_32_TO_24        2L
#define IM_VIA_PRIMARY     1L
#define IM_VIA_DISPLAY     2L
#define IM_VIA_SOURCE      3L
#define IM_VIA_DESTINATION 4L
#define IM_RGB555          1L
#define IM_RGB565          2L
#define IM_PROGRESSIVE     0L
#define IM_INTERLACED      1L
#define IM_ODD             0L
#define IM_EVEN            1L
#define IM_NEXT            2L

/* Display control */
#define IM_KEY_OFF         2L
#define IM_KEY_ALWAYS      3L
#define IM_KEY_IN_RANGE    4L
#define IM_KEY_OUT_RANGE   5L

/* VGA Mode */
#define IM_SINGLE_SCREEN   0L
#define IM_DUAL_SCREEN     1L
#define IM_DUAL_HEAD       2L

/* File formats */
#define IM_MIL             0L
#define IM_RAW             1L
#define IM_TIFF            2L
#define IM_GIF             3L

/* Additional file formats */
#define IM_NATIVE         10L

/* Conversions */
#define IM_TRUNCATE        1L
#define IM_ROUND           2L
#define IM_ZERO_EXTEND     4L
#define IM_SIGN_EXTEND     5L
#define IM_CLIP         0x80L
#define IM_ABS_CLIP    (IM_ABS | IM_CLIP)

/* imIntFindExtreme() */
#define IM_MAX_PIXEL       1L
#define IM_MIN_PIXEL       2L

/* imIntFlip() */
#define IM_FLIP_H       0x0001L
#define IM_FLIP_V       0x0002L
#define IM_ROTATE_90    0x0010L
#define IM_ROTATE_180   0x0020L
#define IM_ROTATE_270   0x0030L

/* imIntHistogramEqualize() */
#define IM_UNIFORM           1L
#define IM_EXPONENTIAL       2L
#define IM_RAYLEIGH          3L
#define IM_HYPER_CUBE_ROOT   4L
#define IM_HYPER_LOG         5L
#define IM_IMAGE_TO_LUT      1L
#define IM_HIST_TO_LUT       3L

/* imIntRank() */
#define IM_MEDIAN      0x10000L

/* Geometric transforms */
#define IM_ROTATE            1L
#define IM_SCALE             2L
#define IM_TRANSLATE         4L
#define IM_SHEAR_X           5L
#define IM_SHEAR_Y           6L

/* Interpolation types */
#define IM_NO_INTERPOLATE   0x00000002L
#define IM_INTERPOLATE      0x00000004L
#define IM_BILINEAR         0x00000008L
#define IM_BICUBIC          0x00000010L
#define IM_AVERAGE          0x00000020L
#define IM_NEAREST_NEIGHBOR 0x00000040L

/* Overscan or graphic modes */
#define IM_OPAQUE           0x01000058L
#define IM_TRANSPARENT      0x01000059L
#define IM_REPLACE          0x01000060L
#define IM_MIRROR           0x01000061L
#define IM_REPLACE_MAX      0x01000063L
#define IM_REPLACE_MIN      0x01000064L

/* Synchronization */
#define IM_WAITING                   10L
#define IM_EXECUTING                 20L
#define IM_CANCELING                 25L
#define IM_READY                     30L
#define IM_STARTED                   40L
#define IM_COMPLETED                 50L
#define IM_INQUIRE            0x0800000L
#define IM_LINE_INT           0x1000000L
#define IM_FRAME_NUMBER       0x2000000L
#define IM_INFINITE          -1L
#define IM_NON_SIGNALLED      IM_WAITING
#define IM_SIGNALLED          IM_COMPLETED
#define IM_AUTO_RESET         1L
#define IM_MANUAL_RESET       2L

/* Buffer location */
#define IM_PROC               1L
#define IM_DISP               2L
#define IM_HOST               3L
#define IM_PAGED              4L
#define IM_NON_PAGED          5L
#define IM_CURRENT            6L
#define IM_HOST_PAGED         7L
#define IM_NON_PAGED_VIRTUAL  8L
#define IM_PROC_EXTENDED      9L
#define IM_PROC_FAST          10L

/* Buffer control */
#define IM_BUF_LOCK        1L
#define IM_BUF_UNLOCK      2L
#define IM_BUF_FLUSH       3L

/* PP ALU opcodes for imBinTriadic() and imIntTriadic() */
#define IM_PP_ZERO      0x00000000L
#define IM_PP_ONE       0x07f80000L
#define IM_PP_PASS_A    0x05500000L
#define IM_PP_PASS      IM_PP_PASS_A
#define IM_PP_NOT       0x02a80000L
#define IM_PP_AND       0x04400000L
#define IM_PP_OR        0x07700000L
#define IM_PP_XOR       0x03300000L
#define IM_PP_NAND      0x03b80000L
#define IM_PP_NOR       0x00880000L
#define IM_PP_XNOR      0x04c80000L
#define IM_PP_MERGE     0x05600000L
#define IM_PP_XOR_XOR   0x04b00000L

/* PP ALU opcodes for imIntTriadic() */
#define IM_PP_PASS_B    0x06600000L
#define IM_PP_PASS_C    0x07800000L
#define IM_PP_SRA_ADD   0x0b510000L
#define IM_PP_SRA_SUB   0x0cad0000L
#define IM_PP_ADD_AND   0x0b500000L
#define IM_PP_SUB_AND   0x0cac0000L
#define IM_PP_ADD_OR    0x0ab00000L
#define IM_PP_SUB_OR    0x0d4c0000L
#define IM_PP_ADD_ABS   0x0cb30000L
#define IM_PP_SUB_ABS   0x0b4f0000L
#define IM_PP_EXT_FIELD 0x06000000L
#define IM_PP_INS_FIELD 0x05600000L
#define IM_PP_ADD_FIELD 0x0b000000L

/* Pseudo-opcodes for imIntTriadic() */
#define IM_PP_ADD_ADD   0xf0000f00L
#define IM_PP_ADD_SUB   0xf0000f01L
#define IM_PP_SUB_SUB   0xf0000f02L

/* Colour conversion */
#define IM_RGB_TO_HSL      1L
#define IM_RGB_TO_L        2L
#define IM_HSL_TO_RGB      3L
#define IM_L_TO_RGB        4L
#define IM_RGB_TO_I        5L
#define IM_RGB_TO_H        6L
#define IM_MATRIX      0x100L

/* Distance transforms */
#define IM_CHAMFER_3_4     1L
#define IM_CITY_BLOCK      2L
#define IM_CHESSBOARD      3L

/* Lattice values */
#define IM_4_CONNECTED     0x10L
#define IM_8_CONNECTED     0x20L

/* imIntTriadic() */
#define IM_CONSTANT_A      0x100L
#define IM_CONSTANT_B      0x200L
#define IM_CONSTANT_C      0x400L
#define IM_CONSTANT_AC     (IM_CONSTANT_A | IM_CONSTANT_C)

/* Graphics control */
#define IM_PLOT_POLY       1L
#define IM_PLOT_LINES      2L
#define IM_PLOT_DOTS       3L
#define IM_FONT_DEFAULT    1L
#define IM_FONT_SMALL      2L
#define IM_FONT_MEDIUM     3L
#define IM_FONT_LARGE      4L

/* JPEG module */
#define IM_BASELINE        0L
#define IM_LOSSLESS        3L
#define IM_HUFFMAN         0L
#define IM_ARITHMETIC      8L

/*************************************/
/* Pattern matching module           */
/*************************************/
#define IM_TEMPLATE   0x0001L
#define IM_NORMALIZED 0x0002L
#define IM_ROTATION   0x0004L

#define IM_PAT_FOUND_FLAG   1L
#define IM_PAT_SCORE        2L
#define IM_PAT_POSITION_X   3L
#define IM_PAT_POSITION_Y   4L
#define IM_PAT_ANGLE        5L
#define IM_PAT_SCALE        6L
#define IM_PAT_ORIENTATION  7L

#define IM_PAT_TYPE               1L
#define IM_PAT_SIZE_X             2L
#define IM_PAT_SIZE_Y             3L
#define IM_PAT_CENTRE_X           4L
#define IM_PAT_CENTRE_Y           5L
#define IM_PAT_NOMINAL_X          6L
#define IM_PAT_NOMINAL_Y          7L
#define IM_PAT_SPEED              8L
#define IM_PAT_POSITION_START_X   9L
#define IM_PAT_POSITION_START_Y  10L
#define IM_PAT_POSITION_SIZE_X   11L
#define IM_PAT_POSITION_SIZE_Y   12L
#define IM_PAT_POSITION_ACCURACY 13L
#define IM_PAT_PREPROCESSED      14L
#define IM_PAT_OFFSET_X          15L
#define IM_PAT_OFFSET_Y          16L
#define IM_PAT_ACCEPTANCE        17L
#define IM_PAT_NUMBER            18L
#define IM_PAT_WORKBUF_SIZE_X    19L
#define IM_PAT_WORKBUF_SIZE_Y    20L
#define IM_PAT_WORKBUF_FAST      21L
#define IM_PAT_WORKBUF_ROTATION  22L
#define IM_PAT_WORKBUF           23L
#define IM_PAT_RESULT_SIZE       24L
#define IM_PAT_CERTAINTY         25L

#define IM_PAT_FIRST_LEVEL       31L
#define IM_PAT_LAST_LEVEL        32L
#define IM_PAT_MODEL_STEP        33L
#define IM_PAT_FAST_FIND         34L
#define IM_PAT_MIN_SPACING_X     35L
#define IM_PAT_MIN_SPACING_Y     36L
#define IM_PAT_SCORE_TYPE        37L
#define IM_PAT_FILE_TYPE         38L

#define IM_PAT_MODEL_POINTER     39L
#define IM_PAT_RESULT_POINTER    40L
#define IM_PAT_REJECTION         41L
#define IM_PAT_BEST_REJECT_SCORE 42L
#define IM_PAT_BEST_REJECT_LEVEL 43L

#define IM_PAT_CENTER_X     IM_PAT_CENTRE_X
#define IM_PAT_CENTER_Y     IM_PAT_CENTRE_Y
#define IM_PAT_ORIGINAL_X   IM_PAT_NOMINAL_X
#define IM_PAT_ORIGINAL_Y   IM_PAT_NOMINAL_Y

/**********************************/
/* Blob Analysis module           */
/**********************************/
/* Binary features */
#define IM_BLOB_LABEL_VALUE              1L
#define IM_BLOB_AREA                     2L
#define IM_BLOB_PERIMETER                3L
#define IM_BLOB_FERET_X                  4L
#define IM_BLOB_FERET_Y                  5L
#define IM_BLOB_BOX_X_MIN                6L
#define IM_BLOB_BOX_Y_MIN                7L
#define IM_BLOB_BOX_X_MAX                8L
#define IM_BLOB_BOX_Y_MAX                9L
#define IM_BLOB_FIRST_POINT_X           10L
#define IM_BLOB_FIRST_POINT_Y           11L
#define IM_BLOB_AXIS_PRINCIPAL_LENGTH   12L
#define IM_BLOB_AXIS_SECONDARY_LENGTH   13L
#define IM_BLOB_FERET_MIN_DIAMETER      14L
#define IM_BLOB_FERET_MIN_ANGLE         15L
#define IM_BLOB_FERET_MAX_DIAMETER      16L
#define IM_BLOB_FERET_MAX_ANGLE         17L
#define IM_BLOB_FERET_MEAN_DIAMETER     18L
#define IM_BLOB_CONVEX_AREA             19L
#define IM_BLOB_CONVEX_PERIMETER        20L
#define IM_BLOB_X_MIN_AT_Y_MIN          21L
#define IM_BLOB_X_MAX_AT_Y_MAX          22L
#define IM_BLOB_Y_MIN_AT_X_MAX          23L
#define IM_BLOB_Y_MAX_AT_X_MIN          24L
#define IM_BLOB_COMPACTNESS             25L
#define IM_BLOB_NUMBER_OF_HOLES         26L
#define IM_BLOB_FERET_ELONGATION        27L
#define IM_BLOB_ROUGHNESS               28L
#define IM_BLOB_EULER_NUMBER            47L
#define IM_BLOB_LENGTH                  48L
#define IM_BLOB_BREADTH                 49L
#define IM_BLOB_ELONGATION              50L
#define IM_BLOB_INTERCEPT_0             51L
#define IM_BLOB_INTERCEPT_45            52L
#define IM_BLOB_INTERCEPT_90            53L
#define IM_BLOB_INTERCEPT_135           54L
#define IM_BLOB_NUMBER_OF_RUNS          55L
#define IM_BLOB_ASPECT_RATIO           IM_BLOB_FERET_ELONGATION
#define IM_BLOB_GENERAL_FERET        0x400L

/* Greyscale features */
#define IM_BLOB_SUM_PIXEL               29L
#define IM_BLOB_MIN_PIXEL               30L
#define IM_BLOB_MAX_PIXEL               31L
#define IM_BLOB_MEAN_PIXEL              32L
#define IM_BLOB_SIGMA_PIXEL             33L
#define IM_BLOB_SUM_PIXEL_SQUARED       46L

/* Binary or greyscale features */
#define IM_BLOB_CENTER_OF_GRAVITY_X     34L
#define IM_BLOB_CENTER_OF_GRAVITY_Y     35L
#define IM_BLOB_MOMENT_X0_Y1            36L
#define IM_BLOB_MOMENT_X1_Y0            37L
#define IM_BLOB_MOMENT_X1_Y1            38L
#define IM_BLOB_MOMENT_X0_Y2            39L
#define IM_BLOB_MOMENT_X2_Y0            40L
#define IM_BLOB_MOMENT_CENTRAL_X1_Y1    41L
#define IM_BLOB_MOMENT_CENTRAL_X0_Y2    42L
#define IM_BLOB_MOMENT_CENTRAL_X2_Y0    43L
#define IM_BLOB_AXIS_PRINCIPAL_ANGLE    44L
#define IM_BLOB_AXIS_SECONDARY_ANGLE    45L
#define IM_BLOB_GENERAL_MOMENT       0x800L

/* Short cuts for enabling multiple features */
#define IM_BLOB_ALL_FEATURES         0x100L
#define IM_BLOB_BOX                  0x101L
#define IM_BLOB_CONTACT_POINTS       0x102L
#define IM_BLOB_CENTER_OF_GRAVITY    0x103L
#define IM_BLOB_NO_FEATURES          0x104L

/* Groups of results that can be read back together */
#define IM_BLOB_GROUP1               0x201L
#define IM_BLOB_GROUP2               0x202L
#define IM_BLOB_GROUP3               0x203L
#define IM_BLOB_GROUP4               0x204L
#define IM_BLOB_GROUP5               0x205L
#define IM_BLOB_GROUP6               0x206L
#define IM_BLOB_GROUP7               0x207L
#define IM_BLOB_GROUP8               0x208L
#define IM_BLOB_GROUP9               0x209L

/* imBlobControl() and/or imBlobInquire() */
#define IM_BLOB_IMAGE_TYPE               1L
#define IM_BLOB_IDENTIFICATION           2L
#define IM_BLOB_LATTICE                  3L
#define IM_BLOB_FOREGROUND_VALUE         4L
#define IM_BLOB_PIXEL_ASPECT_RATIO       5L
#define IM_BLOB_NUMBER_OF_FERETS         6L
#define IM_BLOB_RESET                    9L
#define IM_BLOB_SAVE_RUNS               14L
#define IM_BLOB_MAX_LABEL               16L
#define IM_BLOB_MAX_TIME                17L
#define IM_BLOB_TIMEOUT                 18L
#define IM_BLOB_TIME_SLICE              19L

/* General moment type */
#define IM_ORDINARY             0x400L
#define IM_CENTRAL              0x800L

/* Blob identification */
#define IM_WHOLE_IMAGE              1L
#define IM_INDIVIDUAL               2L
#define IM_LABELLED                 4L

/* Foreground values */
#define IM_NONZERO               0x80L
#define IM_ZERO                 0x100L
#define IM_NON_ZERO        IM_NONZERO

/* Image type values (and modifiers for certain features) */
#define IM_GREYSCALE           0x0200L
#define IM_GRAYSCALE     IM_GREYSCALE

/* Data types for results */
#define IM_TYPE_CHAR          0x10000L
#define IM_TYPE_SHORT         0x20000L
#define IM_TYPE_LONG          0x40000L
#define IM_TYPE_FLOAT         0x80000L
#define IM_TYPE_DOUBLE       0x100000L

/* Miscellaneous */
#define IM_ALWAYS                   0L
#define IM_ALL_BLOBS            0x105L
#define IM_INCLUDED_BLOBS       0x106L
#define IM_EXCLUDED_BLOBS       0x107L
#define IM_INCLUDE                  1L
#define IM_EXCLUDE                  2L
#define IM_DELETE                   3L
#define IM_COMPRESS                 8L
#define IM_MIN_FERETS               2L
#define IM_MAX_FERETS              64L
#define IM_INCLUDE_ONLY         0x101L
#define IM_EXCLUDE_ONLY         0x102L
/*********************************/
/* End of Blob Analysis #defines */
/*********************************/

/* Error handling */
#define IM_ERR_RESET          0x1L
#define IM_ERR_CODE           0x2L
#define IM_ERR_MSG            0x4L
#define IM_ERR_FUNC           0x8L
#define IM_ERR_MSG_FUNC       0xcL
#define IM_ERR_MSG_SIZE       (80L)                    /* Multiple of 8 for endian portability */
#define IM_ERR_FUNC_SIZE      (32L)                    /* Multiple of 8 for endian portability */
#define IM_ERR_SIZE           (2L * IM_ERR_MSG_SIZE)   /* to hold both message and function plus some extra */

/* Error codes */
#define IM_SUCCESS             0L
#define IM_ERR_BUFFER         -1L
#define IM_ERR_DEVICE         -2L
#define IM_ERR_FILE           -3L
#define IM_ERR_MEMORY         -4L
#define IM_ERR_NOT_PRESENT    -5L
#define IM_ERR_OPCODE         -6L
#define IM_ERR_OSB            -7L
#define IM_ERR_PARAMETER      -8L
#define IM_ERR_RESTRICTION    -9L
#define IM_ERR_THREAD        -10L
#define IM_ERR_TIMEOUT       -11L
#define IM_ERR_SYSTEM        -12L
#define IM_ERR_HALTED        -13L
#define IM_ERR_BUF_ATTRIBUTE -14L
#define IM_ERR_MISC          -15L
#define IM_ERR_BUF_PARAM      IM_ERR_BUF_ATTRIBUTE

/*******************************************************************
 * Pre-defined pseudo-buffers.
 * These can be passed in place of a buffer only where documented.
 *******************************************************************/

/* Flag bit to identify pre-defined buffers */
#define IM_BUF_PREDEFINED           0x40000000L
#define IM_BUF_PREDEFINED_SPECIAL   0x20000000L


/* Miscellaneous */
#define IM_VM_CHANNEL               (IM_BUF_PREDEFINED | 0x00L)
#define IM_PCI_TRANSFER_WINDOW      (IM_BUF_PREDEFINED | 0x01L)
#define IM_DISP_TEXT                (IM_BUF_PREDEFINED | 0x02L)
#define IM_METRO_TRK_LINK           (IM_BUF_PREDEFINED | 0x0fL)

/* the internal predefined buffers go here */
#define _IM_DEFAULT_THREAD          (IM_BUF_PREDEFINED | 0x10L)

/* imBufChild() */
#define IM_DISP_MONO                (IM_BUF_PREDEFINED | 0x20L)
#define IM_DISP_COLOR               (IM_BUF_PREDEFINED | 0x30L)
#define IM_DISP_RED                 (IM_BUF_PREDEFINED | 0x40L)
#define IM_DISP_GREEN               (IM_BUF_PREDEFINED | 0x50L)
#define IM_DISP_BLUE                (IM_BUF_PREDEFINED | 0x60L)
#define IM_DISP_OVERLAY             (IM_BUF_PREDEFINED | 0x70L)

/* imIntConvolve() */
#define IM_SMOOTH                   (IM_BUF_PREDEFINED | 0x80L)
#define IM_LAPLACIAN_EDGE           (IM_BUF_PREDEFINED | 0x81L)
#define IM_LAPLACIAN_EDGE2          (IM_BUF_PREDEFINED | 0x82L)
#define IM_SHARPEN                  (IM_BUF_PREDEFINED | 0x83L)
#define IM_SHARPEN2                 (IM_BUF_PREDEFINED | 0x84L)
#define IM_HORIZ_EDGE               (IM_BUF_PREDEFINED | 0x85L)
#define IM_VERT_EDGE                (IM_BUF_PREDEFINED | 0x86L)
#define IM_SOBEL_EDGE               (IM_BUF_PREDEFINED | 0x87L)
#define IM_PREWITT_EDGE             (IM_BUF_PREDEFINED | 0x88L)
#define IM_ROBERTS_EDGE             (IM_BUF_PREDEFINED | 0x89L)

/* imIntRank() or morphology */
#define IM_3X3_RECT_0               (IM_BUF_PREDEFINED | 0x8aL)
#define IM_3X3_CROSS_0              (IM_BUF_PREDEFINED | 0x8bL)

/* Morphology */
#define IM_3X3_RECT_1               (IM_BUF_PREDEFINED | 0x8cL)
#define IM_3X3_CROSS_1              (IM_BUF_PREDEFINED | 0x8dL)

/* imIntRank() */
#define IM_3X1                      (IM_BUF_PREDEFINED | 0x8eL)
#define IM_5X1                      (IM_BUF_PREDEFINED | 0x8fL)
#define IM_7X1                      (IM_BUF_PREDEFINED | 0x90L)
#define IM_9X1                      (IM_BUF_PREDEFINED | 0x91L)
#define IM_1X3                      (IM_BUF_PREDEFINED | 0x92L)
#define IM_1X5                      (IM_BUF_PREDEFINED | 0x93L)
#define IM_1X7                      (IM_BUF_PREDEFINED | 0x94L)
#define IM_1X9                      (IM_BUF_PREDEFINED | 0x95L)

/* Morphology */
#define IM_5X5_RECT_1               (IM_BUF_PREDEFINED | 0x96L)
#define IM_7X7_RECT_1               (IM_BUF_PREDEFINED | 0x97L)

/* imIntRank() */
#define IM_3X3_X                    (IM_BUF_PREDEFINED | 0x98L)   /* 0x98 */

/* imIntConvolve() */
#define IM_SMOOTH_FAST              (IM_BUF_PREDEFINED | 0x99L)

#define _IM_PROC_TAG                (IM_BUF_PREDEFINED | 0xa0L)   /* Internal TAG buffers */
#define _IM_DISP_TAG                (IM_BUF_PREDEFINED | 0xb0L)

#define _IM_DEFAULT_GRAB_THREAD     (IM_BUF_PREDEFINED | 0xc0L)
#define _IM_DEFAULT_COPY_THREAD     (IM_BUF_PREDEFINED | 0xd0L)

#define __PUT_NEXT_ONE_HERE__       (IM_BUF_PREDEFINED | 0xe0L)   /* I mean on the next lines update _IM_BUF_LAST_PREDEF accordingly */

/* ---------------- */
#define _IM_BUF_LAST_PREDEF         (IM_BUF_PREDEFINED | 0xe1L)   /* This one must always stay the last one */

#define _IM_BUF_NUM_PREDEF          (_IM_BUF_LAST_PREDEF & ~IM_BUF_PREDEFINED)


/*******************************************************************
 * Buffer fields (all tag values must be unique).
 * Tags below 10000 are reserved for user-defined fields.
 *******************************************************************/

/* VIA control options */
#define IM_CTL_BYTE_SWAP       10000L
#define IM_CTL_DIR_X           10001L
#define IM_CTL_DIR_Y           10002L
#define IM_CTL_PACK            10003L
#define IM_CTL_PRIORITY        10004L
#define IM_CTL_SUBSAMP_X       10005L
#define IM_CTL_SUBSAMP_Y       10006L
#define IM_CTL_TAG_BUF         10007L
#define IM_CTL_VIA             10008L
#define IM_CTL_FMTCVR          10009L
#define IM_CTL_WRTMSK          10010L
#define IM_CTL_ZOOM_X          10011L
#define IM_CTL_ZOOM_Y          10012L
#define IM_CTL_BYTE_EXT        10013L
#define IM_CTL_HEADER_EOF      10014L
#define IM_CTL_HEADER_SOF      10015L
#define IM_CTL_COUNT           10016L
#define IM_CTL_SCAN_MODE       10017L
#define IM_CTL_STREAM_ID       10018L
#define IM_CTL_START_X         10019L
#define IM_CTL_START_Y         10020L
#define IM_CTL_STOP_X          10021L
#define IM_CTL_STOP_Y          10022L
#define IM_CTL_START_FIELD     10023L
#define IM_CTL_ADDR_MODE       10024L
#define IM_CTL_COUNT_MODE      10025L
#define IM_CTL_LINE_INT        10026L
#define IM_CTL_GRAB_MODE       10027L
#define IM_CTL_CHANNEL         10028L
#define IM_CTL_BYPASS          10029L
#define IM_CTL_CAPTURE_MODE    10030L
#define IM_CTL_LINE_INT_FIELD  10031L
#define IM_CTL_LINE_INT_STEP   10032L
#define IM_CTL_SETUP           10033L
#define IM_CTL_DISPLAY_SYNC    10034L
#define IM_CTL_SETUP_ADDRESS   10035L
#define IM_CTL_USE_SCATTER     10036L
#define IM_CTL_REPLICATE       10037L
#define IM_CTL_CHANNEL_DELAY   10038L
#define IM_CTL_REGEN_LIST      10039L
#define IM_CTL_XFER_TIMEOUT    10040L

#define _IM_CTL_TEST           10995L      /* Don't document this one */
#define _IM_CTL_TEST2          10996L      /* Don't document this one */
#define _IM_CTL_GBLENGTH       10998L      /* Don't document this one */
#define _IM_CTL_VBLENGTH       10999L      /* Don't document this one */

/* Processing results */
#define IM_RES_MIN_PIXEL       11000L
#define IM_RES_MAX_PIXEL       11001L
#define IM_RES_NUM_EVENTS      11002L
#define IM_RES_NUM_DIFFERENCES 11003L
#define IM_RES_NUM_PIXELS      11004L
#define IM_RES_IDEMPOTENCE     11005L

/* Run length encoding */
#define IM_RLE_SIZE            12000L
#define IM_RLE_START           12001L
#define IM_RLE_MODE            12002L
#define IM_RLE_COLOR           12003L
#define IM_RLE_BACK_COLOR      12004L

/* Display control and inquiry */
#define IM_DISP_BUF            13000L
#define IM_DISP_KEY_MODE       13001L
#define IM_DISP_KEY_LOW        13002L
#define IM_DISP_KEY_HIGH       13003L
#define IM_DISP_LUT_BUF        13004L
#define IM_DISP_MODE           13005L
#define IM_DISP_PAN_X          13006L
#define IM_DISP_PAN_Y          13007L
#define IM_DISP_WRTMSK         13008L
#define IM_DISP_ZOOM           13010L
#define IM_DISP_RESOLUTION_X   13011L
#define IM_DISP_RESOLUTION_Y   13012L
#define IM_DISP_VGA_MODE       13013L
#define IM_DISP_ZOOM_Y         13014L
#define IM_DISP_OVERLAY_MODE   13015L

/* Neighbourhood processing options */
#define IM_KER_ABSOLUTE        14050L
#define IM_KER_FACTOR          14052L
#define IM_CTL_OVERSCAN        14053L
#define IM_CTL_OVERSCAN_VAL    14054L
#define IM_KER_CENTER_X        14055L
#define IM_KER_CENTER_Y        14056L

/* Additional kernel attributes */
#define IM_KER_CLIP            14200L
#define IM_KER_SHIFT           14201L
#define IM_KER_OFFSET          14202L

/* Thread attributes */
#define IM_THR_MAX_PPS         15001L
#define IM_THR_PRIORITY        15002L
#define IM_THR_OWNER_ID        15003L
#define IM_THR_STACK_SIZE      15004L
#define IM_THR_VERIFY          15005L
#define IM_THR_EXECUTE         15006L
#define IM_THR_ACCELERATOR     15007L
#define IM_THR_TMP_BUFFER      15008L

/* Additional control options */
#define IM_CTL_DIRECTION       16000L
#define IM_CTL_BLOCK_X         16001L
#define IM_CTL_BLOCK_Y         16002L
#define IM_CTL_WORK_BUF        16003L
#define IM_CTL_WORK_BUF2       16004L
#define IM_CTL_WORK_BUF3       16005L
#define IM_CTL_NORMALIZE       16006L
#define IM_CTL_THRESHOLD       16007L
#define IM_CTL_RESAMPLE        16008L
#define IM_CTL_SAMPLE_X        16009L
#define IM_CTL_SAMPLE_Y        16010L
#define IM_CTL_PRECISION       16011L
#define IM_CTL_CENTER_X        16012L
#define IM_CTL_CENTER_Y        16013L
#define IM_CTL_INPUT_BITS      16014L
#define IM_CTL_OUTPUT_BITS     16015L
#define IM_CTL_COMPUTATION     16016L
#define IM_CTL_OVERSCAN_X      16017L
#define IM_CTL_OVERSCAN_Y      16018L
#define IM_CTL_SRC_SIZE_X      16019L
#define IM_CTL_SRC_SIZE_Y      16020L
#define IM_CTL_ZOOM            16021L
#define IM_CTL_MASK_BUF        16022L
#define IM_CTL_MAX_SCORE       16023L
#define IM_CTL_SCORE_TYPE      16024L
#define IM_CTL_SHIFT           16025L
#define IM_CTL_STEP            16026L
#define IM_CTL_STEP_X          16027L
#define IM_CTL_STEP_Y          16028L
#define IM_CTL_CLIP            16029L
#define IM_CTL_COEF_ORDER      16030L
#define IM_CTL_SKIP_ZERO       16031L
#define IM_CTL_INPUT_FORMAT    16032L
#define IM_CTL_OUTPUT_FORMAT   16033L
#define IM_CTL_WEIGHT          16034L
#define IM_CTL_SRC_BUF3        16035L
#define IM_CTL_RASTER_OUT      16036L
#define IM_CTL_COEF_TYPE       16037L
#define IM_CTL_KER_SIZE        16038L
#define IM_CTL_MASK_OP         16039L
#define IM_CTL_CACHE_BUF       16040L
#define IM_CTL_LUT_BUF         16041L
#define IM_CTL_THRESHOLD_FRAC  16042L
#define IM_CTL_WEIGHT_2        16043L
#define IM_CTL_BIT_ORDER       16044L


/* Graphics context */
#define IM_GRA_COLOR           17000L
#define IM_GRA_BACK_COLOR      17001L
#define IM_GRA_DRAW_MODE       17002L
#define IM_GRA_PLOT_MODE       17003L
#define IM_GRA_SCALE_X         17004L
#define IM_GRA_SCALE_Y         17005L
#define IM_GRA_OFFSET_X        17006L
#define IM_GRA_OFFSET_Y        17007L
#define IM_GRA_FONT            17008L
#define IM_GRA_FONT_SCALE_X    17009L
#define IM_GRA_FONT_SCALE_Y    17010L
#define IM_GRA_BACK_MODE       17011L
#define IM_GRA_COLOR_MODE      17012L
#define IM_GRA_BOX_X_MIN       17013L
#define IM_GRA_BOX_X_MAX       17014L
#define IM_GRA_BOX_Y_MIN       17015L
#define IM_GRA_BOX_Y_MAX       17016L
#define IM_GRA_START_X         17017L
#define IM_GRA_START_Y         17018L
#define IM_GRA_NUMBER          17019L
#define IM_GRA_THRESHOLD       17020L
#define IM_GRA_MAX_SIZE        17021L
#define IM_GRA_FLUSH           17022L

/* OSB attributes */
#define IM_OSB_STATE             18000L
#define IM_OSB_MODE              18001L
#define IM_OSB_INTERRUPT_DRIVEN  18002L      /* Internal use only */
#define IM_OSB_TIMEOUT           18003L

/* JPEG control */
#define IM_JPEG_MODE           19000L
#define IM_JPEG_NUM_BANDS      19001L
#define IM_JPEG_SIZE_X         19002L
#define IM_JPEG_SIZE_Y         19003L
#define IM_JPEG_SIZE_BIT       19004L
#define IM_JPEG_SIZE           19005L
#define IM_JPEG_TYPE           19006L
#define IM_JPEG_TABLE_QUANT    19007L
#define IM_JPEG_TABLE_AC       19008L
#define IM_JPEG_TABLE_DC       19009L
#define IM_JPEG_SAVE_TABLES    19010L
#define IM_JPEG_SAVE_IMAGE     19011L
#define IM_JPEG_SAVE_HEADER    19012L
#define IM_JPEG_PREDICTOR      19013L
#define IM_JPEG_Q_FACTOR       19014L
#define IM_JPEG_NUM_BLOCKS     19015L
#define IM_JPEG_SUBSAMP_X      19016L
#define IM_JPEG_SUBSAMP_Y      19017L
#define IM_JPEG_RESTART_ROWS   19018L
#define IM_JPEG_COMPUTE_TABLES 19019L
#define IM_JPEG_ENTROPY_CODING 19020L
#define IM_JPEG_RESET          19021L
#define IM_JPEG_MEM_SEG_LENGTH 19022L
#define IM_JPEG_START_INTERVAL 19023L
#define IM_JPEG_SAVE_RSTINFO   19024L

#define IM_GMOD_TYPE           20000L

/* imBufCopyROI */
#define IM_ROI_SIZE_X          21001L
#define IM_ROI_SIZE_Y          21002L
#define IM_ROI_SRC_START_X     21003L
#define IM_ROI_SRC_START_Y     21004L
#define IM_ROI_DST_START_X     21005L
#define IM_ROI_DST_START_Y     21006L
#define IM_ROI_NUMBER          21007L

/***************************************
* Grab control and inquire defines     *
****************************************/

/* Limit of the grab control generic defines */
#define IM_DIG_CHANNEL              30000L
#define IM_DIG_SYNC_CHANNEL         30001L
#define IM_DIG_GAIN                 30002L
#define IM_DIG_REF_WHITE            30003L
#define IM_DIG_REF_BLACK            30004L
#define IM_DIG_LUT_BUF              30005L
#define IM_DIG_USER_IN              30006L
#define IM_DIG_USER_OUT             30007L
#define IM_DIG_EXP_TIME             30008L
#define IM_DIG_EXP_DELAY            30009L
#define IM_DIG_EXP_SOURCE           30010L
#define IM_DIG_EXP_MODE             30011L
#define IM_DIG_EXPOSURE             30012L
#define IM_DIG_TRIG_SOURCE          30013L
#define IM_DIG_TRIG_MODE            30014L
#define IM_DIG_TRIGGER              30015L
#define IM_DIG_SIZE_X               30016L
#define IM_DIG_SIZE_Y               30017L
#define IM_DIG_SIZE_BIT             30018L
#define IM_DIG_TYPE                 30019L
#define IM_DIG_NUM_BANDS            30020L
#define IM_DIG_SCAN_MODE            30021L
#define IM_DIG_MAX_CHANNELS         30022L
#define IM_DIG_INPUT_MODE           30023L
#define IM_DIG_USER_IN_FORMAT       30024L
#define IM_DIG_USER_OUT_FORMAT      30025L
#define IM_DIG_GRAB_SOURCE          30026L
#define IM_DIG_BRIGHTNESS           30027L
#define IM_DIG_CONTRAST             30028L
#define IM_DIG_HUE                  30029L
#define IM_DIG_SATURATION           30030L
#define IM_DIG_YC_SEPARATION        30031L
#define IM_DIG_SIGNAL_AMPLITUDE     30032L
#define IM_DIG_SIGNAL_BLACK         30033L
#define IM_DIG_SIGNAL_WHITE         30034L
#define IM_DIG_PIXEL_CLOCK          30035L
#define IM_DIG_AUTOMATIC_INPUT_GAIN 30036L
#define IM_DIG_INPUT_GAIN           30037L

/* Additional control for UART (Meteor II/Dig) */
#define IM_UART_BAUD_RATE           30038L
#define IM_UART_PARITY              30039L
#define IM_UART_STOP_BITS           30040L
#define IM_UART_DATA_BITS           30041L
#define IM_UART_TIMEOUT             30042L
#define IM_UART_WRITE_CHAR          30043L
#define IM_UART_READ_CHAR           30044L
#define IM_UART_READ_LENGTH         30045L
#define IM_UART_READ_MAX_LENGTH     30046L
#define IM_UART_READ_STRING         30047L
#define IM_UART_WRITE_LENGTH        30048L
#define IM_UART_WRITE_STRING        30049L
#define IM_UART_DATA_PRESENT        30050L
#define IM_UART_ERROR               30051L
/* IM_UART_ERROR+IM_ERR_RESET is reserved 30052 */
#define IM_UART_WRITE_TERMINATOR    30053L
#define IM_UART_READ_TERMINATOR     30054L
#define _IM_UART_READ_CONFIG        30055L       /* Internal use only */

/* Additional control for DAC module */
#define IM_DIG_ANALOG_SOURCE        30056L
#define IM_DIG_DIGITAL_SOURCE       30057L

/* Additional control for Genesis PMC module */
#define IM_DIG_EXP_ARM_SOURCE       30058L
#define IM_DIG_EXP_ARM_MODE         30059L
#define IM_DIG_HRST_MODE            30060L
#define IM_DIG_VRST_MODE            30061L

/* Additional control for Meteor II/Camera Link module */
#define IM_DIG_CC1_SOURCE           30062L
#define IM_DIG_CC2_SOURCE           30063L
#define IM_DIG_CC3_SOURCE           30064L
#define IM_DIG_CC4_SOURCE           30065L

#define IM_UART_FRAMING_ERROR       0x0001L
#define IM_UART_PARITY_ERROR        0x0002L
#define IM_UART_OVERRUN_ERROR       0x0004L
#define IM_UART_TIMEOUT_ERROR       0x0008L

#define IM_SEQ_TIME                 50100L
#define IM_SEQ_FRAMES               50101L
#define IM_SEQ_MAX_TIME             50102L
#define IM_SEQ_TIME_BUF             50103L
#define IM_SEQ_TIME_BUF2            50104L
#define IM_SEQ_PRIORITY             50105L

#define IM_SEQ_WAIT                 1L
#define IM_SEQ_HALT                 2L
#define IM_SEQ_ABORT                3L
#define IM_SEQ_WAIT_THREAD          4L

/* Digitizer Low Level control */
#define IM_DIGLL_REF_WHITE          4L
#define IM_DIGLL_REF_BLACK          5L
#define IM_DIGLL_LEVEL_COARSE       6L
#define IM_DIGLL_LEVEL_FINE         7L


/***************************************/
/* Control and inquire values          */
/***************************************/

#define IM_CHANNEL_0          0x10000L
#define IM_CHANNEL_1          0x20000L
#define IM_CHANNEL_2          0x40000L
#define IM_CHANNEL_3          0x80000L
#define IM_CHANNEL_GRAB       0x1000000L

#define IM_CHANNEL(index)     (IM_CHANNEL_0 << (index))

#define IM_BIT0               0x0L
#define IM_BIT1               0x10000L
#define IM_BIT2               0x20000L
#define IM_BIT3               0x40000L
#define IM_BIT4               0x80000L

/* Flags that could be ored with channels */
#define IM_AUTO               0x0L
#define IM_MANUAL             0x1000000L

#define IM_SOFTWARE           0L
#define IM_HARDWARE           1L
#define IM_VSYNC              2L
#define IM_HSYNC              3L
#define IM_EXPOSURE           4L
#define IM_USER_BIT           5L          /* equal IM_VSYNC+IM_FIELD (used by Genesis PMC) */
#define IM_USER_OUT           6L          /* Camera Link only */
#define IM_TIMER1             0x010000L
#define IM_TIMER2             0x020000L
#define IM_TIMER3             0x040000L
#define IM_TIMER4             0x080000L
#define IM_TRIGGER1           0x100000L
#define IM_TRIGGER2           0x200000L

#define IM_FALLING_EDGE       0L
#define IM_RISING_EDGE        1L

#define IM_ACTIVE_LOW         2L
#define IM_ACTIVE_HIGH        3L

#define IM_ANALOG             0L
#define IM_DIGITAL            1L

#define IM_TTL                0L
#define IM_RS422              1L
#define IM_LVDS               IM_RS422    /* This is the same as IM_RS422 (used by Camera Link) */

#define IM_USE_MEMORY_DCF     0L
#define IM_USE_EMBEDDED_DCF   1L

#define IM_PORT1              1L
#define IM_PORT2              2L


/***************************************/
/* Composite signal conversion         */
/***************************************/

#define IM_NTSC_SIZE_X             704L
#define IM_NTSC_SIZE_Y             480L
#define IM_NTSC_TO_RGB               0L
#define IM_NTSC_TO_MONO              1L

#endif   /* __IMAPIDEF_H__ */

