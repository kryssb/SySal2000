/***************************************************************************/
/*

    Filename:  MILERR.H
    Owner   :  Matrox Imaging dept.
    Rev     :  $Revision:   1.0  $
    Content :  This file contains the defines that are used by the
               mil functions to generate error codes and messages that
               will be used by the MIL Application Error Logging and
               other error related functions.

    COPYRIGHT (c) 1993  Matrox Electronic Systems Ltd.
    All Rights Reserved

*/
/***************************************************************************/

#ifndef  __MILERR_H
#define  __MILERR_H

/*
First line is the error code.
Second line is the error message for this code.
Other 9 lines are optional sub-messages with more detailed information.

------------------------------------------------------------------------
-                                                                      -
-  WARNING: Strings (including the NULL character at the end) should   -
-           never be longer than M_ERROR_MESSAGE_SIZE (128L).          -
-           No checking is done anywhere in the code to ensure this.   -
-                                                                      -
------------------------------------------------------------------------
*/


#define NO_MSG             MIL_TEXT("")  /* empty error message          */
#define NO_SUBMSG          MIL_TEXT("")  /* empty sub-error message      */
#define NO_FCTNAME         MIL_TEXT("")  /* empty function name          */

/* ActiveMIL Definitions */

/* 
   NOTE: if you add anything else than defines in this file, please put them 
         within a "#ifndef MILOCX_COMPILATION" block.
*/

#ifndef MILOCX_COMPILATION
   #define MILERR(Ignore1, ErrCode, Ignore2, SubErrCode, NewString)
#endif

/* LIST OF ERROR CODES AND MESSAGES */

#define M_NULL_ERROR             0L
#define M_ERR_0_MSG              MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_1         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_2         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_3         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_4         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_5         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_6         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_7         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_8         MIL_TEXT("Null.")
#define M_ERR_0_SUBMSG_9         MIL_TEXT("Null.")

#define M_MMX_ERROR              1L
#define M_ERR_1_MSG              MIL_TEXT("MMX Error.")
#define M_ERR_1_SUBMSG_1         MIL_TEXT("Cannot force MMX usage on a non-MMX CPU.")
#define M_ERR_1_SUBMSG_2         NO_SUBMSG
#define M_ERR_1_SUBMSG_3         NO_SUBMSG
#define M_ERR_1_SUBMSG_4         NO_SUBMSG
#define M_ERR_1_SUBMSG_5         NO_SUBMSG
#define M_ERR_1_SUBMSG_6         NO_SUBMSG
#define M_ERR_1_SUBMSG_7         NO_SUBMSG
#define M_ERR_1_SUBMSG_8         NO_SUBMSG
#define M_ERR_1_SUBMSG_9         NO_SUBMSG

#define M_SSE_ERROR              2L
#define M_ERR_2_MSG              MIL_TEXT("SSE Error.")
#define M_ERR_2_SUBMSG_1         MIL_TEXT("Cannot force SSE usage on a non-SSE CPU or OS don't support SSE.")
#define M_ERR_2_SUBMSG_2         NO_SUBMSG
#define M_ERR_2_SUBMSG_3         NO_SUBMSG
#define M_ERR_2_SUBMSG_4         NO_SUBMSG
#define M_ERR_2_SUBMSG_5         NO_SUBMSG
#define M_ERR_2_SUBMSG_6         NO_SUBMSG
#define M_ERR_2_SUBMSG_7         NO_SUBMSG
#define M_ERR_2_SUBMSG_8         NO_SUBMSG
#define M_ERR_2_SUBMSG_9         NO_SUBMSG

#define M_XX3XX_ERROR            3L
#define M_ERR_3_MSG              NO_SUBMSG
#define M_ERR_3_SUBMSG_1         NO_SUBMSG
#define M_ERR_3_SUBMSG_2         NO_SUBMSG
#define M_ERR_3_SUBMSG_3         NO_SUBMSG
#define M_ERR_3_SUBMSG_4         NO_SUBMSG
#define M_ERR_3_SUBMSG_5         NO_SUBMSG
#define M_ERR_3_SUBMSG_6         NO_SUBMSG
#define M_ERR_3_SUBMSG_7         NO_SUBMSG
#define M_ERR_3_SUBMSG_8         NO_SUBMSG
#define M_ERR_3_SUBMSG_9         NO_SUBMSG

#define M_XX4XX_ERROR            4L
#define M_ERR_4_MSG              NO_MSG
#define M_ERR_4_SUBMSG_1         NO_SUBMSG
#define M_ERR_4_SUBMSG_2         NO_SUBMSG
#define M_ERR_4_SUBMSG_3         NO_SUBMSG
#define M_ERR_4_SUBMSG_4         NO_SUBMSG
#define M_ERR_4_SUBMSG_5         NO_SUBMSG
#define M_ERR_4_SUBMSG_6         NO_SUBMSG
#define M_ERR_4_SUBMSG_7         NO_SUBMSG
#define M_ERR_4_SUBMSG_8         NO_SUBMSG
#define M_ERR_4_SUBMSG_9         NO_SUBMSG

#define M_XX5XX_ERROR            5L
#define M_ERR_5_MSG              NO_SUBMSG
#define M_ERR_5_SUBMSG_1         NO_SUBMSG
#define M_ERR_5_SUBMSG_2         NO_SUBMSG
#define M_ERR_5_SUBMSG_3         NO_SUBMSG
#define M_ERR_5_SUBMSG_4         NO_SUBMSG
#define M_ERR_5_SUBMSG_5         NO_SUBMSG
#define M_ERR_5_SUBMSG_6         NO_SUBMSG
#define M_ERR_5_SUBMSG_7         NO_SUBMSG
#define M_ERR_5_SUBMSG_8         NO_SUBMSG
#define M_ERR_5_SUBMSG_9         NO_SUBMSG

#define M_INVALID_PARAM_ERROR    6L
#define M_ERR_6_MSG              MIL_TEXT("Invalid parameter.")
#define M_ERR_6_SUBMSG_1         MIL_TEXT("Bad parameter value.")
#define M_ERR_6_SUBMSG_2         MIL_TEXT("One parameter does not reside within the buffer's limits.")
#define M_ERR_6_SUBMSG_3         MIL_TEXT("Pointer must be non-null.")
/* WARNING: Obsolete sub errors (4,5); if you want to use these, notify ActiveMIL team */
#define M_ERR_6_SUBMSG_4         MIL_TEXT("Parameter 1 not in supported list.")
#define M_ERR_6_SUBMSG_5         MIL_TEXT("Parameter 2 not in supported list.")
#define M_ERR_6_SUBMSG_6         MIL_TEXT("No graphic text font selected.")
#define M_ERR_6_SUBMSG_7         MIL_TEXT("The member StructSize from the MILBUFFERINFO structure given as an argument is invalid.")
#define M_ERR_6_SUBMSG_8         MIL_TEXT("Result buffer too small to hold result.")
#define M_ERR_6_SUBMSG_9         MIL_TEXT("Scale factors out of supported range.")

#define M_OVERSCAN_ERROR         7L
#define M_ERR_7_MSG              MIL_TEXT("Overscan processing error.")
#define M_ERR_7_SUBMSG_1         MIL_TEXT("Cannot allocate temporary buffer in memory.")
#define M_ERR_7_SUBMSG_2         MIL_TEXT("Buffer too small to perform the selected overscan")
#define M_ERR_7_SUBMSG_3         NO_SUBMSG
#define M_ERR_7_SUBMSG_4         NO_SUBMSG
#define M_ERR_7_SUBMSG_5         NO_SUBMSG
#define M_ERR_7_SUBMSG_6         NO_SUBMSG
#define M_ERR_7_SUBMSG_7         NO_SUBMSG
#define M_ERR_7_SUBMSG_8         NO_SUBMSG
#define M_ERR_7_SUBMSG_9         NO_SUBMSG

#define M_ALLOC_ERROR            8L
#define M_ERR_8_MSG              MIL_TEXT("Allocation error.")
#define M_ERR_8_SUBMSG_1         MIL_TEXT("Not enough memory to allocate application.")
#define M_ERR_8_SUBMSG_2         MIL_TEXT("Only one application can be allocated by host thread.")
#define M_ERR_8_SUBMSG_3         MIL_TEXT("Cannot allocate temporary buffer in memory.")
#define M_ERR_8_SUBMSG_4         MIL_TEXT("Not enough memory to allocate buffer.")
#define M_ERR_8_SUBMSG_5         MIL_TEXT("Cannot allocate system.")
#define M_ERR_8_SUBMSG_6         MIL_TEXT("Cannot allocate digitizer.")
#define M_ERR_8_SUBMSG_7         MIL_TEXT("Cannot allocate display.")
#define M_ERR_8_SUBMSG_8         MIL_TEXT("Not enough host memory to allocate buffer.")
#define M_ERR_8_SUBMSG_9         MIL_TEXT("Buffer type not supported.")

#define M_CHILD_ERROR            9L
#define M_ERR_9_MSG              MIL_TEXT("Child allocation error.")
#define M_ERR_9_SUBMSG_1         MIL_TEXT("Only one application can be allocated by host thread.")
#define M_ERR_9_SUBMSG_2         MIL_TEXT("Not enough memory to allocate child application.")
#define M_ERR_9_SUBMSG_3         MIL_TEXT("Not enough memory to allocate child buffer.")
#define M_ERR_9_SUBMSG_4         MIL_TEXT("Cannot allocate temporary child buffer in memory.")
#define M_ERR_9_SUBMSG_5         MIL_TEXT("Impossible to make a band child of a Jpeg buffer.")
#define M_ERR_9_SUBMSG_6         NO_SUBMSG
#define M_ERR_9_SUBMSG_7         NO_SUBMSG
#define M_ERR_9_SUBMSG_8         NO_SUBMSG
#define M_ERR_9_SUBMSG_9         NO_SUBMSG

#define M_ACCESS_ERROR           10L
#define M_ERR_10_MSG             MIL_TEXT("Buffer access error.")
#define M_ERR_10_SUBMSG_1        MIL_TEXT("Cannot M_RESTORE a M_RAW file format buffer.")
MILERR( M_ERR,10,SUBMSG,1,       MIL_TEXT("Cannot load a raw file format buffer with the AdjustBuffer parameter set to True."))
#define M_ERR_10_SUBMSG_2        MIL_TEXT("Cannot export buffer.")
#define M_ERR_10_SUBMSG_3        MIL_TEXT("Source buffer must be a M_IMAGE buffer.")
MILERR( M_ERR,10,SUBMSG,3,       MIL_TEXT("The BufferType of the source buffer must be set to mImage."))
#define M_ERR_10_SUBMSG_4        MIL_TEXT("Cannot import buffer.")
MILERR( M_ERR,10,SUBMSG,4,       MIL_TEXT("Cannot load buffer."))
#define M_ERR_10_SUBMSG_5        MIL_TEXT("Cannot restore buffer.")
MILERR( M_ERR,10,SUBMSG,5,       MIL_TEXT("Cannot load buffer."))
#define M_ERR_10_SUBMSG_6        MIL_TEXT("Cannot export child buffer in M_PLANAR format")
MILERR( M_ERR,10,SUBMSG,6,       MIL_TEXT("Cannot save child buffer in planar format"))
#define M_ERR_10_SUBMSG_7        NO_SUBMSG
#define M_ERR_10_SUBMSG_8        NO_SUBMSG
#define M_ERR_10_SUBMSG_9        NO_SUBMSG

#define M_DISPLAY_ERROR          11L
#define M_ERR_11_MSG             MIL_TEXT("Display error.")
#define M_ERR_11_SUBMSG_1        MIL_TEXT("Display and buffer must belong to same system.")
#define M_ERR_11_SUBMSG_2        MIL_TEXT("Display Lut dimensions are not compatible with the user Lut.")
#define M_ERR_11_SUBMSG_3        MIL_TEXT("Cannot associate a M_PSEUDO Lut with a monochrome display.")
MILERR( M_ERR,11,SUBMSG,3,       MIL_TEXT("Cannot associate a mPseudo LUT with a monochrome display."))
#define M_ERR_11_SUBMSG_4        MIL_TEXT("Zoom factors out of zoom limits or equal to zero.")
#define M_ERR_11_SUBMSG_5        MIL_TEXT("Buffer not currently selected on display.")
MILERR( M_ERR,11,SUBMSG,5,       MIL_TEXT("Buffer not currently associated with a display."))
#define M_ERR_11_SUBMSG_6        MIL_TEXT("Incompatible display type.")
#define M_ERR_11_SUBMSG_7        MIL_TEXT("Display must be allocated with the M_WINDOWED init flag.")
MILERR( M_ERR,11,SUBMSG,7,       MIL_TEXT("The DisplayType must be set to mDefaultWindow, mUserWindow, or mExternalWindow."))
#define M_ERR_11_SUBMSG_8        NO_SUBMSG
#define M_ERR_11_SUBMSG_9        NO_SUBMSG

#define M_OPERATION_ERROR        12L
#define M_ERR_12_MSG             MIL_TEXT("Operation error.")
#define M_ERR_12_SUBMSG_1        MIL_TEXT("Cannot allocate temporary buffer in memory.")
#define M_ERR_12_SUBMSG_2        MIL_TEXT("Not enough host memory to allocate buffer.")
#define M_ERR_12_SUBMSG_3        MIL_TEXT("Application still has MIL objects associated with it.")
#define M_ERR_12_SUBMSG_4        MIL_TEXT("Only logical addresses are supported on host system.")
#define M_ERR_12_SUBMSG_5        MIL_TEXT("Pitch must be a multiple of 4 bytes for binary buffers.")
#define M_ERR_12_SUBMSG_6        MIL_TEXT("Requested operation not supported.") 
#define M_ERR_12_SUBMSG_7        MIL_TEXT("Pitch must be a multiple of 2 pixels.")
#define M_ERR_12_SUBMSG_8        MIL_TEXT("Creation with physical address must be done on non paged buffers.")
#define M_ERR_12_SUBMSG_9        MIL_TEXT("The polar band to put must fit in the destination.")

#define M_DIGITIZER_ERROR        13L
#define M_ERR_13_MSG             MIL_TEXT("Digitizer error.")
#define M_ERR_13_SUBMSG_1        MIL_TEXT("Digitizer and buffer must belong to same system.")
#define M_ERR_13_SUBMSG_2        NO_SUBMSG
#define M_ERR_13_SUBMSG_3        NO_SUBMSG
#define M_ERR_13_SUBMSG_4        NO_SUBMSG
#define M_ERR_13_SUBMSG_5        NO_SUBMSG
#define M_ERR_13_SUBMSG_6        NO_SUBMSG
#define M_ERR_13_SUBMSG_7        NO_SUBMSG
#define M_ERR_13_SUBMSG_8        NO_SUBMSG
#define M_ERR_13_SUBMSG_9        NO_SUBMSG

#define M_HOOK_ERROR             14L
#define M_ERR_14_MSG             MIL_TEXT("Hook function error")
#define M_ERR_14_SUBMSG_1        MIL_TEXT("Unhooking by hooking the previous hook function is obsolete.  Please see documentation.")
#define M_ERR_14_SUBMSG_2        MIL_TEXT("A hook function must be provided.")
#define M_ERR_14_SUBMSG_3        MIL_TEXT("MxxxHookFunction functions should not be called within user hook function.")
#define M_ERR_14_SUBMSG_4        MIL_TEXT("Invalid hook type .")
#define M_ERR_14_SUBMSG_5        MIL_TEXT("Required hardware not present .")
#define M_ERR_14_SUBMSG_6        MIL_TEXT("Invalid system type .")
#define M_ERR_14_SUBMSG_7        NO_SUBMSG
#define M_ERR_14_SUBMSG_8        NO_SUBMSG
#define M_ERR_14_SUBMSG_9        NO_SUBMSG

#define M_JPEG_COMPRESS_ERROR    15L
#define M_ERR_15_MSG             MIL_TEXT("Jpeg compression error.")
#define M_ERR_15_SUBMSG_1        MIL_TEXT("Unable to allocate memory.")
#define M_ERR_15_SUBMSG_2        MIL_TEXT("Invalid image depth for Jpeg compression.")
#define M_ERR_15_SUBMSG_3        MIL_TEXT("Invalid compression parameter.")
#define M_ERR_15_SUBMSG_4        MIL_TEXT("Invalid Huffman table")
#define M_ERR_15_SUBMSG_5        MIL_TEXT("Invalid predictor.")
#define M_ERR_15_SUBMSG_6        MIL_TEXT("Invalid Q Factor.")
#define M_ERR_15_SUBMSG_7        MIL_TEXT("Invalid quantization table.")
#define M_ERR_15_SUBMSG_8        MIL_TEXT("Invalid restart interval.")
#define M_ERR_15_SUBMSG_9        MIL_TEXT("Invalid source or destination format.")

#define M_COMPRESS_ERROR         16L
#define M_ERR_16_MSG             MIL_TEXT("Compression Error")
#define M_ERR_16_SUBMSG_1        MIL_TEXT("Invalid compression type.")
#define M_ERR_16_SUBMSG_2        MIL_TEXT("Corrupted data.")
#define M_ERR_16_SUBMSG_3        MIL_TEXT("Invalid image depth for required compression type.")
#define M_ERR_16_SUBMSG_4        MIL_TEXT("Buffer allocated with MbufCreateXX cannot be the destination of a compression operation.")
#define M_ERR_16_SUBMSG_5        MIL_TEXT("Buffer allocated with MbufCreateXX cannot be the destination of a MbufPut operation.")
#define M_ERR_16_SUBMSG_6        NO_SUBMSG
#define M_ERR_16_SUBMSG_7        NO_SUBMSG
#define M_ERR_16_SUBMSG_8        NO_SUBMSG
#define M_ERR_16_SUBMSG_9        NO_SUBMSG

#define M_JPEG_COMPRESS_ERROR_2  17L
#define M_ERR_17_MSG             MIL_TEXT("Jpeg compression error.")
#define M_ERR_17_SUBMSG_1        MIL_TEXT("Chrominance tables are allowed only with 3 band YUV buffers.")
#define M_ERR_17_SUBMSG_2        MIL_TEXT("Luminance tables are allowed only with 3 band YUV buffers.")
#define M_ERR_17_SUBMSG_3        MIL_TEXT("The predictor value is only available for 1 band buffers or band childs.")
#define M_ERR_17_SUBMSG_4        MIL_TEXT("The Q factor is only available for 1 band buffers or band childs.")
#define M_ERR_17_SUBMSG_5        MIL_TEXT("The restart interval is only available for 1 band buffers or band childs.")
#define M_ERR_17_SUBMSG_6        MIL_TEXT("The source image must be a multiple of 16 in X and a multiple of 8 in Y.")
#define M_ERR_17_SUBMSG_7        MIL_TEXT("The destination image must be a multiple of 16 in X and a multiple of 8 in Y.")
#define M_ERR_17_SUBMSG_8        MIL_TEXT("The source image must be a multiple of 16 in X and a multiple of 16 in Y.")
#define M_ERR_17_SUBMSG_9        MIL_TEXT("The destination image must be a multiple of 16 in X and a multiple of 16 in Y.")


#define M_BMP_ERROR              18L
#define M_ERR_18_MSG             MIL_TEXT("BMP handler file access error.")
#define M_ERR_18_SUBMSG_1        MIL_TEXT("Not a bitmap file.")
#define M_ERR_18_SUBMSG_2        MIL_TEXT("Error closing bitmap file.")
#define M_ERR_18_SUBMSG_3        MIL_TEXT("Cannot open file in read mode.")
#define M_ERR_18_SUBMSG_4        MIL_TEXT("Error reading file.")
#define M_ERR_18_SUBMSG_5        MIL_TEXT("Unable to position file pointer.")
#define M_ERR_18_SUBMSG_6        MIL_TEXT("Cannot create or open file in write mode.")
#define M_ERR_18_SUBMSG_7        MIL_TEXT("No bitmap file opened in read mode.")
#define M_ERR_18_SUBMSG_8        MIL_TEXT("No bitmap file opened in write mode.")
#define M_ERR_18_SUBMSG_9        MIL_TEXT("Error writing file.")

#define M_BMP_ERROR_2            19L
#define M_ERR_19_MSG             MIL_TEXT("BMP handler general error.")
#define M_ERR_19_SUBMSG_1        MIL_TEXT("Unable to allocate sufficient memory.")
#define M_ERR_19_SUBMSG_2        MIL_TEXT("Not supported color format.")
#define M_ERR_19_SUBMSG_3        MIL_TEXT("Invalid write color format specified.")
#define M_ERR_19_SUBMSG_4        MIL_TEXT("Invalid write compression type specified.")
#define M_ERR_19_SUBMSG_5        MIL_TEXT("Not supported type of conversion.")
#define M_ERR_19_SUBMSG_6        MIL_TEXT("Invalid array format specified.")
#define M_ERR_19_SUBMSG_7        MIL_TEXT("Invalid length of palette arrays specified.")
#define M_ERR_19_SUBMSG_8        MIL_TEXT("No palette to read.")
#define M_ERR_19_SUBMSG_9        MIL_TEXT("Palette not needed for current write format.")


#define M_TIFF_ERROR             20L
#define M_ERR_20_MSG             MIL_TEXT("TIFF file access error.")
#define M_ERR_20_SUBMSG_1        MIL_TEXT("Cannot open file.")
#define M_ERR_20_SUBMSG_2        MIL_TEXT("Cannot close file.")
#define M_ERR_20_SUBMSG_3        MIL_TEXT("Cannot read file.")
#define M_ERR_20_SUBMSG_4        MIL_TEXT("Cannot read file.")
#define M_ERR_20_SUBMSG_5        MIL_TEXT("Cannot write to file.")
#define M_ERR_20_SUBMSG_6        MIL_TEXT("Cannot allocate temporary buffer in memory.")
#define M_ERR_20_SUBMSG_7        MIL_TEXT("The image file does not conform to the TIFF 6.0 specification.")
#define M_ERR_20_SUBMSG_8        MIL_TEXT("Wrong Byte Order, Only INTEL Byte Ordering supported.")
#define M_ERR_20_SUBMSG_9        MIL_TEXT("Not a TIFF file.")

#define M_MIL_FILE_ERROR         21L
#define M_ERR_21_MSG             MIL_TEXT("MIL file access error.")
#define M_ERR_21_SUBMSG_1        MIL_TEXT("Cannot open file.")
#define M_ERR_21_SUBMSG_2        MIL_TEXT("Cannot close file.")
#define M_ERR_21_SUBMSG_3        MIL_TEXT("Cannot read file.")
#define M_ERR_21_SUBMSG_4        MIL_TEXT("Cannot read file.")
#define M_ERR_21_SUBMSG_5        MIL_TEXT("Cannot write to file.")
#define M_ERR_21_SUBMSG_6        MIL_TEXT("Cannot allocate temporary buffer in memory.")
#define M_ERR_21_SUBMSG_7        MIL_TEXT("The image file does not conform to the TIFF 6.0 specification.")
#define M_ERR_21_SUBMSG_8        MIL_TEXT("Wrong Byte Order, Only INTEL Byte Ordering supported.")
#define M_ERR_21_SUBMSG_9        MIL_TEXT("Not a MIL file.")

#define M_MIL_FILE_ERROR_2       22L
#define M_ERR_22_MSG             MIL_TEXT("MIL file access error.")
#define M_ERR_22_SUBMSG_1        MIL_TEXT("Only 8, 16 or 32 BitsPerSample supported.")
#define M_ERR_22_SUBMSG_2        MIL_TEXT("Only the Lempel-Ziv & Welch (LZW) compression supported.")
#define M_ERR_22_SUBMSG_3        MIL_TEXT("PhotometricInterp incompatible with SamplePerPixel.")
#define M_ERR_22_SUBMSG_4        MIL_TEXT("Only PlanarConfiguration 2 supported for multi-band images.")
#define M_ERR_22_SUBMSG_5        MIL_TEXT("Up to 8 Samples Per Pixel supported.")
#define M_ERR_22_SUBMSG_6        MIL_TEXT("Only identical BitsPerSample for every sample supported.")
#define M_ERR_22_SUBMSG_7        MIL_TEXT("Cannot seek in file.")
#define M_ERR_22_SUBMSG_8        MIL_TEXT("Bad file format detected.")
#define M_ERR_22_SUBMSG_9        MIL_TEXT("Invalid info requested.")

#define M_MIL_FILE_ERROR_3       23L
#define M_ERR_23_MSG             MIL_TEXT("MIL file access error.")
#define M_ERR_23_SUBMSG_1        MIL_TEXT("Invalid parameter detected.")
#define M_ERR_23_SUBMSG_2        MIL_TEXT("Missing information in file.")
#define M_ERR_23_SUBMSG_3        MIL_TEXT("Bad size information detected in file.")
#define M_ERR_23_SUBMSG_4        MIL_TEXT("Bad identification information detected in file.")
#define M_ERR_23_SUBMSG_5        MIL_TEXT("Invalid data information detected in file.")
#define M_ERR_23_SUBMSG_6        MIL_TEXT("Unexpected internal error.")
#define M_ERR_23_SUBMSG_7        NO_SUBMSG
#define M_ERR_23_SUBMSG_8        NO_SUBMSG
#define M_ERR_23_SUBMSG_9        NO_SUBMSG

#define M_MULTI_THREAD_ERROR     24L
#define M_ERR_24_MSG             MIL_TEXT("Multi thread error.")
#define M_ERR_24_SUBMSG_1        MIL_TEXT("Cannot find synchronization event to delete.")
#define M_ERR_24_SUBMSG_2        MIL_TEXT("Invalid MIL_ID, MIL thread or event was not allocated in current HOST thread.")
MILERR( M_ERR,24,SUBMSG,2,       MIL_TEXT("Invalid thread or event ID; it was not allocated in current host thread."))
#define M_ERR_24_SUBMSG_3        MIL_TEXT("Application must be freed before exiting a thread.")
#define M_ERR_24_SUBMSG_4        NO_SUBMSG
#define M_ERR_24_SUBMSG_5        NO_SUBMSG
#define M_ERR_24_SUBMSG_6        NO_SUBMSG
#define M_ERR_24_SUBMSG_7        NO_SUBMSG
#define M_ERR_24_SUBMSG_8        NO_SUBMSG
#define M_ERR_24_SUBMSG_9        NO_SUBMSG

#define M_JPEG_ERROR             25L
#define M_ERR_25_MSG             MIL_TEXT("JPEG handler general error.")
#define M_ERR_25_SUBMSG_1        MIL_TEXT("Not supported color format.")
#define M_ERR_25_SUBMSG_2        MIL_TEXT("Error closing Jpeg file.")
#define M_ERR_25_SUBMSG_3        MIL_TEXT("Error opening Jpeg file.")
#define M_ERR_25_SUBMSG_4        MIL_TEXT("Unable to allocate sufficient memory.")
#define M_ERR_25_SUBMSG_5        MIL_TEXT("Image too large to save.")
#define M_ERR_25_SUBMSG_6        MIL_TEXT("Invalid Jpeg Marker.")
#define M_ERR_25_SUBMSG_7        MIL_TEXT("Bad identification information detected in file.")
#define M_ERR_25_SUBMSG_8        MIL_TEXT("Buffer to receive data does not fit with data.")
#define M_ERR_25_SUBMSG_9        MIL_TEXT("Error reading Jpeg file.")

#define M_BUFFER_FREE_ERROR      26L
#define M_ERR_26_MSG             MIL_TEXT("Buffer free operation error.")
#define M_ERR_26_SUBMSG_1        MIL_TEXT("Buffer still has child(ren) associated with it.")
#define M_ERR_26_SUBMSG_2        MIL_TEXT("Use MnatBufDestroy() on this kind of buffer.")
#define M_ERR_26_SUBMSG_3        MIL_TEXT("User attempting to free a system allocated buffer.")
#define M_ERR_26_SUBMSG_4        MIL_TEXT("Internal error, internal function attempting to free a user allocated buffer.")
#define M_ERR_26_SUBMSG_5        NO_SUBMSG
#define M_ERR_26_SUBMSG_6        NO_SUBMSG
#define M_ERR_26_SUBMSG_7        NO_SUBMSG
#define M_ERR_26_SUBMSG_8        NO_SUBMSG
#define M_ERR_26_SUBMSG_9        NO_SUBMSG

#define M_SYSTEM_FREE_ERROR      27L
#define M_ERR_27_MSG             MIL_TEXT("System free operation error.")
#define M_ERR_27_SUBMSG_1        MIL_TEXT("System still has buffer(s) associated with it.")
#define M_ERR_27_SUBMSG_2        MIL_TEXT("System still has display(s) associated with it.")
#define M_ERR_27_SUBMSG_3        MIL_TEXT("System still has digitizer(s) associated with it.")
#define M_ERR_27_SUBMSG_4        NO_SUBMSG
#define M_ERR_27_SUBMSG_5        NO_SUBMSG
#define M_ERR_27_SUBMSG_6        NO_SUBMSG
#define M_ERR_27_SUBMSG_7        NO_SUBMSG
#define M_ERR_27_SUBMSG_8        NO_SUBMSG
#define M_ERR_27_SUBMSG_9        NO_SUBMSG

#define M_FUNCTION_START_ERROR   28L
#define M_ERR_28_MSG             MIL_TEXT("Function start error.")
#define M_ERR_28_SUBMSG_1        MIL_TEXT("No application allocated.")
#define M_ERR_28_SUBMSG_2        NO_SUBMSG
#define M_ERR_28_SUBMSG_3        NO_SUBMSG
#define M_ERR_28_SUBMSG_4        NO_SUBMSG
#define M_ERR_28_SUBMSG_5        NO_SUBMSG
#define M_ERR_28_SUBMSG_6        NO_SUBMSG
#define M_ERR_28_SUBMSG_7        NO_SUBMSG
#define M_ERR_28_SUBMSG_8        NO_SUBMSG
#define M_ERR_28_SUBMSG_9        NO_SUBMSG

#define M_COMMAND_DECODER_ERROR  29L
#define M_ERR_29_MSG             MIL_TEXT("System command error.")
#define M_ERR_29_SUBMSG_1        MIL_TEXT("Requested operation not supported.")
#define M_ERR_29_SUBMSG_2        MIL_TEXT("Operation execution failed.")
#define M_ERR_29_SUBMSG_3        NO_SUBMSG
#define M_ERR_29_SUBMSG_4        NO_SUBMSG
#define M_ERR_29_SUBMSG_5        NO_SUBMSG
#define M_ERR_29_SUBMSG_6        NO_SUBMSG
#define M_ERR_29_SUBMSG_7        NO_SUBMSG
#define M_ERR_29_SUBMSG_8        NO_SUBMSG
#define M_ERR_29_SUBMSG_9        NO_SUBMSG

#define M_LABELLING_ERROR        30L
#define M_ERR_30_MSG             MIL_TEXT("Labelling error.")
#define M_ERR_30_SUBMSG_1        MIL_TEXT("Maximum number of labels reached.")
#define M_ERR_30_SUBMSG_2        MIL_TEXT("Should use a buffer of greater bit depth.")
#define M_ERR_30_SUBMSG_3        NO_SUBMSG
#define M_ERR_30_SUBMSG_4        NO_SUBMSG
#define M_ERR_30_SUBMSG_5        NO_SUBMSG
#define M_ERR_30_SUBMSG_6        NO_SUBMSG
#define M_ERR_30_SUBMSG_7        NO_SUBMSG
#define M_ERR_30_SUBMSG_8        NO_SUBMSG
#define M_ERR_30_SUBMSG_9        NO_SUBMSG

#define M_FILE_ERROR             31L
#define M_ERR_31_MSG             MIL_TEXT("File access error.")
#define M_ERR_31_SUBMSG_1        MIL_TEXT("Cannot open output file.")
#define M_ERR_31_SUBMSG_2        MIL_TEXT("Cannot write to file.")
#define M_ERR_31_SUBMSG_3        MIL_TEXT("Cannot open input file.")
#define M_ERR_31_SUBMSG_4        MIL_TEXT("Cannot read file.")
#define M_ERR_31_SUBMSG_5        MIL_TEXT("Cannot close output file.")
#define M_ERR_31_SUBMSG_6        MIL_TEXT("Cannot close input file.")
#define M_ERR_31_SUBMSG_7        MIL_TEXT("The FileFormatBufId does not represent the actual file format.")
#define M_ERR_31_SUBMSG_8        NO_SUBMSG
#define M_ERR_31_SUBMSG_9        MIL_TEXT("Not a MIL file.")

#define M_APP_FREE_ERROR         32L
#define M_ERR_32_MSG             MIL_TEXT("Application free operation error.")
#define M_ERR_32_SUBMSG_1        MIL_TEXT("Application still has system(s) associated with it.")
#define M_ERR_32_SUBMSG_2        MIL_TEXT("Default host system still has buffer(s) associated with it.")
#define M_ERR_32_SUBMSG_3        MIL_TEXT("Application still has child(ren) associated with it.")
#define M_ERR_32_SUBMSG_4        MIL_TEXT("Application was not freed.")
#define M_ERR_32_SUBMSG_5        MIL_TEXT("Application still has object(s) associated with it.")
#define M_ERR_32_SUBMSG_6        NO_SUBMSG
#define M_ERR_32_SUBMSG_7        NO_SUBMSG
#define M_ERR_32_SUBMSG_8        NO_SUBMSG
#define M_ERR_32_SUBMSG_9        NO_SUBMSG

#define M_TIFF_ERROR_2           33L
#define M_ERR_33_MSG             MIL_TEXT("TIFF File access error.")
#define M_ERR_33_SUBMSG_1        MIL_TEXT("Only 1, 8, 16 or 32 BitsPerSample supported.")
#define M_ERR_33_SUBMSG_2        MIL_TEXT("Only the Lempel-Ziv & Welch (LZW) compression supported.")
#define M_ERR_33_SUBMSG_3        MIL_TEXT("PhotometricInterp incompatible with SamplePerPixel.")
#define M_ERR_33_SUBMSG_4        MIL_TEXT("Only PlanarConfiguration 2 supported for multi-band images.")
#define M_ERR_33_SUBMSG_5        MIL_TEXT("Up to 8 Samples Per Pixel supported.")
#define M_ERR_33_SUBMSG_6        MIL_TEXT("Only identical BitsPerSample for every sample supported.")
#define M_ERR_33_SUBMSG_7        MIL_TEXT("Cannot seek in file.")
#define M_ERR_33_SUBMSG_8        MIL_TEXT("Bad file format detected.")
#define M_ERR_33_SUBMSG_9        MIL_TEXT("Invalid info requested.")

#define M_PROCESSING_ERROR       34L
#define M_ERR_34_MSG             MIL_TEXT("Processing error.")
#define M_ERR_34_SUBMSG_1        MIL_TEXT("All buffers do not have the same working system.")
#define M_ERR_34_SUBMSG_2        MIL_TEXT("Cannot find any working system between buffers.")
#define M_ERR_34_SUBMSG_3        MIL_TEXT("Cannot process a HOST buffer as a whole and a temporary buffer.")
#define M_ERR_34_SUBMSG_4        MIL_TEXT("Source buffers cannot overlap destination buffer.")
#define M_ERR_34_SUBMSG_5        MIL_TEXT("No processor on target processing system.")
#define M_ERR_34_SUBMSG_6        NO_SUBMSG
#define M_ERR_34_SUBMSG_7        NO_SUBMSG
#define M_ERR_34_SUBMSG_8        NO_SUBMSG
#define M_ERR_34_SUBMSG_9        MIL_TEXT("Not enough memory or system limitation, cannot process buffer.")

#define M_INVALID_ID             35L
#define M_ERR_35_MSG             MIL_TEXT("Invalid MIL ID.")
#define M_ERR_35_SUBMSG_1        MIL_TEXT("Invalid parameter 1.")
#define M_ERR_35_SUBMSG_2        MIL_TEXT("Invalid parameter 2.")
#define M_ERR_35_SUBMSG_3        MIL_TEXT("Invalid parameter 3.")
#define M_ERR_35_SUBMSG_4        MIL_TEXT("Invalid parameter 4.")
#define M_ERR_35_SUBMSG_5        MIL_TEXT("Invalid parameter 5.")
#define M_ERR_35_SUBMSG_6        MIL_TEXT("Invalid parameter 6.")
#define M_ERR_35_SUBMSG_7        MIL_TEXT("Invalid parameter 7.")
#define M_ERR_35_SUBMSG_8        MIL_TEXT("Invalid parameter 8.")
#define M_ERR_35_SUBMSG_9        MIL_TEXT("Invalid parameter 9.")

#define M_INVALID_NATURE         36L
#define M_ERR_36_MSG             MIL_TEXT("Inappropriate MIL ID.")
#define M_ERR_36_SUBMSG_1        MIL_TEXT("Invalid parameter 1.")
#define M_ERR_36_SUBMSG_2        MIL_TEXT("Invalid parameter 2.")
#define M_ERR_36_SUBMSG_3        MIL_TEXT("Invalid parameter 3.")
#define M_ERR_36_SUBMSG_4        MIL_TEXT("Invalid parameter 4.")
#define M_ERR_36_SUBMSG_5        MIL_TEXT("Invalid parameter 5.")
#define M_ERR_36_SUBMSG_6        MIL_TEXT("Invalid parameter 6.")
#define M_ERR_36_SUBMSG_7        MIL_TEXT("Invalid parameter 7.")
#define M_ERR_36_SUBMSG_8        MIL_TEXT("Invalid parameter 8.")
#define M_ERR_36_SUBMSG_9        MIL_TEXT("Invalid parameter 9.")

#define M_INVALID_PARAM_ERROR_2  37L
#define M_ERR_37_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_37_SUBMSG_1        MIL_TEXT("For this operation, you should supply a LUT buffer with at least 512 entries.")
#define M_ERR_37_SUBMSG_2        MIL_TEXT("For this operation the grab mode must be asynchronous.")
#define M_ERR_37_SUBMSG_3        MIL_TEXT("This type of conversion requires two 3 band buffers.")
#define M_ERR_37_SUBMSG_4        MIL_TEXT("This type of conversion requires a 3 band source buffer.")
#define M_ERR_37_SUBMSG_5        MIL_TEXT("This type of conversion requires a 3 band destination buffer.")
#define M_ERR_37_SUBMSG_6        MIL_TEXT("Invalid interpolation type specified.")
#define M_ERR_37_SUBMSG_7        MIL_TEXT("Specified center is outside buffer.")
#define M_ERR_37_SUBMSG_8        MIL_TEXT("Image buffer must be 8 bit monochrome for this operation.")
#define M_ERR_37_SUBMSG_9        MIL_TEXT("Look up table must be 1 or 3 bands, 8 bits deep and have an X size of 256 or more.")

#define M_INVALID_ATTRIBUTE      38L
#define M_ERR_38_MSG             MIL_TEXT("Invalid attributes.")
#define M_ERR_38_SUBMSG_1        MIL_TEXT("Invalid parameter 1.")
#define M_ERR_38_SUBMSG_2        MIL_TEXT("Invalid parameter 2.")
#define M_ERR_38_SUBMSG_3        MIL_TEXT("Invalid parameter 3.")
#define M_ERR_38_SUBMSG_4        MIL_TEXT("Invalid parameter 4.")
#define M_ERR_38_SUBMSG_5        MIL_TEXT("Invalid parameter 5.")
#define M_ERR_38_SUBMSG_6        MIL_TEXT("Invalid parameter 6.")
#define M_ERR_38_SUBMSG_7        MIL_TEXT("Invalid parameter 7.")
#define M_ERR_38_SUBMSG_8        MIL_TEXT("Invalid parameter 8.")
#define M_ERR_38_SUBMSG_9        MIL_TEXT("Invalid parameter 9.")

#define M_CALL_CONTEXT_ERROR     39L
#define M_ERR_39_MSG             MIL_TEXT("Call context error")
#define M_ERR_39_SUBMSG_1        MIL_TEXT("Cannot allocate temporary buffer in memory.")
#define M_ERR_39_SUBMSG_2        NO_SUBMSG
#define M_ERR_39_SUBMSG_3        NO_SUBMSG
#define M_ERR_39_SUBMSG_4        NO_SUBMSG
#define M_ERR_39_SUBMSG_5        NO_SUBMSG
#define M_ERR_39_SUBMSG_6        NO_SUBMSG
#define M_ERR_39_SUBMSG_7        NO_SUBMSG
#define M_ERR_39_SUBMSG_8        NO_SUBMSG
#define M_ERR_39_SUBMSG_9        NO_SUBMSG

#define M_DRIVER_OBSOLETE        40L
#define M_ERR_40_MSG             MIL_TEXT("MIL driver obsolete.")
#define M_ERR_40_SUBMSG_1        MIL_TEXT("Version must be 2.0 or higher.")
#define M_ERR_40_SUBMSG_2        NO_SUBMSG
#define M_ERR_40_SUBMSG_3        NO_SUBMSG
#define M_ERR_40_SUBMSG_4        NO_SUBMSG
#define M_ERR_40_SUBMSG_5        NO_SUBMSG
#define M_ERR_40_SUBMSG_6        NO_SUBMSG
#define M_ERR_40_SUBMSG_7        NO_SUBMSG
#define M_ERR_40_SUBMSG_8        NO_SUBMSG
#define M_ERR_40_SUBMSG_9        NO_SUBMSG

#define M_INVALID_PARAM_ERROR_3  41L
#define M_ERR_41_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_41_SUBMSG_1        MIL_TEXT("Parameter 1 not in supported list.")
#define M_ERR_41_SUBMSG_2        MIL_TEXT("Parameter 2 not in supported list.")
#define M_ERR_41_SUBMSG_3        MIL_TEXT("Parameter 3 not in supported list.")
#define M_ERR_41_SUBMSG_4        MIL_TEXT("Parameter 4 not in supported list.")
#define M_ERR_41_SUBMSG_5        MIL_TEXT("Parameter 5 not in supported list.")
#define M_ERR_41_SUBMSG_6        MIL_TEXT("Parameter 6 not in supported list.")
#define M_ERR_41_SUBMSG_7        MIL_TEXT("Parameter 7 not in supported list.")
#define M_ERR_41_SUBMSG_8        MIL_TEXT("Parameter 8 not in supported list.")
#define M_ERR_41_SUBMSG_9        MIL_TEXT("Parameter 9 not in supported list.")

#define M_ALLOC_ERROR_2          42L
#define M_ERR_42_MSG             MIL_TEXT("Allocation error.")
#define M_ERR_42_SUBMSG_1        MIL_TEXT("Not enough host memory to do operation.")
#define M_ERR_42_SUBMSG_2        MIL_TEXT("Invalid attribute, M_GRAB not supported on host.")
MILERR( M_ERR,42,SUBMSG,2,       MIL_TEXT("The CanGrab property is not supported on host."))
#define M_ERR_42_SUBMSG_3        MIL_TEXT("Incompatible buffer dimensions, SizeBand, SizeY and (SizeX x SizeBit) must be identical.")
MILERR( M_ERR,42,SUBMSG,3,       MIL_TEXT("Incompatible buffer dimensions, NumberOfBands, SizeY and (SizeX x DataDepth) must be identical."))
#define M_ERR_42_SUBMSG_4        MIL_TEXT("Unable to communicate with MIL MtxDMA service.")
#define M_ERR_42_SUBMSG_5        MIL_TEXT("The size of the memory allocated is zero.")
#define M_ERR_42_SUBMSG_6        MIL_TEXT("Impossible to make a band child of a Jpeg buffer.")
#define M_ERR_42_SUBMSG_7        MIL_TEXT("Cannot create a host buffer with a physical address on DOS platforms.")
#define M_ERR_42_SUBMSG_8        MIL_TEXT("Cannot create a host buffer with a physical address on Windows 9x platforms.")
#define M_ERR_42_SUBMSG_9        MIL_TEXT("Cannot allocate a host buffer in the non paged pool on DOS platforms.")

#define M_TIMER_ERROR            43L
#define M_ERR_43_MSG             MIL_TEXT("Timer error.")
#define M_ERR_43_SUBMSG_1        MIL_TEXT("Invalid timer mode specified.")
#define M_ERR_43_SUBMSG_2        MIL_TEXT("TimePtr parameter cannot be null.")
#define M_ERR_43_SUBMSG_3        MIL_TEXT("Installed hardware does not supports a high-resolution performance counter.")
#define M_ERR_43_SUBMSG_4        MIL_TEXT("Timer must be resetted prior to reading it.")
#define M_ERR_43_SUBMSG_5        NO_SUBMSG
#define M_ERR_43_SUBMSG_6        NO_SUBMSG
#define M_ERR_43_SUBMSG_7        NO_SUBMSG
#define M_ERR_43_SUBMSG_8        NO_SUBMSG
#define M_ERR_43_SUBMSG_9        NO_SUBMSG

#define M_INVALID_PARAM_ERROR_4  44L
#define M_ERR_44_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_44_SUBMSG_1        MIL_TEXT("Valid data formats for binary buffers are M_SINGLE_BAND and M_PLANAR.")
MILERR( M_ERR,44,SUBMSG,1,       MIL_TEXT("Valid formats for binary buffers are SingleBand and Planar."))
#define M_ERR_44_SUBMSG_2        MIL_TEXT("Operation not supported on float buffer.")
#define M_ERR_44_SUBMSG_3        MIL_TEXT("Destination buffer is binary, MaskValue must be equal to 0 or 1.")
#define M_ERR_44_SUBMSG_4        MIL_TEXT("Image buffer must be monochrome for this operation.")
#define M_ERR_44_SUBMSG_5        MIL_TEXT("Source buffers must be of the same type")
#define M_ERR_44_SUBMSG_6        MIL_TEXT("Integer source buffers must be unsigned")
#define M_ERR_44_SUBMSG_7        MIL_TEXT("Operation not supported on binary buffer.")
#define M_ERR_44_SUBMSG_8        MIL_TEXT("Source buffers must be of the same pixel depth.")
#define M_ERR_44_SUBMSG_9        MIL_TEXT("The width and height of the source and destination buffers must be a power of 2.")

#define M_INVALID_PARAM_ERROR_5  45L
#define M_ERR_45_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_45_SUBMSG_1        MIL_TEXT("The number of bands is not valid.")
#define M_ERR_45_SUBMSG_2        MIL_TEXT("The X dimension is not valid.")
#define M_ERR_45_SUBMSG_3        MIL_TEXT("The Y dimension is not valid.")
#define M_ERR_45_SUBMSG_4        MIL_TEXT("The pixel depth is not valid.")
#define M_ERR_45_SUBMSG_5        MIL_TEXT("The buffer attributes are not valid.")
#define M_ERR_45_SUBMSG_6        MIL_TEXT("The data type is not valid.")
#define M_ERR_45_SUBMSG_7        MIL_TEXT("Invalid FFT type specified.")
#define M_ERR_45_SUBMSG_8        MIL_TEXT("Invalid operation mode specified.")
#define M_ERR_45_SUBMSG_9        MIL_TEXT("Invalid transform specified.")

#define M_INVALID_PARAM_ERROR_6  46L
#define M_ERR_46_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_46_SUBMSG_1        MIL_TEXT("Operation not supported on 32 bits buffer.")
#define M_ERR_46_SUBMSG_2        MIL_TEXT("Invalid minimal variation specified.")
#define M_ERR_46_SUBMSG_3        MIL_TEXT("Invalid combination of control flag.")
#define M_ERR_46_SUBMSG_4        MIL_TEXT("A marker image or a minimal variation must be supplied.")
#define M_ERR_46_SUBMSG_5        MIL_TEXT("Value out of range.")
#define M_ERR_46_SUBMSG_6        MIL_TEXT("Invalid mode specified.")
#define M_ERR_46_SUBMSG_7        MIL_TEXT("The pointer should not be null.")
#define M_ERR_46_SUBMSG_8        MIL_TEXT("The buffer must be a M_IMAGE + M_COMPRESS buffer.")
#define M_ERR_46_SUBMSG_9        MIL_TEXT("Invalid compression type.")

#define M_INVALID_PARAM_ERROR_7  47L
#define M_ERR_47_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_47_SUBMSG_1        MIL_TEXT("Cannot change compression type of a single band.")
#define M_ERR_47_SUBMSG_2        MIL_TEXT("Invalid ControlFlag value.")
#define M_ERR_47_SUBMSG_3        MIL_TEXT("Compressed buffers are not supported under MIL-Lite")
#define M_ERR_47_SUBMSG_4        MIL_TEXT("Invalid source buffers.")
#define M_ERR_47_SUBMSG_5        MIL_TEXT("Invalid Q factor value.")
#define M_ERR_47_SUBMSG_6        MIL_TEXT("Invalid destination buffers.")
#define M_ERR_47_SUBMSG_7        MIL_TEXT("The second LUT must be M_NULL for M_WARP_POLYNOMIAL operation mode.")
#define M_ERR_47_SUBMSG_8        MIL_TEXT("The angle range must be lower than 360 degrees.")
#define M_ERR_47_SUBMSG_9        MIL_TEXT("Invalid First Warp parameter. Size or Type invalid.")

#define M_INVALID_PARAM_ERROR_8  48L
#define M_ERR_48_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_48_SUBMSG_1        MIL_TEXT("Source buffers must be of the same type and pixel depth.")
#define M_ERR_48_SUBMSG_2        MIL_TEXT("Destination buffers must be of the same type and pixel depth.")
#define M_ERR_48_SUBMSG_3        MIL_TEXT("Angle value must be between -360 and 360.")
#define M_ERR_48_SUBMSG_4        MIL_TEXT("Polar conversion only supported on float buffer.")
#define M_ERR_48_SUBMSG_5        MIL_TEXT("This type of conversion requires a 1 band destination buffer.")
#define M_ERR_48_SUBMSG_6        MIL_TEXT("Invalid transform type")
#define M_ERR_48_SUBMSG_7        MIL_TEXT("The M_NORMALIZE flag must be used with this transform.")
#define M_ERR_48_SUBMSG_8        MIL_TEXT("This type of conversion requires a 1 band source buffer.")
#define M_ERR_48_SUBMSG_9        MIL_TEXT("Invalid number of bytes. Use zero or a positive value.")

#define M_JPEG_ERROR_2           49L
#define M_ERR_49_MSG             MIL_TEXT("JPEG handler general error.")
#define M_ERR_49_SUBMSG_1        MIL_TEXT("Vertical sampling factor of more than 4 not supported.")
#define M_ERR_49_SUBMSG_2        MIL_TEXT("MIL supports only 1-band and 3-band buffers.")
#define M_ERR_49_SUBMSG_3        MIL_TEXT("MIL only supports sequential baseline DCT jpeg and lossless jpeg files.")
#define M_ERR_49_SUBMSG_4        MIL_TEXT("Point transform not supported.")
#define M_ERR_49_SUBMSG_5        MIL_TEXT("Reading beyond the available data.")
#define M_ERR_49_SUBMSG_6        MIL_TEXT("End Of Image marker before the end of the file.")
#define M_ERR_49_SUBMSG_7        MIL_TEXT("16-bit quantization table not supported.")
#define M_ERR_49_SUBMSG_8        MIL_TEXT("Horizontal sampling factor of more than 4 not supported.")
#define M_ERR_49_SUBMSG_9        MIL_TEXT("Sampling factors do not correspond to any supported format.")

#define M_INVALID_PARAM_ERROR_9  50L
#define M_ERR_50_MSG             MIL_TEXT("Invalid parameter.")
#define M_ERR_50_SUBMSG_1        MIL_TEXT("Inquire type not supported.")
#define M_ERR_50_SUBMSG_2        MIL_TEXT("The look up table must have a Y size of 1.")
#define M_ERR_50_SUBMSG_3        MIL_TEXT("The number of pixels should be a positive value.")
#define M_ERR_50_SUBMSG_4        MIL_TEXT("The destination buffer cannot be 1-bit.")
#define M_ERR_50_SUBMSG_5        MIL_TEXT("SaturationSizeBit must be 1, 8, 16 or 32.")
#define M_ERR_50_SUBMSG_6        MIL_TEXT("SaturationType must be M_SIGNED, M_UNSIGNED or M_FLOAT.")
#define M_ERR_50_SUBMSG_7        MIL_TEXT("Invalid combinaison of SaturationType and SizeBit.")
#define M_ERR_50_SUBMSG_8        MIL_TEXT("YUV buffers must be M_UNSIGNED.")
#define M_ERR_50_SUBMSG_9        MIL_TEXT("Invalid filename: Filename length must be at least 1.")

#define M_AVI_FILE_ERROR         51L
#define M_ERR_51_MSG             MIL_TEXT("AVI file error.")
#define M_ERR_51_SUBMSG_1        MIL_TEXT("Error creating AVI file.")
#define M_ERR_51_SUBMSG_2        MIL_TEXT("Error writing into AVI file.")
#define M_ERR_51_SUBMSG_3        MIL_TEXT("File format not supported.")
#define M_ERR_51_SUBMSG_4        MIL_TEXT("Incompatible format between file and images.")
#define M_ERR_51_SUBMSG_5        MIL_TEXT("Error opening AVI file.")
#define M_ERR_51_SUBMSG_6        MIL_TEXT("One of the buffers to export is empty.")
#define M_ERR_51_SUBMSG_7        MIL_TEXT("Incompatible Jpeg format between the buffers and the file type requested.")
#define M_ERR_51_SUBMSG_8        MIL_TEXT("The number of bands should be the same for all the buffers in the sequence.")
#define M_ERR_51_SUBMSG_9        MIL_TEXT("The depth should be the same for all the buffers in the sequence.")

#define M_DMA_ERROR              52L
#define M_ERR_52_MSG             MIL_TEXT("Error using Matrox Dma service")
#define M_ERR_52_SUBMSG_1        MIL_TEXT("Cannot open the Matrox Dma manager")
#define M_ERR_52_SUBMSG_2        MIL_TEXT("Cannot acces PCI data")
#define M_ERR_52_SUBMSG_3        MIL_TEXT("Cannot perform this operation on the Host system with MS_DOS.")
#define M_ERR_52_SUBMSG_4        MIL_TEXT("Cannot perform this operation on the Host system with Windows 95/98.")
#define M_ERR_52_SUBMSG_5        MIL_TEXT("Cannot acces hook information")
#define M_ERR_52_SUBMSG_6        MIL_TEXT("Can perform this operation only on Default Host")
#define M_ERR_52_SUBMSG_7        MIL_TEXT("Unable to recover info on Dma pool")
#define M_ERR_52_SUBMSG_8        MIL_TEXT("Cannot perform this operation on the Host system with Windows 95.")
#define M_ERR_52_SUBMSG_9        NO_SUBMSG

#define M_BMP_ERROR_3            53L
#define M_ERR_53_MSG             MIL_TEXT("BMP handler general error.")
#define M_ERR_53_SUBMSG_1        MIL_TEXT("MIL does not support a bit count of zero in BMP files.")
#define M_ERR_53_SUBMSG_2        MIL_TEXT("MIL does not support 1-bit BMP files.")
#define M_ERR_53_SUBMSG_3        MIL_TEXT("MIL does not support 4-bit BMP files.")
#define M_ERR_53_SUBMSG_4        MIL_TEXT("Run Length Encoding ( RLE ) compression not supported.")
#define M_ERR_53_SUBMSG_5        NO_SUBMSG
#define M_ERR_53_SUBMSG_6        NO_SUBMSG
#define M_ERR_53_SUBMSG_7        NO_SUBMSG
#define M_ERR_53_SUBMSG_8        NO_SUBMSG
#define M_ERR_53_SUBMSG_9        NO_SUBMSG

#define M_JPEG_ERROR_3           54L
#define M_ERR_54_MSG             MIL_TEXT("JPEG handler general error.")
#define M_ERR_54_SUBMSG_1        MIL_TEXT("Invalid Jpeg data.")
#define M_ERR_54_SUBMSG_2        MIL_TEXT("Invalid data for a MTRX specific marker.")
#define M_ERR_54_SUBMSG_3        MIL_TEXT("Extended Sequential DCT not supported in MIL.")
#define M_ERR_54_SUBMSG_4        MIL_TEXT("Progressive DCT not supported in MIL.")
#define M_ERR_54_SUBMSG_5        MIL_TEXT("YUV9 Packed images not supported.")
#define M_ERR_54_SUBMSG_6        MIL_TEXT("YUV12 Packed images not supported.")
#define M_ERR_54_SUBMSG_7        MIL_TEXT("YUV24 Packed images not supported.")
#define M_ERR_54_SUBMSG_8        MIL_TEXT("Invalid data. EOI marker not found.")
#define M_ERR_54_SUBMSG_9        MIL_TEXT("Cannot create or open file in write mode.")

#define M_ALLOC_ERROR_3          55L
#define M_ERR_55_MSG             MIL_TEXT("Allocation error.")
#define M_ERR_55_SUBMSG_1        MIL_TEXT("Cannot allocate a host buffer in the non paged pool on Windows 9x platforms.")
#define M_ERR_55_SUBMSG_2        MIL_TEXT("Cannot create a buffer with physical address.")
#define M_ERR_55_SUBMSG_3        MIL_TEXT("Cannot allocate a M_COMPRESS buffer with the M_DISP attribute.")
#define M_ERR_55_SUBMSG_4        MIL_TEXT("Cannot allocate a M_COMPRESS buffer with the M_SIGNED type.")
#define M_ERR_55_SUBMSG_5        MIL_TEXT("Interlaced buffers should have a height of at least 2.")
#define M_ERR_55_SUBMSG_6        NO_SUBMSG
#define M_ERR_55_SUBMSG_7        NO_SUBMSG
#define M_ERR_55_SUBMSG_8        NO_SUBMSG
#define M_ERR_55_SUBMSG_9        NO_SUBMSG

#define M_LIMITATION_ERROR       56L
#define M_ERR_56_MSG             MIL_TEXT("Limitation error.")
#define M_ERR_56_SUBMSG_1        MIL_TEXT("This operation cannot be performed on a section of a compressed buffer.")
#define M_ERR_56_SUBMSG_2        MIL_TEXT("This operation cannot be performed on a child of a compressed buffer.")
#define M_ERR_56_SUBMSG_3        MIL_TEXT("This operation cannot be performed on a section of a YUV buffer.")
#define M_ERR_56_SUBMSG_4        MIL_TEXT("This operation cannot be performed on a child of a YUV buffer.")
#define M_ERR_56_SUBMSG_5        MIL_TEXT("This operation cannot be performed on a section of a M_PACKED buffer.")
#define M_ERR_56_SUBMSG_6        MIL_TEXT("This operation cannot be performed on a child of a M_PACKED buffer.")
#define M_ERR_56_SUBMSG_7        MIL_TEXT("This operation cannot be performed on a section of a M_PLANAR buffer.")
#define M_ERR_56_SUBMSG_8        MIL_TEXT("This operation cannot be performed on a child of a M_PLANAR buffer.")
#define M_ERR_56_SUBMSG_9        NO_SUBMSG

#define M_OPERATION_ERROR_2      57L
#define M_ERR_57_MSG             MIL_TEXT("Operation error.")
#define M_ERR_57_SUBMSG_1        MIL_TEXT("Pitch must be a multiple of 4 pixels.")
#define M_ERR_57_SUBMSG_2        NO_SUBMSG
#define M_ERR_57_SUBMSG_3        NO_SUBMSG
#define M_ERR_57_SUBMSG_4        NO_SUBMSG
#define M_ERR_57_SUBMSG_5        NO_SUBMSG
#define M_ERR_57_SUBMSG_6        NO_SUBMSG
#define M_ERR_57_SUBMSG_7        NO_SUBMSG
#define M_ERR_57_SUBMSG_8        NO_SUBMSG
#define M_ERR_57_SUBMSG_9        NO_SUBMSG

#define M_LICENSING_ERROR        58L
#define M_ERR_58_MSG             MIL_TEXT("License error")
#define M_ERR_58_SUBMSG_1        MIL_TEXT("No valid license found")
#define M_ERR_58_SUBMSG_2        MIL_TEXT("License watchdog timed out")
#define M_ERR_58_SUBMSG_3        MIL_TEXT("Could not initialize machine code")
#define M_ERR_58_SUBMSG_4        MIL_TEXT("Could not get machine code")
#define M_ERR_58_SUBMSG_5        MIL_TEXT("Could not lock machine code")
#define M_ERR_58_SUBMSG_6        MIL_TEXT("Could not load milprot.dll")
#define M_ERR_58_SUBMSG_7        MIL_TEXT("Could not get address of function in milprot.dll")
#define M_ERR_58_SUBMSG_8        MIL_TEXT("You need a MIL 6.1 or newer run-time license to use this system")
#define M_ERR_58_SUBMSG_9        NO_SUBMSG

#define M_AVI_FILE_ERROR_2       59L
#define M_ERR_59_MSG             MIL_TEXT("AVI file error.")
#define M_ERR_59_SUBMSG_1        MIL_TEXT("Cannot export a sequence of compressed child buffers.")
#define M_ERR_59_SUBMSG_2        MIL_TEXT("The compression type should be the same for all the buffers in the sequence.")
#define M_ERR_59_SUBMSG_3        MIL_TEXT("The internal format shouls be the same for all the buffers in the sequence.")
#define M_ERR_59_SUBMSG_4        MIL_TEXT("The file format requested for the M_APPEND is not the same as the file format of the file to append into.")
#define M_ERR_59_SUBMSG_5        MIL_TEXT("The size of the images should all be the same." )
#define M_ERR_59_SUBMSG_6        MIL_TEXT("Impossible to write into a closed file.")
#define M_ERR_59_SUBMSG_7        MIL_TEXT("Error creating AVI stream.")
#define M_ERR_59_SUBMSG_8        MIL_TEXT("The file is already opened.")
#define M_ERR_59_SUBMSG_9        MIL_TEXT("Impossible to read from a closed file.")

#define M_JPEG_COMPRESS_ERROR_3  60L
#define M_ERR_60_MSG             MIL_TEXT("Jpeg compression error.")
#define M_ERR_60_SUBMSG_1        MIL_TEXT("Cannot allocate 3-band M_JPEG_LOSSLESS_INTERLACED buffer.")
#define M_ERR_60_SUBMSG_2        MIL_TEXT("In lossless, the RestartInterval multiplied by the number of \ncolumns in the buffer must fit on 16 bits ( smaller than 65535 ).")
#define M_ERR_60_SUBMSG_3        MIL_TEXT("The restart interval must fit on 16 bits ( smaller than 65535 ).")
#define M_ERR_60_SUBMSG_4        MIL_TEXT("Only JPEG lossless buffers can have predictors.")
#define M_ERR_60_SUBMSG_5        MIL_TEXT("Luminance parameters are only allowed for YUV buffers.")
#define M_ERR_60_SUBMSG_6        MIL_TEXT("Chrominance parameters are only allowed for YUV buffers.")
#define M_ERR_60_SUBMSG_7        MIL_TEXT("AC tables and quantization parameters are only allowed \nfor JPEG lossy buffers.")
#define M_ERR_60_SUBMSG_8        MIL_TEXT("For YUV buffers, specific luminance or chrominance \nflags must be used.")
#define M_ERR_60_SUBMSG_9        NO_SUBMSG

#define M_AVI_FILE_ERROR_3       61L
#define M_ERR_61_MSG             MIL_TEXT("AVI file error.")
#define M_ERR_61_SUBMSG_1        MIL_TEXT("Error reading from the AVI file.")
#define M_ERR_61_SUBMSG_2        MIL_TEXT("Cannot read after the last frame.")
#define M_ERR_61_SUBMSG_3        NO_SUBMSG
#define M_ERR_61_SUBMSG_4        NO_SUBMSG
#define M_ERR_61_SUBMSG_5        NO_SUBMSG
#define M_ERR_61_SUBMSG_6        NO_SUBMSG
#define M_ERR_61_SUBMSG_7        NO_SUBMSG
#define M_ERR_61_SUBMSG_8        NO_SUBMSG
#define M_ERR_61_SUBMSG_9        NO_SUBMSG

#define M_USER_BIT_CONFIG_ERROR  62L
#define M_ERR_62_MSG             MIL_TEXT("Auxiliary I/O pins configuration Error:")
#define M_ERR_62_SUBMSG_1        MIL_TEXT("4Sight not detected, or pins already allocated on an other system.")
#define M_ERR_62_SUBMSG_2        MIL_TEXT("Cannot write register, register is read only.")
#define M_ERR_62_SUBMSG_3        MIL_TEXT("Cannot read register, register is write only.")
#define M_ERR_62_SUBMSG_4        MIL_TEXT("Invalid data or register.")
#define M_ERR_62_SUBMSG_5        MIL_TEXT("Unkown Error.")
#define M_ERR_62_SUBMSG_6        NO_SUBMSG
#define M_ERR_62_SUBMSG_7        NO_SUBMSG
#define M_ERR_62_SUBMSG_8        NO_SUBMSG
#define M_ERR_62_SUBMSG_9        NO_SUBMSG

#define M_USER_BIT_ERROR         63L
#define M_ERR_63_MSG             MIL_TEXT("Invalid parameter error:")
#define M_ERR_63_SUBMSG_1        MIL_TEXT("Cannot write selected pin, pin is in input mode.")
#define M_ERR_63_SUBMSG_2        MIL_TEXT("Cannot enable interrupt, pin is in output mode.")
#define M_ERR_63_SUBMSG_3        MIL_TEXT("Cannot hook to selected pin, pin is not configured as an interrupt.")
#define M_ERR_63_SUBMSG_4        MIL_TEXT("Control type not supported.")
#define M_ERR_63_SUBMSG_5        MIL_TEXT("Control value not supported.")
#define M_ERR_63_SUBMSG_6        MIL_TEXT("Inquire type not supported.")
#define M_ERR_63_SUBMSG_7        MIL_TEXT("Invalid bit mask.")
#define M_ERR_63_SUBMSG_8        MIL_TEXT("Cannot hook or set interrupt.")
#define M_ERR_63_SUBMSG_9        MIL_TEXT("No interrupt line has been assigned to auxiliary IO.")

#define M_TIFF_ERROR_3           64L
#define M_ERR_64_MSG             MIL_TEXT("TIFF File access error.")
#define M_ERR_64_SUBMSG_1        MIL_TEXT("Error recording tag")
#define M_ERR_64_SUBMSG_2        MIL_TEXT("LZW compression not supported in multi strips TIFF file")
#define M_ERR_64_SUBMSG_3        NO_SUBMSG
#define M_ERR_64_SUBMSG_4        NO_SUBMSG
#define M_ERR_64_SUBMSG_5        NO_SUBMSG
#define M_ERR_64_SUBMSG_6        NO_SUBMSG
#define M_ERR_64_SUBMSG_7        NO_SUBMSG
#define M_ERR_64_SUBMSG_8        NO_SUBMSG
#define M_ERR_64_SUBMSG_9        NO_SUBMSG

#define M_MIL_FILE_ERROR_4       65L
#define M_ERR_65_MSG             MIL_TEXT("MIL File access error.")
#define M_ERR_65_SUBMSG_1        MIL_TEXT("Error recording tag")
#define M_ERR_65_SUBMSG_2        MIL_TEXT("LZW compression not supported in multi strips MIL file")
#define M_ERR_65_SUBMSG_3        NO_SUBMSG
#define M_ERR_65_SUBMSG_4        NO_SUBMSG
#define M_ERR_65_SUBMSG_5        NO_SUBMSG
#define M_ERR_65_SUBMSG_6        NO_SUBMSG
#define M_ERR_65_SUBMSG_7        NO_SUBMSG
#define M_ERR_65_SUBMSG_8        NO_SUBMSG
#define M_ERR_65_SUBMSG_9        NO_SUBMSG

#define M_JPEG_ERROR_4           66L
#define M_ERR_66_MSG             MIL_TEXT("JPEG handler general error.")
#define M_ERR_66_SUBMSG_1        MIL_TEXT("Second field of interlaced image not found.")
#define M_ERR_66_SUBMSG_2        NO_SUBMSG
#define M_ERR_66_SUBMSG_3        NO_SUBMSG
#define M_ERR_66_SUBMSG_4        NO_SUBMSG
#define M_ERR_66_SUBMSG_5        NO_SUBMSG
#define M_ERR_66_SUBMSG_6        NO_SUBMSG
#define M_ERR_66_SUBMSG_7        NO_SUBMSG
#define M_ERR_66_SUBMSG_8        NO_SUBMSG
#define M_ERR_66_SUBMSG_9        NO_SUBMSG

#define M_XX67XX_ERROR           67L
#define M_ERR_67_MSG             NO_MSG
#define M_ERR_67_SUBMSG_1        NO_SUBMSG
#define M_ERR_67_SUBMSG_2        NO_SUBMSG
#define M_ERR_67_SUBMSG_3        NO_SUBMSG
#define M_ERR_67_SUBMSG_4        NO_SUBMSG
#define M_ERR_67_SUBMSG_5        NO_SUBMSG
#define M_ERR_67_SUBMSG_6        NO_SUBMSG
#define M_ERR_67_SUBMSG_7        NO_SUBMSG
#define M_ERR_67_SUBMSG_8        NO_SUBMSG
#define M_ERR_67_SUBMSG_9        NO_SUBMSG

#define M_XX68XX_ERROR           68L
#define M_ERR_68_MSG             NO_MSG
#define M_ERR_68_SUBMSG_1        NO_SUBMSG
#define M_ERR_68_SUBMSG_2        NO_SUBMSG
#define M_ERR_68_SUBMSG_3        NO_SUBMSG
#define M_ERR_68_SUBMSG_4        NO_SUBMSG
#define M_ERR_68_SUBMSG_5        NO_SUBMSG
#define M_ERR_68_SUBMSG_6        NO_SUBMSG
#define M_ERR_68_SUBMSG_7        NO_SUBMSG
#define M_ERR_68_SUBMSG_8        NO_SUBMSG
#define M_ERR_68_SUBMSG_9        NO_SUBMSG

#define M_XX69XX_ERROR           69L
#define M_ERR_69_MSG             NO_MSG
#define M_ERR_69_SUBMSG_1        NO_SUBMSG
#define M_ERR_69_SUBMSG_2        NO_SUBMSG
#define M_ERR_69_SUBMSG_3        NO_SUBMSG
#define M_ERR_69_SUBMSG_4        NO_SUBMSG
#define M_ERR_69_SUBMSG_5        NO_SUBMSG
#define M_ERR_69_SUBMSG_6        NO_SUBMSG
#define M_ERR_69_SUBMSG_7        NO_SUBMSG
#define M_ERR_69_SUBMSG_8        NO_SUBMSG
#define M_ERR_69_SUBMSG_9        NO_SUBMSG

#define M_XX70XX_ERROR           70L
#define M_ERR_70_MSG             NO_MSG
#define M_ERR_70_SUBMSG_1        NO_SUBMSG
#define M_ERR_70_SUBMSG_2        NO_SUBMSG
#define M_ERR_70_SUBMSG_3        NO_SUBMSG
#define M_ERR_70_SUBMSG_4        NO_SUBMSG
#define M_ERR_70_SUBMSG_5        NO_SUBMSG
#define M_ERR_70_SUBMSG_6        NO_SUBMSG
#define M_ERR_70_SUBMSG_7        NO_SUBMSG
#define M_ERR_70_SUBMSG_8        NO_SUBMSG
#define M_ERR_70_SUBMSG_9        NO_SUBMSG

#define M_XX71XX_ERROR           71L
#define M_ERR_71_MSG             NO_MSG
#define M_ERR_71_SUBMSG_1        NO_SUBMSG
#define M_ERR_71_SUBMSG_2        NO_SUBMSG
#define M_ERR_71_SUBMSG_3        NO_SUBMSG
#define M_ERR_71_SUBMSG_4        NO_SUBMSG
#define M_ERR_71_SUBMSG_5        NO_SUBMSG
#define M_ERR_71_SUBMSG_6        NO_SUBMSG
#define M_ERR_71_SUBMSG_7        NO_SUBMSG
#define M_ERR_71_SUBMSG_8        NO_SUBMSG
#define M_ERR_71_SUBMSG_9        NO_SUBMSG

#define M_XX72XX_ERROR           72L
#define M_ERR_72_MSG             NO_MSG
#define M_ERR_72_SUBMSG_1        NO_SUBMSG
#define M_ERR_72_SUBMSG_2        NO_SUBMSG
#define M_ERR_72_SUBMSG_3        NO_SUBMSG
#define M_ERR_72_SUBMSG_4        NO_SUBMSG
#define M_ERR_72_SUBMSG_5        NO_SUBMSG
#define M_ERR_72_SUBMSG_6        NO_SUBMSG
#define M_ERR_72_SUBMSG_7        NO_SUBMSG
#define M_ERR_72_SUBMSG_8        NO_SUBMSG
#define M_ERR_72_SUBMSG_9        NO_SUBMSG

#define M_XX73XX_ERROR           73L
#define M_ERR_73_MSG             NO_MSG
#define M_ERR_73_SUBMSG_1        NO_SUBMSG
#define M_ERR_73_SUBMSG_2        NO_SUBMSG
#define M_ERR_73_SUBMSG_3        NO_SUBMSG
#define M_ERR_73_SUBMSG_4        NO_SUBMSG
#define M_ERR_73_SUBMSG_5        NO_SUBMSG
#define M_ERR_73_SUBMSG_6        NO_SUBMSG
#define M_ERR_73_SUBMSG_7        NO_SUBMSG
#define M_ERR_73_SUBMSG_8        NO_SUBMSG
#define M_ERR_73_SUBMSG_9        NO_SUBMSG

#define M_XX74XX_ERROR           74L
#define M_ERR_74_MSG             NO_MSG
#define M_ERR_74_SUBMSG_1        NO_SUBMSG
#define M_ERR_74_SUBMSG_2        NO_SUBMSG
#define M_ERR_74_SUBMSG_3        NO_SUBMSG
#define M_ERR_74_SUBMSG_4        NO_SUBMSG
#define M_ERR_74_SUBMSG_5        NO_SUBMSG
#define M_ERR_74_SUBMSG_6        NO_SUBMSG
#define M_ERR_74_SUBMSG_7        NO_SUBMSG
#define M_ERR_74_SUBMSG_8        NO_SUBMSG
#define M_ERR_74_SUBMSG_9        NO_SUBMSG

#define M_XX75XX_ERROR           75L
#define M_ERR_75_MSG             NO_MSG
#define M_ERR_75_SUBMSG_1        NO_SUBMSG
#define M_ERR_75_SUBMSG_2        NO_SUBMSG
#define M_ERR_75_SUBMSG_3        NO_SUBMSG
#define M_ERR_75_SUBMSG_4        NO_SUBMSG
#define M_ERR_75_SUBMSG_5        NO_SUBMSG
#define M_ERR_75_SUBMSG_6        NO_SUBMSG
#define M_ERR_75_SUBMSG_7        NO_SUBMSG
#define M_ERR_75_SUBMSG_8        NO_SUBMSG
#define M_ERR_75_SUBMSG_9        NO_SUBMSG

#define M_XX76XX_ERROR           76L
#define M_ERR_76_MSG             NO_MSG
#define M_ERR_76_SUBMSG_1        NO_SUBMSG
#define M_ERR_76_SUBMSG_2        NO_SUBMSG
#define M_ERR_76_SUBMSG_3        NO_SUBMSG
#define M_ERR_76_SUBMSG_4        NO_SUBMSG
#define M_ERR_76_SUBMSG_5        NO_SUBMSG
#define M_ERR_76_SUBMSG_6        NO_SUBMSG
#define M_ERR_76_SUBMSG_7        NO_SUBMSG
#define M_ERR_76_SUBMSG_8        NO_SUBMSG
#define M_ERR_76_SUBMSG_9        NO_SUBMSG

#define M_XX77XX_ERROR           77L
#define M_ERR_77_MSG             NO_MSG
#define M_ERR_77_SUBMSG_1        NO_SUBMSG
#define M_ERR_77_SUBMSG_2        NO_SUBMSG
#define M_ERR_77_SUBMSG_3        NO_SUBMSG
#define M_ERR_77_SUBMSG_4        NO_SUBMSG
#define M_ERR_77_SUBMSG_5        NO_SUBMSG
#define M_ERR_77_SUBMSG_6        NO_SUBMSG
#define M_ERR_77_SUBMSG_7        NO_SUBMSG
#define M_ERR_77_SUBMSG_8        NO_SUBMSG
#define M_ERR_77_SUBMSG_9        NO_SUBMSG

#define M_XX78XX_ERROR           78L
#define M_ERR_78_MSG             NO_MSG
#define M_ERR_78_SUBMSG_1        NO_SUBMSG
#define M_ERR_78_SUBMSG_2        NO_SUBMSG
#define M_ERR_78_SUBMSG_3        NO_SUBMSG
#define M_ERR_78_SUBMSG_4        NO_SUBMSG
#define M_ERR_78_SUBMSG_5        NO_SUBMSG
#define M_ERR_78_SUBMSG_6        NO_SUBMSG
#define M_ERR_78_SUBMSG_7        NO_SUBMSG
#define M_ERR_78_SUBMSG_8        NO_SUBMSG
#define M_ERR_78_SUBMSG_9        NO_SUBMSG

#define M_XX79XX_ERROR           79L
#define M_ERR_79_MSG             NO_MSG
#define M_ERR_79_SUBMSG_1        NO_SUBMSG
#define M_ERR_79_SUBMSG_2        NO_SUBMSG
#define M_ERR_79_SUBMSG_3        NO_SUBMSG
#define M_ERR_79_SUBMSG_4        NO_SUBMSG
#define M_ERR_79_SUBMSG_5        NO_SUBMSG
#define M_ERR_79_SUBMSG_6        NO_SUBMSG
#define M_ERR_79_SUBMSG_7        NO_SUBMSG
#define M_ERR_79_SUBMSG_8        NO_SUBMSG
#define M_ERR_79_SUBMSG_9        NO_SUBMSG

#define M_XX80XX_ERROR           80L
#define M_ERR_80_MSG             NO_MSG
#define M_ERR_80_SUBMSG_1        NO_SUBMSG
#define M_ERR_80_SUBMSG_2        NO_SUBMSG
#define M_ERR_80_SUBMSG_3        NO_SUBMSG
#define M_ERR_80_SUBMSG_4        NO_SUBMSG
#define M_ERR_80_SUBMSG_5        NO_SUBMSG
#define M_ERR_80_SUBMSG_6        NO_SUBMSG
#define M_ERR_80_SUBMSG_7        NO_SUBMSG
#define M_ERR_80_SUBMSG_8        NO_SUBMSG
#define M_ERR_80_SUBMSG_9        NO_SUBMSG

#define M_XX81XX_ERROR           81L
#define M_ERR_81_MSG             NO_MSG
#define M_ERR_81_SUBMSG_1        NO_SUBMSG
#define M_ERR_81_SUBMSG_2        NO_SUBMSG
#define M_ERR_81_SUBMSG_3        NO_SUBMSG
#define M_ERR_81_SUBMSG_4        NO_SUBMSG
#define M_ERR_81_SUBMSG_5        NO_SUBMSG
#define M_ERR_81_SUBMSG_6        NO_SUBMSG
#define M_ERR_81_SUBMSG_7        NO_SUBMSG
#define M_ERR_81_SUBMSG_8        NO_SUBMSG
#define M_ERR_81_SUBMSG_9        NO_SUBMSG

#define M_XX82XX_ERROR           82L
#define M_ERR_82_MSG             NO_MSG
#define M_ERR_82_SUBMSG_1        NO_SUBMSG
#define M_ERR_82_SUBMSG_2        NO_SUBMSG
#define M_ERR_82_SUBMSG_3        NO_SUBMSG
#define M_ERR_82_SUBMSG_4        NO_SUBMSG
#define M_ERR_82_SUBMSG_5        NO_SUBMSG
#define M_ERR_82_SUBMSG_6        NO_SUBMSG
#define M_ERR_82_SUBMSG_7        NO_SUBMSG
#define M_ERR_82_SUBMSG_8        NO_SUBMSG
#define M_ERR_82_SUBMSG_9        NO_SUBMSG

#define M_XX83XX_ERROR           83L
#define M_ERR_83_MSG             NO_MSG
#define M_ERR_83_SUBMSG_1        NO_SUBMSG
#define M_ERR_83_SUBMSG_2        NO_SUBMSG
#define M_ERR_83_SUBMSG_3        NO_SUBMSG
#define M_ERR_83_SUBMSG_4        NO_SUBMSG
#define M_ERR_83_SUBMSG_5        NO_SUBMSG
#define M_ERR_83_SUBMSG_6        NO_SUBMSG
#define M_ERR_83_SUBMSG_7        NO_SUBMSG
#define M_ERR_83_SUBMSG_8        NO_SUBMSG
#define M_ERR_83_SUBMSG_9        NO_SUBMSG

#define M_XX84XX_ERROR           84L
#define M_ERR_84_MSG             NO_MSG
#define M_ERR_84_SUBMSG_1        NO_SUBMSG
#define M_ERR_84_SUBMSG_2        NO_SUBMSG
#define M_ERR_84_SUBMSG_3        NO_SUBMSG
#define M_ERR_84_SUBMSG_4        NO_SUBMSG
#define M_ERR_84_SUBMSG_5        NO_SUBMSG
#define M_ERR_84_SUBMSG_6        NO_SUBMSG
#define M_ERR_84_SUBMSG_7        NO_SUBMSG
#define M_ERR_84_SUBMSG_8        NO_SUBMSG
#define M_ERR_84_SUBMSG_9        NO_SUBMSG

#define M_XX85XX_ERROR           85L
#define M_ERR_85_MSG             NO_MSG
#define M_ERR_85_SUBMSG_1        NO_SUBMSG
#define M_ERR_85_SUBMSG_2        NO_SUBMSG
#define M_ERR_85_SUBMSG_3        NO_SUBMSG
#define M_ERR_85_SUBMSG_4        NO_SUBMSG
#define M_ERR_85_SUBMSG_5        NO_SUBMSG
#define M_ERR_85_SUBMSG_6        NO_SUBMSG
#define M_ERR_85_SUBMSG_7        NO_SUBMSG
#define M_ERR_85_SUBMSG_8        NO_SUBMSG
#define M_ERR_85_SUBMSG_9        NO_SUBMSG

#define M_XX86XX_ERROR           86L
#define M_ERR_86_MSG             NO_MSG
#define M_ERR_86_SUBMSG_1        NO_SUBMSG
#define M_ERR_86_SUBMSG_2        NO_SUBMSG
#define M_ERR_86_SUBMSG_3        NO_SUBMSG
#define M_ERR_86_SUBMSG_4        NO_SUBMSG
#define M_ERR_86_SUBMSG_5        NO_SUBMSG
#define M_ERR_86_SUBMSG_6        NO_SUBMSG
#define M_ERR_86_SUBMSG_7        NO_SUBMSG
#define M_ERR_86_SUBMSG_8        NO_SUBMSG
#define M_ERR_86_SUBMSG_9        NO_SUBMSG

#define M_XX87XX_ERROR           87L
#define M_ERR_87_MSG             NO_MSG
#define M_ERR_87_SUBMSG_1        NO_SUBMSG
#define M_ERR_87_SUBMSG_2        NO_SUBMSG
#define M_ERR_87_SUBMSG_3        NO_SUBMSG
#define M_ERR_87_SUBMSG_4        NO_SUBMSG
#define M_ERR_87_SUBMSG_5        NO_SUBMSG
#define M_ERR_87_SUBMSG_6        NO_SUBMSG
#define M_ERR_87_SUBMSG_7        NO_SUBMSG
#define M_ERR_87_SUBMSG_8        NO_SUBMSG
#define M_ERR_87_SUBMSG_9        NO_SUBMSG

#define M_XX88XX_ERROR           88L
#define M_ERR_88_MSG             NO_MSG
#define M_ERR_88_SUBMSG_1        NO_SUBMSG
#define M_ERR_88_SUBMSG_2        NO_SUBMSG
#define M_ERR_88_SUBMSG_3        NO_SUBMSG
#define M_ERR_88_SUBMSG_4        NO_SUBMSG
#define M_ERR_88_SUBMSG_5        NO_SUBMSG
#define M_ERR_88_SUBMSG_6        NO_SUBMSG
#define M_ERR_88_SUBMSG_7        NO_SUBMSG
#define M_ERR_88_SUBMSG_8        NO_SUBMSG
#define M_ERR_88_SUBMSG_9        NO_SUBMSG

#define M_XX89XX_ERROR           89L
#define M_ERR_89_MSG             NO_MSG
#define M_ERR_89_SUBMSG_1        NO_SUBMSG
#define M_ERR_89_SUBMSG_2        NO_SUBMSG
#define M_ERR_89_SUBMSG_3        NO_SUBMSG
#define M_ERR_89_SUBMSG_4        NO_SUBMSG
#define M_ERR_89_SUBMSG_5        NO_SUBMSG
#define M_ERR_89_SUBMSG_6        NO_SUBMSG
#define M_ERR_89_SUBMSG_7        NO_SUBMSG
#define M_ERR_89_SUBMSG_8        NO_SUBMSG
#define M_ERR_89_SUBMSG_9        NO_SUBMSG

#define M_XX90XX_ERROR           90L
#define M_ERR_90_MSG             NO_MSG
#define M_ERR_90_SUBMSG_1        NO_SUBMSG
#define M_ERR_90_SUBMSG_2        NO_SUBMSG
#define M_ERR_90_SUBMSG_3        NO_SUBMSG
#define M_ERR_90_SUBMSG_4        NO_SUBMSG
#define M_ERR_90_SUBMSG_5        NO_SUBMSG
#define M_ERR_90_SUBMSG_6        NO_SUBMSG
#define M_ERR_90_SUBMSG_7        NO_SUBMSG
#define M_ERR_90_SUBMSG_8        NO_SUBMSG
#define M_ERR_90_SUBMSG_9        NO_SUBMSG

#define M_XX91XX_ERROR           91L
#define M_ERR_91_MSG             NO_MSG
#define M_ERR_91_SUBMSG_1        NO_SUBMSG
#define M_ERR_91_SUBMSG_2        NO_SUBMSG
#define M_ERR_91_SUBMSG_3        NO_SUBMSG
#define M_ERR_91_SUBMSG_4        NO_SUBMSG
#define M_ERR_91_SUBMSG_5        NO_SUBMSG
#define M_ERR_91_SUBMSG_6        NO_SUBMSG
#define M_ERR_91_SUBMSG_7        NO_SUBMSG
#define M_ERR_91_SUBMSG_8        NO_SUBMSG
#define M_ERR_91_SUBMSG_9        NO_SUBMSG

#define M_XX92XX_ERROR           92L
#define M_ERR_92_MSG             NO_MSG
#define M_ERR_92_SUBMSG_1        NO_SUBMSG
#define M_ERR_92_SUBMSG_2        NO_SUBMSG
#define M_ERR_92_SUBMSG_3        NO_SUBMSG
#define M_ERR_92_SUBMSG_4        NO_SUBMSG
#define M_ERR_92_SUBMSG_5        NO_SUBMSG
#define M_ERR_92_SUBMSG_6        NO_SUBMSG
#define M_ERR_92_SUBMSG_7        NO_SUBMSG
#define M_ERR_92_SUBMSG_8        NO_SUBMSG
#define M_ERR_92_SUBMSG_9        NO_SUBMSG

#define M_XX93XX_ERROR           93L
#define M_ERR_93_MSG             NO_MSG
#define M_ERR_93_SUBMSG_1        NO_SUBMSG
#define M_ERR_93_SUBMSG_2        NO_SUBMSG
#define M_ERR_93_SUBMSG_3        NO_SUBMSG
#define M_ERR_93_SUBMSG_4        NO_SUBMSG
#define M_ERR_93_SUBMSG_5        NO_SUBMSG
#define M_ERR_93_SUBMSG_6        NO_SUBMSG
#define M_ERR_93_SUBMSG_7        NO_SUBMSG
#define M_ERR_93_SUBMSG_8        NO_SUBMSG
#define M_ERR_93_SUBMSG_9        NO_SUBMSG

#define M_XX94XX_ERROR           94L
#define M_ERR_94_MSG             NO_MSG
#define M_ERR_94_SUBMSG_1        NO_SUBMSG
#define M_ERR_94_SUBMSG_2        NO_SUBMSG
#define M_ERR_94_SUBMSG_3        NO_SUBMSG
#define M_ERR_94_SUBMSG_4        NO_SUBMSG
#define M_ERR_94_SUBMSG_5        NO_SUBMSG
#define M_ERR_94_SUBMSG_6        NO_SUBMSG
#define M_ERR_94_SUBMSG_7        NO_SUBMSG
#define M_ERR_94_SUBMSG_8        NO_SUBMSG
#define M_ERR_94_SUBMSG_9        NO_SUBMSG

#define M_XX95XX_ERROR           95L
#define M_ERR_95_MSG             NO_MSG
#define M_ERR_95_SUBMSG_1        NO_SUBMSG
#define M_ERR_95_SUBMSG_2        NO_SUBMSG
#define M_ERR_95_SUBMSG_3        NO_SUBMSG
#define M_ERR_95_SUBMSG_4        NO_SUBMSG
#define M_ERR_95_SUBMSG_5        NO_SUBMSG
#define M_ERR_95_SUBMSG_6        NO_SUBMSG
#define M_ERR_95_SUBMSG_7        NO_SUBMSG
#define M_ERR_95_SUBMSG_8        NO_SUBMSG
#define M_ERR_95_SUBMSG_9        NO_SUBMSG

#define M_XX96XX_ERROR           96L
#define M_ERR_96_MSG             NO_MSG
#define M_ERR_96_SUBMSG_1        NO_SUBMSG
#define M_ERR_96_SUBMSG_2        NO_SUBMSG
#define M_ERR_96_SUBMSG_3        NO_SUBMSG
#define M_ERR_96_SUBMSG_4        NO_SUBMSG
#define M_ERR_96_SUBMSG_5        NO_SUBMSG
#define M_ERR_96_SUBMSG_6        NO_SUBMSG
#define M_ERR_96_SUBMSG_7        NO_SUBMSG
#define M_ERR_96_SUBMSG_8        NO_SUBMSG
#define M_ERR_96_SUBMSG_9        NO_SUBMSG

#define M_XX97XX_ERROR           97L
#define M_ERR_97_MSG             NO_MSG
#define M_ERR_97_SUBMSG_1        NO_SUBMSG
#define M_ERR_97_SUBMSG_2        NO_SUBMSG
#define M_ERR_97_SUBMSG_3        NO_SUBMSG
#define M_ERR_97_SUBMSG_4        NO_SUBMSG
#define M_ERR_97_SUBMSG_5        NO_SUBMSG
#define M_ERR_97_SUBMSG_6        NO_SUBMSG
#define M_ERR_97_SUBMSG_7        NO_SUBMSG
#define M_ERR_97_SUBMSG_8        NO_SUBMSG
#define M_ERR_97_SUBMSG_9        NO_SUBMSG

#define M_XX98XX_ERROR           98L
#define M_ERR_98_MSG             NO_MSG
#define M_ERR_98_SUBMSG_1        NO_SUBMSG
#define M_ERR_98_SUBMSG_2        NO_SUBMSG
#define M_ERR_98_SUBMSG_3        NO_SUBMSG
#define M_ERR_98_SUBMSG_4        NO_SUBMSG
#define M_ERR_98_SUBMSG_5        NO_SUBMSG
#define M_ERR_98_SUBMSG_6        NO_SUBMSG
#define M_ERR_98_SUBMSG_7        NO_SUBMSG
#define M_ERR_98_SUBMSG_8        NO_SUBMSG
#define M_ERR_98_SUBMSG_9        NO_SUBMSG

#define M_XX99XX_ERROR           99L
#define M_ERR_99_MSG             NO_MSG
#define M_ERR_99_SUBMSG_1        NO_SUBMSG
#define M_ERR_99_SUBMSG_2        NO_SUBMSG
#define M_ERR_99_SUBMSG_3        NO_SUBMSG
#define M_ERR_99_SUBMSG_4        NO_SUBMSG
#define M_ERR_99_SUBMSG_5        NO_SUBMSG
#define M_ERR_99_SUBMSG_6        NO_SUBMSG
#define M_ERR_99_SUBMSG_7        NO_SUBMSG
#define M_ERR_99_SUBMSG_8        NO_SUBMSG
#define M_ERR_99_SUBMSG_9        NO_SUBMSG


/* LIST FUNCTION NAMES AND MESSAGES */


/* MIM */

#define M_NO_FUNCTION               0L
#define M_FCT_0_NAME                MIL_TEXT("")

#define M_MIMSTARTOPCODE            1L
#define M_MIMALLOCRESULT            1L
#define M_FCT_1_NAME                MIL_TEXT("MimAllocResult")
#define M_MIMARITH                  2L
#define M_FCT_2_NAME                MIL_TEXT("MimArith")
#define M_MIMEDGEDETECT             3L
#define M_FCT_3_NAME                MIL_TEXT("MimEdgeDetect")
#define M_MIMBINARIZE               4L
#define M_FCT_4_NAME                MIL_TEXT("MimBinarize")
#define M_MIMCLIP                   5L
#define M_FCT_5_NAME                MIL_TEXT("MimClip")
#define M_MIMCLOSE                  6L
#define M_FCT_6_NAME                MIL_TEXT("MimClose")
#define M_MIMCONNECTMAP             7L
#define M_FCT_7_NAME                MIL_TEXT("MimConnectMap")
#define M_MIMCONVOLVE               8L
#define M_FCT_8_NAME                MIL_TEXT("MimConvolve")
#define M_MIMCOUNTDIFFERENCE        9L
#define M_FCT_9_NAME                MIL_TEXT("MimCountDifference")
#define M_MIMDILATE                10L
#define M_FCT_10_NAME              MIL_TEXT("MimDilate")
#define M_MIMERODE                 11L
#define M_FCT_11_NAME              MIL_TEXT("MimErode")
#define M_MIMFINDEXTREME           12L
#define M_FCT_12_NAME              MIL_TEXT("MimFindExtreme")
#define M_MIMFREE                  13L
#define M_FCT_13_NAME              MIL_TEXT("MimFree")
#define M_MIMGETRESULT1D           14L
#define M_FCT_14_NAME              MIL_TEXT("MimGetResult1d")
#define M_MIMHISTOGRAM             15L
#define M_FCT_15_NAME              MIL_TEXT("MimHistogram")
#define M_MIMHISTOGRAMEQUALIZE     16L
#define M_FCT_16_NAME              MIL_TEXT("MimHistogramEqualize")
#define M_MIMLABEL                 17L
#define M_FCT_17_NAME              MIL_TEXT("MimLabel")
#define M_MIMLOCATEEVENT           18L
#define M_FCT_18_NAME              MIL_TEXT("MimLocateEvent")
#define M_MIMLUTMAP                19L
#define M_FCT_19_NAME              MIL_TEXT("MimLutMap")
#define M_MIMMORPHIC               20L
#define M_FCT_20_NAME              MIL_TEXT("MimMorphic")
#define M_MIMOPEN                  21L
#define M_FCT_21_NAME              MIL_TEXT("MimOpen")
#define M_MIMPROJECT               22L
#define M_FCT_22_NAME              MIL_TEXT("MimProject")
#define M_MIMRANK                  23L
#define M_FCT_23_NAME              MIL_TEXT("MimRank")
#define M_MIMRESIZE                24L
#define M_FCT_24_NAME              MIL_TEXT("MimResize")
#define M_MIMROTATE                25L
#define M_FCT_25_NAME              MIL_TEXT("MimRotate")
#define M_MIMSHIFT                 26L
#define M_FCT_26_NAME              MIL_TEXT("MimShift")
#define M_MIMTHIN                  27L
#define M_FCT_27_NAME              MIL_TEXT("MimThin")
#define M_MIMTRANSLATE             28L
#define M_FCT_28_NAME              MIL_TEXT("MimTranslate")
#define M_MIMGETRESULT             29L
#define M_FCT_29_NAME              MIL_TEXT("MimGetResult")
#define M_MIMINQUIRE               30L
#define M_FCT_30_NAME              MIL_TEXT("MimInquire")
#define M_MIMCONVERT               31L
#define M_FCT_31_NAME              MIL_TEXT("MimConvert")
#define M_MIMTHICK                 32L
#define M_FCT_32_NAME              MIL_TEXT("MimThick")
#define M_MIMDISTANCE              33L
#define M_FCT_33_NAME              MIL_TEXT("MimDistance")
#define M_MIMARITHMULTIPLE         34L
#define M_FCT_34_NAME              MIL_TEXT("MimArithMultiple")
#define M_MIMFLIP                  35L
#define M_FCT_35_NAME              MIL_TEXT("MimFlip")
#define M_MIMWARP                  36L
#define M_FCT_36_NAME              MIL_TEXT("MimWarp")
#define M_MIMFFT                   37L
#define M_FCT_37_NAME              MIL_TEXT("MimFFT")
#define M_MIMWATERSHED             38L
#define M_FCT_38_NAME              MIL_TEXT("MimWatershed")
#define M_MIMZONEOFINFLUENCE       39L
#define M_FCT_39_NAME              MIL_TEXT("MimZoneOfInfluence")
#define M_MIMTRANSFORM             40L
#define M_FCT_40_NAME              MIL_TEXT("MimTransform")
#define M_MIMPOLAR                 41L
#define M_FCT_41_NAME              MIL_TEXT("MimPolarTransform")
#define M_MIMBAYER                 42L
#define M_FCT_42_NAME              MIL_TEXT("MimBayer")
#define M_FCT_43                   43L
#define M_FCT_43_NAME              NO_FCTNAME
#define M_FCT_44                   44L
#define M_FCT_44_NAME              NO_FCTNAME
#define M_FCT_45                   45L
#define M_FCT_45_NAME              NO_FCTNAME
#define M_FCT_46                   46L
#define M_FCT_46_NAME              NO_FCTNAME
#define M_FCT_47                   47L
#define M_FCT_47_NAME              NO_FCTNAME
#define M_FCT_48                   48L
#define M_FCT_48_NAME              NO_FCTNAME
#define M_FCT_49                   49L
#define M_FCT_49_NAME              NO_FCTNAME
#define M_FCT_50                   50L
#define M_FCT_50_NAME              NO_FCTNAME
#define M_FCT_51                   51L
#define M_FCT_51_NAME              NO_FCTNAME
#define M_FCT_52                   52L
#define M_FCT_52_NAME              NO_FCTNAME
#define M_FCT_53                   53L
#define M_FCT_53_NAME              NO_FCTNAME
#define M_FCT_54                   54L
#define M_FCT_54_NAME              NO_FCTNAME
#define M_FCT_55                   55L
#define M_FCT_55_NAME              NO_FCTNAME
#define M_FCT_56                   56L
#define M_FCT_56_NAME              NO_FCTNAME
#define M_FCT_57                   57L
#define M_FCT_57_NAME              NO_FCTNAME
#define M_FCT_58                   58L
#define M_FCT_58_NAME              NO_FCTNAME
#define M_FCT_59                   59L
#define M_FCT_59_NAME              NO_FCTNAME
#define M_FCT_60                   60L
#define M_FCT_60_NAME              NO_FCTNAME
#define M_MIMENDOPCODE             60L

/* MGRA */
#define M_MGRASTARTOPCODE          61L
#define M_MGRAARC                  61L
#define M_FCT_61_NAME              MIL_TEXT("MgraArc")
#define M_MGRAARCFILL              62L
#define M_FCT_62_NAME              MIL_TEXT("MgraArcFill")
#define M_MGRABACKCOLOR            63L
#define M_FCT_63_NAME              MIL_TEXT("MgraBackColor")
#define M_MGRAFILL                 64L
#define M_FCT_64_NAME              MIL_TEXT("MgraFill")
#define M_MGRACLEAR                65L
#define M_FCT_65_NAME              MIL_TEXT("MgraClear")
#define M_MGRACOLOR                66L
#define M_FCT_66_NAME              MIL_TEXT("MgraColor")
#define M_MGRADOT                  67L
#define M_FCT_67_NAME              MIL_TEXT("MgraDot")
#define M_MGRAFONT                 68L
#define M_FCT_68_NAME              MIL_TEXT("MgraFont")
#define M_MGRAFONTSCALE            69L
#define M_FCT_69_NAME              MIL_TEXT("MgraFontScale")
#define M_MGRAINQUIRE              70L
#define M_FCT_70_NAME              MIL_TEXT("MgraInquire")
#define M_MGRALINE                 71L
#define M_FCT_71_NAME              MIL_TEXT("MgraLine")
#define M_MGRARECT                 72L
#define M_FCT_72_NAME              MIL_TEXT("MgraRect")
#define M_MGRARECTFILL             73L
#define M_FCT_73_NAME              MIL_TEXT("MgraRectFill")
#define M_MGRATEXT                 74L
#define M_FCT_74_NAME              MIL_TEXT("MgraText")
#define M_MGRAALLOC                75L
#define M_FCT_75_NAME              MIL_TEXT("MgraAlloc")
#define M_MGRAFREE                 76L
#define M_FCT_76_NAME              MIL_TEXT("MgraFree")
#define M_MGRACONTROL              77L
#define M_FCT_77_NAME              MIL_TEXT("MgraControl")
#define M_FCT_78                   78L
#define M_FCT_78_NAME              NO_FCTNAME
#define M_FCT_79                   79L
#define M_FCT_79_NAME              NO_FCTNAME
#define M_FCT_80                   80L
#define M_FCT_80_NAME              NO_FCTNAME
#define M_FCT_81                   81L
#define M_FCT_81_NAME              NO_FCTNAME
#define M_FCT_82                   82L
#define M_FCT_82_NAME              NO_FCTNAME
#define M_FCT_83                   83L
#define M_FCT_83_NAME              NO_FCTNAME
#define M_FCT_84                   84L
#define M_FCT_84_NAME              NO_FCTNAME
#define M_FCT_85                   85L
#define M_FCT_85_NAME              NO_FCTNAME
#define M_FCT_86                   86L
#define M_FCT_86_NAME              NO_FCTNAME
#define M_FCT_87                   87L
#define M_FCT_87_NAME              NO_FCTNAME
#define M_FCT_88                   88L
#define M_FCT_88_NAME              NO_FCTNAME
#define M_MGRAENDOPCODE            88L

/* MGEN */

#define M_MGENSTARTOPCODE          89L
#define M_MGENLUTFUNCTION          89L
#define M_FCT_89_NAME              MIL_TEXT("MgenLutFunction")
#define M_MGENLUTRAMP              90L
#define M_FCT_90_NAME              MIL_TEXT("MgenLutRamp")
#define M_MGENWARPPARAMETER        91L
#define M_FCT_91_NAME              MIL_TEXT("MgenWarpParameter")
#define M_FCT_92                   92L
#define M_FCT_92_NAME              NO_FCTNAME
#define M_FCT_93                   93L
#define M_FCT_93_NAME              NO_FCTNAME
#define M_FCT_94                   94L
#define M_FCT_94_NAME              NO_FCTNAME
#define M_FCT_95                   95L
#define M_FCT_95_NAME              NO_FCTNAME
#define M_FCT_96                   96L
#define M_FCT_96_NAME              NO_FCTNAME
#define M_FCT_97                   97L
#define M_FCT_97_NAME              NO_FCTNAME
#define M_FCT_98                   98L
#define M_FCT_98_NAME              NO_FCTNAME
#define M_FCT_99                   99L
#define M_FCT_99_NAME              NO_FCTNAME
#define M_FCT_100                  100L
#define M_FCT_100_NAME             NO_FCTNAME
#define M_FCT_101                  101L
#define M_FCT_101_NAME             NO_FCTNAME
#define M_FCT_102                  102L
#define M_FCT_102_NAME             NO_FCTNAME
#define M_MGENENDOPCODE            102L

/* MBUF */

#define M_MBUFSTARTOPCODE          103L
#define M_MBUFALLOC1D              103L
#define M_FCT_103_NAME             MIL_TEXT("MbufAlloc1d")
#define M_MBUFALLOC2D              104L
#define M_FCT_104_NAME             MIL_TEXT("MbufAlloc2d")
#define M_MBUFATTRIBUTE            105L
#define M_FCT_105_NAME             MIL_TEXT("MbufAttribute")
#define M_MBUFCHILD1D              106L
#define M_FCT_106_NAME             MIL_TEXT("MbufChild1d")
#define M_MBUFCHILD2D              107L
#define M_FCT_107_NAME             MIL_TEXT("MbufChild2d")
#define M_MBUFCONTROLNEIGHBORHOOD  108L
#define M_FCT_108_NAME             MIL_TEXT("MbufControlNeighborhood")
#define M_MBUFCOPY                 109L
#define M_FCT_109_NAME             MIL_TEXT("MbufCopy")
#define M_MBUFDISKINQUIRE          110L
#define M_FCT_110_NAME             MIL_TEXT("MbufDiskInquire")
#define M_MBUFEXPORT               111L
#define M_FCT_111_NAME             MIL_TEXT("MbufExport")
#define M_MBUFFREE                 112L
#define M_FCT_112_NAME             MIL_TEXT("MbufFree")
#define M_MBUFGET1D                113L
#define M_FCT_113_NAME             MIL_TEXT("MbufGet1d")
#define M_MBUFGET2D                114L
#define M_FCT_114_NAME             MIL_TEXT("MbufGet2d")
#define M_MBUFIMPORT               115L
#define M_FCT_115_NAME             MIL_TEXT("MbufImport")
#define M_MBUFINQUIRE              116L
#define M_FCT_116_NAME             MIL_TEXT("MbufInquire")
#define M_MBUFLOAD                 117L
#define M_FCT_117_NAME             MIL_TEXT("MbufLoad")
#define M_MBUFRESTORE              118L
#define M_FCT_118_NAME             MIL_TEXT("MbufRestore")
#define M_MBUFSAVE                 119L
#define M_FCT_119_NAME             MIL_TEXT("MbufSave")
#define M_MBUFPUT1D                120L
#define M_FCT_120_NAME             MIL_TEXT("MbufPut1d")
#define M_MBUFPUT2D                121L
#define M_FCT_121_NAME             MIL_TEXT("MbufPut2d")
#define M_MBUFPUT                  122L
#define M_FCT_122_NAME             MIL_TEXT("MbufPut")
#define M_MBUFCLEAR                123L
#define M_FCT_123_NAME             MIL_TEXT("MbufClear")
#define M_MBUFCOPYCLIP             124L
#define M_FCT_124_NAME             MIL_TEXT("MbufCopyClip")
#define M_MBUFCOPYCOND             125L
#define M_FCT_125_NAME             MIL_TEXT("MbufCopyCond")
#define M_MBUFCOPYMASK             126L
#define M_FCT_126_NAME             MIL_TEXT("MbufCopyMask")
#define M_MBUFGET                  127L
#define M_FCT_127_NAME             MIL_TEXT("MbufGet")
#define M_MBUFCHILDCOLOR           128L
#define M_FCT_128_NAME             MIL_TEXT("MbufChildColor")
#define M_MBUFALLOCCOLOR           129L
#define M_FCT_129_NAME             MIL_TEXT("MbufAllocColor")
#define M_MBUFGETCOLOR             130L
#define M_FCT_130_NAME             MIL_TEXT("MbufGetColor")
#define M_MBUFPUTCOLOR             131L
#define M_FCT_131_NAME             MIL_TEXT("MbufPutColor")
#define M_MBUFCOPYCOLOR            132L
#define M_FCT_132_NAME             MIL_TEXT("MbufCopyColor")
#define M_MBUFCONTROL              133L
#define M_FCT_133_NAME             MIL_TEXT("MbufControl")
#define M_MBUFRESIZE               134L
#define M_FCT_134_NAME             MIL_TEXT("MbufResize")
#define M_MBUFSHIFT                135L
#define M_FCT_135_NAME             MIL_TEXT("MbufShift")
#define M_MBUFGETLINE              136L
#define M_FCT_136_NAME             MIL_TEXT("MbufGetLine")
#define M_MBUFPUTLINE              137L
#define M_FCT_137_NAME             MIL_TEXT("MbufPutLine")
#define M_MBUFCLIP                 138L
#define M_FCT_138_NAME             MIL_TEXT("MbufClip")
#define M_MBUFLUTMAP               139L
#define M_FCT_139_NAME             MIL_TEXT("MbufLutMap")
#define M_MBUFMODIFIED2D           140L
#define M_FCT_140_NAME             MIL_TEXT("MbufModified2d")
#define M_MBUFCREATECOLOR          141L
#define M_FCT_141_NAME             MIL_TEXT("MbufCreateColor")
#define M_MBUFCHILDCOLOR2D         142L
#define M_FCT_142_NAME             MIL_TEXT("MbufChildColor2d")
#define M_MBUFPUTCOLOR2D           143L
#define M_FCT_143_NAME             MIL_TEXT("MbufPutColor2d")
#define M_MBUFGETCOLOR2D           144L
#define M_FCT_144_NAME             MIL_TEXT("MbufGetColor2d")
#define M_MBUFCOPYCOLOR2D          145L
#define M_FCT_145_NAME             MIL_TEXT("MbufCopyColor2d")
#define M_MBUFCREATE2D             146L
#define M_FCT_146_NAME             MIL_TEXT("MbufCreate2d")
#define M_MBUFCOMPRESSION          147L
#define M_FCT_147_NAME             MIL_TEXT("MbufCompression")
#define M_MBUFBINARIZE             148L
#define M_FCT_148_NAME             MIL_TEXT("MbufBinarize")
#define M_MBUFEXPORTSEQ            149L
#define M_FCT_149_NAME             MIL_TEXT("MbufExportSequence")
#define M_MBUFIMPORTSEQ            150L
#define M_FCT_150_NAME             MIL_TEXT("MbufImportSequence")
#define M_FCT_151                  151L
#define M_FCT_151_NAME             NO_FCTNAME
#define M_MBUFENDOPCODE            151L

/* MDIG */

#define M_MDIGSTARTOPCODE         152L
#define M_MDIGALLOC               152L
#define M_FCT_152_NAME            MIL_TEXT("MdigAlloc")
#define M_MDIGCHANNEL             153L
#define M_FCT_153_NAME            MIL_TEXT("MdigChannel")
#define M_MDIGFREE                154L
#define M_FCT_154_NAME            MIL_TEXT("MdigFree")
#define M_MDIGGRAB                155L
#define M_FCT_155_NAME            MIL_TEXT("MdigGrab")
#define M_MDIGINQUIRE             156L
#define M_FCT_156_NAME            MIL_TEXT("MdigInquire")
#define M_MDIGLUT                 157L
#define M_FCT_157_NAME            MIL_TEXT("MdigLut")
#define M_MDIGREFERENCE           158L
#define M_FCT_158_NAME            MIL_TEXT("MdigReference")
#define M_MDIGGRABCONTINUOUS      159L
#define M_FCT_159_NAME            MIL_TEXT("MdigGrabContinuous")
#define M_MDIGHALT                160L
#define M_FCT_160_NAME            MIL_TEXT("MdigHalt")
#define M_MDIGCONTROL             161L
#define M_FCT_161_NAME            MIL_TEXT("MdigControl")
#define M_MDIGGRABWAIT            162L
#define M_FCT_162_NAME            MIL_TEXT("MdigGrabWait")
#define M_MDIGAVERAGE             163L
#define M_FCT_163_NAME            MIL_TEXT("MdigAverage")
#define M_MDIGHOOKFUNCTION        164L
#define M_FCT_164_NAME            MIL_TEXT("MdigHookFunction")
#define M_MDISPHOOKFUNCTION       165L
#define M_FCT_165_NAME            MIL_TEXT("MdispHookFunction")
#define M_MDIGFOCUS               166L
#define M_FCT_166_NAME            MIL_TEXT("MdigFocus")
#define M_FCT_167                 167L
#define M_FCT_167_NAME            NO_FCTNAME
#define M_FCT_168                 168L
#define M_FCT_168_NAME            NO_FCTNAME
#define M_FCT_169                 169L
#define M_FCT_169_NAME            NO_FCTNAME
#define M_FCT_170                 170L
#define M_FCT_170_NAME            NO_FCTNAME
#define M_FCT_171                 171L
#define M_FCT_171_NAME            NO_FCTNAME
#define M_FCT_172                 172L
#define M_FCT_172_NAME            NO_FCTNAME
#define M_FCT_173                 173L
#define M_FCT_173_NAME            NO_FCTNAME
#define M_FCT_174                 174L
#define M_FCT_174_NAME            NO_FCTNAME
#define M_FCT_175                 175L
#define M_FCT_175_NAME            NO_FCTNAME
#define M_FCT_176                 176L
#define M_FCT_176_NAME            NO_FCTNAME
#define M_FCT_177                 177L
#define M_FCT_177_NAME            NO_FCTNAME
#define M_MDIGENDOPCODE           177L

/* MDISP */

#define M_MDISPSTARTOPCODE        178L
#define M_MDISPDESELECT           178L
#define M_FCT_178_NAME            MIL_TEXT("MdispDeselect")
#define M_MDISPINQUIRE            179L
#define M_FCT_179_NAME            MIL_TEXT("MdispInquire")
#define M_MDISPLUT                180L
#define M_FCT_180_NAME            MIL_TEXT("MdispLut")
#define M_MDISPPAN                181L
#define M_FCT_181_NAME            MIL_TEXT("MdispPan")
#define M_MDISPSELECT             182L
#define M_FCT_182_NAME            MIL_TEXT("MdispSelect")
#define M_MDISPZOOM               183L
#define M_FCT_183_NAME            MIL_TEXT("MdispZoom")
#define M_MDISPALLOC              184L
#define M_FCT_184_NAME            MIL_TEXT("MdispAlloc")
#define M_MDISPFREE               185L
#define M_FCT_185_NAME            MIL_TEXT("MdispFree")
#define M_MDISPOVERLAYKEY         186L
#define M_FCT_186_NAME            MIL_TEXT("MdispOverlayKey")
#define M_MDISPSELECTWINDOW       187L
#define M_FCT_187_NAME            MIL_TEXT("MdispSelectWindow")
#define M_MDISPCONTROL            188L
#define M_FCT_188_NAME            MIL_TEXT("MdispControl")
#define M_FCT_189                 189L
#define M_FCT_189_NAME            NO_FCTNAME
#define M_FCT_190                 190L
#define M_FCT_190_NAME            NO_FCTNAME
#define M_FCT_191                 191L
#define M_FCT_191_NAME            NO_FCTNAME
#define M_FCT_192                 192L
#define M_FCT_192_NAME            NO_FCTNAME
#define M_FCT_193                 193L
#define M_FCT_193_NAME            NO_FCTNAME
#define M_FCT_194                 194L
#define M_FCT_194_NAME            NO_FCTNAME
#define M_FCT_195                 195L
#define M_FCT_195_NAME            NO_FCTNAME
#define M_FCT_196                 196L
#define M_FCT_196_NAME            NO_FCTNAME
#define M_FCT_197                 197L
#define M_FCT_197_NAME            NO_FCTNAME
#define M_FCT_198                 198L
#define M_FCT_198_NAME            NO_FCTNAME
#define M_MDISPENDOPCODE          198L

/* MSYS */

#define M_MSYSSTARTOPCODE         199L
#define M_MSYSALLOC               199L
#define M_FCT_199_NAME            MIL_TEXT("MsysAlloc")
#define M_MSYSFREE                200L
#define M_FCT_200_NAME            MIL_TEXT("MsysFree")
#define M_MSYSINQUIRE             201L
#define M_FCT_201_NAME            MIL_TEXT("MsysInquire")
#define M_MSYSCONTROL             202L
#define M_FCT_202_NAME            MIL_TEXT("MsysControl")
#define M_MSYSCONFIGACCESS        203L
#define M_FCT_203_NAME            MIL_TEXT("MsysConfigAccess")
#define M_MSYSHOOKFCT             204L
#define M_FCT_204_NAME            MIL_TEXT("MsysHookFunction")
#define M_FCT_205                 205L
#define M_FCT_205_NAME            NO_FCTNAME
#define M_FCT_206                 206L
#define M_FCT_206_NAME            NO_FCTNAME
#define M_FCT_207                 207L
#define M_FCT_207_NAME            NO_FCTNAME
#define M_FCT_208                 208L
#define M_FCT_208_NAME            NO_FCTNAME
#define M_FCT_209                 209L
#define M_FCT_209_NAME            NO_FCTNAME
#define M_FCT_210                 210L
#define M_FCT_210_NAME            NO_FCTNAME
#define M_FCT_211                 211L
#define M_FCT_211_NAME            NO_FCTNAME
#define M_FCT_212                 212L
#define M_FCT_212_NAME            NO_FCTNAME
#define M_FCT_213                 213L
#define M_FCT_213_NAME            NO_FCTNAME
#define M_FCT_214                 214L
#define M_FCT_214_NAME            NO_FCTNAME
#define M_FCT_215                 215L
#define M_FCT_215_NAME            NO_FCTNAME
#define M_FCT_216                 216L
#define M_FCT_216_NAME            NO_FCTNAME
#define M_MSYSENDOPCODE           216L

/* MAPP */

#define M_MAPPSTARTOPCODE         217L
#define M_MAPPALLOC               217L
#define M_FCT_217_NAME            MIL_TEXT("MappAlloc")
#define M_MAPPCONTROL             218L
#define M_FCT_218_NAME            MIL_TEXT("MappControl")
#define M_MAPPFREE                219L
#define M_FCT_219_NAME            MIL_TEXT("MappFree")
#define M_MAPPGETERROR            220L
#define M_FCT_220_NAME            MIL_TEXT("MappGetError")
#define M_MAPPHOOKFUNCTION        221L
#define M_FCT_221_NAME            MIL_TEXT("MappHookFunction")
#define M_MAPPGETHOOKINFO         222L
#define M_FCT_222_NAME            MIL_TEXT("MappGetHookInfo")
#define M_MAPPINQUIRE             223L
#define M_FCT_223_NAME            MIL_TEXT("MappInquire")
#define M_MAPPMODIFY              224L
#define M_FCT_224_NAME            MIL_TEXT("MappModify")
#define M_MAPPGETDEVICETYPE       225L
#define M_FCT_225_NAME            MIL_TEXT("MappGetDeviceType")
#define M_MAPPTIMER               226L
#define M_FCT_226_NAME            MIL_TEXT("MappTimer")
#define M_MAPPCHILD               227L
#define M_FCT_227_NAME            MIL_TEXT("MappChild")
#define M_MAPPCONTROLTHREAD       228L
#define M_FCT_228_NAME            MIL_TEXT("MappControlThread")
#define M_FCT_229                 229L
#define M_FCT_229_NAME            NO_FCTNAME
#define M_FCT_230                 230L
#define M_FCT_230_NAME            NO_FCTNAME
#define M_FCT_231                 231L
#define M_FCT_231_NAME            NO_FCTNAME
#define M_FCT_232                 232L
#define M_FCT_232_NAME            NO_FCTNAME
#define M_FCT_233                 233L
#define M_FCT_233_NAME            NO_FCTNAME
#define M_FCT_234                 234L
#define M_FCT_234_NAME            NO_FCTNAME
#define M_MFUNC                   235L
#define M_FCT_235_NAME            NO_FCTNAME
#define M_MAPPENDOPCODE           235L

#endif
