/* FILE NAME: RND.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Prototipes
 */
#include "../def.h"

typedef struct tagvg6VERTEX
{
  VEC P;  /* Vertex position */
} vg6VERTEX;

typedef struct tagvg6PRIM
{
  vg6VERTEX *V; /* Vertex attributes array */
  INT NumOfV;   /* Number of vertices */
  INT *I;       /* Index array (for trimesh – by 3 ones) */
  INT NumOfI;   /* Number of indices */
  MATR Trans;   /* Additional transformation matrix */
} vg6PRIM;

extern HWND VG6_hWndRnd;
extern HDC VG6_hDCRndFrame;
extern HBITMAP VG6_hBmRndFrame;
extern INT VG6_RndFrameW, VG6_RndFrameH;
extern DBL
  VG6_RndProjSize,  /* Project plane fit square */
  VG6_RndProjDist,  /* Distance to project plane from viewer (near) */
  VG6_RndProjFarClip;  /* Distance to project far clip plane (far) */
extern MATR
  VG6_RndMatrView, /* View coordinate system matrix */
  VG6_RndMatrProj, /* Projection coordinate system matrix */
  VG6_RndMatrVP;   /* Stored (View * Proj) matrix */

VOID VG6_RndInit( HWND hWnd );
VOID VG6_RndClose( VOID );
VOID VG6_RndResize( INT w, INT h );
VOID VG6_RndStart( VOID );
VOID VG6_RndEnd( VOID );
VOID VG6_RndCopyFrame( HDC hDC );
VOID VG6_RndProjSet( VOID );
VOID VG6_RndCamSet( VEC Loc, VEC At, VEC Up1 );
BOOL VG6_RndPrimCreate( vg6PRIM *Pr, INT NoofV, INT NoofI );
VOID VG6_RndPrimFree( vg6PRIM *Pr );
VOID VG6_RndPrimDraw( vg6PRIM *Pr, MATR World );
BOOL VG6_RndPrimLoad( vg6PRIM *Pr, CHAR *FileName );
