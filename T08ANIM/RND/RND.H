/* FILE NAME: RND.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Prototipes
 */
#pragma once
#include "../def.h"
extern HWND VG6_hWndRn;
extern HDC VG6_hDCRndFrame;
extern HBITMAP VG6_hBmRndFrame;
extern INT VG6_RndFrameW, VG6_RndFrameH;
extern DBL VG6_RndProjSize;
extern DBL VG6_RndProjDist;
extern DBL VG6_RndProjFarClip;
extern MATR VG6_RndMatrView;
extern MATR VG6_RndMatrProj;
extern MATR VG6_RndMatrVP;
typedef struct tagvg6VERTEX
{
  VEC P;  /* Vertex position */
} vg6VERTEX;
typedef struct tagvg6PRIM
{
  vg6VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */
  INT *I;       /* Index array (for trimesh � by 3 ones) */
  INT NumOfI;   /* Number of indices */
  MATR Trans;   /* Additional transformation matrix */
} vg6PRIM;

VOID VG6_RndInit( HWND hWnd );
VOID VG6_RndClose( VOID );
VOID VG6_RndResize( INT W, INT H );
VOID VG6_RndStart( VOID );
VOID VG6_RndEnd( VOID );
VOID VG6_RndCopyFrame( HDC hDC );
VOID VG6_RndProjSet( VOID );
VOID VG6_RndCamSet( VEC Loc, VEC At, VEC Up1 );
BOOL VG6_RndPrimCreate( vg6PRIM *Pr, INT NoofV, INT NoofI );
VOID VG6_RndPrimFree( vg6PRIM *Pr );
VOID VG6_RndPrimDraw( vg6PRIM *Pr, MATR World );
BOOL VG6_RndPrimLoad( vg6PRIM *Pr, CHAR *FileName );