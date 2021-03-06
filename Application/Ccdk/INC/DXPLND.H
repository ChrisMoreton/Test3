//================== SysCAD - Copyright Kenwalt (Pty) Ltd ===================
// $Nokeywords: $
//===========================================================================
/****************************** DXPLND.H ***********************************/
#ifndef     DXPLND 
#define     DXPLND 
typedef     struct  dx_polyline_struct {
            DXF_ENTITY_HEADER_S    polyline_entity_header ;
            INT     pline_vflag ;
            REAL    pline_origin[3] ;
            INT     pline_flags ;
            REAL    pline_w0 ;
            REAL    pline_w1 ;
            INT     pline_m_cnt ;
            INT     pline_n_cnt ;
            INT     pline_m_dens ;
            INT     pline_n_dens ;
            INT     pline_type ;
            DXF_ENAME   pline_seqend ;
            DML_LIST    pline_vlist ;
            } DX_POLYLINE_S ;
typedef     DX_POLYLINE_S *DX_POLYLINE ;
#endif
