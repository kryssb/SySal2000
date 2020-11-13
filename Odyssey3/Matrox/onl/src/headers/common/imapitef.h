/*******************************************************************
 *
 * COPYRIGHT (c) 2000 Matrox Electronic Systems Ltd.
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
 * ODYSSEY Native Library data structures.
 *
 *******************************************************************/

/* Blob analysis results --- group1 */
typedef struct
{
    IM_UINT16  number_of_blobs;
    IM_UINT16  label_value;
    IM_UINT32  area;
    IM_UINT16  box_x_min;
    IM_UINT16  box_y_min;
    IM_UINT16  box_x_max;
    IM_UINT16  box_y_max;
    IM_UINT16  number_of_holes;
    IM_UINT16  number_of_runs;
    float      perimeter;
    float      length;
    float      breadth;
    float      center_of_gravity_x;
    float      center_of_gravity_y;
} IM_BLOB_GROUP1_ST;

/* Blob analysis results --- group2 */
typedef struct
{
    IM_UINT16  number_of_blobs;
    IM_UINT16  label_value;
    IM_UINT16  x_min_at_y_min;
    IM_UINT16  x_max_at_y_max;
    IM_UINT16  y_min_at_x_max;
    IM_UINT16  y_max_at_x_min;
    IM_UINT16  intercept_0;
    IM_UINT16  intercept_45;
    IM_UINT16  intercept_90;
    IM_UINT16  intercept_135;
} IM_BLOB_GROUP2_ST;

/* Blob analysis results --- group3 */
typedef struct
{
    IM_UINT16  number_of_blobs;
    IM_UINT16  label_value;
    float      moment_x1_y1;
    float      moment_x2_y0;
    float      moment_x0_y2;
    float      moment_central_x1_y1;
    float      moment_central_x2_y0;
    float      moment_central_x0_y2;
} IM_BLOB_GROUP3_ST;

/* Blob analysis results --- group4 */
typedef struct
{
    IM_UINT16  number_of_blobs;
    IM_UINT16  label_value;
    float      feret_min_diameter;
    float      feret_min_angle;
    float      feret_max_diameter;
    float      feret_max_angle;
    float      feret_mean_diameter;
    float      convex_perimeter;
} IM_BLOB_GROUP4_ST;

/* Blob analysis results --- group5 */
typedef struct
{
    IM_UINT16  number_of_blobs;
    IM_UINT16  label_value;
    IM_UINT32  sum_pixel;
    IM_UINT16  min_pixel;
    IM_UINT16  max_pixel;
    float      sum_pixel_squared;
    float      center_of_gravity_x;
    float      center_of_gravity_y;
} IM_BLOB_GROUP5_ST;

/* Blob analysis results --- group6 */
typedef struct
{
    IM_UINT16  number_of_blobs;
    IM_UINT16  label_value;
    float      moment_x1_y1;
    float      moment_x2_y0;
    float      moment_x0_y2;
    float      moment_central_x1_y1;
    float      moment_central_x2_y0;
    float      moment_central_x0_y2;
} IM_BLOB_GROUP6_ST;

/* Pattern matching results */
typedef struct
{
    IM_INT16   number;
    IM_INT16   reserved;
    float      score;
    float      position_x;
    float      position_y;
} IM_PAT_RESULT_ST;

/* Pattern matching inquiries */
typedef struct
{
    IM_INT16   type;
    IM_INT16   offset_x;
    IM_INT16   offset_y;
    IM_INT16   size_x;
    IM_INT16   size_y;
    IM_INT16   preprocessed;
    float      center_x;
    float      center_y;
    float      original_x;
    float      original_y;
    IM_INT16   number;
    IM_INT16   speed;
    IM_INT16   position_start_x;
    IM_INT16   position_start_y;
    IM_INT16   position_size_x;
    IM_INT16   position_size_y;
    IM_INT16   position_accuracy;
    IM_INT16   reserved;
    float      acceptance;
    float      certainty;
    IM_INT32   first_level;
    IM_INT32   last_level;
    IM_INT32   model_step;
    IM_INT32   fast_find;
    IM_INT32   score_type;
} IM_PAT_INQUIRE_ST;

/* BufStatistics results */
typedef struct
{
    double num_pixel;
    double min_pixel;
    double max_pixel;
    double sum_pixel;
    double sum_pixel_squared;
    double mean_pixel;
    double sigma_pixel;
    double min_abs_pixel;
    double max_abs_pixel;
    double sum_abs_pixel;
} IM_BUF_STATS_ST;

/* imSysInquire IM_SYS_PRODUCT_LIST inquiries */
typedef struct
{
   IM_UINT32   NodeId;
   IM_INT32    ProductId;
   IM_UINT32   ExtDevType;
   IM_UINT32   ExtDevRev;
   IM_UINT32   BoardId;
   IM_UINT32   LinkANode;
   IM_UINT32   LinkBNode;
   IM_UINT32   LinkCNode;
   IM_UINT32   LinkDNode;
} IM_SYS_PRODUCT_LIST_ST;

#endif /*__IMAPITEF_H__*/

