/* FILE NAME: RND.H
 * PROGRAMMER: VG6
 * DATE: 08.06.2018
 * PURPOSE: Prototipes
 */
#ifndef __RND_H_
#define __RND_H_

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#pragma comment(lib, "glew32s")
#include "../def.h"
#define GLEW_STATIC
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>


extern HWND VG6_hWndRn;
extern HDC VG6_hDCRndFrame;
extern HBITMAP VG6_hBmRndFrame;
extern INT VG6_RndFrameW, VG6_RndFrameH;
extern FLT VG6_RndProjSize;
extern FLT VG6_RndProjDist;
extern FLT VG6_RndProjFarClip;
extern MATR VG6_RndMatrView;
extern MATR VG6_RndMatrProj;
extern MATR VG6_RndMatrVP;

/* Space vertex representation type */
typedef struct tagvg6VERTEX
{
  VEC P;  /* Vertex position */
  VEC2 T; /* Vertex texture coordinates */
  VEC N;  /* Vertex normal */
  VEC4 C; /* Vertex color */
} vg6VERTEX;

/* Primitive type */
typedef enum tagvg6PRIM_TYPE
{
  VG6_RND_PRIM_TRIMESH, VG6_RND_PRIM_FRID
} vg6PRIM_TYPE;

/* Primitive representation type */
typedef struct tagvg6PRIM
{
  vg6PRIM_TYPE Type; /* Primitive type */
  INT
    VA,          /* Vertex array Id */
    VBuf,        /* Vertex buffer Id */
    IBuf;        /* Index buffer Id (if 0 - use only vertex buffer) */
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
BOOL VG6_RndPrimCreate( vg6PRIM *Pr, vg6PRIM_TYPE Type, vg6VERTEX *V, INT NoofV, INT *I, INT NoofI );
VOID VG6_RndPrimFree( vg6PRIM *Pr );
VOID VG6_RndPrimDraw( vg6PRIM *Pr, MATR World );
BOOL VG6_RndPrimLoad( vg6PRIM *Pr, CHAR *FileName );
#endif