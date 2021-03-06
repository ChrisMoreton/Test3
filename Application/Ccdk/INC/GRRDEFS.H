//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================
/******************************* GRRDEFS.H *********************************/
/************************ Graphics prototypes ******************************/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!(C) Copyright 1989, 1990, 1991 Building Block Software!!!!!!!!*/
/*!!!!!!!!                    All rights reserved                  !!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#ifndef GRRDEFS
#define GRRDEFS

#include <grdefs.h>

EXTERN  REAL    GR_SELECT_WIDTH ;
extern  void    grr_set_textposition __(( REAL DUMMY0 [2] )) ;
extern  void    grr_init_textposition __(( void )) ;
extern  INT*    grr_point_to_pixel __(( REAL DUMMY0 [2], INT DUMMY1 [2] )) ;
extern  REAL*   grr_pixel_to_point __(( INT DUMMY0 [2], REAL DUMMY1 [2] )) ;
extern  REAL*   grr_pixel_to_point_real __(( REAL DUMMY0 [2], REAL DUMMY1 [2] )) ;
extern  void    grr_moveto __(( REAL DUMMY0 [2] )) ;
extern  void    grr_lineto __(( REAL DUMMY0 [2] )) ;
extern  void    grr_line __(( REAL DUMMY0 [2], REAL DUMMY1 [2] )) ;
extern  void    grr_box __(( REAL DUMMY0 [2], REAL DUMMY1 [2] )) ;
extern  void    grr_fill_box __(( REAL DUMMY0 [2], REAL DUMMY1 [2] )) ;
extern  void    grr_point __(( REAL DUMMY0 [2], REAL DUMMY1 )) ;
extern  void    grr_arrow __(( REAL DUMMY0 [2], REAL DUMMY1 [2], REAL DUMMY2 ,
            REAL DUMMY3 , REAL DUMMY4 )) ;
extern  void    grr_clip __(( REAL DUMMY0 [2], REAL DUMMY1 [2] )) ;
extern  void    grr_clip_inside __(( REAL DUMMY0 [2], REAL DUMMY1 [2] )) ;
extern  REAL    grr_get_max_x __(( void )) ;
extern  REAL    grr_get_max_y __(( void )) ;
extern  BOOLEAN grr_init __(( int DUMMY0 , GR_COLOR DUMMY1, int DUMMY2)) ; /*cnm*/
extern  void    grr_set_context (HDC hdc, GR_COLOR colour);  /*cnm*/
extern  void    grr_get_context (HDC *hdc, GR_COLOR * color);  /*cnm*/
extern  void    grr_printing (BOOLEAN printing);  /*kga 22/1/99*/
extern  void    grr_exit __(( void )) ;
extern  REAL    grr_get_screen_ratio __(( void )) ;
extern  void    grr_set_screen_ratio __(( REAL DUMMY0 )) ;
extern  void    grr_set_color __(( GR_COLOR DUMMY0 )) ;
extern  GR_COLOR grr_get_color __(( void )) ;
extern  void    grr_set_thickness __(( REAL DUMMY0 )) ;
extern  REAL    grr_get_thickness __(( void )) ;
extern  void    grr_set_patt __(( GR_PATT DUMMY0 )) ;
extern  void    grr_set_solid_patt __(( void )) ;
extern  GR_PATT    grr_get_patt __(( void )) ;
extern  void    grr_clear_screen __(( GR_COLOR DUMMY0 )) ;
extern  void    grr_putimage __(( REAL DUMMY0 , REAL DUMMY1 , ANY DUMMY2 )) ;
extern  ANY     grr_getimage __(( REAL DUMMY0 , REAL DUMMY1 , REAL DUMMY2 ,
            REAL DUMMY3 )) ;
extern  REAL    grr_get_select_width __(( void )) ;
extern  void    grr_set_select_width __(( REAL DUMMY0 )) ;

#endif /* GRRDEFS */

