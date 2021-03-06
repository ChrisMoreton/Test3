//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================
/* -3 */
/******************************* DX3G.C *********************************/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!                                                      !!!!!!!!*/
/*!!!!!!!!(C) Copyright 1989, 1990, 1991 Building Block Software!!!!!!!!*/
/*!!!!!!!!                   All rights reserved                !!!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
#include <c3vdefs.h>
#include <dx3defs.h>
#include <dx3priv.h>
#include <c3vmcrs.h>

/*-------------------------------------------------------------------------*/
BBS_PRIVATE void dx3_arb_axis ( z, x, y ) 
/*-------------------------------------------------------------------------*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*!!!!!!!!(C) Copyright 1989, 1990, 1991 Building Block Software!!!!!!!!*/
/*!!!!!!!!                    All rights reserved                   !!!!!!!*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
PT3 z, x, y ;
{ 
    if ( IS_ZERO(C3V_NORML1(z)) ) /* If z undefined, its WCS */
        z[2] = 1.0 ;
    if ( fabs(z[0]) < 0.015625 && fabs(z[1]) < 0.015625 ) {
        x[0] = z[2] ;
        x[1] = 0.0 ;
        x[2] = -z[0] ;
    }
    else {
        x[0] = -z[1] ;
        x[1] = z[0] ;
        x[2] = 0.0 ;
    }
    c3v_normalize ( x, x ) ;
    C3V_CROSS ( z, x, y ) ;
}

