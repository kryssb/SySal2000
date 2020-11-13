/*******************************************************************
 *
 * COPYRIGHT (c) 1994-1997 Matrox Electronic Systems Ltd.
 * All Rights Reserved
 *
 *******************************************************************/

#ifndef __IMAPITEF_H__
#define __IMAPITEF_H__

#if !defined(_IM_LOCAL_CODE) && defined(SHOW_INCLUDE_FILE)
#pragma message ("#include "__FILE__)
#endif

/*******************************************************************
 *
 * Genesis Native Library data structures.
 *
 *******************************************************************/

/* Blob analysis results --- group1 */
typedef struct
{
    unsigned short number_of_blobs;
    unsigned short label_value;
    unsigned long area;
    unsigned short box_x_min;
    unsigned short box_y_min;
    unsigned short box_x_max;
    unsigned short box_y_max;
    unsigned short number_of_holes;
    unsigned short number_of_runs;
    float perimeter;
    float length;
    float breadth;
    float center_of_gravity_x;
    float center_of_gravity_y;
} IM_BLOB_GROUP1_ST;

/* Blob analysis results --- group2 */
typedef struct
{
    unsigned short number_of_blobs;
    unsigned short label_value;
    unsigned short x_min_at_y_min;
    unsigned short x_max_at_y_max;
    unsigned short y_min_at_x_max;
    unsigned short y_max_at_x_min;
    unsigned short intercept_0;
    unsigned short intercept_45;
    unsigned short intercept_90;
    unsigned short intercept_135;
} IM_BLOB_GROUP2_ST;

/* Blob analysis results --- group3 */
typedef struct
{
    unsigned short number_of_blobs;
    unsigned short label_value;
    float moment_x1_y1;
    float moment_x2_y0;
    float moment_x0_y2;
    float moment_central_x1_y1;
    float moment_central_x2_y0;
    float moment_central_x0_y2;
} IM_BLOB_GROUP3_ST;

/* Blob analysis results --- group4 */
typedef struct
{
    unsigned short number_of_blobs;
    unsigned short label_value;
    float feret_min_diameter;
    float feret_min_angle;
    float feret_max_diameter;
    float feret_max_angle;
    float feret_mean_diameter;
    float convex_perimeter;
} IM_BLOB_GROUP4_ST;

/* Blob analysis results --- group5 */
typedef struct
{
    unsigned short number_of_blobs;
    unsigned short label_value;
    unsigned long sum_pixel;
    unsigned short min_pixel;
    unsigned short max_pixel;
    float sum_pixel_squared;
    float center_of_gravity_x;
    float center_of_gravity_y;
} IM_BLOB_GROUP5_ST;

/* Blob analysis results --- group6 */
typedef struct
{
    unsigned short number_of_blobs;
    unsigned short label_value;
    float moment_x1_y1;
    float moment_x2_y0;
    float moment_x0_y2;
    float moment_central_x1_y1;
    float moment_central_x2_y0;
    float moment_central_x0_y2;
} IM_BLOB_GROUP6_ST;

/* Pattern matching results */
typedef struct
{
    short number;
    short reserved;
    float score;
    float position_x;
    float position_y;
} IM_PAT_RESULT_ST;

/* Pattern matching inquiries */
typedef struct
{
    short type;
    short offset_x;
    short offset_y;
    short size_x;
    short size_y;
    short preprocessed;
    float center_x;
    float center_y;
    float original_x;
    float original_y;
    short number;
    short speed;
    short position_start_x;
    short position_start_y;
    short position_size_x;
    short position_size_y;
    short position_accuracy;
    short reserved;
    float acceptance;
    float certainty;
    long  first_level;
    long  last_level;
    long  model_step;
    long  fast_find;
    long  score_type;
} IM_PAT_INQUIRE_ST;


/* imSysInquire IM_SYS_PRODUCT_LIST inquiries */
typedef struct
{
   unsigned long System;
   unsigned long Node;
   unsigned long NodeId;
   unsigned long ProductId;
   unsigned long GrabModulePresent;
   unsigned long ExtModuleType;

} IM_SYS_PRODUCT_LIST_ST;

#endif /*__IMAPITEF_H__*/
