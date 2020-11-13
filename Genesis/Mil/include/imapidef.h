/*******************************************************************
 *
 * COPYRIGHT (c) 1995-1997 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

#ifndef __IMAPIDEF_H__
#define __IMAPIDEF_H__


/* Internal defines identifying External Register Port devices.
 * Use IM_EXTDEV_... #defines in user mode.
 */
#define _IM_EXT_PORT_DEVICE_ID_NONE                   0
#define _IM_EXT_PORT_DEVICE_ID_GRAB(g)                (g+1)    /* g is 0 to 30 */
#define _IM_EXT_PORT_DEVICE_ID_MJPEG                  32
#define _IM_EXT_PORT_DEVICE_ID_OTHERS                 64       /* Corona, Meteor II, ... */
#define _IM_EXT_PORT_DEVICE_ID_RASTER_BLASTER         128

#define _IM_EXT_PORT_DEVICE_ID_GENESIS_GRAB           _IM_EXT_PORT_DEVICE_ID_GRAB(0)      /* 1    is Genesis & Genesis LC grab module */
#define _IM_EXT_PORT_DEVICE_ID_METEOR_II_DIG          _IM_EXT_PORT_DEVICE_ID_GRAB(1)      /* 2    is Meteor II/Dig */
#define _IM_EXT_PORT_DEVICE_ID_METEOR_II_DIG_MJPEG    _IM_EXT_PORT_DEVICE_ID_GRAB(32+1)   /* 32+2 is Meteor II/Dig with MJPEG */
#define _IM_EXT_PORT_DEVICE_ID_2CH_MACABRE            _IM_EXT_PORT_DEVICE_ID_GRAB(2)      /* 3    is 2 channels MACABre */
#define _IM_EXT_PORT_DEVICE_ID_4CH_MACABRE            _IM_EXT_PORT_DEVICE_ID_GRAB(3)      /* 4    is 4 channels MACABre */


/*******************************************************************
 *
 * Genesis Native Library #defines.
 *
 *******************************************************************/

/* Initialization */
#define IM_RESET           0
#define IM_PARTIAL_RESET   1
#define IM_DOWNLOAD        2
#define IM_FULL_RESET      IM_RESET

/* Data formats */
#define IM_UNSIGNED     0x00000000
#define IM_SIGNED       0x10000000
#define IM_IEEE754      0x20000000
#define IM_PACKED       0x40000000
#define IM_ALIGN_64K    0x80000000        /* Internal use only */

/* Buffer types */
#define IM_BINARY    (1  | IM_PACKED)
#define IM_RGB       (24 | IM_PACKED)
#define IM_UBYTE     (8  | IM_UNSIGNED)
#define IM_USHORT    (16 | IM_UNSIGNED)
#define IM_ULONG     (32 | IM_UNSIGNED)
#define IM_BYTE      (8  | IM_SIGNED)
#define IM_SHORT     (16 | IM_SIGNED)
#define IM_LONG      (32 | IM_SIGNED)
#define IM_FLOAT     (32 | IM_IEEE754)
#define IM_DOUBLE    (64 | IM_IEEE754)

/* Conditional operators */
#define IM_IN_RANGE         1
#define IM_OUT_RANGE        2
#define IM_EQUAL            3
#define IM_NOT_EQUAL        4
#define IM_GREATER          5
#define IM_LESS             6
#define IM_GREATER_OR_EQUAL 7
#define IM_LESS_OR_EQUAL    8

/* Morphological operators */
#define IM_ERODE            1
#define IM_DILATE           2
#define IM_THIN             3
#define IM_THICK            4
#define IM_HIT_OR_MISS      5
#define IM_MATCH            6
#define IM_CLOSE           10
#define IM_OPEN            11

/* Arithmetic operators */
#define IM_ADD         0x0000
#define IM_SUB         0x0001
#define IM_SUB_NEG     0x000A
#define IM_SUB_ABS     0x0011
#define IM_MIN         0x0012
#define IM_MAX         0x0013
#define IM_OR          0x0016
#define IM_AND         0x0017
#define IM_XOR         0x0018
#define IM_NOR         0x0019
#define IM_NAND        0x001A
#define IM_XNOR        0x001B
#define IM_NOT         0x0014
#define IM_NEG         0x0023
#define IM_ABS         0x000C
#define IM_PASS        0x0002
#define IM_MULT        0x0100
#define IM_DIV         0x0101
#define IM_DIV_INTO    0x0102

/* Additional arithmetic operators */
#define IM_LOG         0x0000
#define IM_EXP         0x0001
#define IM_SIN         0x0002
#define IM_COS         0x0003
#define IM_TAN         0x0004
#define IM_QUAD        0x0005

/* Yet more arithmetic operators */
#define IM_SUB_CLIP    0x0081
#define IM_SHIFT       0x0200
#define IM_ADD_SAT     0x0201
#define IM_SUB_SAT     0x0202
#define IM_MULT_SAT    0x0203
#define IM_SQUARE      0x0300
#define IM_SQRT        0x0301
#define IM_ATAN        0x0302
#define IM_CUBE        0x0303
#define IM_CBRT        0x0304
#define IM_SQUARE_ADD  0x0305
#define IM_MULT_MSB    0x0306
#define IM_DIV_FRAC    0x0307
#define IM_ATAN2       0x0308

/* imGen1d() */
#define IM_POLYNOMIAL  0x0400

/* Buffer inquiries */
#define IM_BUF_SIZE_X          3
#define IM_BUF_SIZE_Y          4
#define IM_BUF_NUM_BANDS       6
#define IM_BUF_TYPE            8
#define IM_BUF_SIZE_BIT       10
#define IM_BUF_FORMAT         11
#define IM_BUF_PARENT_ID      30
#define IM_BUF_OFFSET_X       32
#define IM_BUF_OFFSET_Y       33
#define IM_BUF_OFFSET_BAND    37
#define IM_BUF_NUM_FIELDS     38
#define IM_BUF_OWNER_ID      124

/* Additional buffer inquiries */
#define IM_BUF_LOCATION         200
#define IM_BUF_PHYSICAL_ADDRESS 201
#define IM_BUF_PITCH            202
#define IM_BUF_BUF_POINTER      400
#define IM_BUF_BUF_JPEG_POINTER 401

/* System inquiries */
#define IM_SYS_NUM_NODES      1
#define IM_SYS_NUM_DIGITIZERS 2
#define IM_SYS_NUM_DISPLAYS   3
#define IM_SYS_NUM_SYSTEMS    4
#define IM_SYS_PRODUCT_LIST   5

/* Device inquiries */
#define IM_DEV_MVP                     1
#define IM_DEV_MVP_SPEED               2
#define IM_DEV_VIA_PRIMARY             3
#define IM_DEV_VIA_DISPLAY             4
#define IM_DEV_ACCELERATOR             5
#define IM_DEV_MEM_PROC                6
#define IM_DEV_MEM_DISP                7
#define IM_DEV_MEM_OVERLAY             8
#define IM_DEV_OWNER_SYSTEM            9
#define IM_DEV_OWNER_NODE              10
#define IM_DEV_MSG_TOTAL               11
#define IM_DEV_MSG_FREE                12
#define IM_DEV_FREE_MEM_PROC           13
#define IM_DEV_FREE_MEM_DISP           14
#define IM_DEV_PRODUCT_ID              15
#define IM_DEV_CUSTOMER_PRODUCT_ID     16
#define IM_DEV_PRODUCT_SERIAL_NUMBER   17
#define _IM_DEV_ACCESS_NOA_REGISTER    18    /* Don't document this one */
#define _IM_DEV_ACCESS_MAC_REGISTER    19    /* Don't document this one */

/* Device inquiries product id */
#define IM_DEV_GENESIS              1
#define IM_DEV_GENESIS_PRO          2
#define IM_DEV_GENESIS_LC           3
#define IM_DEV_GENESIS_MEMORY       4
#define IM_DEV_METEOR_II_DIG        5
#define IM_DEV_MACABRE              6
#define IM_DEV_GENESIS_UNDEF        99

/* Externel Device inquiries board id */
#define IM_EXTDEV_NONE                    _IM_EXT_PORT_DEVICE_ID_NONE
#define IM_EXTDEV_GENESIS_GRAB            _IM_EXT_PORT_DEVICE_ID_GENESIS_GRAB
#define IM_EXTDEV_METEOR_II_DIG           _IM_EXT_PORT_DEVICE_ID_METEOR_II_DIG
#define IM_EXTDEV_METEOR_II_DIG_MJPEG     _IM_EXT_PORT_DEVICE_ID_METEOR_II_DIG_MJPEG
#define IM_EXTDEV_2CH_MACABRE             _IM_EXT_PORT_DEVICE_ID_2CH_MACABRE
#define IM_EXTDEV_4CH_MACABRE             _IM_EXT_PORT_DEVICE_ID_4CH_MACABRE
#define IM_EXTDEV_RASTER_BLASTER          _IM_EXT_PORT_DEVICE_ID_RASTER_BLASTER


/* Application inquires */
#define IM_APP_TIMEOUT        1

/* Miscellaneous defines */
#define IM_DEFAULT      0x10000000
#define IM_NONE         0x20000000
#define IM_DONT_CARE_32 0x00ffffff
#define IM_NO_CHANGE         -9999
#define IM_ALL                   0
#define IM_ENABLE            -9997
#define IM_DISABLE           -9999
#define IM_UNKNOWN           -9999
#define IM_CONTINUOUS           -1
#define IM_FORWARD               1
#define IM_REVERSE               2
#define IM_VERY_LOW              0
#define IM_LOW                   1
#define IM_MEDIUM                2
#define IM_HIGH                  3
#define IM_CLEAR                 1
#define IM_NO_CLEAR              2
#define IM_IDEMPOTENCE          -1
#define IM_FAST            0x40000
#define IM_VERY_FAST       0x80000
#define IM_BEST           0x100000
#define IM_MULTIPLE       0x400000
#define IM_ABSOLUTE              1
#define IM_OFFSET                2
#define IM_CLEAR_BACKGROUND 0x2000
#define IM_SYNCHRONOUS           1
#define IM_ASYNCHRONOUS          2
#define IM_FILL                 -1
#define IM_VIA_ONLY              0
#define IM_ADDRESS_ONLY          1
#define IM_SAVE                  2
#define IM_FASTEST               3
#define IM_SAME_KERNEL           4
#define IM_CACHE_BUF_SIZE   0x1000

/* More miscellaneous stuff */
#define IM_NOW                 1
#define IM_FRAME               2
#define IM_FIELD               3
#define IM_LINE                4
#define IM_PACK_0              1
#define IM_UNPACK_0            2
#define IM_PACK_1             17
#define IM_UNPACK_1           18
#define IM_DONT_CARE      0x8000
#define IM_EXACT         0x20000
#define IM_URGENT              5
#define IM_SYNCHRONIZED        1
#define IM_CLIP_SQUARE        10
#define IM_FIRST_FIELD        -1
#define IM_FIRST               0
#define IM_SECOND              1
#define IM_BOTH                2
#define IM_MODE_2      0x8000000
#define IM_THRESH_CONSTANT 0x100
#define IM_THRESH_PIXEL    0x200
#define IM_PASS_CONSTANT   0x400
#define IM_PASS_PIXEL      0x800
#define IM_PIXEL               1

/* VIA-related values not defined elsewhere */
#define IM_24_TO_32        1
#define IM_32_TO_24        2
#define IM_VIA_PRIMARY     1
#define IM_VIA_DISPLAY     2
#define IM_VIA_SOURCE      3
#define IM_VIA_DESTINATION 4
#define IM_RGB555          1
#define IM_RGB565          2
#define IM_PROGRESSIVE     0
#define IM_INTERLACED      1
#define IM_ODD             0
#define IM_EVEN            1
#define IM_NEXT            2

/* Display control */
#define IM_KEY_OFF         2
#define IM_KEY_ALWAYS      3
#define IM_KEY_IN_RANGE    4
#define IM_KEY_OUT_RANGE   5

/* VGA Mode */
#define IM_SINGLE_SCREEN   0
#define IM_DUAL_SCREEN     1
#define IM_DUAL_HEAD       2

/* File formats */
#define IM_MIL             0
#define IM_RAW             1
#define IM_TIFF            2
#define IM_GIF             3

/* Additional file formats */
#define IM_NATIVE         10

/* Conversions */
#define IM_TRUNCATE        1
#define IM_ROUND           2
#define IM_ZERO_EXTEND     4
#define IM_SIGN_EXTEND     5
#define IM_CLIP         0x80
#define IM_ABS_CLIP    (IM_ABS | IM_CLIP)

/* imIntFindExtreme() */
#define IM_MAX_PIXEL       1
#define IM_MIN_PIXEL       2

/* imIntFlip() */
#define IM_FLIP_H       0x0001
#define IM_FLIP_V       0x0002
#define IM_ROTATE_90    0x0010
#define IM_ROTATE_180   0x0020
#define IM_ROTATE_270   0x0030

/* imIntHistogramEqualize() */
#define IM_UNIFORM           1
#define IM_EXPONENTIAL       2
#define IM_RAYLEIGH          3
#define IM_HYPER_CUBE_ROOT   4
#define IM_HYPER_LOG         5
#define IM_IMAGE_TO_LUT      1
#define IM_HIST_TO_LUT       3

/* imIntRank() */
#define IM_MEDIAN      0x10000

/* Geometric transforms */
#define IM_ROTATE            1
#define IM_SCALE             2
#define IM_TRANSLATE         4
#define IM_SHEAR_X           5
#define IM_SHEAR_Y           6

/* Interpolation types */
#define IM_NO_INTERPOLATE   0x00000002
#define IM_INTERPOLATE      0x00000004
#define IM_BILINEAR         0x00000008
#define IM_BICUBIC          0x00000010
#define IM_AVERAGE          0x00000020
#define IM_NEAREST_NEIGHBOR 0x00000040

/* Overscan or graphic modes */
#define IM_OPAQUE           0x01000058
#define IM_TRANSPARENT      0x01000059
#define IM_REPLACE          0x01000060
#define IM_MIRROR           0x01000061
#define IM_REPLACE_MAX      0x01000063
#define IM_REPLACE_MIN      0x01000064

/* Synchronization */
#define IM_WAITING           10
#define IM_EXECUTING         20
#define IM_CANCELING         25
#define IM_READY             30
#define IM_STARTED           40
#define IM_COMPLETED         50
#define IM_INQUIRE     0x800000
#define IM_LINE_INT   0x1000000
#define IM_INFINITE          -1
#define IM_NON_SIGNALLED     IM_WAITING
#define IM_SIGNALLED         IM_COMPLETED
#define IM_AUTO_RESET        1
#define IM_MANUAL_RESET      2

/* Buffer location */
#define IM_PROC            1
#define IM_DISP            2
#define IM_HOST            3
#define IM_PAGED           4
#define IM_NON_PAGED       5
#define IM_CURRENT         6
#define IM_HOST_PAGED      7

/* Buffer control */
#define IM_BUF_LOCK        1
#define IM_BUF_UNLOCK      2

/* PP ALU opcodes for imBinTriadic() and imIntTriadic() */
#define IM_PP_ZERO      0x00000000
#define IM_PP_ONE       0x07f80000
#define IM_PP_PASS_A    0x05500000
#define IM_PP_PASS      IM_PP_PASS_A
#define IM_PP_NOT       0x02a80000
#define IM_PP_AND       0x04400000
#define IM_PP_OR        0x07700000
#define IM_PP_XOR       0x03300000
#define IM_PP_NAND      0x03b80000
#define IM_PP_NOR       0x00880000
#define IM_PP_XNOR      0x04c80000
#define IM_PP_MERGE     0x05600000
#define IM_PP_XOR_XOR   0x04b00000

/* PP ALU opcodes for imIntTriadic() */
#define IM_PP_PASS_B    0x06600000
#define IM_PP_PASS_C    0x07800000
#define IM_PP_SRA_ADD   0x0b510000
#define IM_PP_SRA_SUB   0x0cad0000
#define IM_PP_ADD_AND   0x0b500000
#define IM_PP_SUB_AND   0x0cac0000
#define IM_PP_ADD_OR    0x0ab00000
#define IM_PP_SUB_OR    0x0d4c0000
#define IM_PP_ADD_ABS   0x0cb30000
#define IM_PP_SUB_ABS   0x0b4f0000
#define IM_PP_EXT_FIELD 0x06000000
#define IM_PP_INS_FIELD 0x05600000
#define IM_PP_ADD_FIELD 0x0b000000

/* Pseudo-opcodes for imIntTriadic() */
#define IM_PP_ADD_ADD   0xf0000f00
#define IM_PP_ADD_SUB   0xf0000f01
#define IM_PP_SUB_SUB   0xf0000f02

/* Colour conversion */
#define IM_RGB_TO_HSL      1
#define IM_RGB_TO_L        2
#define IM_HSL_TO_RGB      3
#define IM_L_TO_RGB        4
#define IM_RGB_TO_I        5
#define IM_RGB_TO_H        6
#define IM_MATRIX      0x100

/* Distance transforms */
#define IM_CHAMFER_3_4     1
#define IM_CITY_BLOCK      2
#define IM_CHESSBOARD      3

/* Lattice values */
#define IM_4_CONNECTED     0x10
#define IM_8_CONNECTED     0x20

/* imIntTriadic() */
#define IM_CONSTANT_A      0x100
#define IM_CONSTANT_B      0x200
#define IM_CONSTANT_C      0x400
#define IM_CONSTANT_AC     (IM_CONSTANT_A | IM_CONSTANT_C)

/* Graphics control */
#define IM_PLOT_POLY       1
#define IM_PLOT_LINES      2
#define IM_PLOT_DOTS       3
#define IM_FONT_DEFAULT    1
#define IM_FONT_SMALL      2
#define IM_FONT_MEDIUM     3
#define IM_FONT_LARGE      4

/* JPEG module */
#define IM_BASELINE        0
#define IM_LOSSLESS        3
#define IM_HUFFMAN         0
#define IM_ARITHMETIC      8

/*************************************/
/* Pattern matching module           */
/*************************************/
#define IM_TEMPLATE   0x0001
#define IM_NORMALIZED 0x0002
#define IM_ROTATION   0x0004

#define IM_PAT_FOUND_FLAG   1
#define IM_PAT_SCORE        2
#define IM_PAT_POSITION_X   3
#define IM_PAT_POSITION_Y   4
#define IM_PAT_ANGLE        5
#define IM_PAT_SCALE        6
#define IM_PAT_ORIENTATION  7

#define IM_PAT_TYPE               1
#define IM_PAT_SIZE_X             2
#define IM_PAT_SIZE_Y             3
#define IM_PAT_CENTRE_X           4
#define IM_PAT_CENTRE_Y           5
#define IM_PAT_NOMINAL_X          6
#define IM_PAT_NOMINAL_Y          7
#define IM_PAT_SPEED              8
#define IM_PAT_POSITION_START_X   9
#define IM_PAT_POSITION_START_Y  10
#define IM_PAT_POSITION_SIZE_X   11
#define IM_PAT_POSITION_SIZE_Y   12
#define IM_PAT_POSITION_ACCURACY 13
#define IM_PAT_PREPROCESSED      14
#define IM_PAT_OFFSET_X          15
#define IM_PAT_OFFSET_Y          16
#define IM_PAT_ACCEPTANCE        17
#define IM_PAT_NUMBER            18
#define IM_PAT_WORKBUF_SIZE_X    19
#define IM_PAT_WORKBUF_SIZE_Y    20
#define IM_PAT_WORKBUF_FAST      21
#define IM_PAT_WORKBUF_ROTATION  22
#define IM_PAT_WORKBUF           23
#define IM_PAT_RESULT_SIZE       24
#define IM_PAT_CERTAINTY         25

#define IM_PAT_FIRST_LEVEL       31
#define IM_PAT_LAST_LEVEL        32
#define IM_PAT_MODEL_STEP        33
#define IM_PAT_FAST_FIND         34
#define IM_PAT_MIN_SPACING_X     35
#define IM_PAT_MIN_SPACING_Y     36
#define IM_PAT_SCORE_TYPE        37
#define IM_PAT_FILE_TYPE         38

#define IM_PAT_MODEL_POINTER     39
#define IM_PAT_RESULT_POINTER    40
#define IM_PAT_REJECTION         41
#define IM_PAT_BEST_REJECT_SCORE 42
#define IM_PAT_BEST_REJECT_LEVEL 43

#define IM_PAT_CENTER_X     IM_PAT_CENTRE_X
#define IM_PAT_CENTER_Y     IM_PAT_CENTRE_Y
#define IM_PAT_ORIGINAL_X   IM_PAT_NOMINAL_X
#define IM_PAT_ORIGINAL_Y   IM_PAT_NOMINAL_Y

/**********************************/
/* Blob Analysis module           */
/**********************************/
/* Binary features */
#define IM_BLOB_LABEL_VALUE              1
#define IM_BLOB_AREA                     2
#define IM_BLOB_PERIMETER                3
#define IM_BLOB_FERET_X                  4
#define IM_BLOB_FERET_Y                  5
#define IM_BLOB_BOX_X_MIN                6
#define IM_BLOB_BOX_Y_MIN                7
#define IM_BLOB_BOX_X_MAX                8
#define IM_BLOB_BOX_Y_MAX                9
#define IM_BLOB_FIRST_POINT_X           10
#define IM_BLOB_FIRST_POINT_Y           11
#define IM_BLOB_AXIS_PRINCIPAL_LENGTH   12
#define IM_BLOB_AXIS_SECONDARY_LENGTH   13
#define IM_BLOB_FERET_MIN_DIAMETER      14
#define IM_BLOB_FERET_MIN_ANGLE         15
#define IM_BLOB_FERET_MAX_DIAMETER      16
#define IM_BLOB_FERET_MAX_ANGLE         17
#define IM_BLOB_FERET_MEAN_DIAMETER     18
#define IM_BLOB_CONVEX_AREA             19
#define IM_BLOB_CONVEX_PERIMETER        20
#define IM_BLOB_X_MIN_AT_Y_MIN          21
#define IM_BLOB_X_MAX_AT_Y_MAX          22
#define IM_BLOB_Y_MIN_AT_X_MAX          23
#define IM_BLOB_Y_MAX_AT_X_MIN          24
#define IM_BLOB_COMPACTNESS             25
#define IM_BLOB_NUMBER_OF_HOLES         26
#define IM_BLOB_FERET_ELONGATION        27
#define IM_BLOB_ROUGHNESS               28
#define IM_BLOB_EULER_NUMBER            47
#define IM_BLOB_LENGTH                  48
#define IM_BLOB_BREADTH                 49
#define IM_BLOB_ELONGATION              50
#define IM_BLOB_INTERCEPT_0             51
#define IM_BLOB_INTERCEPT_45            52
#define IM_BLOB_INTERCEPT_90            53
#define IM_BLOB_INTERCEPT_135           54
#define IM_BLOB_NUMBER_OF_RUNS          55
#define IM_BLOB_ASPECT_RATIO IM_BLOB_FERET_ELONGATION
#define IM_BLOB_GENERAL_FERET        0x400

/* Greyscale features */
#define IM_BLOB_SUM_PIXEL               29
#define IM_BLOB_MIN_PIXEL               30
#define IM_BLOB_MAX_PIXEL               31
#define IM_BLOB_MEAN_PIXEL              32
#define IM_BLOB_SIGMA_PIXEL             33
#define IM_BLOB_SUM_PIXEL_SQUARED       46

/* Binary or greyscale features */
#define IM_BLOB_CENTER_OF_GRAVITY_X     34
#define IM_BLOB_CENTER_OF_GRAVITY_Y     35
#define IM_BLOB_MOMENT_X0_Y1            36
#define IM_BLOB_MOMENT_X1_Y0            37
#define IM_BLOB_MOMENT_X1_Y1            38
#define IM_BLOB_MOMENT_X0_Y2            39
#define IM_BLOB_MOMENT_X2_Y0            40
#define IM_BLOB_MOMENT_CENTRAL_X1_Y1    41
#define IM_BLOB_MOMENT_CENTRAL_X0_Y2    42
#define IM_BLOB_MOMENT_CENTRAL_X2_Y0    43
#define IM_BLOB_AXIS_PRINCIPAL_ANGLE    44
#define IM_BLOB_AXIS_SECONDARY_ANGLE    45
#define IM_BLOB_GENERAL_MOMENT       0x800

/* Short cuts for enabling multiple features */
#define IM_BLOB_ALL_FEATURES         0x100
#define IM_BLOB_BOX                  0x101
#define IM_BLOB_CONTACT_POINTS       0x102
#define IM_BLOB_CENTER_OF_GRAVITY    0x103
#define IM_BLOB_NO_FEATURES          0x104

/* Groups of results that can be read back together */
#define IM_BLOB_GROUP1               0x201
#define IM_BLOB_GROUP2               0x202
#define IM_BLOB_GROUP3               0x203
#define IM_BLOB_GROUP4               0x204
#define IM_BLOB_GROUP5               0x205
#define IM_BLOB_GROUP6               0x206
#define IM_BLOB_GROUP7               0x207
#define IM_BLOB_GROUP8               0x208
#define IM_BLOB_GROUP9               0x209

/* imBlobControl() and/or imBlobInquire() */
#define IM_BLOB_IMAGE_TYPE               1
#define IM_BLOB_IDENTIFICATION           2
#define IM_BLOB_LATTICE                  3
#define IM_BLOB_FOREGROUND_VALUE         4
#define IM_BLOB_PIXEL_ASPECT_RATIO       5
#define IM_BLOB_NUMBER_OF_FERETS         6
#define IM_BLOB_RESET                    9
#define IM_BLOB_SAVE_RUNS               14
#define IM_BLOB_MAX_LABEL               16
#define IM_BLOB_MAX_TIME                17
#define IM_BLOB_TIMEOUT                 18
#define IM_BLOB_TIME_SLICE              19

/* General moment type */
#define IM_ORDINARY             0x400
#define IM_CENTRAL              0x800

/* Blob identification */
#define IM_WHOLE_IMAGE              1
#define IM_INDIVIDUAL               2
#define IM_LABELLED                 4

/* Foreground values */
#define IM_NONZERO               0x80
#define IM_ZERO                 0x100
#define IM_NON_ZERO        IM_NONZERO

/* Image type values (and modifiers for certain features) */
#define IM_GREYSCALE           0x0200
#define IM_GRAYSCALE     IM_GREYSCALE

/* Data types for results */
#define IM_TYPE_CHAR          0x10000
#define IM_TYPE_SHORT         0x20000
#define IM_TYPE_LONG          0x40000
#define IM_TYPE_FLOAT         0x80000
#define IM_TYPE_DOUBLE       0x100000

/* Miscellaneous */
#define IM_ALWAYS                   0
#define IM_ALL_BLOBS            0x105
#define IM_INCLUDED_BLOBS       0x106
#define IM_EXCLUDED_BLOBS       0x107
#define IM_INCLUDE                  1
#define IM_EXCLUDE                  2
#define IM_DELETE                   3
#define IM_COMPRESS                 8
#define IM_MIN_FERETS               2
#define IM_MAX_FERETS              64
#define IM_INCLUDE_ONLY         0x101
#define IM_EXCLUDE_ONLY         0x102
/*********************************/
/* End of Blob Analysis #defines */
/*********************************/

/* Error handling */
#define IM_ERR_RESET          0x1
#define IM_ERR_CODE           0x2
#define IM_ERR_MSG            0x4
#define IM_ERR_FUNC           0x8
#define IM_ERR_MSG_FUNC       0xc
#define IM_ERR_MSG_SIZE       (80)                    /* Multiple of 8 for endian portability */
#define IM_ERR_FUNC_SIZE      (32)                    /* Multiple of 8 for endian portability */
#define IM_ERR_SIZE           (2 * IM_ERR_MSG_SIZE)   /* to hold both message and function plus some extra */

/* Error codes */
#define IM_SUCCESS             0
#define IM_ERR_BUFFER         -1
#define IM_ERR_DEVICE         -2
#define IM_ERR_FILE           -3
#define IM_ERR_MEMORY         -4
#define IM_ERR_NOT_PRESENT    -5
#define IM_ERR_OPCODE         -6
#define IM_ERR_OSB            -7
#define IM_ERR_PARAMETER      -8
#define IM_ERR_RESTRICTION    -9
#define IM_ERR_THREAD        -10
#define IM_ERR_TIMEOUT       -11
#define IM_ERR_SYSTEM        -12
#define IM_ERR_HALTED        -13
#define IM_ERR_BUF_ATTRIBUTE -14
#define IM_ERR_MISC          -15
#define IM_ERR_BUF_PARAM      IM_ERR_BUF_ATTRIBUTE

/*******************************************************************
 * Pre-defined pseudo-buffers.
 * These can be passed in place of a buffer only where documented.
 *******************************************************************/

/* Flag bit to identify pre-defined buffers */
#define IM_BUF_PREDEFINED           0x40000000
#define IM_BUF_PREDEFINED_SPECIAL   0x20000000


enum PreDefinedBufferType {
   /* Miscellaneous */
   IM_VM_CHANNEL           = (IM_BUF_PREDEFINED | 0x00),
   IM_PCI_TRANSFER_WINDOW,
   IM_DISP_TEXT,

   /* the internal predefined buffers go here */
   _IM_DEFAULT_THREAD      = (IM_BUF_PREDEFINED | 0x10),

   /* imBufChild() */
   IM_DISP_MONO            = (IM_BUF_PREDEFINED | 0x20),
   IM_DISP_COLOR           = (IM_BUF_PREDEFINED | 0x30),
   IM_DISP_RED             = (IM_BUF_PREDEFINED | 0x40),
   IM_DISP_GREEN           = (IM_BUF_PREDEFINED | 0x50),
   IM_DISP_BLUE            = (IM_BUF_PREDEFINED | 0x60),
   IM_DISP_OVERLAY         = (IM_BUF_PREDEFINED | 0x70),

   /* imIntConvolve() */
   IM_SMOOTH               = (IM_BUF_PREDEFINED | 0x80),
   IM_LAPLACIAN_EDGE,
   IM_LAPLACIAN_EDGE2,
   IM_SHARPEN,
   IM_SHARPEN2,
   IM_HORIZ_EDGE,
   IM_VERT_EDGE,
   IM_SOBEL_EDGE,
   IM_PREWITT_EDGE,
   IM_ROBERTS_EDGE,

   /* imIntRank() or morphology */
   IM_3X3_RECT_0,
   IM_3X3_CROSS_0,

   /* Morphology */
   IM_3X3_RECT_1,
   IM_3X3_CROSS_1,

   /* imIntRank() */
   IM_3X1,
   IM_5X1,
   IM_7X1,
   IM_9X1,
   IM_1X3,
   IM_1X5,
   IM_1X7,
   IM_1X9,

   /* Morphology */
   IM_5X5_RECT_1,
   IM_7X7_RECT_1,          /* 0x97 */

   _IM_PROC_TAG            = (IM_BUF_PREDEFINED | 0xa0),    /* Internal TAG buffers */
   _IM_DISP_TAG            = (IM_BUF_PREDEFINED | 0xb0),

   __PUT_NEXT_ONE_HERE__   = (IM_BUF_PREDEFINED | 0xc0),

   /* ---------------- */
   _IM_BUF_LAST_PREDEF        /* This one must always stay the last one */

};

#define _IM_BUF_NUM_PREDEF    (_IM_BUF_LAST_PREDEF & ~IM_BUF_PREDEFINED)


/*******************************************************************
 * Buffer fields (all tag values must be unique).
 * Tags below 10000 are reserved for user-defined fields.
 *******************************************************************/

/* VIA control options */
#define IM_CTL_BYTE_SWAP       10000
#define IM_CTL_DIR_X           10001
#define IM_CTL_DIR_Y           10002
#define IM_CTL_PACK            10003
#define IM_CTL_PRIORITY        10004
#define IM_CTL_SUBSAMP_X       10005
#define IM_CTL_SUBSAMP_Y       10006
#define IM_CTL_TAG_BUF         10007
#define IM_CTL_VIA             10008
#define IM_CTL_FMTCVR          10009
#define IM_CTL_WRTMSK          10010
#define IM_CTL_ZOOM_X          10011
#define IM_CTL_ZOOM_Y          10012
#define IM_CTL_BYTE_EXT        10013
#define IM_CTL_HEADER_EOF      10014
#define IM_CTL_HEADER_SOF      10015
#define IM_CTL_COUNT           10016
#define IM_CTL_SCAN_MODE       10017
#define IM_CTL_STREAM_ID       10018
#define IM_CTL_START_X         10019
#define IM_CTL_START_Y         10020
#define IM_CTL_STOP_X          10021
#define IM_CTL_STOP_Y          10022
#define IM_CTL_START_FIELD     10023
#define IM_CTL_ADDR_MODE       10024
#define IM_CTL_COUNT_MODE      10025
#define IM_CTL_LINE_INT        10026
#define IM_CTL_GRAB_MODE       10027
#define IM_CTL_CHANNEL         10028
#define IM_CTL_BYPASS          10029
#define IM_CTL_CAPTURE_MODE    10030
#define IM_CTL_LINE_INT_FIELD  10031
#define IM_CTL_LINE_INT_STEP   10032
#define IM_CTL_SETUP           10033
#define IM_CTL_DISPLAY_SYNC    10034
#define IM_CTL_SETUP_ADDRESS   10035

/* Processing results */
#define IM_RES_MIN_PIXEL       11000
#define IM_RES_MAX_PIXEL       11001
#define IM_RES_NUM_EVENTS      11002
#define IM_RES_NUM_DIFFERENCES 11003
#define IM_RES_NUM_PIXELS      11004
#define IM_RES_IDEMPOTENCE     11005

/* Run length encoding */
#define IM_RLE_SIZE            12000
#define IM_RLE_START           12001
#define IM_RLE_MODE            12002
#define IM_RLE_COLOR           12003
#define IM_RLE_BACK_COLOR      12004

/* Display control and inquiry */
#define IM_DISP_BUF            13000
#define IM_DISP_KEY_MODE       13001
#define IM_DISP_KEY_LOW        13002
#define IM_DISP_KEY_HIGH       13003
#define IM_DISP_LUT_BUF        13004
#define IM_DISP_MODE           13005
#define IM_DISP_PAN_X          13006
#define IM_DISP_PAN_Y          13007
#define IM_DISP_WRTMSK         13008
#define IM_DISP_ZOOM           13010
#define IM_DISP_RESOLUTION_X   13011
#define IM_DISP_RESOLUTION_Y   13012
#define IM_DISP_VGA_MODE       13013

/* Neighbourhood processing options */
#define IM_KER_ABSOLUTE        14050
#define IM_KER_FACTOR          14052
#define IM_CTL_OVERSCAN        14053
#define IM_CTL_OVERSCAN_VAL    14054
#define IM_KER_CENTER_X        14055
#define IM_KER_CENTER_Y        14056

/* Additional kernel attributes */
#define IM_KER_CLIP            14200
#define IM_KER_SHIFT           14201
#define IM_KER_OFFSET          14202

/* Thread attributes */
#define IM_THR_MAX_PPS         15001
#define IM_THR_PRIORITY        15002
#define IM_THR_OWNER_ID        15003
#define IM_THR_STACK_SIZE      15004
#define IM_THR_VERIFY          15005
#define IM_THR_EXECUTE         15006
#define IM_THR_ACCELERATOR     15007

/* Additional control options */
#define IM_CTL_DIRECTION       16000
#define IM_CTL_BLOCK_X         16001
#define IM_CTL_BLOCK_Y         16002
#define IM_CTL_WORK_BUF        16003
#define IM_CTL_WORK_BUF2       16004
#define IM_CTL_WORK_BUF3       16005
#define IM_CTL_NORMALIZE       16006
#define IM_CTL_THRESHOLD       16007
#define IM_CTL_RESAMPLE        16008
#define IM_CTL_SAMPLE_X        16009
#define IM_CTL_SAMPLE_Y        16010
#define IM_CTL_PRECISION       16011
#define IM_CTL_CENTER_X        16012
#define IM_CTL_CENTER_Y        16013
#define IM_CTL_INPUT_BITS      16014
#define IM_CTL_OUTPUT_BITS     16015
#define IM_CTL_COMPUTATION     16016
#define IM_CTL_OVERSCAN_X      16017
#define IM_CTL_OVERSCAN_Y      16018
#define IM_CTL_SRC_SIZE_X      16019
#define IM_CTL_SRC_SIZE_Y      16020
#define IM_CTL_ZOOM            16021
#define IM_CTL_MASK_BUF        16022
#define IM_CTL_MAX_SCORE       16023
#define IM_CTL_SCORE_TYPE      16024
#define IM_CTL_SHIFT           16025
#define IM_CTL_STEP            16026
#define IM_CTL_STEP_X          16027
#define IM_CTL_STEP_Y          16028
#define IM_CTL_CLIP            16029
#define IM_CTL_COEF_ORDER      16030
#define IM_CTL_SKIP_ZERO       16031
#define IM_CTL_INPUT_FORMAT    16032
#define IM_CTL_OUTPUT_FORMAT   16033
#define IM_CTL_WEIGHT          16034
#define IM_CTL_SRC_BUF3        16035
#define IM_CTL_RASTER_OUT      16036
#define IM_CTL_COEF_TYPE       16037
#define IM_CTL_KER_SIZE        16038
#define IM_CTL_MASK_OP         16039
#define IM_CTL_CACHE_BUF       16040

/* Graphics context */
#define IM_GRA_COLOR           17000
#define IM_GRA_BACK_COLOR      17001
#define IM_GRA_DRAW_MODE       17002
#define IM_GRA_PLOT_MODE       17003
#define IM_GRA_SCALE_X         17004
#define IM_GRA_SCALE_Y         17005
#define IM_GRA_OFFSET_X        17006
#define IM_GRA_OFFSET_Y        17007
#define IM_GRA_FONT            17008
#define IM_GRA_FONT_SCALE_X    17009
#define IM_GRA_FONT_SCALE_Y    17010
#define IM_GRA_BACK_MODE       17011
#define IM_GRA_COLOR_MODE      17012
#define IM_GRA_BOX_X_MIN       17013
#define IM_GRA_BOX_X_MAX       17014
#define IM_GRA_BOX_Y_MIN       17015
#define IM_GRA_BOX_Y_MAX       17016

/* OSB attributes */
#define IM_OSB_STATE           18000
#define IM_OSB_MODE            18001

/* JPEG control */
#define IM_JPEG_MODE           19000
#define IM_JPEG_NUM_BANDS      19001
#define IM_JPEG_SIZE_X         19002
#define IM_JPEG_SIZE_Y         19003
#define IM_JPEG_SIZE_BIT       19004
#define IM_JPEG_SIZE           19005
#define IM_JPEG_TYPE           19006
#define IM_JPEG_TABLE_QUANT    19007
#define IM_JPEG_TABLE_AC       19008
#define IM_JPEG_TABLE_DC       19009
#define IM_JPEG_SAVE_TABLES    19010
#define IM_JPEG_SAVE_IMAGE     19011
#define IM_JPEG_SAVE_HEADER    19012
#define IM_JPEG_PREDICTOR      19013
#define IM_JPEG_Q_FACTOR       19014
#define IM_JPEG_NUM_BLOCKS     19015
#define IM_JPEG_SUBSAMP_X      19016
#define IM_JPEG_SUBSAMP_Y      19017
#define IM_JPEG_RESTART_ROWS   19018
#define IM_JPEG_COMPUTE_TABLES 19019
#define IM_JPEG_ENTROPY_CODING 19020
#define IM_JPEG_RESET          19021
#define IM_JPEG_MEM_SEG_LENGTH 19022
#define IM_JPEG_START_INTERVAL 19023
#define IM_JPEG_SAVE_RSTINFO   19024

#define IM_GMOD_TYPE           20000


/***************************************
* Grab control and inquire defines     *
****************************************/

/* Limit of the grab control generic defines */
#define IM_DIG_CHANNEL          30000
#define IM_DIG_SYNC_CHANNEL     30001
#define IM_DIG_GAIN             30002
#define IM_DIG_REF_WHITE        30003
#define IM_DIG_REF_BLACK        30004
#define IM_DIG_LUT_BUF          30005
#define IM_DIG_USER_IN          30006
#define IM_DIG_USER_OUT         30007
#define IM_DIG_EXP_TIME         30008
#define IM_DIG_EXP_DELAY        30009
#define IM_DIG_EXP_SOURCE       30010
#define IM_DIG_EXP_MODE         30011
#define IM_DIG_EXPOSURE         30012
#define IM_DIG_TRIG_SOURCE      30013
#define IM_DIG_TRIG_MODE        30014
#define IM_DIG_TRIGGER          30015
#define IM_DIG_SIZE_X           30016
#define IM_DIG_SIZE_Y           30017
#define IM_DIG_SIZE_BIT         30018
#define IM_DIG_TYPE             30019
#define IM_DIG_NUM_BANDS        30020
#define IM_DIG_SCAN_MODE        30021
#define IM_DIG_MAX_CHANNELS     30022
#define IM_DIG_INPUT_MODE       30023
#define IM_DIG_USER_IN_FORMAT   30024
#define IM_DIG_USER_OUT_FORMAT  30025
#define IM_DIG_GRAB_SOURCE      30026
#define IM_DIG_BRIGHTNESS       30027
#define IM_DIG_CONTRAST         30028
#define IM_DIG_HUE              30029
#define IM_DIG_SATURATION       30030
#define IM_DIG_YC_SEPARATION    30031

/***************************************/
/* Control and inquire values          */
/***************************************/

#define IM_CHANNEL_0          0x10000
#define IM_CHANNEL_1          0x20000
#define IM_CHANNEL_2          0x40000
#define IM_CHANNEL_3          0x80000
#define IM_CHANNEL_GRAB       0x1000000

#define IM_CHANNEL(index)     (IM_CHANNEL_0 << (index))

#define IM_BIT0               0x0
#define IM_BIT1               0x10000
#define IM_BIT2               0x20000
#define IM_BIT3               0x40000
#define IM_BIT4               0x80000

/* Flags that could be ored with channels */
#define IM_AUTO               0x0
#define IM_MANUAL             0x1000000

#define IM_SOFTWARE           0
#define IM_HARDWARE           1
#define IM_VSYNC              2
#define IM_HSYNC              3
#define IM_EXPOSURE           4
#define IM_TIMER1             0x10000
#define IM_TIMER2             0x20000
#define IM_TRIGGER1           0x100000
#define IM_TRIGGER2           0x200000
#define IM_USER_BIT           5

#define IM_FALLING_EDGE       0
#define IM_RISING_EDGE        1

#define IM_ACTIVE_LOW         2
#define IM_ACTIVE_HIGH        3

#define IM_ANALOG             0
#define IM_DIGITAL            1

#define IM_TTL                0
#define IM_RS422              1

#define IM_USE_MEMORY_DCF     0

#define IM_PORT1              1
#define IM_PORT2              2

/***************************************/
/* Composite signal conversion         */
/***************************************/

#define IM_NTSC_SIZE_X             704
#define IM_NTSC_SIZE_Y             480
#define IM_NTSC_TO_RGB               0
#define IM_NTSC_TO_MONO              1

#endif   /* __IMAPIDEF_H__ */

